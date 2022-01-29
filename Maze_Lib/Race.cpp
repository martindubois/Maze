
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Race.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/IInfo.h>

extern "C"
{
    #include "Maze_Protocol.h"
}

#include <Maze/Race.h>

// ===== Maze_Lib ===========================================================
#include "Interface_ASCII.h"
#include "Interface_Binary.h"
#include "Utilities.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define MODE_DEFAULT Maze::Race::MODE_REQUEST

#define RUNNER_COUNT_DEFAULT (3)

#define RUNNER_COUNT_MAX (3)
#define RUNNER_COUNT_MIN (1)

#define SEED_DEFAULT (0)

#define SLOW_DEFAULT_ms (0)

#define SLOW_MAX_ms (1000)

#define TCP_PORT_DEFAULT (0)

#define ZOOM_DEFAULT (4)

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

static DWORD WINAPI Run(LPVOID aParam);

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Race::Race()
        : mMode(MODE_DEFAULT)
        , mRunnerCount(RUNNER_COUNT_DEFAULT)
        , mSeed(SEED_DEFAULT)
        , mSlow_ms(SLOW_DEFAULT_ms)
        , mTcpPort(TCP_PORT_DEFAULT)
        , mZoom(ZOOM_DEFAULT)
    {
        DWORD lRet = GetEnvironmentVariable("USERPROFILE", mProfile, sizeof(mProfile));
        assert(0 < lRet);
        assert(sizeof(mProfile) > lRet);

        char lMazeName[1024];

        sprintf_s(lMazeName, "%s\\.Maze.bmp", mProfile);

        mMazeName = lMazeName;
    }

    Race::~Race()
    {
        for (InterfaceList::iterator lIt = mInterfaces.begin(); lIt != mInterfaces.end(); lIt++)
        {
            delete* lIt;
        }
    }

    Maze_Result Race::SetGenerator(const char* aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mGenerator = aIn;

        return Maze_OK;
    }

    Maze_Result Race::SetMazeName(const char* aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mMazeName = aIn;

        return Maze_OK;
    }

    Maze_Result Race::SetMode(Mode aIn)
    {
        if (MODE_QTY <= aIn) { return Maze_ERROR_ENUM; }

        mMode = aIn;

        return Maze_OK;
    }

    Maze_Result Race::SetRunnerCount(unsigned int aIn)
    {
        if (RUNNER_COUNT_MAX < aIn) { return Maze_ERROR_MAX; }
        if (RUNNER_COUNT_MIN > aIn) { return Maze_ERROR_MIN; }

        mRunnerCount = aIn;

        return Maze_OK;
    }

    Maze_Result Race::SetSeed(unsigned int aIn) { mSeed = aIn; return Maze_OK; }

    Maze_Result Race::SetSlow(unsigned int aIn_ms)
    {
        if (SLOW_MAX_ms < aIn_ms) { return Maze_ERROR_MAX; }

        mSlow_ms = aIn_ms;

        return Maze_OK;
    }

    Maze_Result Race::SetTcpPort(uint16_t aIn) { mTcpPort = aIn; return Maze_OK; }
    Maze_Result Race::SetZoom(unsigned int aIn) { mZoom = aIn; return Maze_OK; }

    Maze_Result Race::Start(IInfo * aInfo)
    {
        if (NULL == aInfo) { return Maze_ERROR_POINTER; }

        mInfo = aInfo;

        Maze_Result lResult;
        SOCKET      lSocket = INVALID_SOCKET;

        Utl_Socket_Init();

        try
        {
            Maze_Prepare();

            lSocket = Socket_Create();
            assert(INVALID_SOCKET != lSocket);

            DisplayTcpPort(lSocket);

            for (unsigned int i = 0; i < mRunnerCount; i++)
            {
                sockaddr_in lAddr;
                int lSize_byte = sizeof(lAddr);

                SOCKET lConnection = accept(lSocket, reinterpret_cast<sockaddr*>(&lAddr), &lSize_byte);
                if (INVALID_SOCKET == lConnection)
                {
                    throw Maze_ERROR_SOCKET_ACCEPT;
                }

                Connect(lConnection, lAddr.sin_addr.S_un.S_addr);
            }

            Run();

            lResult = Maze_OK;
        }
        catch (Maze_Result eE)
        {
            lResult = eE;
        }

        if (INVALID_SOCKET != lSocket)
        {
            int lRet = closesocket(lSocket);
            assert(0 == lRet);
        }

        Utl_Socket_Uninit();

        return lResult;
    }

    // ===== IConfigurable ==================================================

    Maze_Result Race::Property_Set(const char* aName, const char* aValue)
    {
        if ((NULL == aName) || (NULL == aValue)) { return Maze_ERROR_POINTER; }

        if (0 == _stricmp("Generator", aName)) { return SetGenerator(aValue); }
        if (0 == _stricmp("MazeName" , aName)) { return SetMazeName (aValue); }

        if (0 == _stricmp("Mode"       , aName)) { return SetMode_Str       (aValue); }
        if (0 == _stricmp("RunnerCount", aName)) { return SetRunnerCount_Str(aValue); }
        if (0 == _stricmp("Seed"       , aName)) { return SetSeed_Str       (aValue); }
        if (0 == _stricmp("Slow"       , aName)) { return SetSlow_Str       (aValue); }
        if (0 == _stricmp("TcpPort"    , aName)) { return SetTcpPort_Str    (aValue); }
        if (0 == _stricmp("Zoom"       , aName)) { return SetZoom_Str       (aValue); }

        return Maze_OK_IGNORED;
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    void Race::Connect(SOCKET aSocket, uint32_t aIPv4)
    {
        Maze_Result lResult = Maze_OK;

        char lData[6];

        int lRet = recv(aSocket, lData, sizeof(lData), 0);
        if (sizeof(lData) != lRet)
        {
            throw Maze_ERROR_SOCKET_RECEIVE;
        }

        Interface* lInterface = NULL;

        if (0 == strncmp(Maze_BINARY, lData, sizeof(lData)))
        {
            lInterface = new Interface_Binary();
        }
        else if (0 == strncmp(Maze_ASCII, lData, sizeof(lData)))
        {
            lInterface = new Interface_ASCII();
        }
        else
        {
            throw Maze_ERROR_PROTOCOL;
        }

        try
        {
            lInterface->Init(mInfo, &mBitmap, mSlow_ms, mInterfaces.size(), aIPv4, aSocket);

            lInterface->Connect();

            mInterfaces.push_back(lInterface);
        }
        catch (...)
        {
            delete lInterface;
            throw;
        }
    }

    void Race::DisplayStart()
    {
        assert(NULL != mInfo);

        mInfo->DisplayStart();
    }

    void Race::DisplayTcpPort(SOCKET aSocket)
    {
        assert(INVALID_SOCKET != aSocket);

        assert(NULL != mInfo);

        sockaddr_in lAddr;

        int lSize_byte = sizeof(lAddr);

        int lRet = getsockname(aSocket, reinterpret_cast<sockaddr*>(&lAddr), &lSize_byte);
        assert(0 == lRet);

        mInfo->DisplayTcpPort(ntohs(lAddr.sin_port));
    }

    void Race::Maze_Generate()
    {
        char lGenerator[1024];

        if (NULL == strchr(mGenerator.c_str(), '\\'))
        {
            DWORD lRet = GetModuleFileName(NULL, lGenerator, sizeof(lGenerator));
            assert(0 < lRet);
            assert(sizeof(lGenerator) > lRet);

            char* lPtr = strrchr(lGenerator, '\\');
            assert(NULL != lPtr);

            lPtr++;

            strcpy_s(lPtr, sizeof(lGenerator) - strlen(lGenerator), mGenerator.c_str());
        }
        else
        {
            strcpy_s(lGenerator, mGenerator.c_str());
        }

        char lCmd[2048];

        sprintf_s(lCmd, "%s Output=%s Seed=%u", lGenerator, mMazeName.c_str(), mSeed);

        if (0 != system(lCmd))
        {
            throw Maze_ERROR_GENERATOR;
        }
    }

    void Race::Maze_Prepare()
    {
        if (0 < mGenerator.size())
        {
            Maze_Generate();
        }

        char lTmpName[1024];

        sprintf_s(lTmpName, "%s\\.Maze_Temp.bmp", mProfile);

        if (!CopyFile(mMazeName.c_str(), lTmpName, FALSE))
        {
            throw Maze_ERROR_FILE_COPY;
        }

        Maze_Result lRet = mBitmap.Open(lTmpName);
        if (Maze_OK != lRet)
        {
            throw lRet;
        }

        if (0 < mZoom)
        {
            Utl_Display_Start(lTmpName, "Race", mZoom);
        }
    }

    void Race::Run()
    {
        switch (mMode)
        {
        case MODE_MEASUREMENT: Run_Measurement(); break;
        case MODE_MOVE: Run_Move(); break;
        case MODE_REQUEST: Run_Request(); break;
        case MODE_THREAD: Run_Thread(); break;

        default: assert(false);
        }
    }

    void Race::Run_Measurement()
    {
        unsigned int lMeasurement = 0;

        while (0 < mInterfaces.size())
        {
            for (InterfaceList::iterator lIt = mInterfaces.begin(); lIt != mInterfaces.end(); lIt++)
            {
                if (lMeasurement >= (*lIt)->GetStats().GetMeasurments())
                {
                    if ((*lIt)->ProcessRequest())
                    {
                        mInterfaces.erase(lIt);
                        delete (*lIt);
                        break;
                    }
                }
            }

            lMeasurement++;
        }
    }

    void Race::Run_Move()
    {
        unsigned int lMove = 0;

        while (0 < mInterfaces.size())
        {
            for (InterfaceList::iterator lIt = mInterfaces.begin(); lIt != mInterfaces.end(); lIt++)
            {
                if (lMove >= (*lIt)->GetStats().GetMoves())
                {
                    if ((*lIt)->ProcessRequest())
                    {
                        mInterfaces.erase(lIt);
                        delete (*lIt);
                        break;
                    }
                }
            }

            lMove++;
        }
    }

    void Race::Run_Request()
    {
        while (0 < mInterfaces.size())
        {
            for (InterfaceList::iterator lIt = mInterfaces.begin(); lIt != mInterfaces.end(); lIt++)
            {
                if ((*lIt)->ProcessRequest())
                {
                    mInterfaces.erase(lIt);
                    delete (*lIt);
                    break;
                }
            }
        }
    }

    void Race::Run_Thread()
    {
        unsigned int lCount = 0;
        HANDLE lThreads[3];
        DWORD lThreadIds[3];

        for (InterfaceList::iterator lIt = mInterfaces.begin(); lIt != mInterfaces.end(); lIt++)
        {
            lThreads[lCount] = CreateThread(NULL, 0, ::Run, *lIt, CREATE_SUSPENDED, lThreadIds + lCount);
            assert(NULL != lThreads);

            lCount++;
        }

        for (unsigned int i = 0; i < lCount; i++)
        {
            DWORD lRet = ResumeThread(lThreads[i]);
            assert(1 == lRet);
        }

        WaitForMultipleObjects(lCount, lThreads, TRUE, 1000000);
    }

    Maze_Result Race::SetMode_Str(const char* aIn)
    {
        assert(NULL != aIn);

        if (0 == _stricmp("MEASUREMENT", aIn)) { return SetMode(Race::MODE_MEASUREMENT); }
        if (0 == _stricmp("MOVE", aIn)) { return SetMode(Race::MODE_MOVE); }
        if (0 == _stricmp("REQUEST", aIn)) { return SetMode(Race::MODE_REQUEST); }
        if (0 == _stricmp("THREAD", aIn)) { return SetMode(Race::MODE_THREAD); }

        return Maze_ERROR_INVALID;
    }

    Maze_Result Race::SetRunnerCount_Str(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetRunnerCount(lIn);
        }

        return lResult;
    }

    Maze_Result Race::SetSeed_Str(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetSeed(lIn);
        }

        return lResult;
    }

    Maze_Result Race::SetSlow_Str(const char* aIn)
    {
        unsigned int lIn_ms;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn_ms);
        if (Maze_OK == lResult)
        {
            lResult = SetSlow(lIn_ms);
        }

        return lResult;
    }

    Maze_Result Race::SetTcpPort_Str(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = (0xffff >= lIn) ? SetTcpPort(lIn) : Maze_ERROR_INVALID;
        }

        return lResult;
    }

    Maze_Result Race::SetZoom_Str(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetZoom(lIn);
        }

        return lResult;
    }

    SOCKET Race::Socket_Create()
    {
        SOCKET lResult = Utl_Socket_Create(mTcpPort);
        assert(INVALID_SOCKET != lResult);

        if (0 != listen(lResult, RUNNER_COUNT_MAX))
        {
            throw Maze_ERROR_SOCKET_LISTEN;
        }

        return lResult;
    }

}

// Static functions
// //////////////////////////////////////////////////////////////////////////

DWORD WINAPI Run(LPVOID aParam)
{
    assert(NULL != aParam);

    Interface* lInterface = reinterpret_cast<Interface *>(aParam);

    while (!lInterface->ProcessRequest())
    {
    }

    delete lInterface;

    return 0;
}

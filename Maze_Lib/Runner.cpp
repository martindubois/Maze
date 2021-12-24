
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Runner.cpp

#include "Component.h"

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Protocol.h>
}

#include <Maze/Runner.h>

// ===== Maze_Lib ===========================================================
#include "Utilities.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define HAND_DEFAULT (0)

#define HAND_LEFT  (0)
#define HAND_RIGHT (1)

#define HAND_MAX (1)

#define IPv4_DEFAULT (0)

#define TCP_PORT_DEFAULT (0)
#define TCP_PORT_MIN     (1)

#define ZOOM_DEFAULT (4)

// Static function declaration
// //////////////////////////////////////////////////////////////////////////

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Runner::~Runner()
    {
        if (INVALID_SOCKET != mSocket)
        {
            closesocket(mSocket);
        }

        Utl_Socket_Uninit();
    }

    Maze_Result Runner::SetHand(unsigned int aIn)
    {
        if (HAND_MAX < aIn) { return Maze_ERROR_MAX; }

        mHand = aIn;

        return Maze_OK;
    }

    Maze_Result Runner::SetIPv4(const char* aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mIPv4 = inet_addr(aIn);

        return Maze_OK;
    }

    Maze_Result Runner::SetName(const char* aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mName = aIn;

        return Maze_OK;
    }

    Maze_Result Runner::SetTcpPort(uint16_t aIn)
    {
        if (TCP_PORT_MIN > aIn) { return Maze_ERROR_MIN; }

        mTcpPort = aIn;

        return Maze_OK;
    }

    Maze_Result Runner::SetZoom(unsigned int aIn)
    {
        mZoom = aIn;

        return Maze_OK;
    }

    Maze_Result Runner::Start()
    {
        Maze_Result lResult;

        try
        {
            char lFileName[1024];

            sprintf_s(lFileName, "%s\\.Maze_%u.bmp", mProfile, GetCurrentProcessId());

            lResult = mBitmap.Create(lFileName, Color::UNKNOWN);
            if (Maze_OK == lResult)
            {
                mBitmap.SetPixel(mPosition, Color::RED);

                if (0 < mZoom)
                {
                    Utl_Display_Start(lFileName, mZoom);
                }

                mSocket = Utl_Socket_Create();
                assert(INVALID_SOCKET != mSocket);

                Connect();

                lResult = Run();
            }
        }
        catch (Maze_Result eE)
        {
            lResult = eE;
        }

        return lResult;
    }

    // ===== IConfigurable ==================================================

    Maze_Result Runner::Property_Set(const char* aName, const char* aValue)
    {
        assert(NULL != aName);
        assert(NULL != aValue);

        if (0 == _stricmp("Hand"   , aName)) { return SetHand   (aValue); }
        if (0 == _stricmp("IPv4"   , aName)) { return SetIPv4   (aValue); }
        if (0 == _stricmp("Name"   , aName)) { return SetName   (aValue); }
        if (0 == _stricmp("TcpPort", aName)) { return SetTcpPort(aValue); }
        if (0 == _stricmp("Zoom"   , aName)) { return SetZoom   (aValue); }

        return Maze_OK_IGNORED;
    }

    // Protected
    // //////////////////////////////////////////////////////////////////////

    Runner::Runner() : mDirection(Maze_DIR_EAST), mHand(HAND_DEFAULT), mIPv4(IPv4_DEFAULT), mSocket(INVALID_SOCKET), mTcpPort(TCP_PORT_DEFAULT), mZoom(ZOOM_DEFAULT)
    {
        DWORD lRet = GetEnvironmentVariable("USERPROFILE", mProfile, sizeof(mProfile));
        assert(0 < lRet);
        assert(sizeof(mProfile) > lRet);

        Utl_Socket_Init();
    }

    void Runner::Iteration_Hand(Maze_Response* aResponse)
    {
        switch (mHand)
        {
        case HAND_LEFT : Iteration_Hand_Left (aResponse); break;
        case HAND_RIGHT: Iteration_Hand_Right(aResponse); break;

        default: assert(false);
        }
    }

    void Runner::Iteration_Hand_Left(Maze_Response * aResponse)
    {
        assert(NULL != aResponse);

        for (;;)
        {
            unsigned int lNewDir = (mDirection - 1) % Maze_DIR_QTY;

            Maze::Position lPos;

            if (mPosition.GetNeighbor(lNewDir % Maze_DIR_QTY, &lPos) && (mBitmap.IsTrail(lPos) || mBitmap.IsPixel(lPos, Color::RED)))
            {
                mDirection = lNewDir;
                Request(mDirection, 1, Maze_DIR_ALL_BITS, aResponse);
                break;
            }

            if (mPosition.GetNeighbor(mDirection, &lPos) && (mBitmap.IsTrail(lPos) || mBitmap.IsPixel(lPos, Color::RED)))
            {
                Request(mDirection, 1, Maze_DIR_ALL_BITS, aResponse);
                break;
            }

            mDirection = (mDirection + 1) % Maze_DIR_QTY;
        }
    }

    void Runner::Iteration_Hand_Right(Maze_Response * aResponse)
    {
        assert(NULL != aResponse);

        for (;;)
        {
            unsigned int lNewDir = (mDirection + 1) % Maze_DIR_QTY;

            Maze::Position lPos;

            if (mPosition.GetNeighbor(lNewDir % Maze_DIR_QTY, &lPos) && (mBitmap.IsTrail(lPos) || mBitmap.IsPixel(lPos, Color::RED)))
            {
                mDirection = lNewDir;
                Request(mDirection, 1, Maze_DIR_ALL_BITS, aResponse);
                break;
            }

            if (mPosition.GetNeighbor(mDirection, &lPos) && (mBitmap.IsTrail(lPos) || mBitmap.IsPixel(lPos, Color::RED)))
            {
                Request(mDirection, 1, Maze_DIR_ALL_BITS, aResponse);
                break;
            }

            mDirection = (mDirection - 1) % Maze_DIR_QTY;
        }
    }

    Maze_Result Runner::Request(uint8_t aDirection, uint8_t aDistance_pixel, uint8_t aMeasures, Maze_Response * aResponse)
    {
        if (Maze_DIR_QTY <= aDirection) { return Maze_ERROR_DIRECTION; }
        if (NULL == aResponse) { return Maze_ERROR_POINTER; }

        memset(aResponse, 0, sizeof(Maze_Response));

        Maze_Result lResult = Maze_OK;

        try
        {
            Maze_Request lRequest;

            memset(&lRequest, 0, sizeof(lRequest));

            lRequest.mDirection = aDirection;
            lRequest.mDistance_pixel = aDistance_pixel;
            lRequest.mMeasures = aMeasures;

            Send(&lRequest, sizeof(lRequest));

            Receive(aResponse, sizeof(Maze_Response));

            assert(aDirection == aResponse->mDirection);

            if (0 < aResponse->mDistance_pixel)
            {
                mPosition.Go_Direction(aDirection, aResponse->mDistance_pixel);
                mBitmap.SetPixel(mPosition, Color::RED);
            }

            for (unsigned int lDir = 0; lDir < Maze_DIR_QTY; lDir++)
            {
                Position lPosition(mPosition);

                for (unsigned int i = 0; i < aResponse->mData[lDir]; i++)
                {
                    bool lRet = lPosition.Go_Direction(lDir, 1);
                    assert(lRet);

                    if (mBitmap.IsUnknown(lPosition))
                    {
                        mBitmap.SetPixel(lPosition, Color::TRAIL);
                    }
                }

                if (lPosition.Go_Direction(lDir, 1))
                {
                    mBitmap.SetPixel(lPosition, Color::BRICK);
                }
            }
        }
        catch (Maze_Result eE)
        {
            lResult = eE;
        }

        return lResult;
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    void Runner::Connect()
    {
        sockaddr_in lAddr;

        memset(&lAddr, 0, sizeof(lAddr));

        lAddr.sin_addr.S_un.S_addr = mIPv4;
        lAddr.sin_family = AF_INET;
        lAddr.sin_port = htons(mTcpPort);

        if (0 != connect(mSocket, reinterpret_cast<sockaddr*>(&lAddr), sizeof(lAddr)))
        {
            throw Maze_ERROR_SOCKET_CONNECT;
        }

        Send(Maze_BINARY, strlen(Maze_BINARY));

        Maze_Connect lConnect;

        memset(&lConnect, 0, sizeof(lConnect));

        strncpy_s(lConnect.mName, mName.c_str(), sizeof(lConnect.mName) - 1);

        Send(&lConnect, sizeof(lConnect));
    }

    void Runner::Receive(void* aOut, int aSize_byte)
    {
        assert(NULL != aOut);
        assert(0 < aSize_byte);

        assert(INVALID_SOCKET != mSocket);

        int lRet = recv(mSocket, reinterpret_cast<char *>(aOut), aSize_byte, 0);
        if (aSize_byte != lRet)
        {
            throw Maze_ERROR_SOCKET_RECEIVE;
        }
    }

    void Runner::Send(const void* aIn, int aSize_byte)
    {
        assert(NULL != aIn);
        assert(0 < aSize_byte);

        assert(INVALID_SOCKET != mSocket);

        int lRet = send(mSocket, reinterpret_cast<const char*>(aIn), aSize_byte, 0);
        if (aSize_byte != lRet)
        {
            throw Maze_ERROR_SOCKET_SEND;
        }
    }

    Maze_Result Runner::SetHand(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetHand(lIn);
        }

        return lResult;
    }

    Maze_Result Runner::SetTcpPort(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = (0xffff >= lIn) ? SetTcpPort(lIn) : Maze_ERROR_INVALID;
        }

        return lResult;
    }

    Maze_Result Runner::SetZoom(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = IConfigurable::ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetZoom(lIn);
        }

        return lResult;
    }

}

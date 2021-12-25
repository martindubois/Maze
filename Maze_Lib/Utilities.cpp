
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Utilities.cpp

#include "Component.h"

// ===== Maze_Lib ===========================================================
#include "Utilities.h"

// Functions
// //////////////////////////////////////////////////////////////////////////

void Utl_Display_Start(const char* aFileName, const char * aTitle, unsigned int aZoom)
{
    assert(NULL != aFileName);
    assert(NULL != aTitle);

    char lFolder[1024];

    DWORD lRet = GetModuleFileName(NULL, lFolder, sizeof(lFolder));
    assert((0 < lRet) && (sizeof(lFolder) > lRet));

    char* lPtr = strrchr(lFolder, '\\');
    assert(NULL != lPtr);

    *lPtr = '\0';

    char lCmd[2048];
    char lExe[1024];

    sprintf_s(lCmd, sizeof(lCmd), "%s\\Maze_Show.exe Input=%s Title=%s Zoom=%u", lFolder, aFileName, aTitle, aZoom);
    sprintf_s(lExe, sizeof(lExe), "%s\\Maze_Show.exe", lFolder);

    STARTUPINFO         lStart;
    PROCESS_INFORMATION lInfo;

    memset(&lStart, 0, sizeof(lStart));

    lStart.cb = sizeof(lStart);

    BOOL lRetB = CreateProcess(lExe, lCmd, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &lStart, &lInfo);
    if (!lRetB)
    {
        throw Maze_ERROR_PROCESS;
    }
}

SOCKET Utl_Socket_Create(uint16_t aLocalTcpPort)
{
    SOCKET lResult = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == lResult)
    {
        throw Maze_ERROR_SOCKET;
    }

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    lAddr.sin_family = AF_INET;
    lAddr.sin_port = htons(aLocalTcpPort);

    if (0 != bind(lResult, reinterpret_cast<sockaddr*>(&lAddr), sizeof(lAddr)))
    {
        throw Maze_ERROR_SOCKET_BIND;
    }

    return lResult;
}

void Utl_Socket_Init()
{
    WSAData lData;

    int lRet = WSAStartup(MAKEWORD(2, 2), &lData);
    assert(NO_ERROR == lRet);
}

void Utl_Socket_Uninit()
{
    int lRet = WSACleanup();
    assert(0 == lRet);
}



// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Interface_Binary.cpp

#include "Component.h"

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Protocol.h>
    #include <Maze_Result.h>
}

// ===== Maze_Lib ===========================================================
#include "Interface_BINARY.h"

// Public
// //////////////////////////////////////////////////////////////////////////

void Interface_Binary::Connect()
{
    Maze_Connect lConnect;

    int lRet = Receive(&lConnect, sizeof(lConnect));
    if (sizeof(lConnect) != lRet)
    {
        throw Maze_ERROR_PROTOCOL_CONNECT;
    }

    SetName(lConnect.mName);

    Interface::Connect();
}

bool Interface_Binary::ProcessRequest()
{
    Maze_Request lRequest;

    int lRet = Receive(&lRequest, sizeof(lRequest));
    if (sizeof(lRequest) != lRet)
    {
        throw Maze_ERROR_PROTOCOL_REQUEST;
    }

    Maze_Response lResponse;

    bool lResult = Interface::ProcessRequest(&lRequest, &lResponse);

    Send(&lResponse, sizeof(lResponse));

    return lResult;
}

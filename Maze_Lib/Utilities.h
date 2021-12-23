
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Utilities.h

#pragma once

// ===== C ==================================================================
#include <stdint.h>

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Result.h>
}

// Functions
// //////////////////////////////////////////////////////////////////////////

extern void Utl_Display_Start(const char* aFileName, unsigned int aZoom);

extern SOCKET Utl_Socket_Create(uint16_t aLocalTcpPort = 0);
extern void   Utl_Socket_Init  ();
extern void   Utl_Socket_Uninit();

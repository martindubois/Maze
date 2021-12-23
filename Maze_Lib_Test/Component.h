
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/Component.h

#pragma once

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Windows ============================================================
#include <Windows.h>

// Macros
// //////////////////////////////////////////////////////////////////////////

#define TEST_ASSERT(C)                                                   \
    if (!(C))                                                            \
    {                                                                    \
        fprintf(stderr, "TEST ERROR  " __FILE__ " line %u\n", __LINE__); \
        return 1;                                                        \
    }

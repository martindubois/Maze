
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Maze_Run0.cpp

#include "Component.h"

// ===== Maze_Gen0 ==========================================================
#include "../Common/Version.h"
#include "Run0.h"

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    printf("Maze - Maze_Run0 - " VERSION_STR "\n");

    Run0 lRun;

    Maze_Result lRet = Maze::Configurable_Parse(&lRun, aVector + 1, aCount - 1);
    if (Maze_OK == lRet)
    {
        lRet = lRun.Start();
    }

    if (Maze_OK == lRet)
    {
        printf("Maze_Run - OK\n");
    }
    else
    {
        fprintf(stderr, "Maze_Run - ERROR  %u\n", lRet);
    }

    return lRet;
}

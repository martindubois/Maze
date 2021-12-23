
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Maze_Show.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Display.h>

// ===== Maze_Gen0 ==========================================================
#include "../Common/Version.h"

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    printf("Maze - Maze_Show - " VERSION_STR "\n");

    Maze::Display lDisp;

    Maze_Result lRet = Maze::Configurable_Parse(&lDisp, aVector + 1, aCount - 1);
    if (Maze_OK == lRet)
    {
        lRet = lDisp.Show();
    }

    if (Maze_OK == lRet)
    {
        printf("Maze_Show - OK\n");
    }
    else
    {
        fprintf(stderr, "Maze_Show - ERROR  %u\n", lRet);
    }

    return lRet;
}

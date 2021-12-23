
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Maze_Gen0.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Info_StdOut.h>

// ===== Maze_Gen0 ==========================================================
#include "../Common/Version.h"
#include "Gen0.h"

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char ** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    printf("Maze - Maze_Gen0 - " VERSION_STR "\n");

    Gen0 lGen;
    Maze::Info_StdOut lInfo;

    Maze_Result lRet = Maze::Configurable_Parse(&lGen, aVector + 1, aCount - 1);
    if (Maze_OK == lRet)
    {
        lRet = lGen.Generate(&lInfo);
    }

    if (Maze_OK == lRet)
    {
        printf("Maze_Gen0 - OK\n");
    }
    else
    {
        fprintf(stderr, "Maze_Gen0 - ERROR  %u\n", lRet);
    }

    return lRet;
}

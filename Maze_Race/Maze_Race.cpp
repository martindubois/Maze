
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Maze_Race.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Info_StdOut.h>
#include <Maze/Race.h>

// ===== Maze_Gen0 ==========================================================
#include "../Common/Version.h"

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    printf("Maze - Maze_Race - " VERSION_STR "\n");

    Maze::Info_StdOut lInfo;
    Maze::Race lRace;

    Maze_Result lRet = Maze::Configurable_Parse(&lRace, aVector + 1, aCount - 1);
    if (Maze_OK == lRet)
    {
        lRet = lRace.Start(&lInfo);
    }

    if (Maze_OK == lRet)
    {
        printf("Maze_Race - OK\n");
    }
    else
    {
        fprintf(stderr, "Maze_Race - ERROR  %u\n", lRet);
    }

    return lRet;
}

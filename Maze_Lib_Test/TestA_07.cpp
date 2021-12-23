
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_07.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Info_None.h>
#include <Maze/Info_StdOut.h>
#include <Maze/Stats.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Info_StdOut
//           DisplayProgress.
//           DisplayProgress_End.
//           DisplayProgress_Start.
//           DisplayRace.
//           DisplayRunner.
//           DisplayStart.
//           DisplayTcpPort.
//           DisplayWinner.
int TestA_07()
{
    Maze::Info_None lIN;
    Maze::Info_StdOut lISO;

    Maze::IInfo * lIIs[2];

    lIIs[0] = &lIN;
    lIIs[1] = &lISO;

    for (unsigned int i = 0; i < 2; i++)
    {
        Maze::IInfo* lII = lIIs[i];

        lII->DisplayProgress_Start("Start");
        lII->DisplayProgress();
        lII->DisplayProgress_End("End");

        lII->DisplayRace(Maze::Race::MODE_MEASUREMENT);
        lII->DisplayRace(Maze::Race::MODE_MOVE);
        lII->DisplayRace(Maze::Race::MODE_REQUEST);
        lII->DisplayRace(Maze::Race::MODE_THREAD);

        lII->DisplayRunner(0, "Nom", 0);

        lII->DisplayStart();

        lII->DisplayTcpPort(1);

        lII->DisplayWinner(0, "Nom", Maze::Stats());
    }
    
    return 0;
}

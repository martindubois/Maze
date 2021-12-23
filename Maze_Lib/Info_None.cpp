
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Info_None.cpp

// CODE REVIEW 2021-12-23 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-23 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Info_None.h>

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    void Info_None::DisplayProgress() {}
    void Info_None::DisplayProgress_End  (const char*) {}
    void Info_None::DisplayProgress_Start(const char*) {}

    void Info_None::DisplayRace(Race::Mode) {}

    void Info_None::DisplayRunner(unsigned int, const char*, uint32_t) {}

    void Info_None::DisplayStart() {}

    void Info_None::DisplayTcpPort(uint16_t) {}

    void Info_None::DisplayWinner(unsigned int, const char*, const Stats&) {}

}

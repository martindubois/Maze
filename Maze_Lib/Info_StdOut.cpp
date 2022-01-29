
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021-2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Info_StdOut.cpp

// CODE REVIEW 2021-12-23 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-23 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Stats.h>

#include <Maze/Info_StdOut.h>

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    void Info_StdOut::DisplayProgress()
    {
        printf(".");
    }

    void Info_StdOut::DisplayProgress_End(const char* aEnd)
    {
        if (NULL != aEnd)
        {
            printf(" %s", aEnd);
        }

        printf("\n");
    }

    void Info_StdOut::DisplayProgress_Start(const char* aStart)
    {
        printf("\n");

        if (NULL != aStart)
        {
            printf("%s ", aStart);
        }
    }

    void Info_StdOut::DisplayRace(Race::Mode aMode)
    {
        printf("The race mode is ");

        switch (aMode)
        {
        case Race::MODE_MEASUREMENT: printf("MEASUREMENT"); break;
        case Race::MODE_MOVE       : printf("MOVE"       ); break;
        case Race::MODE_REQUEST    : printf("REQUEST"    ); break;
        case Race::MODE_THREAD     : printf("THREAD"     ); break;

        default:assert(false);
        }

        printf("\n");
    }

    void Info_StdOut::DisplayRunner(unsigned int aIndex, const char* aName, uint32_t aIPv4)
    {
        assert(NULL != aName);

        printf("The runner %u, %s, is connected from %u.%u.%u.%u\n",
            aIndex, aName,
            aIPv4       & 0xff,
            aIPv4 >>  8 & 0xff,
            aIPv4 >> 16 & 0xff,
            aIPv4 >> 24 & 0xff);
    }

    void Info_StdOut::DisplayStart()
    {
        printf("The race is now started\n");
    }

    void Info_StdOut::DisplayTcpPort(uint16_t aTcpPort)
    {
        printf("The TCP port is %u\n", aTcpPort);
    }

    void Info_StdOut::DisplayWinner(unsigned int aIndex, const char* aName, const Stats& aStats)
    {
        printf("The runner %u, %s, reach the end (%u requests, %u moves, %u measurements)\n",
            aIndex, aName,
            aStats.GetRequests(),
            aStats.GetMoves(),
            aStats.GetMeasurements());
    }

}

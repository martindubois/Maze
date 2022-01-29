
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021-2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Stats.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Stats.h>

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Stats::Stats() : mMeasurements(0), mMoves(0), mRequests(0)
    {
    }

    unsigned int Stats::GetMeasurements() const { return mMeasurements; }
    unsigned int Stats::GetMoves       () const { return mMoves; }
    unsigned int Stats::GetRequests    () const { return mRequests; }

    // Internal
    // //////////////////////////////////////////////////////////////////////

    void Stats::IncMeasurements() { mMeasurements++; }
    void Stats::IncMoves       () { mMoves       ++; }
    void Stats::IncRequests    () { mRequests    ++; }

}

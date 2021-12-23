
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Run0/Run0.cpp

#include "Component.h"

// ===== Maze_Gen0 ==========================================================
#include "Run0.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

//                                                    North          East            South          West
static const unsigned int FIRST_TRY[Maze_DIR_QTY] = { Maze_DIR_EAST, Maze_DIR_SOUTH, Maze_DIR_WEST, Maze_DIR_NORTH };
static const unsigned int NEXT_DIR [Maze_DIR_QTY] = { Maze_DIR_WEST, Maze_DIR_NORTH, Maze_DIR_EAST, Maze_DIR_SOUTH };

// Public
// //////////////////////////////////////////////////////////////////////////

Maze_Result Run0::Run()
{
    Maze_Response lResponse;

    Request(Maze_DIR_EAST, 0, Maze_DIR_ALL_BITS, &lResponse);

    unsigned int lDir = Maze_DIR_EAST;

    do
    {
        Iteration_Hand(&lResponse);
        /*
        Maze::Position lPos;

        if (mPosition.GetNeighbor(FIRST_TRY[lDir], &lPos) && mBitmap.IsTrail(lPos))
        {
            lDir = FIRST_TRY[lDir];
            Request(lDir, 1, Maze_DIR_ALL_BITS, &lResponse);
        }
        else if (mPosition.GetNeighbor(lDir, &lPos) && mBitmap.IsTrail(lPos))
        {
            Request(lDir, 1, Maze_DIR_ALL_BITS, &lResponse);
        }
        else
        {
            lDir = NEXT_DIR[lDir];
        }
        */
    }
    while (Maze::Position::END != mPosition);

    return Maze_OK;
}

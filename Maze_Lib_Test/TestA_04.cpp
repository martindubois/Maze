
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_04.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Display.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Position
//           operator == => false, true.
//           operator != => false, true.
//           GetEast => false.
//           GetNorth => false.
//           GetSouth => false.
//           GoDirection => false, true.
//           Go_XY_Destination.
//           GoEast => true.
//           GoNorth => true.
//           GoSouth => true.
//           GoWest => true.
//           GoX_Destination.
//           GoY_Destination.
int TestA_04()
{
    Maze::Position lP0;

    TEST_ASSERT(!(Maze::Position(0, 0) == Maze::Position(0, 1)));
    TEST_ASSERT(  Maze::Position(0, 0) == Maze::Position(0, 0));
    TEST_ASSERT(!(Maze::Position(0, 0) != Maze::Position(0, 0)));
    TEST_ASSERT(  Maze::Position(0, 0) != Maze::Position(0, 1));

    TEST_ASSERT(!Maze::Position(0, 255).GetNorth(&lP0));
    TEST_ASSERT(!Maze::Position(255, 0).GetEast (&lP0));
    TEST_ASSERT(!Maze::Position(255, 0).GetSouth(&lP0));
    TEST_ASSERT(!Maze::Position(0, 255).GetWest (&lP0));

    TEST_ASSERT(lP0.Go_Direction(Maze_DIR_NORTH));
    TEST_ASSERT(lP0.Go_Direction(Maze_DIR_EAST));
    TEST_ASSERT(lP0.Go_Direction(Maze_DIR_SOUTH));
    TEST_ASSERT(lP0.Go_Direction(Maze_DIR_WEST));

    lP0.Set(0, 255);
    TEST_ASSERT(!lP0.Go_Direction(Maze_DIR_NORTH));

    lP0.Go_XY_Destination(0, Maze::Position(128, 128));
    lP0.Go_XY_Destination(1, Maze::Position(128, 128));

    TEST_ASSERT(lP0.GoNorth());
    TEST_ASSERT(lP0.GoEast ());
    TEST_ASSERT(lP0.GoSouth());
    TEST_ASSERT(lP0.GoWest ());

    lP0.GoX_Destination(128);
    lP0.GoY_Destination(128);

    return 0;
}

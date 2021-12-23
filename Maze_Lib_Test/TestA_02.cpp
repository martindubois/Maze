
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_02.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Display.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Display
//           SetInput => Maze_OK.
//           SetPeriod => Maze_OK.
//           SetTitle => Maze_OK.
//           SetZoom => Maze_OK.
//           Property_Set => Maze_OK, Maze_OK_IGNORED.
int TestA_02()
{
    Maze::Display lD0;

    TEST_ASSERT(Maze_OK == lD0.SetInput("Test.bmp"));
    TEST_ASSERT(Maze_OK == lD0.SetPeriod(100));
    TEST_ASSERT(Maze_OK == lD0.SetTitle("Title"));
    TEST_ASSERT(Maze_OK == lD0.SetZoom(1));

    TEST_ASSERT(Maze_OK == lD0.Property_Set("Input" , "Test.bmp"));
    TEST_ASSERT(Maze_OK == lD0.Property_Set("Period", "100"));
    TEST_ASSERT(Maze_OK == lD0.Property_Set("Title" , "Title"));
    TEST_ASSERT(Maze_OK == lD0.Property_Set("Zoom"  , "1"));

    TEST_ASSERT(Maze_OK_IGNORED == lD0.Property_Set("Property", "Value"));

    return 0;
}


// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_03.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Display.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Display
//           Property_Set => Maze_ERROR_POINTER.
//           SetInput => Maze_ERROR_POINTER.
//           SetPeriod => Maze_ERROR_MAX, Maze_ERROR_MIN.
//           SetTitle => Maze_ERROR_POINTER.
//           SetZoom => Maze_ERROR_MAX, Maze_ERROR_MIN.
//           Show => Maze_ERROR_FILE_CREATE.
int TestA_03()
{
    Maze::Display lD0;

    TEST_ASSERT(Maze_ERROR_POINTER == lD0.SetInput(NULL));
    TEST_ASSERT(Maze_ERROR_MAX == lD0.SetPeriod(1001));
    TEST_ASSERT(Maze_ERROR_MIN == lD0.SetPeriod(14));
    TEST_ASSERT(Maze_ERROR_POINTER == lD0.SetTitle(NULL));
    TEST_ASSERT(Maze_ERROR_MAX == lD0.SetZoom(5));
    TEST_ASSERT(Maze_ERROR_MIN == lD0.SetZoom(0));

    TEST_ASSERT(Maze_ERROR_POINTER == lD0.Property_Set(NULL, "Value"));
    TEST_ASSERT(Maze_ERROR_POINTER == lD0.Property_Set("Property", NULL));

    TEST_ASSERT(Maze_OK == lD0.SetInput("DoesNotExist.bmp"));
    TEST_ASSERT(Maze_ERROR_FILE_CREATE == lD0.Show());

    return 0;
}

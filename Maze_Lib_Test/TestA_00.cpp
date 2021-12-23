
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_00.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>

// Constnts
// //////////////////////////////////////////////////////////////////////////

#define TEST_BMP "Test.bmp"

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Bitmap
//           CountTrail => 0, 1.
//           Create => Maze_OK.
//           GetInfo.
//           Open => Maze_OK.
//           SetPixel.
int TestA_00()
{
    Maze::Bitmap lB0;
    Maze::Bitmap lB1;

    TEST_ASSERT(Maze_OK == lB0.Create(TEST_BMP, Maze::Color::BRICK));

    TEST_ASSERT(0 == lB0.CountTrail(Maze::Position(1, 1)));

    lB0.SetPixel(Maze::Position(1, 2), Maze::Color::TRAIL);

    TEST_ASSERT(1 == lB0.CountTrail(Maze::Position(1, 1)));

    TEST_ASSERT(Maze_OK == lB1.Open(TEST_BMP));

    lB1.SetPixel(Maze::Position(1, 3), 0, 128);

    TEST_ASSERT(NULL != lB1.GetInfo());

    lB1.SetPixel(Maze::Position(1, 2), 0);
    lB1.SetPixel(Maze::Position(1, 3), 0);

    return 0;
}

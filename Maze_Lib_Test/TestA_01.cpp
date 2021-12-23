
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_01.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Bitmap.Error
//           Open => Maze_ERROR_FILE_CREATE, Maze_ERROR_FORMAT,
//                   Maze_ERROR_SIZE, Maze_ERROR_BAD.
int TestA_01()
{
    Maze::Bitmap lB0;

    TEST_ASSERT(Maze_ERROR_FILE_CREATE == lB0.Open("DoesNotExist.bmp"));

    TEST_ASSERT(Maze_ERROR_FORMAT == lB0.Open(Maze_Lib_Test\\TestA_01_0.bin));

    TEST_ASSERT(Maze_ERROR_SIZE == lB0.Open("Maze_Lib_Test\\TestA_01_0.bmp"));
    TEST_ASSERT(Maze_ERROR_BAD  == lB0.Open("Maze_Lib_Test\\TestA_01_1.bmp"));

    return 0;
}

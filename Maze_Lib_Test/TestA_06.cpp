
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_06.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Race.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Race.Error
//           Property_Set => Maze_ERROR_POINTER.
//           SetGenerator => Maze_ERROR_POINTER.
//           SetMazeName => Maze_ERROR_POINTER.
//           SetMode => Maze_ERROR_ENUM.
//           SetSlow => Maze_ERROR_MAX.
//           SetRunnerCount => Maze_ERROR_MAZ, Maze_ERROR_MIN.
//           Start => Maze_ERROR_POINTER.
int TestA_06()
{
    Maze::Race lR0;

    TEST_ASSERT(Maze_ERROR_POINTER == lR0.SetGenerator(NULL));
    TEST_ASSERT(Maze_ERROR_POINTER == lR0.SetMazeName(NULL));
    TEST_ASSERT(Maze_ERROR_ENUM == lR0.SetMode(static_cast<Maze::Race::Mode>(4)));
    TEST_ASSERT(Maze_ERROR_MAX == lR0.SetRunnerCount(4));
    TEST_ASSERT(Maze_ERROR_MIN == lR0.SetRunnerCount(0));
    TEST_ASSERT(Maze_ERROR_MAX == lR0.SetSlow(1001));

    TEST_ASSERT(Maze_ERROR_POINTER == lR0.Property_Set(NULL, "Value"));
    TEST_ASSERT(Maze_ERROR_POINTER == lR0.Property_Set("Property", NULL));

    TEST_ASSERT(Maze_ERROR_POINTER == lR0.Start(NULL));

    return 0;
}

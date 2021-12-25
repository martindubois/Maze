
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/TestA_05.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Race.h>

// Test
// //////////////////////////////////////////////////////////////////////////

// TEST INFO Maze.Race
//           Property_Set => Maze_OK, Maze_OK_IGNORED.
//           SetGenerator => Maze_OK.
//           SetMazeName => Maze_OK.
//           SetMode => Maze_OK.
//           SetRunnerCount => Maze_OK.
//           SetSeed => Maze_OK.
//           SetSlow => Maze_OK.
//           SetZoom => Maze_OK.
int TestA_05()
{
    Maze::Race lR0;

    TEST_ASSERT(Maze_OK == lR0.SetGenerator("Maze_Gen0.exe"));
    TEST_ASSERT(Maze_OK == lR0.SetMazeName("Test.bmp"));
    TEST_ASSERT(Maze_OK == lR0.SetMode(Maze::Race::MODE_REQUEST));
    TEST_ASSERT(Maze_OK == lR0.SetRunnerCount(1));
    TEST_ASSERT(Maze_OK == lR0.SetSeed(1));
    TEST_ASSERT(Maze_OK == lR0.SetSlow(0));
    TEST_ASSERT(Maze_OK == lR0.SetZoom(0));

    TEST_ASSERT(Maze_OK == lR0.Property_Set("Generator"  , "Maze_Gen0.exe"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("MazeName"   , "Test.bmp"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Mode"       , "MEASUREMENT"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Mode"       , "MOVE"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Mode"       , "REQUEST"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Mode"       , "THREAD"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("RunnerCount", "1"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Seed"       , "1"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Slow"       , "0"));
    TEST_ASSERT(Maze_OK == lR0.Property_Set("Zoom"       , "0"));

    TEST_ASSERT(Maze_OK_IGNORED == lR0.Property_Set("Property", "Value"));

    return 0;
}

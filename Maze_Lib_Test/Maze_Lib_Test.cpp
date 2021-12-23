
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib_Test/Maze_Lib_Test.cpp

#include "Component.h"

// ===== Maze_Gen0 ==========================================================
#include "../Common/Version.h"

// ===== Maze_Lib_Test ======================================================
#include "TestList.h"

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

static int ExecuteTest(const TestInfo* aInfo);

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    printf("Maze - Maze_Lib_Test - " VERSION_STR "\n");

    int lRet = 0;

    for (unsigned int i = 0; i < sizeof(TESTS) / sizeof(TESTS[0]); i++)
    {
        lRet += ExecuteTest(TESTS + i);
    }

    if (0 == lRet)
    {
        printf("Maze_Lib_Test - OK\n");
    }
    else
    {
        fprintf(stderr, "Maze_Lib_Test - ERROR  %d\n", lRet);
    }

    return lRet;
}

// Static functions
// //////////////////////////////////////////////////////////////////////////

int ExecuteTest(const TestInfo* aInfo)
{
    printf("Executing  %s  ...\n", aInfo->mName);

    int lRet = aInfo->mFunction();
    if (0 == lRet)
    {
        printf("Test PASSED\n");
    }
    else
    {
        printf("Test FAILED\n");
    }

    return lRet;
}

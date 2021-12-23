
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Run0/Run0.h

#pragma once

// ===== Includes ===========================================================
#include <Maze/Runner.h>

class Run0 : public Maze::Runner
{

public:

    // ===== Maze::Generator ================================================
    virtual Maze_Result Run();

};

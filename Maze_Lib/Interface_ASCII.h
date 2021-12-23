
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Interface_ASCII.h

#pragma once

// ===== Maze_Lib ===========================================================
#include "Interface.h"

class Interface_ASCII : public Interface
{

public:

    // ===== Interface ======================================================
    virtual void Connect();
    virtual bool ProcessRequest();

};

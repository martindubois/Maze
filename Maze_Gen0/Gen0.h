
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Gen0.h

#pragma once

// ===== Includes ===========================================================
#include <Maze/Generator.h>

class Gen0 : public Maze::Generator
{

protected:

    // ===== Maze::Generator ================================================
    virtual void GenerateBitmap(Maze::Bitmap* aBitmap);

private:

    void Phase0(Maze::Bitmap* aBitmap);

};

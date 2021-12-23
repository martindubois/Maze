
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Gen0/Gen0.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>

extern "C"
{
    #include <Maze_Protocol.h>
}

// ===== Maze_Gen0 ==========================================================
#include "Gen0.h"

// Protected
// //////////////////////////////////////////////////////////////////////////

void Gen0::GenerateBitmap(Maze::Bitmap* aBitmap)
{
    Phase0(aBitmap);

    FillBitmap(aBitmap);
}

// Private
// //////////////////////////////////////////////////////////////////////////

void Gen0::Phase0(Maze::Bitmap* aBitmap)
{
    Maze::Position lPos(Maze_START_X_pixel, Maze_START_Y_pixel);

    Maze::Position lPoints[3];

    lPoints[0].Set(GetRandom(Maze_SIZE_X_pixel / 2, Maze_SIZE_X_pixel - 3), GetRandom(2, Maze_SIZE_Y_pixel / 2));
    lPoints[1].Set(GetRandom(2, Maze_SIZE_X_pixel / 2), GetRandom(Maze_SIZE_Y_pixel / 2, Maze_SIZE_Y_pixel - 3));
    lPoints[2].Set(Maze_END_X_pixel, Maze_END_Y_pixel);

    for (unsigned int i = 0; i < 3; i++)
    {
        while (lPoints[i] != lPos)
        {
            lPos.Go_XY_Destination(GetRandom(0, 1), lPoints[i]);

            aBitmap->SetPixel(lPos, Maze::Color::TRAIL);
        }
    }
}

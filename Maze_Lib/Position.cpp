
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Position.cpp

// CODE REVIEW 2021-12-19 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-19 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Protocol.h>
}

#include <Maze/Position.h>

// Constants
// //////////////////////////////////////////////////////////////////////////

static const int MAZE_SIZE_pixel[2] = { Maze_SIZE_X_pixel, Maze_SIZE_Y_pixel };

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    const Position Position::END(Maze_END_X_pixel, Maze_END_Y_pixel);

    Position::Position()
    {
        Set(0, 0);
    }

    Position::Position(uint16_t aX_pixel, uint16_t aY_pixel)
    {
        Set(aX_pixel, aY_pixel);
    }

    bool Position::operator == (const Position& aB) const
    {
        return (aB.GetX() == mXY_pixel[0]) && (aB.GetY() == mXY_pixel[1]);
    }

    bool Position::operator != (const Position& aB) const
    {
        return (aB.GetX() != mXY_pixel[0]) || (aB.GetY() != mXY_pixel[1]);
    }

    bool Position::GetNeighbor(unsigned int aDir, Position* aOut)
    {
        bool lResult = false;

        switch (aDir)
        {
        case Maze_DIR_NORTH: lResult = GetNorth(aOut); break;
        case Maze_DIR_EAST : lResult = GetEast (aOut); break;
        case Maze_DIR_SOUTH: lResult = GetSouth(aOut); break;
        case Maze_DIR_WEST : lResult = GetWest (aOut); break;

        default: assert(false);
        }

        return lResult;
    }

    bool Position::GetEast(Position* aOut) const
    {
        if ((Maze_SIZE_X_pixel - 1) <= mXY_pixel[0])
        {
            return false;
        }

        aOut->Set(mXY_pixel[0] + 1, mXY_pixel[1]);

        return true;
    }

    bool Position::GetNorth(Position* aOut) const
    {
        if ((Maze_SIZE_Y_pixel - 1) <= mXY_pixel[1])
        {
            return false;
        }

        aOut->Set(mXY_pixel[0], mXY_pixel[1] + 1);

        return true;
    }

    bool Position::GetSouth(Position* aOut) const
    {
        if (0 >= mXY_pixel[1])
        {
            return false;
        }

        aOut->Set(mXY_pixel[0], mXY_pixel[1] - 1);

        return true;
    }

    bool Position::GetWest(Position* aOut) const
    {
        if (0 >= mXY_pixel[0])
        {
            return false;
        }

        aOut->Set(mXY_pixel[0] - 1, mXY_pixel[1]);

        return true;
    }

    uint16_t Position::GetX() const { return mXY_pixel[0]; }
    uint16_t Position::GetY() const { return mXY_pixel[1]; }

    bool Position::Go_Direction(unsigned int aDir, int aDist_pixel)
    {
        bool lResult = false;

        switch (aDir)
        {
        case Maze_DIR_NORTH: lResult = Go_XY(1,   aDist_pixel); break;
        case Maze_DIR_EAST : lResult = Go_XY(0,   aDist_pixel); break;
        case Maze_DIR_SOUTH: lResult = Go_XY(1, - aDist_pixel); break;
        case Maze_DIR_WEST : lResult = Go_XY(0, - aDist_pixel); break;

        default: assert(false);
        }

        return lResult;
    }

    bool Position::Go_XY(unsigned int aXY, int aDist_pixel)
    {
        int lPos_pixel = mXY_pixel[aXY];

        lPos_pixel += aDist_pixel;
        if ((0 > lPos_pixel) || (MAZE_SIZE_pixel[aXY] <= lPos_pixel))
        {
            return false;
        }

        mXY_pixel[aXY] = lPos_pixel;

        return true;
    }

    void Position::Go_XY_Destination(unsigned int aXY, Position aDest)
    {
        switch (aXY)
        {
        case 0: Go_XY_Destination(aXY, aDest.GetX()); break;
        case 1: Go_XY_Destination(aXY, aDest.GetY()); break;

        default: assert(false);
        }
    }

    bool Position::GoEast (int aDist_pixel) { return Go_XY(0,  aDist_pixel); }
    bool Position::GoNorth(int aDist_pixel) { return Go_XY(1,  aDist_pixel); }
    bool Position::GoSouth(int aDist_pixel) { return Go_XY(1, -aDist_pixel); }
    bool Position::GoWest (int aDist_pixel) { return Go_XY(0, -aDist_pixel); }

    void Position::GoX_Destination(uint16_t aDest_pixel) { Go_XY_Destination(0, aDest_pixel); }
    void Position::GoY_Destination(uint16_t aDest_pixel) { Go_XY_Destination(1, aDest_pixel); }

    void Position::Set(uint16_t aX_pixel, uint16_t aY_pixel)
    {
        assert(Maze_SIZE_X_pixel > aX_pixel);
        assert(Maze_SIZE_Y_pixel > aY_pixel);

        mXY_pixel[0] = aX_pixel;
        mXY_pixel[1] = aY_pixel;
    }

    // Internal
    // //////////////////////////////////////////////////////////////////////

    unsigned int Position::GetIndex() const
    {
        return Maze_SIZE_X_pixel * mXY_pixel[1] + mXY_pixel[0];
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    void Position::Go_XY_Destination(unsigned int aXY, uint16_t aDest_pixel)
    {
        if (mXY_pixel[aXY] < aDest_pixel)
        {
            mXY_pixel[aXY] ++;
        }
        else if (mXY_pixel[aXY] > aDest_pixel)
        {
            mXY_pixel[aXY] --;
        }
    }

}

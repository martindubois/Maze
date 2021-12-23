
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Color.cpp

// CODE REVIEW 2021-12-18 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-18 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Color.h>

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    const Color Color::BRICK  (  0,   0,   0);
    const Color Color::RED    (255,   0,   0);
    const Color Color::TRAIL  (255, 255, 255);
    const Color Color::UNKNOWN(127, 127, 127);

    Color::Color(uint8_t aR, uint8_t aG, uint8_t aB)
    {
        mBGRA[0] = aB;
        mBGRA[1] = aG;
        mBGRA[2] = aR;
        mBGRA[3] = 0;
    }

    bool Color::operator == (const Color& aB) const
    {
        return ((mBGRA[0] == aB.GetB()) && (mBGRA[1] == aB.GetG()) && (mBGRA[2] == aB.GetR()) && (mBGRA[3] == aB.GetA()));
    }

    uint8_t Color::GetA() const { return mBGRA[3]; }
    uint8_t Color::GetB() const { return mBGRA[0]; }
    uint8_t Color::GetG() const { return mBGRA[1]; }
    uint8_t Color::GetR() const { return mBGRA[2]; }

    void Color::Set(unsigned int aBGR, uint8_t aVal)
    {
        assert(3 > aBGR);

        mBGRA[aBGR] = aVal;
    }

    // Internal
    // //////////////////////////////////////////////////////////////////////

    void Color::Fade()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            mBGRA[i]--;
        }
    }

}

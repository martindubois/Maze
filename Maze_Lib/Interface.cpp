
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Interface.cpp

#include "Component.h"

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Result.h>
}

// ===== Maze_Lib ===========================================================
#include "Interface.h"

// Public
// //////////////////////////////////////////////////////////////////////////

Interface::Interface()
{
}

void Interface::Init(Maze::IInfo * aInfo, Maze::Bitmap* aBitmap, unsigned int aSlow_ms, unsigned int aIndex, uint32_t aIPv4, SOCKET aSocket)
{
    assert(NULL != aInfo);
    assert(NULL != aBitmap);
    assert(3 > aIndex);
    assert(0 != aIPv4);
    assert(NULL != aSocket);

    mInfo = aInfo;
    mBitmap = aBitmap;
    mSlow_ms = aSlow_ms;
    mIndex = aIndex;
    mIPv4 = aIPv4;
    mSocket = aSocket;
}

void Interface::Connect()
{
    assert(NULL != mInfo);

    mInfo->DisplayRunner(mIndex, mName.c_str(), mIPv4);
}

const Maze::Stats& Interface::GetStats() const { return mStats; }

// Protected
// //////////////////////////////////////////////////////////////////////////

bool Interface::ProcessRequest(const Maze_Request* aIn, Maze_Response* aOut)
{
    assert(NULL != aIn);
    assert(NULL != aOut);

    assert(NULL != mInfo);

    mStats.IncRequests();

    memset(aOut, 0, sizeof(Maze_Response));

    aOut->mDirection = aIn->mDirection;
    aOut->mMeasures  = aIn->mMeasures;

    Move   (aIn, aOut);
    Measure(aIn, aOut);

    bool lResult = Maze::Position::END == mPosition;
    if (lResult)
    {
        mInfo->DisplayWinner(mIndex, mName.c_str(), mStats);
    }

    return lResult;
}

int Interface::Receive(void* aOut, int aSize_byte)
{
    assert(NULL != aOut);
    assert(0 < aSize_byte);

    assert(INVALID_SOCKET != mSocket);

    int lResult = recv(mSocket, reinterpret_cast<char *>(aOut), aSize_byte, 0);
    if ((0 >= lResult) || (aSize_byte < lResult))
    {
        throw Maze_ERROR_SOCKET_RECEIVE;
    }

    return lResult;
}

void Interface::Send(const void* aIn, int aSize_byte)
{
    assert(NULL != aIn);
    assert(0 < aSize_byte);

    int lResult = send(mSocket, reinterpret_cast<const char*>(aIn), aSize_byte, 0);
    if (aSize_byte != lResult)
    {
        throw Maze_ERROR_SOCKET_SEND;
    }
}

void Interface::SetName(const char* aName)
{
    assert(NULL != aName);

    mName = aName;
}

// Private
// //////////////////////////////////////////////////////////////////////////

void Interface::Measure(const Maze_Request* aIn, Maze_Response* aOut)
{
    assert(NULL != aIn);
    assert(NULL != aOut);

    assert(NULL != mBitmap);

    for (unsigned int lDir = 0; lDir < Maze_DIR_QTY; lDir++)
    {
        if (0 != (aIn->mMeasures & Maze_DIR_BIT(lDir)))
        {
            mStats.IncMeasurments();

            Maze::Position lPos = mPosition;

            while (lPos.Go_Direction(lDir))
            {
                if (mBitmap->IsBrick(lPos))
                {
                    break;
                }

                aOut->mData[lDir]++;
            }
        }
    }
}

void Interface::Move(const Maze_Request* aIn, Maze_Response* aOut)
{
    assert(NULL != aIn);
    assert(NULL != aOut);

    assert(NULL != mBitmap);

    Maze::Position lPos(mPosition);

    for (unsigned int i = 0; i < aIn->mDistance_pixel; i++)
    {
        mBitmap->Pixel_Leave(lPos, mIndex);

        if (!lPos.Go_Direction(aIn->mDirection))
        {
            break;
        }

        if (mBitmap->IsBrick(lPos))
        {
            break;
        }

        if (0 < mSlow_ms)
        {
            Sleep(mSlow_ms);
        }

        mStats.IncMoves();

        mBitmap->Pixel_Enter(lPos, mIndex);

        mPosition = lPos;

        aOut->mDistance_pixel++;
    }
}

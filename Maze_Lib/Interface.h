
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Interface.h

#pragma once

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>
#include <Maze/Stats.h>

extern "C"
{
    #include <Maze_Protocol.h>
}

class Interface
{

public:

    Interface();

    void Init(Maze::Bitmap* aBitmap, unsigned int aSlow_ms, unsigned int aIndex, uint32_t aIPv4, SOCKET aSocket);

    virtual void Connect() = 0;

    unsigned int       GetIndex() const;
    uint32_t           GetIPv4 () const;
    const char       * GetName () const;
    const Maze::Stats& GetStats() const;

    virtual bool ProcessRequest() = 0;

protected:

    bool ProcessRequest(const Maze_Request* aIn, Maze_Response* aOut);

    int Receive(void* aOut, int aSize_byte);

    void Send(const void* aIn, int aSize_byte);

    void SetName(const char* aName);

private:

    void Measure(const Maze_Request* aIn, Maze_Response* aOut);
    void Move   (const Maze_Request* aIn, Maze_Response* aOut);

    Maze::Bitmap * mBitmap;
    unsigned int   mIndex;
    uint32_t       mIPv4;
    std::string    mName;
    Maze::Position mPosition;
    unsigned int   mSlow_ms;
    SOCKET         mSocket;

    Maze::Stats mStats;

};

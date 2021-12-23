
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Generator.cpp

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Utilisez toujours le meme ordre pour inclure les fichiers d'entete.
// Commencez par inclure les fichiers les plus generaux et terminez en
// incluant les fichiers les plus specifique au projet. Plus precisement:
// 1. Les fichiers d'entete de la librairie C
// 2. Les fichiers d'entete de la librairie C++
// 3. Les fichiers d'entete des librairies externe utilisees par le produit.
// 4. Les fichiers d'entete des librairies externe utilisees par le
//    composant.
// 5. Les fichiers d'entete du produit.
// 6. Les fichiers d'entete publiques du composant.
// 7. Les fichiers d'entete prives du composant.
// Cet ordre suit l'ordre dependance normale. Par exemple, il est normale
// qu'un fichier entete definit dans un composant depende sur les fichiers
// d'entete d'une librairie externe. Au contraire, un fichier d'entete d'un
// produit ne doit jamais dependre d'un fichier d'entete prive d'un
// composant.

#include "Component.h"

// ===== C ==================================================================
#include <string.h>
#include <time.h>

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>
#include <Maze/IInfo.h>

extern "C"
{
    #include <Maze_Protocol.h>
}

#include <Maze/Generator.h>

// ===== Maze_Lib ===========================================================
#include "Utilities.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define FILL_DEFAULT (3)

#define OUTPUT_DEFAULT "Output.bmp"

#define SEED_DEFAULT (0)

#define ZOOM_DEFAULT (0)

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Generator::~Generator()
    {
    }

    Maze_Result Generator::Generate(IInfo * aInfo)
    {
        if (NULL == aInfo) { return Maze_ERROR_POINTER; }

        mInfo = aInfo;

        Maze_Result lResult;

        try
        {
            Bitmap lBitmap;

            lResult = lBitmap.Create(mOutput.c_str(), Color::BRICK);
            if (Maze_OK == lResult)
            {
                lBitmap.SetPixel(Position(Maze_START_X_pixel, Maze_START_Y_pixel), Color::TRAIL);
                lBitmap.SetPixel(Position(Maze_END_X_pixel, Maze_END_Y_pixel), Color::TRAIL);

                if (0 < mZoom)
                {
                    Utl_Display_Start(mOutput.c_str(), mZoom);
                    Sleep(100);
                }

                Random_Init();

                mInfo->DisplayProgress_Start("Generting the maze");

                GenerateBitmap(&lBitmap);
            }

            mInfo->DisplayProgress_End("Generated");
        }
        catch (Maze_Result eE)
        {
            mInfo->DisplayProgress_End("EXCEPTION");
            lResult = eE;
        }

        return lResult;
    }

    Maze_Result Generator::SetOutput(const char * aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mOutput = aIn;

        return Maze_OK;
    }

    Maze_Result Generator::SetSeed(unsigned int aIn) { mSeed = aIn; return Maze_OK; }
    Maze_Result Generator::SetZoom(unsigned int aIn) { mZoom = aIn; return Maze_OK; }

    // ===== IConfigurable ==================================================

    Maze_Result Generator::Property_Set(const char* aName, const char* aValue)
    {
        if (0 == _stricmp("Output", aName)) { return SetOutput(aValue); }
        if (0 == _stricmp("Seed"  , aName)) { return SetSeed  (aValue); }
        if (0 == _stricmp("Zoom"  , aName)) { return SetZoom  (aValue); }

        return Maze_OK_IGNORED;
    }

    // Protected
    // //////////////////////////////////////////////////////////////////////

    Generator::Generator() : mFill(FILL_DEFAULT), mOutput(OUTPUT_DEFAULT), mSeed(SEED_DEFAULT), mZoom(ZOOM_DEFAULT)
    {
    }

    unsigned int Generator::GetRandom(unsigned int aMin, unsigned int aMax)
    {
        unsigned int lRange = aMax - aMin + 1;

        return rand() % lRange + aMin;
    }

    void Generator::FillBitmap(Bitmap* aBitmap)
    {
        assert(NULL != mInfo);

        if (0 < mFill)
        {
            bool lRun;

            do
            {
                mInfo->DisplayProgress();

                lRun = false;

                for (uint16_t lY_pixel = 0; lY_pixel < Maze_SIZE_Y_pixel; lY_pixel++)
                {
                    for (uint16_t lX_pixel = 0; lX_pixel < Maze_SIZE_X_pixel; lX_pixel++)
                    {
                        Maze::Position lPos(lX_pixel, lY_pixel);

                        if (aBitmap->IsBrick(lPos) && (1 == aBitmap->CountTrail(lPos)))
                        {
                            if (0 == GetRandom(0, mFill))
                            {
                                aBitmap->SetPixel(lPos, Maze::Color::TRAIL);
                                lRun = true;
                            }
                        }
                    }
                }
            }
            while (lRun);
        }
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    void Generator::Random_Init()
    {
        srand((0 == mSeed) ? static_cast<unsigned int>(time(NULL)) : mSeed);
    }

    Maze_Result Generator::SetSeed(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetSeed(lIn);
        }

        return lResult;
    }

    Maze_Result Generator::SetZoom(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetZoom(lIn);
        }

        return lResult;
    }

}

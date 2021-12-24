
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Bitmap.cpp

// CODE REVIEW 2021-12-18 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-18 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>

extern "C"
{
    #include <Maze_Protocol.h>
}

// Constants
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// Le mot cle static, utilise a l'exterieur d'une classe, indique que la
// constante, la variable ou la fonction n'est pas visible a l'exterieur du
// module dans lequel il est definit.

// COMMENTAIRE PEDAGOGIQUE
// La ligne qui suit utilise une fonctionnalitee peu connue du langage C.
// Elle initialise une variable de type entiere (ici, un entier non signe de
// 16 bits) en utilisant des caracteres ASCII. La norme du format ".bmp"
// exige qu'un champ de l'entete du fichier soit initialise avec le
// caracteres BM. La structure BITMAPFILEHEADER definit par Windows pour cet
// entete definit ce champ comme un entier non signe de 16 bits. La valeur
// 'MB' initialise l'entier de 16 bit correctement. L'inversion des deux
// lettre est necessaire car ce code est compiler pour une architecture qui
// utilise l'ordre des octets en memoire nommee "Little endian". Si le code
// etait compiler sur des architectures ordonant le octets differement, il
// faudrait changer la ligne et probablement utiliser une compilation
// conditionnel en fonction de l'architecture.
static const uint16_t FORMAT = 'MB';

static const unsigned int IMAGE_SIZE_byte = Maze_SIZE_X_pixel * Maze_SIZE_Y_pixel * 4;

static const unsigned int FILE_HEADERS_byte = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

static const unsigned int FILE_SIZE_byte = FILE_HEADERS_byte + IMAGE_SIZE_byte;

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Bitmap::Bitmap() : mFile(INVALID_HANDLE_VALUE)
    {
    }

    Bitmap::~Bitmap()
    {
        Close();
    }

    void Bitmap::Clear(Color aColor)
    {
        assert(NULL != mInfo);
        assert(NULL != mInfo->bmiColors);

        Color* lData = reinterpret_cast<Color *>(mInfo->bmiColors);

        for (unsigned int i = 0; i < Maze_SIZE_X_pixel * Maze_SIZE_Y_pixel; i++)
        {
            lData[i] = aColor;
        }
    }

    void Bitmap::Close()
    {
        if (INVALID_HANDLE_VALUE != mFile)
        {
            BOOL lRet;

            if (NULL != mMapping)
            {
                if (NULL != mView)
                {
                    lRet = UnmapViewOfFile(mView);
                    assert(lRet);
                }

                lRet = CloseHandle(mMapping);
                assert(lRet);
            }

            lRet = CloseHandle(mFile);
            assert(lRet);

            mFile = INVALID_HANDLE_VALUE;
        }
    }

    unsigned int Bitmap::CountTrail(Position aPos) const
    {
        unsigned int lResult = 0;

        for (unsigned int lDir = 0; lDir < Maze_DIR_QTY; lDir++)
        {
            Position lPos;

            if (aPos.GetNeighbor(lDir, &lPos) && IsTrail(lPos))
            {
                lResult++;
            }
        }

        return lResult;
    }

    Maze_Result Bitmap::Create(const char* aFileName, Color aColor)
    {
        Maze_Result lResult = Map(aFileName, CREATE_ALWAYS);
        if (Maze_OK == lResult)
        {
            InitHeaders();

            Clear(aColor);
        }

        return lResult;
    }

    bool Bitmap::IsPixel(Position aPos, Color aColor) const
    {
        const Color* lPtr = GetPointer(aPos);

        return *lPtr == aColor;
    }

    bool Bitmap::IsBrick(Position aPos) const { return IsPixel(aPos, Color::BRICK); }
    bool Bitmap::IsTrail(Position aPos) const { return IsPixel(aPos, Color::TRAIL); }
    bool Bitmap::IsUnknown(Position aPos) const { return IsPixel(aPos, Color::UNKNOWN); }

    Maze_Result Bitmap::Open(const char* aFileName)
    {
        Maze_Result lResult = Map(aFileName, OPEN_EXISTING);
        if (Maze_OK == lResult)
        {
            lResult = ValidateHeaders();
        }
        return lResult;
    }
     
    void Bitmap::SetPixel(Position aPos, Color aColor)
    {
        Color * lPtr = GetPointer(aPos);
        assert(NULL != lPtr);

        *lPtr = aColor;
    }

    void Bitmap::SetPixel(Position aPos, unsigned int aBGR, uint8_t aVal)
    {
        Color* lPtr = GetPointer(aPos);
        assert(NULL != lPtr);

        lPtr->Set(aBGR, aVal);
    }

    // Internal
    // //////////////////////////////////////////////////////////////////////

    const BITMAPINFO* Bitmap::GetInfo() const
    {
        return mInfo;
    }

    void Bitmap::SetPixel(Position aPos, unsigned int aBGR)
    {
        Color* lPtr = GetPointer(aPos);
        assert(NULL != lPtr);

        if (Color::TRAIL == *lPtr)
        {
            *lPtr = Color::UNKNOWN;
        }
        else
        {
            lPtr->Fade();
        }

        lPtr->Set(aBGR, 255);
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    const Color* Bitmap::GetPointer(Position aPos) const
    {
        return reinterpret_cast<const Color*>(mInfo->bmiColors + aPos.GetIndex());
    }

    Color* Bitmap::GetPointer(Position aPos)
    {
        return reinterpret_cast<Color *>(mInfo->bmiColors + aPos.GetIndex());
    }

    void Bitmap::InitHeaders()
    {
        assert(NULL != mFileHeader);
        assert(NULL != mInfo);

        memset(mFileHeader      , 0, sizeof(BITMAPFILEHEADER));
        memset(&mInfo->bmiHeader, 0, sizeof(BITMAPINFOHEADER));

        mFileHeader->bfOffBits = FILE_HEADERS_byte;
        mFileHeader->bfSize    = FILE_SIZE_byte;
        mFileHeader->bfType    = FORMAT;

        mInfo->bmiHeader.biBitCount    = 32;
        mInfo->bmiHeader.biCompression = BI_RGB;
        mInfo->bmiHeader.biHeight      = Maze_SIZE_Y_pixel;
        mInfo->bmiHeader.biPlanes      = 1;
        mInfo->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
        mInfo->bmiHeader.biWidth       = Maze_SIZE_X_pixel;
    }

    void Bitmap::InitPointers()
    {
        assert(NULL != mView);

        mFileHeader = reinterpret_cast<BITMAPFILEHEADER*>(mView);
        mInfo       = reinterpret_cast<BITMAPINFO      *>(mFileHeader + 1);
    }

    Maze_Result Bitmap::Map(const char * aFileName, DWORD aDispo)
    {
        if (NULL == aFileName) { return Maze_ERROR_POINTER; }

        Close();

        assert(INVALID_HANDLE_VALUE == mFile);

        mFile = CreateFile(aFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, aDispo, 0, NULL);
        if (INVALID_HANDLE_VALUE == mFile)
        {
            return Maze_ERROR_FILE_CREATE;
        }

        mMapping = CreateFileMapping(mFile, NULL, PAGE_READWRITE, 0, FILE_SIZE_byte, NULL);
        if (NULL == mMapping)
        {
            // NOT TESTED Maze.Bitmap.Error
            return Maze_ERROR_MAPPING;
        }

        mView = MapViewOfFile(mMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, FILE_SIZE_byte);
        if (NULL == mView)
        {
            // NOT TESTED Maze.Bitmap.Error
            return Maze_ERROR_VIEW;
        }

        InitPointers();

        return Maze_OK;
    }

    Maze_Result Bitmap::ValidateHeaders()
    {
        assert(NULL != mFileHeader);
        assert(NULL != mInfo);

        if (   (FORMAT != mFileHeader->bfType)
            || (1 != mInfo->bmiHeader.biPlanes))
        {
            return Maze_ERROR_FORMAT;
        }

        if (   (Maze_SIZE_Y_pixel != mInfo->bmiHeader.biHeight)
            || (Maze_SIZE_X_pixel != mInfo->bmiHeader.biWidth))
        {
            return Maze_ERROR_SIZE;
        }

        if (   (FILE_HEADERS_byte != mFileHeader->bfOffBits)
            || (FILE_SIZE_byte    != mFileHeader->bfSize)
            || (32                       != mInfo->bmiHeader.biBitCount)
            || (BI_RGB                   != mInfo->bmiHeader.biCompression)
            || (sizeof(BITMAPINFOHEADER) != mInfo->bmiHeader.biSize))
        {
            return Maze_ERROR_BAD;
        }

        return Maze_OK;
    }

}

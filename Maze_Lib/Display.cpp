
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/Display.cpp

// CODE REVIEW 2021-12-19 KMS - Martin Dubois, P. Eng.

// TEST COVERAGE 2021-12-19 KMS - Martin Dubois, P. Eng.

#include "Component.h"

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Protocol.h>
}

#include <Maze/Display.h>

// Constants
// //////////////////////////////////////////////////////////////////////////

#define CLASS_NAME "Maze"

#define INPUT_DEFAULT "Input.bmp"

#define PERIOD_DISABLE (0)

#define PERIOD_DEFAULT_ms (15)

#define PERIOD_MAX_ms (1000)
#define PERIOD_MIN_ms (15)

#define TITLE_DEFAULT "Maze"

#define ZOOM_DEFAULT (4)

#define ZOOM_MAX (4)
#define ZOOM_MIN (1)

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// Remarquez le CALLBACK dans la declaration de la fonction qui sera appele
// par le code de Windows pour demander au programme de traiter les messages
// lie a l'interface utilisateur. Ce CALLBACK est un macro que le
// preprocesseur remplacera par __stdcall (vous pouvez le voir en placant
// votre curseur de sourie dessus dans VisualStudio). Le mot cle __stdcall,
// indique au compilateur d'utiliser la methode de passage de parametre
// definit par le standard du langage C. Si la fonction est declaree dans
// un fichier C, cet indication ne change rien. Cependant, si la fonction
// est declare dans un fichier cpp, comme c'est le cas ici, il faut
// absolument mettre cette indication, sinon la technique de passage des
// parametres ne serait pas compatible avec celle utilise par le code
// Windows qui appellera cette fonction.
static LRESULT CALLBACK WindowProc_Link(HWND, UINT, WPARAM, LPARAM);

namespace Maze
{

    // Public
    // //////////////////////////////////////////////////////////////////////

    Display::Display()
        : mInput(INPUT_DEFAULT)
        , mInstance(GetModuleHandle(NULL))
        , mPeriod_ms(PERIOD_DEFAULT_ms)
        , mTitle(TITLE_DEFAULT)
        , mZoom(ZOOM_DEFAULT)
    {
        assert(NULL != mInstance);

        Class_Register();
        Windows_Create();
    }

    Display::~Display()
    {
        assert(NULL != mInstance);

        BOOL lRet;

        if (NULL != mWindow)
        {
            lRet = DestroyWindow(mWindow);
            assert(lRet);
        }

        lRet = UnregisterClass(CLASS_NAME, mInstance);
        assert(lRet);
    }

    Maze_Result Display::SetInput(const char * aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mInput = aIn;

        return Maze_OK;
    }

    Maze_Result Display::SetPeriod(unsigned int aIn_ms)
    {
        if (PERIOD_DISABLE != aIn_ms)
        {
            if (PERIOD_MIN_ms > aIn_ms) { return Maze_ERROR_MIN; }
            if (PERIOD_MAX_ms < aIn_ms) { return Maze_ERROR_MAX; }
        }

        mPeriod_ms = aIn_ms;

        return Maze_OK;
    }

    Maze_Result Display::SetTitle(const char * aIn)
    {
        if (NULL == aIn) { return Maze_ERROR_POINTER; }

        mTitle = aIn;

        return Maze_OK;
    }

    Maze_Result Display::SetZoom(unsigned int aIn)
    {
        if (ZOOM_MIN > aIn) { return Maze_ERROR_MIN; }
        if (ZOOM_MAX < aIn) { return Maze_ERROR_MAX; }

        mZoom = aIn;

        return Maze_OK;
    }

    Maze_Result Display::Show()
    {
        Maze_Result lResult = mBitmap.Open(mInput.c_str());
        if (Maze_OK == lResult)
        {
            // NOT TESTED Maze.Display
            if (PERIOD_DISABLE != mPeriod_ms)
            {
                UINT_PTR lTimer = SetTimer(mWindow, 1, mPeriod_ms, NULL);
                assert(0 != lTimer);
            }

            Run();
        }

        return lResult;
    }

    // ===== IConfigurable ==================================================

    Maze_Result Display::Property_Set(const char* aName, const char* aValue)
    {
        if ((NULL == aName) || (NULL == aValue)) { return Maze_ERROR_POINTER; }

        if (0 == _stricmp("Input" , aName)) { return SetInput (aValue); }
        if (0 == _stricmp("Period", aName)) { return SetPeriod(aValue); }
        if (0 == _stricmp("Title" , aName)) { return SetTitle (aValue); }
        if (0 == _stricmp("Zoom"  , aName)) { return SetZoom  (aValue); }

        return Maze_OK_IGNORED;
    }

    // Internal
    // //////////////////////////////////////////////////////////////////////

    LRESULT Display::WindowProc(UINT aMsg, WPARAM aParamW, LPARAM aParamL)
    {
        assert(NULL != mWindow);

        LRESULT lResult = 0;

        switch (aMsg)
        {
        case WM_PAINT: lResult = On_WM_PAINT(); break;
        case WM_TIMER: lResult = On_WM_TIMER(); break;

        default: lResult = DefWindowProc(mWindow, aMsg, aParamW, aParamL);
        }

        return lResult;
    }

    // Private
    // //////////////////////////////////////////////////////////////////////

    void Display::Class_Register()
    {
        assert(NULL != mInstance);

        WNDCLASSEX lClass;

        memset(&lClass, 0, sizeof(lClass));

        lClass.cbSize        = sizeof(lClass);
        lClass.cbWndExtra    = sizeof(Display*);
        lClass.hInstance     = mInstance;
        lClass.lpfnWndProc   = WindowProc_Link;
        lClass.lpszClassName = CLASS_NAME;
        lClass.style         = CS_GLOBALCLASS | CS_OWNDC;

        ATOM lAtom = RegisterClassEx(&lClass);
        assert(0 != lAtom);
    }

    LRESULT Display::On_WM_PAINT()
    {
        assert(NULL != mWindow);

        PAINTSTRUCT lPaint;

        HDC lDC = BeginPaint(mWindow, &lPaint);
        {
            Paint(lDC);
        }
        EndPaint(mWindow, &lPaint);

        return 0;
    }

    // NOT TESTED Maze.Display
    LRESULT Display::On_WM_TIMER()
    {
        assert(NULL != mWindow);

        BOOL lRet = InvalidateRect(mWindow, NULL, FALSE);
        assert(lRet);

        return 0;
    }

    void Display::Paint(HDC aDC)
    {
        assert(NULL != aDC);

        assert(ZOOM_MAX >= mZoom);
        assert(ZOOM_MIN <= mZoom);

        const BITMAPINFO* lInfo = mBitmap.GetInfo();
        if (NULL != lInfo)
        {
            BOOL lRet = StretchDIBits(aDC,
                0, 0, Maze_SIZE_X_pixel * mZoom, Maze_SIZE_Y_pixel * mZoom,
                0, 0, Maze_SIZE_X_pixel, Maze_SIZE_Y_pixel,
                lInfo->bmiColors, lInfo, DIB_RGB_COLORS, SRCCOPY);
            assert(lRet);
        }
    }

    // NOT TESTED Maze.Display
    void Display::Run()
    {
        assert(NULL != mWindow);

        MSG lMsg;

        while (IsWindow(mWindow) && 0 < GetMessage(&lMsg, NULL, 0, 0))
        {
            TranslateMessage(&lMsg);
            DispatchMessage(&lMsg);
        }

        if (!IsWindow(mWindow))
        {
            mWindow = NULL;
        }
    }

    Maze_Result Display::SetPeriod(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetPeriod(lIn);
        }

        return lResult;
    }

    Maze_Result Display::SetZoom(const char* aIn)
    {
        unsigned int lIn;

        Maze_Result lResult = ConvertToUInt(aIn, &lIn);
        if (Maze_OK == lResult)
        {
            lResult = SetZoom(lIn);
        }

        return lResult;
    }

    void Display::Windows_Create()
    {
        static const UINT  FLAGS  = SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOZORDER;
        static const DWORD STYLES = WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE;

        assert(NULL != mInstance);
        assert(ZOOM_MAX >= mZoom);
        assert(ZOOM_MIN <= mZoom);

        unsigned int lSizeX_pixel = Maze_SIZE_X_pixel * mZoom;
        unsigned int lSizeY_pixel = Maze_SIZE_Y_pixel * mZoom;

        mWindow = CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, mTitle.c_str(), STYLES,
            CW_USEDEFAULT, CW_USEDEFAULT, lSizeX_pixel, lSizeY_pixel, NULL, NULL, mInstance, NULL);
        assert(NULL != mWindow);

        ULONG_PTR lRet = SetWindowLongPtr(mWindow, 0, reinterpret_cast<ULONG_PTR>(this));
        assert(0 == lRet);

        RECT lRect;

        BOOL lRetB = GetClientRect(mWindow, &lRect);
        assert(lRetB);

        lSizeX_pixel += lSizeX_pixel - (lRect.right - lRect.left + 1);
        lSizeY_pixel += lSizeY_pixel - (lRect.bottom - lRect.top + 1);

        lRetB = SetWindowPos(mWindow, NULL, 0, 0, lSizeX_pixel, lSizeY_pixel, FLAGS);
        assert(lRetB);
    }

}

// Static functions
// //////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProc_Link(HWND aWindow, UINT aMsg, WPARAM aParamW, LPARAM aParamL)
{
    assert(NULL != aWindow);

    LRESULT lResult;

    Maze::Display* lThis = reinterpret_cast<Maze::Display*>(GetWindowLongPtr(aWindow, 0));
    if (NULL != lThis)
    {
        lResult = lThis->WindowProc(aMsg, aParamW, aParamL);
    }
    else
    {
        lResult = DefWindowProc(aWindow, aMsg, aParamW, aParamL);
    }

    return lResult;
}

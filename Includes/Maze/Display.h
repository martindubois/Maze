
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Display
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Display.h

#pragma once

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>
#include <Maze/IConfiguratble.h>

namespace Maze
{

    /// \brief Classe Display
    class Display : public IConfigurable
    {

    public:

        /// \brief Constructeur par defaut
        Display();

        /// \brief Destructeur
        virtual ~Display();

        /// \brief Modifier le nom du fichier a afficher
        /// \param aIn Le nom de fichier
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetInput(const char * aIn);

        /// \brief Modifier le periode d'affichage
        /// \param aIn_ms La periode en ms (La valeur 0 desactive le
        ///               refraichissement automatique)
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        /// \retval Maze_ERROR_MIN
        Maze_Result SetPeriod(unsigned int aIn_ms);

        /// \brief Modifier le titre de la fenetre
        /// \param aIn Le titre
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetTitle(const char * aIn);

        /// \brief Modifier le facteur d'affichage.
        /// \param aIn Le facteur d'affichage
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        /// \retval Maze_ERROR_MIN
        Maze_Result SetZoom(unsigned int aIn);

        /// \brief Afficher
        /// Cette fonction retourne quand la fenetre est ferme par
        /// l'utilisateur.
        /// \retval Maze_OK
        /// \retval Maze_ERROR_BAD
        /// \retval Maze_ERROR_FILE_CREATE
        /// \retval Maze_ERROR_FORMAT
        /// \retval Maze_ERROR_MAPPING
        /// \retval Maze_ERROR_SIZE
        /// \retval Maze_ERROR_VIEW
        virtual Maze_Result Show();

        // ===== IConfigurable ==============================================
        virtual Maze_Result Property_Set(const char * aName, const char * aValue);

    // Internal

        LRESULT WindowProc(UINT aMsg, WPARAM aParamW, LPARAM aParamL);

    private:

        Display(const Display &);

        const Display & operator = (const Display &);

        void Class_Register();

        LRESULT On_WM_PAINT();
        LRESULT On_WM_TIMER();

        void Paint(HDC aDC);

        void Run();

        Maze_Result SetPeriod(const char* aIn);
        Maze_Result SetZoom  (const char* aIn);

        void Windows_Create();

        std::string  mInput;
        unsigned int mPeriod_ms;
        std::string  mTitle;
        unsigned int mZoom;

        Bitmap    mBitmap;
        HINSTANCE mInstance;
        HWND      mWindow;

    };

}

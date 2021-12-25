
// License http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Generator
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Generator.h

#pragma once

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <Maze/IConfiguratble.h>

namespace Maze
{

    class Bitmap;
    class IInfo;

    /// \brief La classe Generator
    class Generator : public IConfigurable
    {

    public:

        /// \brief Destructor
        virtual ~Generator();

        /// \brief Generer un labyrinthe.
        /// \param aInfo L'instance de IInfo
        /// \retval Maze_OK
        /// \retval Maze_ERROR_FILE_CREATE
        /// \retval Maze_ERROR_MAPPING
        /// \retval Maze_ERROR_VIEW
        Maze_Result Generate(IInfo * aInfo);

        /// \brief Modifier la configuration de la methode qui complete un
        ///        labyrinthe contenant un chemin.
        /// \param aIn Une valeur de 0 desactive completement la fonction.
        /// \retval Maze_OK
        Maze_Result SetFill(unsigned int aIn);

        /// \brief Modifier le nom du fichier de sortie
        /// \param aIn Le nom de fichier
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetOutput(const char * aIn);

        /// \brief Modifier la valeur d'initialisation du generateur de
        ///        hasard
        /// \param aIn La nouvelle valeur (la valeur de 0 indiquer d'utiliser
        ///            une valeur automatique)
        /// \retval Maze_OK
        Maze_Result SetSeed(unsigned int aIn);

        /// \brief Modifier le facteur d'affichage
        /// \param aIn La nouvelle valeur (la valeur de 0 indique de ne pas
        ///            afficher)
        /// \retval Maze_OK
        Maze_Result SetZoom(unsigned int aIn);

        // ===== IConfigurable ==============================================
        virtual Maze_Result Property_Set(const char * aName, const char * aValue);

    protected:

        // COMMENTAIRE PEDAGOGIQUE
        // Un constructeur "protected" indique clairement qu'il faut creer
        // une classe derive pour utiliser cette classe.

        /// \brief Contructeur par defaut
        Generator();

        /// \brief Completer un labyrinthe
        /// \param aBitmap Le labyrinthe
        void FillBitmap(Bitmap * aBitmap);

        /// \brief Obtenir un nombre au hasard
        /// \param aMin Valeur minimum
        /// \param aMax Valeur maximum
        /// \return Une valeur entre le minimum et le maximum
        static unsigned int GetRandom(unsigned int aMin, unsigned int aMax);

        /// \brief Generer un labyrinthe
        /// \param aBitmap Le labyrinthe a modifier
        virtual void GenerateBitmap(Bitmap * aBitmap) = 0;

    private:

        Generator(const Generator &);

        const Generator & operator = (const Generator &);

        void Random_Init();

        Maze_Result SetFill_Str(const char* aIn);
        Maze_Result SetSeed_Str(const char* aIn);
        Maze_Result SetZoom_Str(const char* aIn);

        unsigned int mFill;
        std::string  mOutput;
        unsigned int mSeed;
        unsigned int mZoom;

        IInfo * mInfo;

    };

}

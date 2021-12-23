
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Bitmap
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Bitmap.h

#pragma once

// ===== C ==================================================================
#include <stdint.h>

// ===== Windows ============================================================
#include <wingdi.h>

// ===== Includes ===========================================================
#include <Maze/Color.h>
#include <Maze/Position.h>

extern "C"
{
    #include <Maze_Result.h>
}

// COMMENTAIRE PEDAGOGIQUE
// La librairie Maze_Lib pourrait etre utilisee dans des projets qui
// utiliseront d'autres librairies. Une de ces autres librairies pourrait
// declarrer une class Bitmap. L'utilisation de l'espace de nom (namespace)
// evitera les conflit.
namespace Maze
{

    /// \brief Classe Bitmap
    class Bitmap
    {

    public:

        /// \brief Contructeur par defaut
        Bitmap();

        /// \brief Destructeur
        virtual ~Bitmap();

        /// \brief Effacer
        /// \param aColor La couleur
        void Clear(Color aColor);

        /// \brief Fermer le fichier
        void Close();

        /// \brief Compter le nombre de chemin autour d'une position
        /// \param aPos La position
        /// \return Le nombre de chemin autour de la position (0 a 4)
        unsigned int CountTrail(Position aPos) const;

        /// \brief Creer un nouveau fichier bitmap
        /// \param aFileName Le nom du fichier
        /// \param aColor    La couleur pour l'initialisation
        /// \retval Maze_OK
        /// \retval Maze_ERROR_FILE_CREATE
        /// \retval Maze_ERROR_POINTER
        /// \retval Maze_ERROR_MAPPING
        /// \retval Maze_ERROR_VIEW
        Maze_Result Create(const char* aFileName, Color aColor);

        /// \brief Le pixel est t'il de cet couleur ?
        /// \param aPos   La position
        /// \param aColor La couleur
        /// \retval false N'est pas de la couleur specifiee
        /// \retval true  Est de la couleur specifiee
        bool IsPixel(Position aPos, Color aColor) const;

        /// \brief Est une brique ?
        /// \param aPos La position
        /// \retval false N'est pas une brique
        /// \retval true  Est une brique
        bool IsBrick(Position aPos) const;

        /// \brief Est-ce un chemin ?
        /// \param aPos La position
        /// \retval false N'est pas un chemin
        /// \retval true  Est un chemin
        bool IsTrail(Position aPos) const;

        /// \brief Ouvrir un fichier bitmap existant
        /// \param aFileName Le nom du fichier
        /// \retval Maze_OK
        /// \retval Maze_ERROR_BAD
        /// \retval Maze_ERROR_FILE_CREATE
        /// \retval Maze_ERROR_FORMAT
        /// \retval Maze_ERROR_POINTER
        /// \retval Maze_ERROR_MAPPING
        /// \retval Maze_ERROR_SIZE
        /// \retval Maze_ERROR_VIEW
        Maze_Result Open(const char* aFileName);

        /// \brief Changer la couleur d'un pixel
        /// \param aPos   La position
        /// \param aColor La couleur
        void SetPixel(Position aPos, Color aColor);

        /// \brief Changer une composante de la couleur d'un pixel
        /// \param aPos La position
        /// \param aBGR 0 = Blue, 1 = Green, 2 = Red
        /// \param aVal La nouvelle valeure
        void SetPixel(Position aPos, unsigned int aBGR, uint8_t aVal);

    // Internal

        // COMMENTAIRE PEDAGOGIQUE
        // Les methodes dans les section "Interne", meme si elle sont
        // accessible a l'exterieure de la librairie sont concues pour etre
        // utilisees uniquement par d'autres classes de la librairie. Pour
        // cette raison, il n'est pas necessaire de les documenters.
        
        const BITMAPINFO * GetInfo() const;

        void SetPixel(Position aPos, unsigned int aBGR);

    private:

        // COMMENTAIRE PEDAGOGIQUE
        // Les instances de cette class contiennent des pointeurs. Copier
        // binairement une instance causerait la valeur du pointeur a etre
        // copier et deux instance se retrouverais a pointer vers des donnees
        // uniques. Une des instances pourrait alors liberer la memoire et
        // l'autre instance pourrait continuer a les utiliser. Cela causerait
        // de grave ennuies. Les deux lignes qui suivent indique au
        // compilateur C++ de ne pas auto-generer le contructeur par copie ou
        // l'operateur d'assignation. Comme le code ne le definit pas, si un
        // utilisateur de la librairie essaie de s'en servir, l'edition des
        // liens echouera.
        
        Bitmap(const Bitmap &);

        const Bitmap & operator = (const Bitmap &);

        // COMMENTAIRE PEDAGOGIQUE
        // TODO
        const Color* GetPointer(Position aPos) const;

        Color* GetPointer(Position aPos);

        void InitHeaders();
        void InitPointers();

        Maze_Result Map(const char * aFileName, DWORD aDispo);

        Maze_Result ValidateHeaders();

        HANDLE             mFile;
        BITMAPFILEHEADER * mFileHeader;
        BITMAPINFO       * mInfo;
        HANDLE             mMapping;
        void             * mView;

    };

}


// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Position
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Position.h

#pragma once

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Protocol.h>
}

namespace Maze
{

    /// \brief Classe Position
    class Position
    {

    public:

        static const Position END;

        /// \brief Consutrcteur par defaut
        Position();

        /// \brief Constructeur
        /// \param aX_pixel X
        /// \param aY_pixel Y
        Position(uint16_t aX_pixel, uint16_t aY_pixel);

        /// \brief Operateur de comparaison
        /// \param aB La seconde valeure
        /// \retval false Les 2 positions sont identiques
        /// \retval true  Les 2 positions sont differentes
        bool operator == (const Position & aB) const;

        /// \brief Operateur de comparaison
        /// \param aB La seconde valeure
        /// \retval false Les 2 positions sont identiques
        /// \retval true  Les 2 positions sond differentes
        bool operator != (const Position& aB) const;

        /// \brief Obtenir la position d'un voisin
        /// \param aDir Voir Maze_DIR_...
        /// \param aOut Sortie
        /// \retval false La position demandee n'existe pas
        /// \retval true  OK
        bool GetNeighbor(unsigned int aDir, Position*aOut);

        /// \brief Obtenir la position a l'est
        /// \param aOut Sortie
        /// \retval false La position demandee n'existe pas
        /// \retval true  OK
        bool GetEast(Position* aOut) const;

        /// \brief Obtenir la position au nord
        /// \param aOut Sortie
        /// \retval false La position demandee n'existe pas
        /// \retval true  OK
        bool GetNorth(Position* aOut) const;

        /// \brief Obtenir la position au sud
        /// \param aOut Sortie
        /// \retval false La position demandee n'existe pas
        /// \retval true  OK
        bool GetSouth(Position* aOut) const;

        /// \brief Obtenir la position a l'ouest
        /// \param aOut Sortie
        /// \retval false La position demandee n'existe pas
        /// \retval true  OK
        bool GetWest(Position* aOut) const;

        /// \brief Obtenir X
        /// \return La coordonnee X
        uint16_t GetX() const;

        /// \brief Obtenir Y
        /// \return La coordonnee Y
        uint16_t GetY() const;

        /// \brief Deplacer
        /// \param aDir        Voir Maze_DIR_...
        /// \param aDist_pixel La distance
        /// \retval false
        /// \retval true
        bool Go_Direction(unsigned int aDir, int aDist_pixel = 1);

        /// \brief Deplacer
        /// \param aXY         0 = deplacement en X, 1 = deplacement en Y.
        /// \param aDist_pixel La distance
        /// \retval false
        /// \retval true
        bool Go_XY(unsigned int aXY, int aDist_pixel);

        /// \brief Deplacer la position vers la destination
        /// \param aXY   0 = deplacement en X, 1 = deplacement en Y.
        /// \param aDest Destination
        void Go_XY_Destination(unsigned int aXY, Position aDest);

        /// \brief Deplacer vers l'est
        /// \param aDist_pixel La distance
        /// \retval false Impossible
        /// \retval true  OK
        bool GoEast(int aDist_pixel = 1);

        /// \brief Deplacer vers le nord
        /// \param aDist_pixel La distance
        /// \retval false Impossible
        /// \retval true  OK
        bool GoNorth(int aDist_pixel = 1);

        /// \brief Deplacer vers le sud
        /// \param aDist_pixel La distance
        /// \retval false Impossible
        /// \retval true  OK
        bool GoSouth(int aDist_pixel = 1);

        /// \brief Deplacer vers l'ouest
        /// \param aDist_pixel La distance
        /// \retval false Impossible
        /// \retval true  OK
        bool GoWest(int aDist_pixel = 1);

        /// \brief Deplacer vers la destination
        /// \param aDestX_pixel Destination
        void GoX_Destination(uint16_t aDestX_pixel);

        /// \brief Deplacer vers la destination
        /// \param aDestY_pixel Destination
        void GoY_Destination(uint16_t aDestY_pixel);

        /// \brief Modifier la position
        /// \param aX_pixel X
        /// \param aY_pixel Y
        void Set(uint16_t aX_pixel, uint16_t aY_pixel);

    // Internal

        unsigned int GetIndex() const;

    private:

        void Go_XY_Destination(unsigned int aXY, uint16_t aDest);

        uint16_t mXY_pixel[2];

    };

}

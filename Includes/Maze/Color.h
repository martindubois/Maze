
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Color
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Color.h

#pragma once

// ===== C ==================================================================
#include <stdint.h>

namespace Maze
{

    /// \brief Classe Color
    class Color
    {

    public:

        static const Color BLACK;
        static const Color BRICK;
        static const Color GRAY;
        static const Color RED;
        static const Color TRAIL;
        static const Color UNKNOWN;

        /// \brief Contructeur par defaut
        Color();

        /// \brief Contructeur
        /// \param aR
        /// \param aG
        /// \param aB
        Color(uint8_t aR, uint8_t aG, uint8_t aB);

        /// \brief Operateur de comparaison
        /// \param aB
        /// \retval false Les s couleurs ne sont pas identiques
        /// \retval true  Les 2 couleurs sont identiques
        bool operator == (const Color & aB) const;

        /// \retval La composante Alpha
        uint8_t GetA() const;

        /// \retval La composante Bleu
        uint8_t GetB() const;

        /// \retval La composante Verte
        uint8_t GetG() const;

        /// \retval La composante Rouge
        uint8_t GetR() const;

        /// \param aRGB
        /// \param aVal
        void Set(unsigned int aRGB, uint8_t aVal);

    private:

        // COMMENTAIRE PEDAGOGIQUE
        // Cette classe ne contient pas de pointeur. Il est donc acceptable
        // de la copier binairement. C'est pour cette raison que le
        // contructeur par copie et l'operateur d'assignation ne sont pas
        // desactives ici.

        uint8_t mBGRA[4];

    };

}


// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Interface IInfo
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/IInfo.h

#pragma once

// ===== C ==================================================================
#include <stdint.h>

// ===== Includes ===========================================================
#include <Maze/Race.h>

namespace Maze
{

    class Stats;

    // Brief Interface IInfo
    class IInfo
    {

    public:

        /// \brief Afficher le progres
        virtual void DisplayProgress() = 0;

        /// \brief Terminer une operation
        /// \param aEnd Message de fin de l'operation
        virtual void DisplayProgress_End(const char* aEnd = NULL) = 0;

        /// \brief Debuter une operation
        /// \param aStart Message de depart de l'operation
        virtual void DisplayProgress_Start(const char* aStart = NULL) = 0;

        /// \brief Afficher la course
        /// \param aMode Voir Race::Mode
        virtual void DisplayRace(Race::Mode aMode) = 0;

        /// \brief Afficher l'information sur un courreur
        /// \param aIndex L'index du courreur
        /// \param aName Le nom du courreur
        /// \param aIPv4 L'adresse du courreur
        virtual void DisplayRunner(unsigned int aIndex, const char * aName, uint32_t aIPv4) = 0;

        /// \brief Afficher le depart de la course
        virtual void DisplayStart() = 0;

        /// \brief Afficher le port TCP
        /// \param aTcpPort Le numero de port
        virtual void DisplayTcpPort(uint16_t aTcpPort) = 0;

        /// \brief Afficher un gagnant
        /// \param aIndex L'index du courreur
        /// \param aName  Le nom du courreur
        /// \param aStats Les statistique
        virtual void DisplayWinner(unsigned int aIndex, const char* aName, const Stats& aStats) = 0;

    };

}

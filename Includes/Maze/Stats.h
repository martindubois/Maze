
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Stats
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Stats.h

#pragma once

namespace Maze
{

    // Brief Classe Stats
    class Stats
    {

    public:

        /// \brief Constructeur
        Stats();

        /// \brief Optenir le nombre de mesures
        unsigned int GetMeasurments() const;

        /// \brief Optenir le nombre de deplacement
        unsigned int GetMoves() const;

        /// \brief Obtenir le nombre de requetes
        unsigned int GetRequests() const;

    // Internal

        void IncMeasurments();
        void IncMoves      ();
        void IncRequests   ();

    private:

        unsigned int mMeasurments;
        unsigned int mMoves;
        unsigned int mRequests;

    };

}

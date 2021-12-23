
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Info_None
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Info_None.h

#pragma once

// ===== Includes ===========================================================
#include <Maze/IInfo.h>

namespace Maze
{

    // Brief Class Info_None
    class Info_None : public IInfo
    {

    public:

        // ===== IInfo ======================================================

        virtual void DisplayProgress();
        virtual void DisplayProgress_End  (const char* aEnd);
        virtual void DisplayProgress_Start(const char* aStart);

        virtual void DisplayRace   (Race::Mode aMode);
        virtual void DisplayRunner (unsigned int aIndex, const char * aName, uint32_t aIPv4);
        virtual void DisplayStart  ();
        virtual void DisplayTcpPort(uint16_t aTcpPort);
        virtual void DisplayWinner (unsigned int aIndex, const char * aName, const Stats & aStats);

    };

}

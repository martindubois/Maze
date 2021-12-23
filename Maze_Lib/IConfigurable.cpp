
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2021 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze
// File      Maze_Lib/IConfigurable.cpp

#include "Component.h"

// ===== Includes ===========================================================
#include <Maze/IConfiguratble.h>

namespace Maze
{

    // Protected
    // //////////////////////////////////////////////////////////////////////

    Maze_Result IConfigurable::ConvertToUInt(const char * aIn, unsigned int * aOut)
    {
        if ((NULL == aIn) || (NULL == aOut)) { return Maze_ERROR_POINTER; }

        char* lEnd;

        *aOut = strtoul(aIn, &lEnd, 10);
        
        return (aIn == lEnd) ? Maze_ERROR_INVALID : Maze_OK;
    }

    // Functions
    // //////////////////////////////////////////////////////////////////////

    Maze_Result Configurable_Parse(IConfigurable* aInstance, const char** aNameValue, unsigned int aCount)
    {
        Maze_Result lResult = Maze_OK;

        for (unsigned int i = 0; i < aCount; i++)
        {
            char lName[1024];
            char lValue[1024];

            if (2 == sscanf_s(aNameValue[i], "%[A-Za-z0-9_] = %[^\n\r\t]", lName, sizeof(lName), lValue, sizeof(lValue)))
            {
                lResult = aInstance->Property_Set(lName, lValue);
                if (!Maze_Result_IsOK(lResult))
                {
                    break;
                }
            }
        }

        return lResult;
    }

}

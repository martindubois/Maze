
// Product Maze

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/IConfigurable.h
/// \brief     Interface IConfigurable

#pragma once

// ===== Includes ===========================================================
#include <Maze_Result.h>

namespace Maze
{

    /// \brief L'interface IConfiguration
    class IConfigurable
    {

    public:

        /// \brief Modifier la valeur d'une propriete
        /// \param aName   Nom de la propriete
        /// \param aValue  La nouvelle valeur de la propriete
        /// \retval MAZE_OK
        virtual Maze_Result Property_Set(const char * aName, const char * aValue) = 0;

    };

    /// \brief Interpreter une liste d'assignation
    /// \param aInstance   L'instance de IConfigurable
    /// \param aNameValue  La liste d'assignation
    /// \param aCount      Le nom d'assignation dans la liste
    /// \retval MAZE_OK
    extern Maze_Result Configurable_Parse(IConfigurable * aInstance, const char ** aNameValue, unsigned int aCount);

}

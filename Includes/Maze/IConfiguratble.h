
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Interface IConfigurable
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/IConfigurable.h

#pragma once

// ===== Includes ===========================================================
extern "C"
{
    #include <Maze_Result.h>
}

namespace Maze
{

    /// \brief Interface IConfiguration
    class IConfigurable
    {

    public:

        /// \brief Modifier la valeur d'une propriete
        /// \param aName   Nom de la propriete
        /// \param aValue  La nouvelle valeur de la propriete
        /// \retval Maze_OK
        /// \retval Maze_OK_IGNORED
        virtual Maze_Result Property_Set(const char * aName, const char * aValue) = 0;

    protected:

        /// \brief Convertir une chaine de caractere en entier non signe
        /// \param aIn
        /// \param aOut
        /// \retval Maze_OK
        /// \retval Maze_ERROR_INVALID
        /// \retval Maze_ERROR_POINTER
        static Maze_Result ConvertToUInt(const char * aIn, unsigned int * aOut);

    };

    /// \brief Interpreter une liste d'assignation
    /// \param aInstance   L'instance de IConfigurable
    /// \param aNameValue  La liste d'assignation
    /// \param aCount      Le nom d'assignation dans la liste
    /// \retval Maze_OK
    /// \retval Maze_OK_IGNORED
    /// \retval Maze_ERROR_POINTER
    extern Maze_Result Configurable_Parse(IConfigurable * aInstance, const char ** aNameValue, unsigned int aCount);

}

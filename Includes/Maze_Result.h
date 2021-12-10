
// Product Maze

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze_Result.h
/// \brief     Valeur de retour des fonctions et methodes

#pragma once

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Resultat de fonctions ou de methode
typedef enum
{
    MAZE_OK,
    MAZE_OK_IGNORED,
    MAZE_OK_QTY,

    MAZE_ERROR_INVALID = 0x0100,
    MAZE_ERROR_QTY,

    MAZE_RESULT_INVALID = 0xfff0,
    MAZE_RESULT_TODO,
}
Maze_Result;

// Functions
// //////////////////////////////////////////////////////////////////////////

/// \param aIn  La valeur a convertir en chaine de caractere
/// \retval NULL   La valeur de aIn n'est pas un valeur valide.
/// \retval Autre  L'adresse d'une chaine de caractere constante qui
///                correpond au nom de la valeur
extern const char * Maze_Result_GetName(Maze_Result aIn);

/// \param aIn   La valeur a verifier
/// \param true  La valeur correspond a un success de l'operation
/// \param false La valeur correspond a un echec de l'operation
extern bool Maze_Result_IsOK(Maze_Result aIn);

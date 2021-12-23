
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze_Result.h
/// \brief     Valeur de retour des fonctions et methodes

#pragma once

// Data types
// //////////////////////////////////////////////////////////////////////////

/// \brief Resultat de fonctions ou de methode
typedef enum
{
    Maze_OK,
    Maze_OK_IGNORED,
    Maze_OK_QTY,

    Maze_ERROR_BAD = 0x0100,
    Maze_ERROR_BITMAP,
    Maze_ERROR_DIRECTION,
    Maze_ERROR_ENUM,
    Maze_ERROR_EXCEPTION,
    Maze_ERROR_FORMAT,
    Maze_ERROR_FILE_CREATE,
    Maze_ERROR_FILE_COPY,
    Maze_ERROR_GENERATOR,
    Maze_ERROR_INVALID,
    Maze_ERROR_MAPPING,
    Maze_ERROR_MAX,
    Maze_ERROR_MIN,
    Maze_ERROR_POINTER,
    Maze_ERROR_PROCESS,
    Maze_ERROR_PROTOCOL,
    Maze_ERROR_PROTOCOL_CONNECT,
    Maze_ERROR_PROTOCOL_REQUEST,
    Maze_ERROR_SIZE,
    Maze_ERROR_SOCKET,
    Maze_ERROR_SOCKET_ACCEPT,
    Maze_ERROR_SOCKET_BIND,
    Maze_ERROR_SOCKET_CONNECT,
    Maze_ERROR_SOCKET_LISTEN,
    Maze_ERROR_SOCKET_RECEIVE,
    Maze_ERROR_SOCKET_SEND,
    Maze_ERROR_VIEW,
    Maze_ERROR_QTY,

    Maze_RESULT_INVALID = 0xfff0,
    Maze_RESULT_TODO,
}
Maze_Result;

// Functions
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// L'utilisation d'une fonction inline permet a un fichier C qui inclus ce
// fichier entete d'utilise la fonction sans avoir a utilier de librairie.

/// \brief Le resultat correspond-il a un success ?
/// \param aIn   La valeur a verifier
/// \param true  La valeur correspond a un success de l'operation
/// \param false La valeur correspond a un echec de l'operation
inline bool Maze_Result_IsOK(Maze_Result aIn)
{
    return (Maze_OK_QTY > aIn);
}


    Author    KMS - Martin Dubois, P. Eng.
    Copyright (C) 2021 KMS
    License   http://www.apache.org/licenses/LICENSE-2.0
    Product   Maze
    File      README.md

Le projet Maze est conçu pour demontrer de nombreux aspect de la
programmation avancee en C++.

    ===== List des concepts démontrés =======================================

    - Convention de passage des parametres
    - Definition de types
    - Doxygen
    - Enumeration
    - Initialisation d'entier avec des caracteres ASCII
    - Interface
    - Mot cle - C
        - enum
        - extern
        - static
        - struct
    - Mot cle - C++
        - class
        - namespace
        - virtual
    - Namespace
    - Operateurs
        - Decalage a gauche (<<)
    - Preprocesseur
        - #pragma once
        - Definition de constantes et utilisation
        - Inclusion de fichier d'entete standard
    - Representation des donnees en memoire
        - Alignement
    - Structures
    - Types entier standard
    - Vecteur de type simple a une dimenssion

    ===== Les composants ====================================================

    Maze_Gen0
    - Properties
        Output      Nom du fichier .bmp
        Seed        Valeur entre 0 et 2^32-1. La valeur par defaut est
                    time(NULL).
        Zoom        Valeur entre 0 et 6 - La valeur de 0 indique de ne pas
                    afficher. La valeur est passee a Maze_Show si elle est
                    presente.

    Maze_Run0
    - Properties
        IPv4        Adresse IPv4
        Name        Nom du courreur
        TcpPort     Port TCP
        Zoom        Valeur entre 0 et 6 - La valeur de 0 indique de ne pas
                    afficher. La valeur est passee a Maze_Show si elle est
                    presente.

    Maze_Race
    - Properties
        Generator   Le nom du programme de generation de labyrinthe.
        Mode        Measure|Request|Step|Thread
        Runner      Valeur entre 1 et 3 indiquant le nombre de courreurs.
        Seed        Valeur entre 0 et 2^32-1 passee au programme de
                    generation si presente.
        Slow        Nombre de ms pour se deplacer d'une case.
        Zoom        Valeur entre 0 et 6 - La valeur de 0 indique de ne pas
                    afficher. La valeur est passee a Maze_Show si elle est
                    presente.

    Maze_Show
    - Properties
        Input       Nom du fichier .bmp
        Zoom        Valeur de 1 a 6 - La valeur par defaut est 3.

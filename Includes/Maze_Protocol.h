
// Product Maze

/// \author    KMS - Martin Dubois, P.Eng.
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze_Protocol.h
/// \brief     Protocol de communication

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Debutez toujours vos fichiers entete par la ligne qui suit ce commentaire.
// Cette commande indique au preprocesseur de n'inclure ce fichier entete
// qu'une seule fois meme s'il est demande de l'inclure plus d'une fois. Cela
// evitera des erreurs de compilation si un fichier inclus un fichier entete
// alors qu'un autre fichier inclus a deja inclus ce meme fichier entete
// avant.
#pragma once

// COMMENTAIRE PEDAGOGIQUE
// Comme ce fichier definit un protocole de communication, nous avons choisi
// de n'utiliser que le langage C dans ce fichier entete. Il sera donc
// possible de coder un client ou un serveur en langage C on dans un autre
// langage qui supporte certaines interactions avec le langage C.

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Utilisez toujours le meme ordre pour inclure les fichiers d'entete.
// Commencez par inclure les fichiers les plus generaux et terminez en
// incluant les fichiers les plus specifique au projet. Plus precisement:
// 1. Les fichiers d'entete de la librairie C
// 2. Les fichiers d'entete de la librairie C++
// 3. Les fichiers d'entete des librairies externe utilisees par le produit.
// 4. Les fichiers d'entete des librairies externe utilisees par le
//    composant.
// 5. Les fichiers d'entete du produit.
// 6. Les fichiers d'entete publiques du composant.
// 7. Les fichiers d'entete prives du composant.
// Cet ordre suit l'ordre dependance normale. Par exemple, il est normale
// qu'un fichier entete definit dans un composant depende sur les fichiers
// d'entete d'une librairie externe. Au contraire, un fichier d'entete d'un
// produit ne doit jamais dependre d'un fichier d'entete prive d'un
// composant.
// TODO Deplacer ce commentaire pedagogique a un endroit plus approprie.

// ===== C ==================================================================

// COMMENTAIRE PEDAGOGIQUE
// Il faut toujours inclure les fichiers d'entete de la librairie C en
// utilisant les <>. L'utilisation des <> indique au preprocesseur de
// chercher dans les repertoires du systeme avant de chercher dans le
// repertoire courrant. Cela evite d'inclure par accident un fichier du
// repertoire courrant alors que nous desirions inclure un fichier d'entete
// de la librairie C.
#include <stdint.h>

// Constants
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Limitez la longueur des lignes de commentaire.

// La premiere chose que le client envoie suite a la connexion est une des
// deux chaine suivante pour indiquer le mode de communication.
#define MAZE_ASCII  "ASCII\n"
#define MAZE_BINARY "BINARY"

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Quand vous utilisez le preprocesseur pour definir une constante numerique,
// placer toujours la valeur entre parenthese. Ainsi, cette valeur ne pourra
// pas etre concatene avec autre chose par erreur lors de l'utilisation. Par
// exemple, MAZE_DIR_EAST.0 serait une valeur en virgule flotante valide
// si la definition ne contient pas de parenthese (1.0) mais provoquera une
// erreur de compilation si la definition contient des parenthese ((1).0).
#define MAZE_DIR_NORTH (0)
#define MAZE_DIR_EAST  (1)
#define MAZE_DIR_SOUTH (2)
#define MAZE_DIR_WEST  (3)

#define MAZE_DIR_QTY (4)

#define MAZE_DIR_NORTH_BIT (1 << MAZE_DIR_NORTH)
#define MAZE_DIR_EAST_BIT  (1 << MAZE_DIR_EAST)
#define MAZE_DIR_SOUTH_BIY (1 << MAZE_DIR_SOUTH)
#define MAZE_DIR_WEST_BIT  (1 << MAZE_DIR_WEST)

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Utilisez un sufix pour indiquer l'unite de mesure d'une valeur. Ici,
// "_step" indique que la valeur est en pas.
#define MAXE_END_X_step (255)
#define MAXE_END_Y_step (255)

#define MAZE_SIZE_X_step (256)
#define MAZE_SIZE_Y_step (256)

#define MAZE_START_X_step (0)
#define MAXE_START_Y_step (0)

// ASCII protocol
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// Les protocoles ASCII ont ete tres populaire pendant longtemps et certains
// sont toujours grandement utilisee (HTTP, POP3, SMTP...) de nos jours. Ils
// ont l'avantage d'etre completement independant de l'architecture du
// processeur.

// Connect - 1 line
// {Name}
// - La longueur maximum du nom est de 31 octets. Si le nom est plus long,
//   le serveur ignore simplement ce qui depasse.

// Request - 1 line
// {NORTH|EAST|SOUTH|WEST} {Distance_step} {MeasureBitField}

// Response - 1 line
// {NORTH|EAST|SOUTH|WEST} {Distance_step} {DataNorth_step} {DataEast_step} {DataSouth_step} {DataWest_step}

// Binary protocol
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// Quand une structure de donnees est utilise pour un protocole de
// communication binaire, il est possible qu'elle doivent etre echange entre
// des ordinateur avec des architectures de processeur differentes. Il est
// alors dangereux d'utiliser des type de donnees dont la taille change d'une
// architecture a une autre telque : int, long, short... Il est alors
// recommande d'utiliser les types entier de taille specifique que la
// librairie c definit : int8_t, int16_t, int32_t, int64_t.

// COMMENTAIRE PEDAGOGIQUE
// Quand une structure de donnees est utilise pour un protocole de
// communication binaire, il faut absolument qu'elle soit naturellement
// aligne sur toutes les architectures de processeur ou elle sera utilisé.

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Quand une structure de donnees est utilise pour un protocole de
// communication binaire, il est bien de prevoire des champs reserves. Ces
// champs doivent etre initialise a zero par celui qui envoie les donnees et
// simplement ignore par celui qui les recoit. Si dans le future, nous devons
// transmettre une informations supplementaire, nous pourrons la placer dans
// un de ces champs. Les versions du logiciel qui ne connaisse pas cette
// informaton l'ignorerons et les version de logiciel qui la connaisse la
// traiterons. Naturellement, une valeur de 0 pour cette nouvelle information
// doit alors indique que la source des donnees ne connais pas cette nouvelle
// information. De plus, l'ajout de ces champs reserves facilite grandement
// la creation d'une structure naturellement aligne.

// COMMENTAIRE PEDAGOGIQUE - Bonne pratique
// Si une valeur ne peut pas etre negative, il est intressante d'utiliser un
// type de donnees "unsigned" pour la variable. Cela indique clairement aux
// autres programmeurs que la valeur doit etre positive. Cela l'indique aussi
// au compilateur qui dans plusieurs situation peut ameliorer l'optimisation
// fine du code genere grace a cette information supplementaire.

typedef struct
{
    char mName[32];

    uint8_t mReserved[32];
}
Maze_Connect;

typedef struct 
{
    uint8_t mDirection;
    uint8_t mDistance_step;
    uint8_t mMeasures;

    uint8_t mReserved0[13];
}
Maze_Request;

typedef struct
{
    uint8_t mDirection;
    uint8_t mDistance_step;
    uint8_t mMeasures;

    uint8_t mReserved0[2];

    uint8_t mData[MAZE_DIR_QTY];

    uint8_t mReserved0[8];
}
Maze_Response;

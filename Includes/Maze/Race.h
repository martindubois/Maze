
// License http://www.apache.org/licenses/LICENSE-2.0
// Product Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Race
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Race.h

#pragma once

// ===== C++ ================================================================
#include <list>
#include <string>

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>
#include <Maze/IConfiguratble.h>

// ===== Maze_Lib ===========================================================
class Interface;

namespace Maze
{

    class IInfo;

    /// \brief Classe Race
    class Race : public IConfigurable
    {

    public:

        /// \brief Le mode de la course
        typedef enum
        {
            MODE_MEASUREMENT,
            MODE_MOVE,
            MODE_REQUEST,
            MODE_THREAD,

            MODE_QTY
        }
        Mode;

        /// \brief Constructeur par defaut
        Race();

        /// \brief Destructeur
        virtual ~Race();

        /// \brief Modifier le nom du generateur de labyrinthe
        /// \param aIn Le nom (si le nom ne contient pas d'information de
        ///            dossier, il est assume se trouver dans le meme
        ///            repertoire que Maze_Race.exe)
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetGenerator(const char * aIn);

        /// \brief Modifier le nom du labyrinthe
        /// \param aIn Le nom du fichier .bmp
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetMazeName(const char * aIn);

        /// \brief Modifier le mode de la course
        /// \param aIn Voir Mode
        /// \retval Maze_OK
        /// \retval Maze_ERROR_ENUM
        Maze_Result SetMode(Mode aIn);

        /// \brief Modifier le nombre de courreur
        /// \param aIn Le nombre de courreur
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        /// \retval Maze_ERROR_MIN
        Maze_Result SetRunnerCount(unsigned int aIn);

        /// \brief Modifier le seed tu generateur de pseudo nombre aleatoire
        /// \param aIn La valeur 0 indique d'utiliser la fonction time pour
        ///            obtenir le seed.
        /// \retval Maze_OK
        Maze_Result SetSeed(unsigned int aIn);

        /// \brief Modifier le delai de deplacement
        /// \param aIn Le nombre de ms pous se deplacer d'un pixel
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        Maze_Result SetSlow(unsigned int aIn_ms);

        /// \brief Modifier le port TCP
        /// \param aIn 0 indique d'utiliser une numero de port automatique
        /// \retval Maze_OK
        Maze_Result SetTcpPort(uint16_t aIn);

        /// \brief Modifier le facteur d'affichage
        /// \param aIn La valeur 0 indique de ne pas afficher.
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        Maze_Result SetZoom(unsigned int aIn);

        /// \brief Faire la course
        /// \param aInfo L'instance de IInfo
        /// \retval Maze_OK
        Maze_Result Start(IInfo * aInfo);

        // ===== IConfigurable ==============================================
        virtual Maze_Result Property_Set(const char * aName, const char * aValue);

    private:

        typedef std::list<Interface*> InterfaceList;

        Race(const Race &);

        const Race & operator = (const Race &);

        void Connect(SOCKET aSocket, uint32_t aIPv4);

        void DisplayTcpPort(SOCKET aSocket);
        void DisplayRunner (Interface *aInterface);
        void DisplayStart  ();
        void DisplayWinner (Interface *aInterface);

        void Maze_Generate();
        void Maze_Prepare ();

        void Run();

        void Run_Measurement();
        void Run_Move       ();
        void Run_Request    ();
        void Run_Thread     ();

        Maze_Result SetMode_Str       (const char * aIn);
        Maze_Result SetRunnerCount_Str(const char * aIn);
        Maze_Result SetSeed_Str       (const char * aIn);
        Maze_Result SetSlow_Str       (const char * aIn);
        Maze_Result SetTcpPort_Str    (const char * aIn);
        Maze_Result SetZoom_Str       (const char * aIn);

        SOCKET Socket_Create();

        std::string  mGenerator;
        std::string  mMazeName;
        unsigned int mMode;
        unsigned int mRunnerCount;
        unsigned int mSeed;
        unsigned int mSlow_ms;
        uint16_t     mTcpPort;
        unsigned int mZoom;

        Bitmap        mBitmap;
        IInfo       * mInfo;
        InterfaceList mInterfaces;
        char          mProfile[1024];

    };

}

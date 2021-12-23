
// License http://www.apache.org/licenses/LICENSE-2.0
// Product   Maze

/// \author    KMS - Martin Dubois, P. Eng.
/// \brief     Classe Runner
/// \copyright Copyright &copy; 2021 KMS
/// \file      Includes/Maze/Runner.h

#pragma once

// ===== C++ ================================================================
#include <string>

// ===== Includes ===========================================================
#include <Maze/Bitmap.h>
#include <Maze/IConfiguratble.h>

namespace Maze
{

    class Bitmap;

    /// \brief La classe Runner
    class Runner : public IConfigurable
    {

    public:

        /// \brief Destructeur
        virtual ~Runner();

        /// \brief Modifier la main
        /// \param aIn 0 = gauche, 1 = droite
        /// \retval Maze_OK
        /// \retval Maze_ERROR_MAX
        Maze_Result SetHand(unsigned int aIn);

        /// \brief Modifier l'adresse du serveur
        /// \param aIn L'adresse du serveur
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetIPv4(const char* aIn);

        /// \brief Modifier le nom du courreur
        /// \param aIn Le nom du courreur
        /// \retval Maze_OK
        /// \retval Maze_ERROR_POINTER
        Maze_Result SetName(const char *aIn);

        /// \brief Modifier le port du serveur
        /// \param aIn Le port (ordre des octets est celui de l'ordinateur)
        /// \retval Maze_OK
        /// \retval Maze_ERROR_INVALID
        Maze_Result SetTcpPort(uint16_t aIn);

        /// \brief Modifier le facteur d'affichage
        /// \param aIn La nouvelle valeur (la valeur de 0 indique de ne pas
        ///            afficher)
        /// \retval Maze_OK
        Maze_Result SetZoom(unsigned int aIn);

        /// \brief Generer un labyrinthe.
        /// \retval Maze_OK
        Maze_Result Start();

        // ===== IConfigurable ==============================================
        virtual Maze_Result Property_Set(const char * aName, const char * aValue);

    protected:

        /// \brief Contructeur par defaut
        Runner();

        /// \brief Utilise une main
        /// \param aResponse La reponse
        void Iteration_Hand(Maze_Response * aResponse);

        /// \brief Utilise la main gauche
        /// \param aResponse La reponse
        void Iteration_Hand_Left(Maze_Response * aResponse);

        /// \brief Utilise la main droit
        /// \param aResponse La reponse
        void Iteration_Hand_Right(Maze_Response * aResponse);

        /// \brief Envoyer une requete et traiter la reponse
        /// \param aDirection      Voir Maze_DIR_...
        /// \param aDistance_pixel La distance de deplacement
        /// \param aMeasures       Voir Maze_DIR_..._BIT
        /// \param aResponse       La reponse
        /// \retval Maze_OK
        Maze_Result Request(uint8_t aDirection, uint8_t aDistance_pixel, uint8_t aMeasures, Maze_Response * aResponse);

        /// \brief Parcourir le labyrinthe
        /// \retval Maze_OK
        virtual Maze_Result Run() = 0;

        Bitmap       mBitmap;
        unsigned int mDirection;
        Position     mPosition;

    private:

        void Connect();
        void Receive(void* aOut, int aSize_byte);
        void Send(const void * aIn, int aSize_byte);

        Maze_Result SetHand   (const char* aIn);
        Maze_Result SetTcpPort(const char* aIn);
        Maze_Result SetZoom   (const char* aIn);

        unsigned int mHand;
        uint32_t     mIPv4;
        std::string  mName;
        uint16_t     mTcpPort;
        unsigned int mZoom;

        char   mProfile[1024];
        SOCKET mSocket;

    };

}

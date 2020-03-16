/*****************************************************************************************************************
* Copyright (C) 2019 by Matthias Birnthaler                                                                      *
*                                                                                                                *
* This file is part of the TribeSlotCooldown Plugin for Ark Server API                                           *
*                                                                                                                *
*    This program is free software : you can redistribute it and/or modify                                       *
*    it under the terms of the GNU General Public License as published by                                        *
*    the Free Software Foundation, either version 3 of the License, or                                           *
*    (at your option) any later version.                                                                         *
*                                                                                                                *
*    This program is distributed in the hope that it will be useful,                                             *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of                                              *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the                                                 *
*    GNU General Public License for more details.                                                                *
*                                                                                                                *
*    You should have received a copy of the GNU General Public License                                           *
*    along with this program.If not, see <https://www.gnu.org/licenses/>.                                        *
*                                                                                                                *
*****************************************************************************************************************/

/**
* \file Commands.cpp
* \author Matthias Birnthaler Matthias-Birnthaler@outlook.com
* \date 15 May 2019
* \brief Implementation of all Commands 
*
*/

/* ================================================ [includes] ================================================ */

#include "Commands.h"
#include <sstream>
#include <string>




namespace Commands
{
    /* ============================================ [type definitions] ============================================ */

	static void RconCloseCloud(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*);
	static void RconOpenCloud(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*);
	static void ConsoleCloseCloud(APlayerController* player, FString* cmd, bool boolean);
	static void ConsoleOpenCloud(APlayerController* player, FString* cmd, bool boolean);

    /* ===================================== [prototype of local functions] ======================================= */


    static void InitRconCommands(void);
    static void RemoveRconCommands(void);
    static void InitConsoleCommands(void);
    static void RemoveConsoleCommands(void);
    static void InitChatCommands(void);
    static void RemoveChatCommands(void);

    /* ===================================== [definition of local functions] ====================================== */


	/**
	* \brief Rcon command: RconCloseCloud
	*
	* This command returns the slots that are on cooldown of a given player(steamId)
	*
	* \param[in] rcon_connection caller of the command
	* \param[in] rcon_packet rcon data
	* \param[in] UWorld, variable not used
	* \return void
	*/
	static void CloseCloud(bool close)
	{
		AShooterGameMode* game_mode = ArkApi::GetApiUtils().GetShooterGameMode();

		game_mode->PreventDownloadDinosField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventDownloadDinosField() = close;

		game_mode->PreventDownloadItemsField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventDownloadItemsField() = close;

		game_mode->PreventDownloadSurvivorsField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventDownloadSurvivorsField() = close;

		game_mode->bPreventUploadDinosField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventUploadDinosField() = close;

		game_mode->bPreventUploadItemsField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventUploadItemsField() = close;

		game_mode->bPreventUploadSurvivorsField() = close;
		static_cast<AShooterGameState*>(game_mode->GameStateField())->bPreventUploadSurvivorsField() = close;
	}


    /**
    * \brief Rcon command: RconCloseCloud
    *
    * This command returns the slots that are on cooldown of a given player(steamId)
    *
    * \param[in] rcon_connection caller of the command
    * \param[in] rcon_packet rcon data
    * \param[in] UWorld, variable not used
    * \return void
    */
	static void RconCloseCloud(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*)
	{
		CloseCloud(true);
	}


	/**
	* \brief Rcon command: RconCloseCloud
	*
	* This command returns the slots that are on cooldown of a given player(steamId)
	*
	* \param[in] rcon_connection caller of the command
	* \param[in] rcon_packet rcon data
	* \param[in] UWorld, variable not used
	* \return void
	*/
	static void RconOpenCloud(RCONClientConnection* rcon_connection, RCONPacket* rcon_packet, UWorld*)
	{
		CloseCloud(false);
	}



    /**
    * \brief Console command: ConsoleCloseCloud
    *
    * This command is to reset a player slot of a tribe that is on cooldown
    *
    * \param[in] player caller of the command
    * \param[in] cmd, not used
    * \param[in] boolean, variable not used
    * \return void
    */
    static void ConsoleCloseCloud(APlayerController* player, FString* cmd, bool boolean)
    {
		CloseCloud(true);
    }


	/**
	* \brief Console command: ConsoleCloseCloud
	*
	* This command is to reset a player slot of a tribe that is on cooldown
	*
	* \param[in] player caller of the command
	* \param[in] cmd, not used
	* \param[in] boolean, variable not used
	* \return void
	*/
	static void ConsoleOpenCloud(APlayerController* player, FString* cmd, bool boolean)
	{
		CloseCloud(false);
	}



    /**
    * \brief Initialisation of rcon commands
    *
    * This function initializes all rcon commands
    *
    * \return void
    */
    static void InitRconCommands(void)
    {
        ArkApi::GetCommands().AddRconCommand("CloseCloud", &RconCloseCloud);
        ArkApi::GetCommands().AddRconCommand("OpenCloud", &RconOpenCloud);
    }


    /**
    * \brief Remove of rcon commands
    *
    * This function removes all rcon commands
    *
    * \return void
    */
    static void RemoveRconCommands(void)
    {
        ArkApi::GetCommands().RemoveRconCommand("CloseCloud");
        ArkApi::GetCommands().RemoveRconCommand("OpenCloud");

    }


    /**
    * \brief Initialisation of console commands
    *
    * This function initializes all console commands
    *
    * \return void
    */
    static void InitConsoleCommands(void)
    {
        ArkApi::GetCommands().AddConsoleCommand("CloseCloud", &ConsoleCloseCloud);
        ArkApi::GetCommands().AddConsoleCommand("OpenCloud", &ConsoleOpenCloud);
    }


    /**
    * \brief Remove of console commands
    *
    * This function removes all console commands
    *
    * \return void
    */
    static void RemoveConsoleCommands(void)
    {
        ArkApi::GetCommands().RemoveConsoleCommand("CloseCloud");
        ArkApi::GetCommands().RemoveConsoleCommand("OpenCloud");
    }


    /**
    * \brief Initialisation of chat commands
    *
    * This function initializes all chat commands
    *
    * \return void
    */
    static void InitChatCommands(void)
    {

    }


    /**
    * \brief Remove of chat commands
    *
    * This function removes all chat commands
    *
    * \return void
    */
    static void RemoveChatCommands(void)
    {

    }


    /* ===================================== [definition of global functions] ===================================== */

    /**
    * \brief Initialisation of commands
    *
    * This function initializes all commands
    *
    * \return void
    */
    void InitCommands(void)
    {
        InitChatCommands();
        InitConsoleCommands();
        InitRconCommands();
    }


    /**
    * \brief Remove of commands
    *
    * This function removes all commands
    *
    * \return void
    */
    void RemoveComands(void)
    {
        RemoveChatCommands();
        RemoveConsoleCommands();
        RemoveRconCommands();
    }
}

/* =================================================[end of file]================================================= */

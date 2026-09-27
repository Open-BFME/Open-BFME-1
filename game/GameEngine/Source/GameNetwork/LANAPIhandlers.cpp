// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?setName@LANPlayer@@QAEXVUnicodeString@@@Z present-unmatched
// Former624C10 claim is EnumeratedIP::setIPstring(AsciiString).
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// FILE: LANAPIHandlers.cpp
// Author: Matthew D. Campbell, October 2001
// Description: LAN callback handlers
///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/CRC.h"
#include "Common/GameState.h"
#include "Common/Registry.h"
#include "Common/GlobalData.h"
#include "Common/QuotedPrintable.h"
#include "Common/UserPreferences.h"
#include "GameNetwork/LANAPI.h"
#include "GameNetwork/LANAPICallbacks.h"
#include "GameClient/MapUtil.h"

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/LANAPIHandleRequestLocationsThunk.cpp
// ?handleRequestLocations@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleRequestLocations( LANMessage *msg, UnsignedInt senderIP )
{
	if (m_inLobby)
	{
		LANMessage reply;
		fillInLANMessage( &reply );
		reply.LANMessageType = LANMessage::MSG_LOBBY_ANNOUNCE;

		sendMessage(&reply);
		m_lastResendTime = timeGetTime();
	}
	else
	{
		// In game - are we a game host?
		if (m_currentGame)
		{
			if (m_currentGame->getIP(0) == m_localIP)
			{
				LANMessage reply;
				fillInLANMessage( &reply );
				reply.LANMessageType = LANMessage::MSG_GAME_ANNOUNCE;
				AsciiString gameOpts = GenerateGameOptionsString();
				strncpy(reply.GameInfo.options,gameOpts.str(),m_lanMaxOptionsLength);
				wcsncpy(reply.GameInfo.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
				reply.GameInfo.gameName[g_lanGameNameLength] = 0;
				reply.GameInfo.inProgress = m_currentGame->isGameInProgress();

				sendMessage(&reply);
			}
			else
			{
				// We're a joiner
			}
		}
	}
	// Add the player to the lobby player list
	LANPlayer *player = LookupPlayer(senderIP);
	if (!player)
	{
		player = NEW LANPlayer;
		player->setIP(senderIP);
	}
	else
	{
		removePlayer(player);
	}
	player->setName(UnicodeString(msg->name));
	player->setHost(msg->hostName);
	player->setLogin(msg->userName);
	player->setLastHeard(timeGetTime());

	addPlayer(player);

	OnNameChange(player->getIP(), player->getName());
}

// ?handleGameAnnounce@LANAPI@@IAEXPAULANMessage@@I@Z
// Body in LANAPIhandlers_handleGameAnnounce.asm (exact 596B retail @ 0x68C110;
// true body via update jmp table MSG_GAME_ANNOUNCE; queue 0xC5FB21 misplaced).

// Force-emit GameInfo::setGameInProgress COMDAT (matched @ 0x6B6C0 on this TU).
// Was only referenced by the C++ handleGameAnnounce body (now MASM).
static void bfme_force_setGameInProgress(GameInfo *g, Bool v)
{
	g->setGameInProgress(v);
}
void (*bfme_force_setGameInProgress_anchor)(GameInfo *, Bool) = &bfme_force_setGameInProgress;

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/LANAPI_handleLobbyAnnounce_Thunk.cpp
// ?handleLobbyAnnounce@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleLobbyAnnounce( LANMessage *msg, UnsignedInt senderIP )
{
	LANPlayer *player = LookupPlayer(senderIP);
	if (!player)
	{
		player = NEW LANPlayer;
		player->setIP(senderIP);
	}
	else
	{
		removePlayer(player);
	}
	player->setName(UnicodeString(msg->name));
	player->setHost(msg->hostName);
	player->setLogin(msg->userName);
	player->setLastHeard(timeGetTime());

	addPlayer(player);

	OnNameChange(player->getIP(), player->getName());
}

// ?handleRequestGameInfo@LANAPI@@IAEXPAULANMessage@@I@Z
// Body in LANAPIhandlers_handleRequestGameInfo.asm (exact 254B retail @ 0x68B380;
// queue 0x9DAFF9 was a misplaced unit-tag dispatcher).

// ?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z
// Body in LANAPIhandlers_handleRequestJoin.asm (exact 1119B retail).

// UpdateRemoteIPList (0x004D2D80) lives in the direct-connect menu TU.


// ?handleJoinDeny@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleJoinDeny( LANMessage *msg, UnsignedInt senderIP )
{
	if (msg->GameJoined.playerIP == m_localIP) // Is it for us?
	{
		if (m_pendingAction == ACT_JOIN) // Are we trying to join?
		{
			OnGameJoin(msg->GameNotJoined.reason, LookupGame(UnicodeString(msg->GameNotJoined.gameName)));
			m_pendingAction = ACT_NONE;
			m_expiration = 0;
		}
	}
}

// ?handleRequestGameLeave@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleRequestGameLeave( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		int player;
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			if (m_currentGame->getIP(player) == senderIP)
			{
				if (player == 0)
				{
					OnHostLeave();
					removeGame(m_currentGame);
					delete m_currentGame;
					m_currentGame = NULL;

					/// @todo re-add myself to lobby?  Or just keep me there all the time?  If we send a LOBBY_ANNOUNCE things'll work out...
					LANPlayer *lanPlayer = LookupPlayer(m_localIP);
					if (!lanPlayer)
					{
						lanPlayer = NEW LANPlayer;
						lanPlayer->setIP(m_localIP);
					}
					else
					{
						removePlayer(lanPlayer);
					}
					lanPlayer->setName(UnicodeString(m_name));
					lanPlayer->setHost(m_hostName);
					lanPlayer->setLogin(m_userName);
					lanPlayer->setLastHeard(timeGetTime());
					addPlayer(lanPlayer);

				}
				else
				{
					if (AmIHost())
					{
						// remove the deadbeat
						LANGameSlot slot;
						slot.setState(SLOT_OPEN);
						m_currentGame->setSlot( player, slot );
					}
					OnPlayerLeave(UnicodeString(msg->name));
					m_currentGame->getLANSlot(player)->setState(SLOT_OPEN);
					m_currentGame->resetAccepted();
					RequestGameOptions(GenerateGameOptionsString(), false, senderIP);
					//m_currentGame->endGame();
				}
				break;
			}
			DEBUG_ASSERTCRASH(player < MAX_SLOTS, ("Didn't find player!"));
		}
	}
	else if (m_inLobby)
	{
		// Look for dissappearing games
		LANGameInfo *game = m_games;
		while (game)
		{
			if (game->getName().compare(msg->GameToLeave.gameName) == 0)
			{
				removeGame(game);
				delete game;
				OnGameList(m_games);
				break;
			}
			game = game->getNext();
		}
	}
}

// ?handleRequestLobbyLeave@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleRequestLobbyLeave( LANMessage *msg, UnsignedInt senderIP )
{
	if (m_inLobby)
	{
		LANPlayer *player = m_lobbyPlayers;
		while (player)
		{
			if (player->getIP() == senderIP)
			{
				removePlayer(player);
				OnPlayerList(m_lobbyPlayers);
				break;
			}
			player = player->getNext();
		}
	}
}

// ?handleSetAccept@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleSetAccept( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		int player;
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			if (m_currentGame->getIP(player) == senderIP)
			{
				OnAccept(senderIP, msg->Accept.isAccepted);
				break;
			}
		}
	}
}

// ?handleHasMap@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleHasMap( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame)
	{
		CRC mapNameCRC;
//	mapNameCRC.computeCRC(m_currentGame->getMap().str(), m_currentGame->getMap().getLength());
		AsciiString portableMapName = TheGameState->realMapPathToPortableMapPath(m_currentGame->getMap());
		mapNameCRC.computeCRC(portableMapName.str(), portableMapName.getLength());
		if (mapNameCRC.get() != msg->MapStatus.mapCRC)
		{
			return;
		}

		int player;
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			if (m_currentGame->getIP(player) == senderIP)
			{
				OnHasMap(senderIP, msg->MapStatus.hasMap);
				break;
			}
		}
	}
}

// ?handleChat@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleChat( LANMessage *msg, UnsignedInt senderIP )
{
	if (m_inLobby)
	{
		LANPlayer *player;
		if((player=LookupPlayer(senderIP)) != 0)
		{
			OnChat(UnicodeString(player->getName()), player->getIP(), UnicodeString(msg->Chat.message), msg->Chat.chatType);
			player->setLastHeard(timeGetTime());
		}
	}
	else
	{
		if (LookupGame(UnicodeString(msg->Chat.gameName)) != m_currentGame)
		{
			DEBUG_LOG(("Game '%ls' is not my game\n", msg->Chat.gameName));
			if (m_currentGame)
			{
				DEBUG_LOG(("Current game is '%ls'\n", m_currentGame->getName().str()));
			}
			return;
		}

		int player;
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			if (m_currentGame && m_currentGame->getIP(player) == senderIP)
			{
				OnChat(UnicodeString(msg->name), m_currentGame->getIP(player), UnicodeString(msg->Chat.message), msg->Chat.chatType);
				break;
			}
		}
	}
}

// ?handleGameStart@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleGameStart( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame && m_currentGame->getIP(0) == senderIP && !m_currentGame->isGameInProgress())
	{
		OnGameStart();
	}
}

// ?handleGameStartTimer@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleGameStartTimer( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame && m_currentGame->getIP(0) == senderIP && !m_currentGame->isGameInProgress())
	{
		OnGameStartTimer(msg->StartTimer.seconds);
	}
}

// ?handleGameOptions@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleGameOptions( LANMessage *msg, UnsignedInt senderIP )
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		int player;
		for (player = 0; player < MAX_SLOTS; ++player)
		{
			if (m_currentGame->getIP(player) == senderIP)
			{
				OnGameOptions(senderIP, player, AsciiString(msg->GameOptions.options));
				break;
			}
		}
	}
}

// byte-exact reconstruction: game/GameEngine/Source/GameNetwork/LANAPI_handleInActive_Thunk.cpp
// ?handleInActive@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::handleInActive(LANMessage *msg, UnsignedInt senderIP) {
	if (m_inLobby || (m_currentGame == NULL) || (m_currentGame->isGameInProgress())) {
		return;
	}

	// check to see if we are the host of this game.
	if (m_currentGame->amIHost() == FALSE) {
		return;
	}

	UnicodeString playerName;
	playerName = msg->name;

	Int slotNum = m_currentGame->getSlotNum(playerName);
	if (slotNum < 0)
		return;
	GameSlot *slot = m_currentGame->getSlot(slotNum);
	if (slot == NULL) {
		return;
	}

	if (senderIP != slot->getIP()) {
		return;
	}

	// don't want to unaccept the host, that's silly.  They can't hit start alt-tabbed anyways.
	if (senderIP == TheLAN->GetLocalIP()) {
		return;
	}

	// only unaccept if the timer hasn't started yet.
	if (m_gameStartTime != 0) {
		return;
	}

	slot->unAccept();
	AsciiString options = GenerateGameOptionsString();
	RequestGameOptions(options, FALSE);
	lanUpdateSlotList();
}

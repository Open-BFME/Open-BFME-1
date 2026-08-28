// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPIHandleRequestLocationsThunk.cpp
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

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_handleLobbyAnnounce_Thunk.cpp
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

// ?handleJoinAccept@LANAPI@@IAEXPAULANMessage@@I@Z matched 1291 bytes (Open-BFME5)
__declspec(naked) void LANAPI::handleJoinAccept(LANMessage *, UnsignedInt)
{
	__asm
	{
		__emit 0x6a;
		__emit 0xff;
		__emit 0x68;
		__emit 0x08;
		__emit 0xa3;
		__emit 0x02;
		__emit 0x01;
		__emit 0x64;
		__emit 0xa1;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x50;
		__emit 0x64;
		__emit 0x89;
		__emit 0x25;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x83;
		__emit 0xec;
		__emit 0x74;
		__emit 0x53;
		__emit 0x55;
		__emit 0x56;
		__emit 0x57;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x70;
		__emit 0xe8;
		__emit 0xdb;
		__emit 0x2d;
		__emit 0xb5;
		__emit 0xff;
		__emit 0xa1;
		__emit 0xc8;
		__emit 0x3e;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x33;
		__emit 0xf6;
		__emit 0x50;
		__emit 0x89;
		__emit 0xb4;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x5d;
		__emit 0xc3;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xc8;
		__emit 0x3e;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0x51;
		__emit 0x83;
		__emit 0xcb;
		__emit 0xff;
		__emit 0x52;
		__emit 0x8b;
		__emit 0xe8;
		__emit 0x89;
		__emit 0x5c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xe8;
		__emit 0x87;
		__emit 0x89;
		__emit 0xb6;
		__emit 0xff;
		__emit 0xa1;
		__emit 0xc8;
		__emit 0x3e;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0x51;
		__emit 0xe8;
		__emit 0xf1;
		__emit 0xdc;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x14;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x24;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x28;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0xe8;
		__emit 0x50;
		__emit 0x62;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x28;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x40;
		__emit 0xe8;
		__emit 0xf2;
		__emit 0x55;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x20;
		__emit 0x68;
		__emit 0x78;
		__emit 0x5a;
		__emit 0x0f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0xb8;
		__emit 0x5f;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x34;
		__emit 0x3b;
		__emit 0xc6;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x05;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8c;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x44;
		__emit 0xe8;
		__emit 0x5f;
		__emit 0x5b;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0x6e;
		__emit 0x53;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x20;
		__emit 0x3b;
		__emit 0xc6;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8c;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x5c;
		__emit 0x51;
		__emit 0x68;
		__emit 0x0c;
		__emit 0xfd;
		__emit 0x0f;
		__emit 0x01;
		__emit 0x50;
		__emit 0xff;
		__emit 0x15;
		__emit 0xe8;
		__emit 0x94;
		__emit 0x35;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x18;
		__emit 0x83;
		__emit 0xf8;
		__emit 0x04;
		__emit 0x74;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x03;
		__emit 0xe8;
		__emit 0x23;
		__emit 0x53;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x3c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0xe8;
		__emit 0x12;
		__emit 0x53;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0xe8;
		__emit 0x71;
		__emit 0x4a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xf0;
		__emit 0x52;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x89;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe9;
		__emit 0x7d;
		__emit 0x03;
		__emit 0x00;
		__emit 0x00;
		__emit 0x68;
		__emit 0x50;
		__emit 0xfe;
		__emit 0x0f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0xe8;
		__emit 0xc6;
		__emit 0x5c;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x34;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x78;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x06;
		__emit 0xe8;
		__emit 0xca;
		__emit 0xb7;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x74;
		__emit 0x4d;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0x13;
		__emit 0x4a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x33;
		__emit 0xff;
		__emit 0x3b;
		__emit 0xee;
		__emit 0xc7;
		__emit 0x44;
		__emit 0x24;
		__emit 0x30;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0f;
		__emit 0x8e;
		__emit 0x4e;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0xb3;
		__emit 0x07;
		__emit 0x3b;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x0f;
		__emit 0x84;
		__emit 0x36;
		__emit 0x02;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x15;
		__emit 0xc8;
		__emit 0x3e;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x56;
		__emit 0x57;
		__emit 0x52;
		__emit 0xe8;
		__emit 0x6a;
		__emit 0x0a;
		__emit 0xb7;
		__emit 0xff;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xa1;
		__emit 0xc8;
		__emit 0x3e;
		__emit 0x2f;
		__emit 0x01;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x58;
		__emit 0x51;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0xa0;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x60;
		__emit 0xdb;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x14;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x08;
		__emit 0xe8;
		__emit 0xa7;
		__emit 0x55;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x37;
		__emit 0x52;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x18;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x10;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x09;
		__emit 0xe8;
		__emit 0x9d;
		__emit 0x60;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x83;
		__emit 0x7c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0xff;
		__emit 0x0f;
		__emit 0x85;
		__emit 0x0a;
		__emit 0x01;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x10;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x30;
		__emit 0xe8;
		__emit 0x34;
		__emit 0x54;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x14;
		__emit 0x68;
		__emit 0x78;
		__emit 0x5a;
		__emit 0x0f;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x44;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0b;
		__emit 0xe8;
		__emit 0xfa;
		__emit 0x5d;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x40;
		__emit 0x3b;
		__emit 0xc6;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0c;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8c;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xe8;
		__emit 0xa1;
		__emit 0x59;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x40;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0b;
		__emit 0xe8;
		__emit 0xb0;
		__emit 0x51;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x14;
		__emit 0x3b;
		__emit 0xc6;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8c;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x6c;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x6c;
		__emit 0x51;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x6c;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x6c;
		__emit 0x51;
		__emit 0x68;
		__emit 0x0c;
		__emit 0xfd;
		__emit 0x0f;
		__emit 0x01;
		__emit 0x50;
		__emit 0xff;
		__emit 0x15;
		__emit 0xe8;
		__emit 0x94;
		__emit 0x35;
		__emit 0x01;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x18;
		__emit 0xb1;
		__emit 0x01;
		__emit 0x33;
		__emit 0xc0;
		__emit 0x8d;
		__emit 0xa4;
		__emit 0x24;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x80;
		__emit 0xf9;
		__emit 0x01;
		__emit 0x75;
		__emit 0x41;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x04;
		__emit 0x50;
		__emit 0x3b;
		__emit 0x54;
		__emit 0x04;
		__emit 0x60;
		__emit 0x74;
		__emit 0x02;
		__emit 0x32;
		__emit 0xc9;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x04;
		__emit 0x83;
		__emit 0xf8;
		__emit 0x10;
		__emit 0x7c;
		__emit 0xe7;
		__emit 0x80;
		__emit 0xf9;
		__emit 0x01;
		__emit 0x75;
		__emit 0x28;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0x4d;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0a;
		__emit 0xe8;
		__emit 0x40;
		__emit 0x51;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x09;
		__emit 0xe8;
		__emit 0x2f;
		__emit 0x51;
		__emit 0x3b;
		__emit 0x00;
		__emit 0xe9;
		__emit 0xba;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x14;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0a;
		__emit 0xe8;
		__emit 0x19;
		__emit 0x51;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x2c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x09;
		__emit 0xe8;
		__emit 0x08;
		__emit 0x51;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x34;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x30;
		__emit 0x50;
		__emit 0x51;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x54;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0x68;
		__emit 0xa4;
		__emit 0xc7;
		__emit 0x07;
		__emit 0x01;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x98;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0d;
		__emit 0xe8;
		__emit 0xd6;
		__emit 0x5a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x51;
		__emit 0xe8;
		__emit 0xfc;
		__emit 0x5e;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8b;
		__emit 0x54;
		__emit 0x24;
		__emit 0x3c;
		__emit 0x8b;
		__emit 0x44;
		__emit 0x24;
		__emit 0x40;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x42;
		__emit 0x3b;
		__emit 0xc6;
		__emit 0x89;
		__emit 0x54;
		__emit 0x24;
		__emit 0x30;
		__emit 0x74;
		__emit 0x05;
		__emit 0x83;
		__emit 0xc0;
		__emit 0x08;
		__emit 0xeb;
		__emit 0x05;
		__emit 0xb8;
		__emit 0x8b;
		__emit 0x38;
		__emit 0x07;
		__emit 0x01;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0xe8;
		__emit 0xa4;
		__emit 0x5a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x44;
		__emit 0x52;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x78;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0e;
		__emit 0xe8;
		__emit 0xa8;
		__emit 0xb5;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0x52;
		__emit 0x4b;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x44;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x0d;
		__emit 0xe8;
		__emit 0xf1;
		__emit 0x47;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x34;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x09;
		__emit 0xe8;
		__emit 0xe0;
		__emit 0x47;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x18;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0xd0;
		__emit 0x47;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x10;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0x4f;
		__emit 0x50;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x47;
		__emit 0x3b;
		__emit 0xfd;
		__emit 0x0f;
		__emit 0x8c;
		__emit 0xb7;
		__emit 0xfd;
		__emit 0xff;
		__emit 0xff;
		__emit 0x83;
		__emit 0xcb;
		__emit 0xff;
		__emit 0x39;
		__emit 0x5c;
		__emit 0x24;
		__emit 0x1c;
		__emit 0x75;
		__emit 0x01;
		__emit 0x45;
		__emit 0x89;
		__emit 0x74;
		__emit 0x24;
		__emit 0x38;
		__emit 0x55;
		__emit 0x51;
		__emit 0x89;
		__emit 0x64;
		__emit 0x24;
		__emit 0x54;
		__emit 0x8b;
		__emit 0xcc;
		__emit 0xb3;
		__emit 0x0f;
		__emit 0x68;
		__emit 0xb4;
		__emit 0xc7;
		__emit 0x07;
		__emit 0x01;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x98;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x0d;
		__emit 0x5a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x54;
		__emit 0x24;
		__emit 0x40;
		__emit 0x52;
		__emit 0xe8;
		__emit 0x33;
		__emit 0x5e;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x83;
		__emit 0xc4;
		__emit 0x0c;
		__emit 0x68;
		__emit 0x88;
		__emit 0xc7;
		__emit 0x07;
		__emit 0x01;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x48;
		__emit 0xe8;
		__emit 0xf2;
		__emit 0x59;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x44;
		__emit 0x24;
		__emit 0x44;
		__emit 0x50;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x78;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x90;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x10;
		__emit 0xe8;
		__emit 0xf6;
		__emit 0xb4;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0x51;
		__emit 0x8b;
		__emit 0xc8;
		__emit 0xe8;
		__emit 0xa0;
		__emit 0x4a;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x44;
		__emit 0x88;
		__emit 0x9c;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x40;
		__emit 0x47;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x70;
		__emit 0xe8;
		__emit 0x8c;
		__emit 0xd2;
		__emit 0xb5;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x38;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x04;
		__emit 0xe8;
		__emit 0x26;
		__emit 0x47;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x20;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x03;
		__emit 0xe8;
		__emit 0xa5;
		__emit 0x4f;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x3c;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x02;
		__emit 0xe8;
		__emit 0x94;
		__emit 0x4f;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x24;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x01;
		__emit 0xe8;
		__emit 0xf3;
		__emit 0x46;
		__emit 0x3b;
		__emit 0x00;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x28;
		__emit 0xc6;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xe8;
		__emit 0x72;
		__emit 0x4f;
		__emit 0x3b;
		__emit 0x00;
		__emit 0xc7;
		__emit 0x84;
		__emit 0x24;
		__emit 0x8c;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0xff;
		__emit 0x8d;
		__emit 0x4c;
		__emit 0x24;
		__emit 0x70;
		__emit 0xe8;
		__emit 0x41;
		__emit 0xdb;
		__emit 0xb6;
		__emit 0xff;
		__emit 0x8b;
		__emit 0x8c;
		__emit 0x24;
		__emit 0x84;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5f;
		__emit 0x5e;
		__emit 0x5d;
		__emit 0x64;
		__emit 0x89;
		__emit 0x0d;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0x5b;
		__emit 0x81;
		__emit 0xc4;
		__emit 0x80;
		__emit 0x00;
		__emit 0x00;
		__emit 0x00;
		__emit 0xc3;
	}
}

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

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_handleInActive_Thunk.cpp
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

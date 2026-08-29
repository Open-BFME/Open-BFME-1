// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/lanapi /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
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

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define WIN32_LEAN_AND_MEAN  // only bare bones windows stuff wanted

#include "Common/CRC.h"
#include "Common/GameState.h"
#include "Common/Registry.h"
#include "GameNetwork/LANAPI.h"
#include "GameNetwork/NetworkUtil.h"
#include "Common/GlobalData.h"
#include "Common/RandomValue.h"
#include "GameClient/GameText.h"
#include "GameClient/MapUtil.h"
#include "Common/UserPreferences.h"
#include "GameLogic/GameLogic.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

static const UnsignedShort lobbyPort = 8086; ///< This is the UDP port used by all LANAPI communication

AsciiString GetMessageTypeString(UnsignedInt type);

const UnsignedInt LANAPI::s_resendDelta = 10 * 1000;	///< This is how often we announce ourselves to the world
/*
// ??0LANGame@@ present-unmatched
LANGame::LANGame( void )
{
	m_gameName = L"";

	int player;
	for (player = 0; player < MAX_SLOTS; ++player)
	{
		m_playerName[player] = L"";
		m_playerIP[player]= 0;
		m_playerAccepted[player] = false;
	}
	m_lastHeard = 0;
	m_inProgress = false;
	m_next = NULL;
}
*/




// ??0LANAPI@@QAE@XZ present-unmatched
LANAPI::LANAPI( void ) : m_transport(NULL)
{
	DEBUG_LOG(("LANAPI::LANAPI() - max game option size is %d, sizeof(LANMessage)=%d, MAX_PACKET_SIZE=%d\n",
		m_lanMaxOptionsLength, sizeof(LANMessage), MAX_PACKET_SIZE));

	m_lastResendTime = 0;
	//
	m_lobbyPlayers = NULL;
	m_games = NULL;
	m_name = L""; // safe default?
	m_pendingAction = ACT_NONE;
	m_expiration = 0;
	m_localIP = 0;
	m_inLobby = true;
	m_isInLANMenu = TRUE;
	m_currentGame = NULL;
	m_broadcastAddr = INADDR_BROADCAST;
	m_directConnectRemoteIP = 0;
	m_actionTimeout = 5000; // ms
	m_lastUpdate = 0;
	m_transport = new Transport;
	m_isActive = TRUE;
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_dtor.cpp
// ??1LANAPI@@UAE@XZ present-unmatched
LANAPI::~LANAPI( void )
{
	reset();
	if (m_transport)
		delete m_transport;
}

// ?init@LANAPI@@UAEXXZ present-unmatched
void LANAPI::init( void )
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
	m_transport->reset();
	m_transport->init(m_localIP, lobbyPort);
	m_transport->allowBroadcasts(true);

	m_pendingAction = ACT_NONE;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = TRUE;
	m_currentGame = NULL;
	m_directConnectRemoteIP = 0;
	
	m_lastGameopt = "";

	unsigned long bufSize = UNLEN + 1;
	char userName[UNLEN + 1];
	if (!GetUserName(userName, &bufSize))
	{
		strcpy(userName, "unknown");
	}
	m_userName = userName;

	bufSize = MAX_COMPUTERNAME_LENGTH + 1;
	char computerName[MAX_COMPUTERNAME_LENGTH + 1];
	if (!GetComputerName(computerName, &bufSize))
	{
		strcpy(computerName, "unknown");
	}
	m_hostName = computerName;
}

// ?reset@LANAPI@@UAEXXZ present-unmatched
void LANAPI::reset( void )
{
	if (m_inLobby)
	{
		LANMessage msg;
		fillInLANMessage( &msg );
		msg.LANMessageType = LANMessage::MSG_REQUEST_LOBBY_LEAVE;
		sendMessage(&msg);
	}
	m_transport->update();

	LANGameInfo *theGame = m_games;
	LANGameInfo *deletableGame = NULL;

	while (theGame)
	{
		deletableGame = theGame;
		theGame = theGame->getNext();
		delete deletableGame;
	}

	LANPlayer *thePlayer = m_lobbyPlayers;
	LANPlayer *deletablePlayer = NULL;

	while (thePlayer)
	{
		deletablePlayer = thePlayer;
		thePlayer = thePlayer->getNext();
		delete deletablePlayer;
	}

	m_games = NULL;
	m_lobbyPlayers = NULL;
	m_directConnectRemoteIP = 0;
	m_pendingAction = ACT_NONE;
	m_expiration = 0;
	m_inLobby = true;
	m_isInLANMenu = TRUE;
	m_currentGame = NULL;
	
}

// ?sendMessage@LANAPI@@IAEXPAULANMessage@@I@Z present-unmatched
void LANAPI::sendMessage(LANMessage *msg, UnsignedInt ip /* = 0 */)
{
	if (ip != 0)
	{
		m_transport->queueSend(ip, lobbyPort, (unsigned char *)msg, sizeof(LANMessage) /*, 0, 0 */);
	}
	else if ((m_currentGame != NULL) && (m_currentGame->getIsDirectConnect()))
	{
		Int localSlot = m_currentGame->getLocalSlotNum();
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			if (i != localSlot) {
				GameSlot *slot = m_currentGame->getSlot(i);
				if ((slot != NULL) && (slot->isHuman())) {
					m_transport->queueSend(slot->getIP(), lobbyPort, (unsigned char *)msg, sizeof(LANMessage) /*, 0, 0 */);
				}
			}
		}
	}
	else
	{
		m_transport->queueSend(m_broadcastAddr, lobbyPort, (unsigned char *)msg, sizeof(LANMessage) /*, 0, 0 */);
	}
}


AsciiString GetMessageTypeString(UnsignedInt type)
{
	AsciiString returnString;

	switch (type)
	{
		case LANMessage::MSG_REQUEST_LOCATIONS:
			returnString.format( "Request Locations (%d)",type);
			break;
		case LANMessage::MSG_GAME_ANNOUNCE:
			returnString.format("Game Announce (%d)",type);
			break;
		case LANMessage::MSG_LOBBY_ANNOUNCE:
			returnString.format("Lobby Announce (%d)",type);
			break;
		case LANMessage::MSG_REQUEST_JOIN:
			returnString.format("Request Join (%d)",type);
			break;
		case LANMessage::MSG_JOIN_ACCEPT:				
			returnString.format("Join Accept (%d)",type);
			break;
		case LANMessage::MSG_JOIN_DENY:
			returnString.format("Join Deny (%d)",type);
			break;
		case LANMessage::MSG_REQUEST_GAME_LEAVE:
			returnString.format("Request Game Leave (%d)",type);
			break;
		case LANMessage::MSG_REQUEST_LOBBY_LEAVE:
			returnString.format("Request Lobby Leave (%d)",type);
			break;
		case LANMessage::MSG_SET_ACCEPT:
			returnString.format("Set Accept(%d)",type);
			break;
		case LANMessage::MSG_CHAT:
			returnString.format("Chat (%d)",type);
			break;
		case LANMessage::MSG_GAME_START:
			returnString.format("Game Start (%d)",type);
			break;
		case LANMessage::MSG_GAME_START_TIMER:
			returnString.format("Game Start Timer (%d)",type);
			break;
		case LANMessage::MSG_GAME_OPTIONS:
			returnString.format("Game Options (%d)",type);
			break;
		case LANMessage::MSG_REQUEST_GAME_INFO:
			returnString.format("Request GameInfo (%d)", type);
			break;
		case LANMessage::MSG_INACTIVE:
			returnString.format("Inactive (%d)", type);
			break;
		default:
			returnString.format("Unknown Message (%d)",type);
	}
	return returnString;
}


// ?checkMOTD@LANAPI@@UAEXXZ present-unmatched
void LANAPI::checkMOTD( void )
{
#if defined(_DEBUG) || defined(_INTERNAL)
	if (TheGlobalData->m_useLocalMOTD)
	{
		// for a playtest, let's log some play statistics, eh?
		if (TheGlobalData->m_playStats <= 0)
			TheWritableGlobalData->m_playStats = 30;

		static UnsignedInt oldMOTDCRC = 0;
		UnsignedInt newMOTDCRC = 0;
		AsciiString asciiMOTD;
		char buf[4096];
		FILE *fp = fopen(TheGlobalData->m_MOTDPath.str(), "r");
		Int len;
		if (fp)
		{
			while( (len = fread(buf, 1, 4096, fp)) > 0 )
			{
				buf[len] = 0;
				asciiMOTD.concat(buf);
			}
			fclose(fp);
			CRC crcObj;
			crcObj.computeCRC(asciiMOTD.str(), asciiMOTD.getLength());
			newMOTDCRC = crcObj.get();
		}

		if (oldMOTDCRC != newMOTDCRC)
		{
			// different MOTD... display it
			oldMOTDCRC = newMOTDCRC;
			AsciiString line;
			while (asciiMOTD.nextToken(&line, "\n"))
			{
				if (line.getCharAt(line.getLength()-1) == '\r')
					line.removeLastChar();	// there is a trailing '\r'

				if (line.isEmpty())
				{
					line = " ";
				}

				UnicodeString uniLine;
				uniLine.translate(line);
				OnChat( UnicodeString(L"MOTD"), 0, uniLine, LANCHAT_SYSTEM );
			}
		}
	}
#endif
}

extern Bool LANbuttonPushed;
extern Bool LANSocketErrorDetected;
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPIUpdateThunk.cpp
// ?update@LANAPI@@ present-unmatched
void LANAPI::update( void )
{
	if(LANbuttonPushed)
		return;
	static const UnsignedInt LANAPIUpdateDelay = 200;
	UnsignedInt now = timeGetTime();
	
	if( now > m_lastUpdate + LANAPIUpdateDelay)
	{
		m_lastUpdate = now;
	} 
	else
	{
		return;
	}

	// Let the UDP socket breathe
	if ((m_transport->update() == FALSE) && (LANSocketErrorDetected == FALSE)) {
		if (m_isInLANMenu == TRUE) {
			LANSocketErrorDetected = TRUE;
		}
	}

	// Handle any new messages
	int i;
	for (i=0; i<MAX_MESSAGES && !LANbuttonPushed; ++i)
	{
		if (m_transport->m_inBuffer[i].length > 0)
		{
			// Process the new message
			UnsignedInt senderIP = m_transport->m_inBuffer[i].addr;
			if (senderIP == m_localIP)
			{
				m_transport->m_inBuffer[i].length = 0;
				continue;
			}

			LANMessage *msg = (LANMessage *)(m_transport->m_inBuffer[i].data);
			//DEBUG_LOG(("LAN message type %s from %ls (%s@%s)\n", GetMessageTypeString(msg->LANMessageType).str(),
			//	msg->name, msg->userName, msg->hostName));
			switch (msg->LANMessageType)
			{
				// Location specification
			case LANMessage::MSG_REQUEST_LOCATIONS:		// Hey, where is everybody?
				DEBUG_LOG(("LANAPI::update - got a MSG_REQUEST_LOCATIONS from 0x%08x\n", senderIP));
				handleRequestLocations( msg, senderIP );
				break;
			case LANMessage::MSG_GAME_ANNOUNCE:				// Here someone is, and here's his game info!
				DEBUG_LOG(("LANAPI::update - got a MSG_GAME_ANNOUNCE from 0x%08x\n", senderIP));
				handleGameAnnounce( msg, senderIP );
				break;
			case LANMessage::MSG_LOBBY_ANNOUNCE:			// Hey, I'm in the lobby!
				DEBUG_LOG(("LANAPI::update - got a MSG_LOBBY_ANNOUNCE from 0x%08x\n", senderIP));
				handleLobbyAnnounce( msg, senderIP );
				break;
			case LANMessage::MSG_REQUEST_GAME_INFO:
				DEBUG_LOG(("LANAPI::update - got a MSG_REQUEST_GAME_INFO from 0x%08x\n", senderIP));
				handleRequestGameInfo( msg, senderIP );
				break;

				// Joining games
			case LANMessage::MSG_REQUEST_JOIN:				// Let me in!  Let me in!
				DEBUG_LOG(("LANAPI::update - got a MSG_REQUEST_JOIN from 0x%08x\n", senderIP));
				handleRequestJoin( msg, senderIP );
				break;
			case LANMessage::MSG_JOIN_ACCEPT:					// Okay, you can join.
				DEBUG_LOG(("LANAPI::update - got a MSG_JOIN_ACCEPT from 0x%08x\n", senderIP));
				handleJoinAccept( msg, senderIP );
				break;
			case LANMessage::MSG_JOIN_DENY:						// Go away!  We don't want any!
				DEBUG_LOG(("LANAPI::update - got a MSG_JOIN_DENY from 0x%08x\n", senderIP));
				handleJoinDeny( msg, senderIP );
				break;

				// Leaving games, lobby
			case LANMessage::MSG_REQUEST_GAME_LEAVE:				// I'm outa here!
				DEBUG_LOG(("LANAPI::update - got a MSG_REQUEST_GAME_LEAVE from 0x%08x\n", senderIP));
				handleRequestGameLeave( msg, senderIP );
				break;
			case LANMessage::MSG_REQUEST_LOBBY_LEAVE:				// I'm outa here!
				DEBUG_LOG(("LANAPI::update - got a MSG_REQUEST_LOBBY_LEAVE from 0x%08x\n", senderIP));
				handleRequestLobbyLeave( msg, senderIP );
				break;

				// Game options, chat, etc
			case LANMessage::MSG_SET_ACCEPT:					// I'm cool with everything as is.
				handleSetAccept( msg, senderIP );
				break;
			case LANMessage::MSG_MAP_AVAILABILITY:		// Map status
				handleHasMap( msg, senderIP );
				break;
			case LANMessage::MSG_CHAT:								// Just spouting my mouth off.
				handleChat( msg, senderIP );
				break;
			case LANMessage::MSG_GAME_START:					// Hold on; we're starting!
				handleGameStart( msg, senderIP );
				break;
			case LANMessage::MSG_GAME_START_TIMER:
				handleGameStartTimer( msg, senderIP );
				break;
			case LANMessage::MSG_GAME_OPTIONS:				// Here's some info about the game.
				DEBUG_LOG(("LANAPI::update - got a MSG_GAME_OPTIONS from 0x%08x\n", senderIP));
				handleGameOptions( msg, senderIP );
				break;
			case LANMessage::MSG_INACTIVE:		// someone is telling us that we're inactive.
				handleInActive( msg, senderIP );
				break;

			default:
				DEBUG_LOG(("Unknown LAN message type %d\n", msg->LANMessageType));
			}

			// Mark it as read
			m_transport->m_inBuffer[i].length = 0;
		}
	} // End message handling
	if(LANbuttonPushed)
		return;
	// Send out periodic I'm Here messages
	if (now > s_resendDelta + m_lastResendTime)
	{
		m_lastResendTime = now;

		if (m_inLobby)
		{
			RequestSetName(m_name);
		}
		else if (m_currentGame && !m_currentGame->isGameInProgress())
		{
			if (AmIHost())
			{				
				RequestGameOptions( GenerateGameOptionsString(), true );
				RequestGameAnnounce( );
			}
			else
			{
				AsciiString text;
				text.format("User=%s", m_userName.str());
				RequestGameOptions( text, true );
				text.format("Host=%s", m_hostName.str());
				RequestGameOptions( text, true );
				RequestGameOptions( "HELLO", false );
			}
		}
		else if (m_currentGame)
		{
			// game is in progress - RequestGameAnnounce will check if we should send it
			RequestGameAnnounce();
		}
	}

	Bool playerListChanged = false;
	Bool gameListChanged = false;

	// Weed out people we haven't heard from in a while
	LANPlayer *player = m_lobbyPlayers;
	while (player)
	{
		if (player->getLastHeard() + s_resendDelta*2 < now)
		{
			// He's gone!
			removePlayer(player);
			LANPlayer *nextPlayer = player->getNext();
			delete player;
			player = nextPlayer;
			playerListChanged = true;
		}
		else
		{
			player = player->getNext();
		}
	}

	// Weed out people we haven't heard from in a while
	LANGameInfo *game = m_games;
	while (game)
	{
		if (game != m_currentGame && game->getLastHeard() + s_resendDelta*2 < now)
		{
			// He's gone!
			removeGame(game);
			LANGameInfo *nextGame = game->getNext();
			delete game;
			game = nextGame;
			gameListChanged = true;
		}
		else
		{
			game = game->getNext();
		}
	}
	if ( m_currentGame && !m_currentGame->isGameInProgress() )
	{
		if ( !AmIHost() && (m_currentGame->getLastHeard() + s_resendDelta*16 < now) )
		{
			// We haven't heard from the host in a while.  Bail.
			// Actually, fake a host leaving message. :)
			LANMessage msg;
			fillInLANMessage( &msg );
			msg.LANMessageType = LANMessage::MSG_REQUEST_GAME_LEAVE;
			wcsncpy(msg.name, m_currentGame->getPlayerName(0).str(), g_lanPlayerNameLength);
			msg.name[g_lanPlayerNameLength] = 0;
			handleRequestGameLeave(&msg, m_currentGame->getIP(0));
			UnicodeString text;
			text = TheGameText->fetch("LAN:HostNotResponding");
			OnChat(UnicodeString::TheEmptyString, m_localIP, text, LANCHAT_SYSTEM);
		}
		else if ( AmIHost() )
		{
			// Check each player for timeouts
			for (int p=1; p<MAX_SLOTS; ++p)
			{
				if (m_currentGame->getIP(p) && m_currentGame->getPlayerLastHeard(p) + s_resendDelta*8 < now)
				{
					LANMessage msg;
					fillInLANMessage( &msg );
					UnicodeString theStr;
					theStr.format(TheGameText->fetch("LAN:PlayerDropped"), m_currentGame->getPlayerName(p).str());
					msg.LANMessageType = LANMessage::MSG_REQUEST_GAME_LEAVE;
					wcsncpy(msg.name, m_currentGame->getPlayerName(p).str(), g_lanPlayerNameLength);
					msg.name[g_lanPlayerNameLength] = 0;
					handleRequestGameLeave(&msg, m_currentGame->getIP(p));
					OnChat(UnicodeString::TheEmptyString, m_localIP, theStr, LANCHAT_SYSTEM);
				}
			}
		}
	}

	if (playerListChanged)
	{
		OnPlayerList(m_lobbyPlayers);
	}

	if (gameListChanged)
	{
		OnGameList(m_games);
	}

	// Time out old actions
	if (m_pendingAction != ACT_NONE && now > m_expiration)
	{
		switch (m_pendingAction)
		{
		case ACT_JOIN:
			OnGameJoin(RET_TIMEOUT, NULL);
			m_pendingAction = ACT_NONE;
			m_currentGame = NULL;
			m_inLobby = true;
			break;
		case ACT_LEAVE:
			OnPlayerLeave(m_name);
			m_pendingAction = ACT_NONE;
			m_currentGame = NULL;
			m_inLobby = true;
			break;
		case ACT_JOINDIRECTCONNECT:
			OnGameJoin(RET_TIMEOUT, NULL);
			m_pendingAction = ACT_NONE;
			m_currentGame = NULL;
			m_inLobby = true;
			break;
		default:
			m_pendingAction = ACT_NONE;
		}
	}

	// send out "game starting" messages
	if ( m_gameStartTime && m_gameStartSeconds && m_gameStartTime <= now )
	{
		// m_gameStartTime is when the next message goes out
		// m_gameStartSeconds is how many seconds remain in the message

		RequestGameStartTimer( m_gameStartSeconds );
	}
	else if (m_gameStartTime && m_gameStartTime <= now)
	{
//		DEBUG_LOG(("m_gameStartTime=%d, now=%d, m_gameStartSeconds=%d\n", m_gameStartTime, now, m_gameStartSeconds));
		ResetGameStartTimer();
		RequestGameStart();
	}

	// Check for an MOTD every few seconds
	static UnsignedInt lastMOTDCheck = 0;
	static const UnsignedInt motdInterval = 30000;
	if (now > lastMOTDCheck + motdInterval)
	{
		checkMOTD();
		lastMOTDCheck = now;
	}
}

// Request functions generate network traffic
void LANAPI::RequestLocations( void )
{
	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_REQUEST_LOCATIONS;
	fillInLANMessage( &msg );
	sendMessage(&msg);
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_RequestGameJoin.cpp
// BFME's OnGameJoin takes a THIRD argument and sits at vtable +0x74; the
// reference declares two and lands it at +0x60.
#define BFME_LANAPI_V(n) virtual void _bfme_join_v##n( void ) = 0;

class BfmeLANJoinCallbacks
{
public:
	BFME_LANAPI_V(0)   BFME_LANAPI_V(1)   BFME_LANAPI_V(2)   BFME_LANAPI_V(3)   BFME_LANAPI_V(4)
	BFME_LANAPI_V(5)   BFME_LANAPI_V(6)   BFME_LANAPI_V(7)   BFME_LANAPI_V(8)   BFME_LANAPI_V(9)
	BFME_LANAPI_V(10)  BFME_LANAPI_V(11)  BFME_LANAPI_V(12)  BFME_LANAPI_V(13)  BFME_LANAPI_V(14)
	BFME_LANAPI_V(15)  BFME_LANAPI_V(16)  BFME_LANAPI_V(17)  BFME_LANAPI_V(18)  BFME_LANAPI_V(19)
	BFME_LANAPI_V(20)  BFME_LANAPI_V(21)  BFME_LANAPI_V(22)  BFME_LANAPI_V(23)  BFME_LANAPI_V(24)
	BFME_LANAPI_V(25)  BFME_LANAPI_V(26)  BFME_LANAPI_V(27)  BFME_LANAPI_V(28)
	virtual void OnGameJoin( Int ret, LANGameInfo *theGame, void *bfmeExtra = NULL ) = 0;
};

#undef BFME_LANAPI_V

// The join payload is PACKED -- unpacked, the four-dword block forces the union
// to four-byte alignment and every field lands two bytes high of where retail
// addresses it. BFME sends a fourth CRC at msg+0x2E that the reference never
// fills, and its serial field is 0x17 bytes.
#pragma pack(push, 1)
struct BfmeLANJoinPayload
{
	UnsignedByte head[0x22];
	UnsignedInt gameIP;									///< retail msg+0x22
	UnsignedInt exeCRC;									///< retail msg+0x26
	UnsignedInt iniCRC;									///< retail msg+0x2A
	UnsignedInt bfmeExtraCRC;							///< retail msg+0x2E
	char serial[0x17];									///< retail msg+0x32
};
#pragma pack(pop)

struct BfmeGlobalDataCRC
{
	UnsignedByte pad[0xbc8];
	UnsignedInt iniCRC;									///< retail this+0xBC8
	UnsignedByte gap[4];
	UnsignedInt exeCRC;									///< retail this+0xBD0
	UnsignedInt bfmeExtraCRC;							///< retail this+0xBD4
};

// the obfuscation-hook wrapper an obfuscated GlobalData member is read through
Int Rva0009B4B0( Int a, Int b );						///< ILT thunk 0x000019F6

#define BFME_JOIN(m) ((BfmeLANJoinPayload *)(m))
#define BFME_GDCRC   ((BfmeGlobalDataCRC *)TheWritableGlobalData)

// BFME's GameSlot carries one more dword ahead of the IP than the reference's.
#define BFME_SLOT_IP(s) (*(UnsignedInt *)((UnsignedByte *)(s) + 0x30))

// retail inlines str() over the eight-byte header; the shim's is out of line.
#define BFME_STR(s) (*(char **)&(s) ? *(char **)&(s) + 8 : (char *)"")

void LANAPI::RequestGameJoin( LANGameInfo *game, UnsignedInt ip /* = 0 */ )
{
	if ((m_pendingAction != ACT_NONE) && (m_pendingAction != ACT_JOINDIRECTCONNECT))
	{
		((BfmeLANJoinCallbacks *)this)->OnGameJoin( RET_BUSY, NULL );
		return;
	}

	if (!game)
	{
		((BfmeLANJoinCallbacks *)this)->OnGameJoin( RET_GAME_GONE, NULL );
		return;
	}

	LANMessage msg;

	msg.LANMessageType = LANMessage::MSG_REQUEST_JOIN;
	fillInLANMessage( &msg );
	BFME_JOIN(&msg)->gameIP = BFME_SLOT_IP( game->getSlot(0) );
	// retail reads the exe CRC through the obfuscation hook, twice
	BFME_JOIN(&msg)->exeCRC = Rva0009B4B0( BFME_GDCRC->exeCRC, BFME_GDCRC->exeCRC );
	BFME_JOIN(&msg)->iniCRC = BFME_GDCRC->iniCRC;
	BFME_JOIN(&msg)->bfmeExtraCRC = BFME_GDCRC->bfmeExtraCRC;

	AsciiString s = "";
	GetStringFromRegistry("\\ergc", "", s);
	strncpy(BFME_JOIN(&msg)->serial, BFME_STR(s), 0x17);
	BFME_JOIN(&msg)->serial[0x17-1] = '\0';

	sendMessage(&msg, ip);

	m_pendingAction = ACT_JOIN;
	m_expiration = timeGetTime() + m_actionTimeout;
}

// ?RequestGameJoinDirectConnect@LANAPI@@UAEXI@Z present-unmatched
void LANAPI::RequestGameJoinDirectConnect(UnsignedInt ipaddress)
{
	if (m_pendingAction != ACT_NONE)
	{
		OnGameJoin( RET_BUSY, NULL );
		return;
	}

	if (ipaddress == 0)
	{
		OnGameJoin( RET_GAME_GONE, NULL );
		return;
	}

	m_directConnectRemoteIP = ipaddress;

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_REQUEST_GAME_INFO;
	fillInLANMessage(&msg);
	msg.PlayerInfo.ip = GetLocalIP();
	wcsncpy(msg.PlayerInfo.playerName, m_name.str(), m_name.getLength());
	msg.PlayerInfo.playerName[m_name.getLength()] = 0;

	sendMessage(&msg, ipaddress);

	m_pendingAction = ACT_JOINDIRECTCONNECT;
	m_expiration = timeGetTime() + m_actionTimeout;
}

// ?RequestGameLeave@LANAPI@@UAEXXZ present-unmatched
void LANAPI::RequestGameLeave( void )
{
	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_REQUEST_GAME_LEAVE;
	fillInLANMessage( &msg );
	wcsncpy(msg.GameToLeave.gameName, (m_currentGame)?m_currentGame->getName().str():L"", g_lanGameNameLength);
	msg.GameToLeave.gameName[g_lanGameNameLength] = 0;
	sendMessage(&msg);
	m_transport->update();  // Send immediately, before OnPlayerLeave below resets everything.

	if (m_currentGame && m_currentGame->getIP(0) == m_localIP)
	{
		// Exit out immediately if we're hosting
		OnPlayerLeave(m_name);
		removeGame(m_currentGame);
		m_currentGame = NULL;
		m_inLobby = true;
	}
	else
	{
		m_pendingAction = ACT_LEAVE;
		m_expiration = timeGetTime() + m_actionTimeout;
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_RequestGameAnnounce.cpp
// ?RequestGameAnnounce@LANAPI@@UAEXXZ present-unmatched
void LANAPI::RequestGameAnnounce( void )
{
	// In game - are we a game host?
	if (m_currentGame && !(m_currentGame->getIsDirectConnect()))
	{
		if (m_currentGame->getIP(0) == m_localIP || (m_currentGame->isGameInProgress() && TheNetwork && TheNetwork->isPacketRouter())) // if we're in game we should reply if we're the packet router
		{
			LANMessage reply;
			fillInLANMessage( &reply );
			reply.LANMessageType = LANMessage::MSG_GAME_ANNOUNCE;

			AsciiString gameOpts = GameInfoToAsciiString(m_currentGame);
			strncpy(reply.GameInfo.options,gameOpts.str(),m_lanMaxOptionsLength);
			wcsncpy(reply.GameInfo.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
			reply.GameInfo.gameName[g_lanGameNameLength] = 0;
			reply.GameInfo.inProgress = m_currentGame->isGameInProgress();
			reply.GameInfo.isDirectConnect = m_currentGame->getIsDirectConnect();

			sendMessage(&reply);
		}
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_RequestAccept_Thunk.cpp
// ?RequestAccept@LANAPI@@UAEXXZ present-unmatched
void LANAPI::RequestAccept( void )
{
	if (m_inLobby || !m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage( &msg );
	msg.LANMessageType = LANMessage::MSG_SET_ACCEPT;
	msg.Accept.isAccepted = true;
	wcsncpy(msg.Accept.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
	msg.Accept.gameName[g_lanGameNameLength] = 0;
	sendMessage(&msg);
}

// ?RequestHasMap@LANAPI@@UAEXXZ present-unmatched
void LANAPI::RequestHasMap( void )
{
	if (m_inLobby || !m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage( &msg );
	msg.LANMessageType = LANMessage::MSG_MAP_AVAILABILITY;
	msg.MapStatus.hasMap = m_currentGame->getSlot(m_currentGame->getLocalSlotNum())->hasMap();
	wcsncpy(msg.MapStatus.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
	msg.MapStatus.gameName[g_lanGameNameLength] = 0;
	CRC mapNameCRC;
//mapNameCRC.computeCRC(m_currentGame->getMap().str(), m_currentGame->getMap().getLength());
	AsciiString portableMapName = TheGameState->realMapPathToPortableMapPath(m_currentGame->getMap());
	mapNameCRC.computeCRC(portableMapName.str(), portableMapName.getLength());
	msg.MapStatus.mapCRC = mapNameCRC.get();
	sendMessage(&msg);

	if (!msg.MapStatus.hasMap)
	{
		UnicodeString text;
		UnicodeString mapDisplayName;
		const MapMetaData *mapData = TheMapCache->findMap( m_currentGame->getMap() );
		Bool willTransfer = TRUE;
		if (mapData)
		{
			mapDisplayName.format(L"%ls", mapData->m_displayName.str());
			if (mapData->m_isOfficial)
				willTransfer = FALSE;
		}
		else
		{
			mapDisplayName.format(L"%hs", TheGameState->getMapLeafName(m_currentGame->getMap()).str());
			willTransfer = WouldMapTransfer(m_currentGame->getMap());
		}
		if (willTransfer)
			text.format(TheGameText->fetch("GUI:LocalPlayerNoMapWillTransfer"), mapDisplayName.str());
		else
			text.format(TheGameText->fetch("GUI:LocalPlayerNoMap"), mapDisplayName.str());
		OnChat(UnicodeString(L"SYSTEM"), m_localIP, text, LANCHAT_SYSTEM);
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/Common/LANAPI_RequestChat_Thunk.cpp
// ?RequestChat@LANAPI@@UAEXVUnicodeString@@W4ChatType@LANAPIInterface@@@Z present-unmatched
void LANAPI::RequestChat( UnicodeString message, ChatType format )
{
	LANMessage msg;
	fillInLANMessage( &msg );
	wcsncpy(msg.Chat.gameName, (m_currentGame)?m_currentGame->getName().str():L"", g_lanGameNameLength);
	msg.Chat.gameName[g_lanGameNameLength] = 0;
	msg.LANMessageType = LANMessage::MSG_CHAT;
	msg.Chat.chatType = format;
	wcsncpy(msg.Chat.message, message.str(), g_lanMaxChatLength);
	msg.Chat.message[g_lanMaxChatLength] = 0;
	sendMessage(&msg);

	OnChat(m_name, m_localIP, message, format);
}

// ?RequestGameStart@LANAPI@@UAEXXZ present-unmatched
void LANAPI::RequestGameStart( void )
{
	if (m_inLobby || !m_currentGame || m_currentGame->getIP(0) != m_localIP)
		return;

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_GAME_START;
	fillInLANMessage( &msg );
	sendMessage(&msg);
	m_transport->update(); // force a send

	OnGameStart();
}

void LANAPI::ResetGameStartTimer( void )
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
}

// ?RequestGameStartTimer@LANAPI@@UAEXH@Z present-unmatched
void LANAPI::RequestGameStartTimer( Int seconds )
{
	if (m_inLobby || !m_currentGame || m_currentGame->getIP(0) != m_localIP)
		return;

	UnsignedInt now = timeGetTime();
	m_gameStartTime = now + 1000;
	m_gameStartSeconds = (seconds) ? seconds - 1 : 0;

	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_GAME_START_TIMER;
	msg.StartTimer.seconds = seconds;
	fillInLANMessage( &msg );
	sendMessage(&msg);
	m_transport->update(); // force a send

	OnGameStartTimer(seconds);
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_RequestGameOptions.cpp
// ?RequestGameOptions@LANAPI@@UAEXVAsciiString@@_NI@Z present-unmatched
void LANAPI::RequestGameOptions( AsciiString gameOptions, Bool isPublic, UnsignedInt ip /* = 0 */ )
{
	DEBUG_ASSERTCRASH(gameOptions.getLength() < m_lanMaxOptionsLength, ("Game options string is too long!"));

	if (!m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage( &msg );
	msg.LANMessageType = LANMessage::MSG_GAME_OPTIONS;
	strncpy(msg.GameOptions.options, gameOptions.str(), m_lanMaxOptionsLength);
	msg.GameOptions.options[m_lanMaxOptionsLength] = 0;
	sendMessage(&msg, ip);

	m_lastGameopt = gameOptions;

	int player;
	for (player = 0; player<MAX_SLOTS; ++player)
	{
		if (m_currentGame->getIP(player) == m_localIP)
		{
			OnGameOptions(m_localIP, player, AsciiString(msg.GameOptions.options));
			break;
		}
	}

	// We can request game options (side, color, etc) while we don't have a slot yet.  Of course, we don't need to
	// call OnGameOptions for those, so it's okay to silently fail.
	//DEBUG_ASSERTCRASH(player != MAX_SLOTS, ("Requested game options, but we're not in slot list!");
}

// ?RequestGameCreate@LANAPI@@UAEXVUnicodeString@@_N@Z
// Body in Code/masm_dumps/_sa7__RequestGameCreate_LANAPI__UAEXVUnicodeString___N__687E90.asm (exact 722B retail @ 0x00687E90).
/*static const char slotListID		= 'S';
static const char gameOptionsID	= 'G';
static const char acceptID			= 'A';
static const char wannaStartID	= 'W';

// ?createSlotString@LANAPI@@ present-unmatched
AsciiString LANAPI::createSlotString( void )
{
	AsciiString slotList;
	slotList.concat(slotListID);
	for (int i=0; i<MAX_SLOTS; ++i)
	{
		LANGameSlot *slot = GetMyGame()->getLANSlot(i);
		AsciiString str;
		if (slot->isHuman())
		{
			str = "H";
			LANPlayer *user = slot->getUser();
			DEBUG_ASSERTCRASH(user, ("Human player has no User*!"));
			AsciiString name;
			name.translate(user->getName());
			str.concat(name);
			str.concat(',');
		}
		else if (slot->isAI())
		{
			if (slot->getState() == SLOT_EASY_AI)
				str = "CE,";
			if (slot->getState() == SLOT_MED_AI)
				str = "CM,";
			else
				str = "CB,";
		}
		else if (slot->getState() == SLOT_OPEN)
		{
			str = "O,";
		}
		else if (slot->getState() == SLOT_CLOSED)
		{
			str = "X,";
		}
		else
		{
			DEBUG_ASSERTCRASH(false, ("Bad slot type"));
			str = "X,";
		}

		slotList.concat(str);
	}
	return slotList;
}
*/
/*
// ?RequestSlotList@LANAPI@@ present-unmatched
void LANAPI::RequestSlotList( void )
{

	LANMessage reply;
	reply.LANMessageType = LANMessage::MSG_GAME_ANNOUNCE;
	wcsncpy(reply.name, m_name.str(), g_lanPlayerNameLength);
	reply.name[g_lanPlayerNameLength] = 0;
	int player;
	for (player = 0; player < MAX_SLOTS; ++player)
	{
		wcsncpy(reply.GameInfo.name[player], m_currentGame->getPlayerName(player).str(), g_lanPlayerNameLength);
		reply.GameInfo.name[player][g_lanPlayerNameLength] = 0;
		reply.GameInfo.ip[player] = m_currentGame->getIP(player);
		reply.GameInfo.playerAccepted[player] = m_currentGame->getSlot(player)->isAccepted();
	}
	wcsncpy(reply.GameInfo.gameName, m_currentGame->getName().str(), g_lanGameNameLength);
	reply.GameInfo.gameName[g_lanGameNameLength] = 0;
	reply.GameInfo.inProgress = m_currentGame->isGameInProgress();

	sendMessage(&reply);

	OnSlotList(LANAPIInterface::RET_OK, m_currentGame);
} // void LANAPI::RequestSlotList( void )
*/
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_RequestSetName.cpp
// ?RequestSetName@LANAPI@@UAEXVUnicodeString@@@Z present-unmatched
void LANAPI::RequestSetName( UnicodeString newName )
{
	newName.trim();
	if (m_pendingAction != ACT_NONE)
	{
		// Can't change name while joining games
		OnNameChange(m_localIP, newName);
		return;
	}

	// Set up timer
	m_lastResendTime = timeGetTime();

	if (m_inLobby && m_pendingAction == ACT_NONE)
	{
		m_name = newName;
		LANMessage msg;
		fillInLANMessage( &msg );
		msg.LANMessageType = LANMessage::MSG_LOBBY_ANNOUNCE;
		sendMessage(&msg);

		// Update the interface
		LANPlayer *player = LookupPlayer(m_localIP);
		if (!player)
		{
			player = NEW LANPlayer;
			player->setIP(m_localIP);
		}
		else
		{
			removePlayer(player);
		}
		player->setName(m_name);
		player->setHost(m_hostName);
		player->setLogin(m_userName);
		player->setLastHeard(timeGetTime());

		addPlayer(player);

		OnNameChange(player->getIP(), player->getName());
	}
}

// ?fillInLANMessage@LANAPI@@UAEXPAULANMessage@@@Z present-unmatched
void LANAPI::fillInLANMessage( LANMessage *msg )
{
	if (!msg)
		return;

	wcsncpy(msg->name, m_name.str(), g_lanPlayerNameLength);
	msg->name[g_lanPlayerNameLength] = 0;
	strncpy(msg->userName, m_userName.str(), g_lanLoginNameLength);
	msg->userName[g_lanLoginNameLength] = 0;
	strncpy(msg->hostName, m_hostName.str(), g_lanHostNameLength);
	msg->hostName[g_lanHostNameLength] = 0;
}

void LANAPI::RequestLobbyLeave( Bool forced )
{
	LANMessage msg;
	msg.LANMessageType = LANMessage::MSG_REQUEST_LOBBY_LEAVE;
	fillInLANMessage( &msg );
	sendMessage(&msg);

	if (forced)
		m_transport->update();
}

// BFME keeps LANGameInfo's list pointer at +0x398 where the vendored header
// puts it at +0x360, so every walk of m_games goes through this view rather
// than getNext()/setNext().
struct BfmeLANGameLink
{
	UnsignedByte pad[0x398];
	LANGameInfo *next;								///< retail LANGameInfo+0x398
};

#define BFME_LAN_NEXT(g) (((BfmeLANGameLink *)(g))->next)

// Misc utility functions
// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_LookupGame.cpp
// ?LookupGame@LANAPI@@UAEPAVLANGameInfo@@VUnicodeString@@@Z present-unmatched
LANGameInfo * LANAPI::LookupGame( UnicodeString gameName )
{
	LANGameInfo *theGame = m_games;

	while (theGame && theGame->getName() != gameName)
	{
		theGame = theGame->getNext();
	}

	return theGame; // NULL means we didn't find anything.
}

LANGameInfo * LANAPI::LookupGameByListOffset( Int offset )
{
	#pragma pack(push, 1)
	struct RetailLANGameInfoLayout {
		char padding[0x398];
		LANGameInfo *next;
	};
	#pragma pack(pop)
	LANGameInfo *theGame = m_games;

	if (offset < 0)
		return NULL;

	while (offset-- && theGame)
	{
		theGame = reinterpret_cast<RetailLANGameInfoLayout *>(theGame)->next;
	}

	return theGame; // NULL means we didn't find anything.
}

void LANAPI::removeGame( LANGameInfo *game )
{
	LANGameInfo *g = m_games;
	// BFME returns on an empty list too; the reference tests only `game` and
	// then walks into the else branch with a null g.
	if (!game || !g)
	{
		return;
	}
	else if (m_games == game)
	{
		m_games = BFME_LAN_NEXT(m_games);
	}
	else
	{
		while (BFME_LAN_NEXT(g) && BFME_LAN_NEXT(g) != game)
		{
			g = BFME_LAN_NEXT(g);
		}
		if (BFME_LAN_NEXT(g) == game)
		{
			BFME_LAN_NEXT(g) = BFME_LAN_NEXT(game);
		}
	}
}

// ?LookupPlayer@LANAPI@@UAEPAVLANPlayer@@I@Z present-unmatched
LANPlayer * LANAPI::LookupPlayer( UnsignedInt playerIP )
{
	LANPlayer *thePlayer = m_lobbyPlayers;

	while (thePlayer && thePlayer->getIP() != playerIP)
	{
		thePlayer = thePlayer->getNext();
	}

	return thePlayer; // NULL means we didn't find anything.
}

void LANAPI::removePlayer( LANPlayer *player )
{
	LANPlayer *p = m_lobbyPlayers;
	if (!player)
	{
		return;
	}
	else if (m_lobbyPlayers == player)
	{
		m_lobbyPlayers = m_lobbyPlayers->getNext();
	}
	else
	{
		while (p->getNext() && p->getNext() != player)
		{
			p = p->getNext();
		}
		if (p->getNext() == player)
		{
			p->setNext(player->getNext());
		}
		else
		{
			// Odd.  We went the whole way without finding it in the list.
			DEBUG_ASSERTCRASH(false, ("LANPlayer wasn't in the list"));
		}
	}
}

// byte-exact reconstruction: Code/GameEngine/Source/GameNetwork/LANAPI_addGame.cpp
// ?addGame@LANAPI@@IAEXPAVLANGameInfo@@@Z present-unmatched
void LANAPI::addGame( LANGameInfo *game )
{
	if (!m_games)
	{
		m_games = game;
		game->setNext(NULL);
		return;
	}
	else
	{
		if (game->getName().compareNoCase(m_games->getName()) < 0)
		{
			game->setNext(m_games);
			m_games = game;
			return;
		}
		else
		{
			LANGameInfo *g = m_games;
			while (g->getNext() && g->getNext()->getName().compareNoCase(game->getName()) > 0)
			{
				g = g->getNext();
			}
			game->setNext(g->getNext());
			g->setNext(game);
			return;
		}
	}
}

// ?addPlayer@LANAPI@@IAEXPAVLANPlayer@@@Z present-unmatched
void LANAPI::addPlayer( LANPlayer *player )
{
	if (!m_lobbyPlayers)
	{
		m_lobbyPlayers = player;
		player->setNext(NULL);
		return;
	}
	else
	{
		if (player->getName().compareNoCase(m_lobbyPlayers->getName()) < 0)
		{
			player->setNext(m_lobbyPlayers);
			m_lobbyPlayers = player;
			return;
		}
		else
		{
			LANPlayer *p = m_lobbyPlayers;
			while (p->getNext() && p->getNext()->getName().compareNoCase(player->getName()) > 0)
			{
				p = p->getNext();
			}
			player->setNext(p->getNext());
			p->setNext(player);
			return;
		}
	}
}

// ?SetLocalIP@LANAPI@@UAE_NI@Z present-unmatched
Bool LANAPI::SetLocalIP( UnsignedInt localIP )
{
	Bool retval = TRUE;
	m_localIP = localIP;

	m_transport->reset();
	retval = m_transport->init(m_localIP, lobbyPort);
	m_transport->allowBroadcasts(true);

	return retval;
}

// The two SetLocalIP overloads are six BFME-only virtuals further down the
// vtable than this tree's header puts them: retail dispatches the UnsignedInt
// one at +0xB4 where the shim lands it at +0x9C. MSVC lays overloads of one
// virtual name out in reverse, so declaring the pair in Zero Hour's order makes
// the UnsignedInt body slot 45 and this one slot 44.
class BfmeLANLocalIPView
{
public:
	virtual void _bfme_ip_v0( void ) = 0;
	virtual void _bfme_ip_v1( void ) = 0;
	virtual void _bfme_ip_v2( void ) = 0;
	virtual void _bfme_ip_v3( void ) = 0;
	virtual void _bfme_ip_v4( void ) = 0;
	virtual void _bfme_ip_v5( void ) = 0;
	virtual void _bfme_ip_v6( void ) = 0;
	virtual void _bfme_ip_v7( void ) = 0;
	virtual void _bfme_ip_v8( void ) = 0;
	virtual void _bfme_ip_v9( void ) = 0;
	virtual void _bfme_ip_v10( void ) = 0;
	virtual void _bfme_ip_v11( void ) = 0;
	virtual void _bfme_ip_v12( void ) = 0;
	virtual void _bfme_ip_v13( void ) = 0;
	virtual void _bfme_ip_v14( void ) = 0;
	virtual void _bfme_ip_v15( void ) = 0;
	virtual void _bfme_ip_v16( void ) = 0;
	virtual void _bfme_ip_v17( void ) = 0;
	virtual void _bfme_ip_v18( void ) = 0;
	virtual void _bfme_ip_v19( void ) = 0;
	virtual void _bfme_ip_v20( void ) = 0;
	virtual void _bfme_ip_v21( void ) = 0;
	virtual void _bfme_ip_v22( void ) = 0;
	virtual void _bfme_ip_v23( void ) = 0;
	virtual void _bfme_ip_v24( void ) = 0;
	virtual void _bfme_ip_v25( void ) = 0;
	virtual void _bfme_ip_v26( void ) = 0;
	virtual void _bfme_ip_v27( void ) = 0;
	virtual void _bfme_ip_v28( void ) = 0;
	virtual void _bfme_ip_v29( void ) = 0;
	virtual void _bfme_ip_v30( void ) = 0;
	virtual void _bfme_ip_v31( void ) = 0;
	virtual void _bfme_ip_v32( void ) = 0;
	virtual void _bfme_ip_v33( void ) = 0;
	virtual void _bfme_ip_v34( void ) = 0;
	virtual void _bfme_ip_v35( void ) = 0;
	virtual void _bfme_ip_v36( void ) = 0;
	virtual void _bfme_ip_v37( void ) = 0;
	virtual void _bfme_ip_v38( void ) = 0;
	virtual void _bfme_ip_v39( void ) = 0;
	virtual void _bfme_ip_v40( void ) = 0;
	virtual void _bfme_ip_v41( void ) = 0;
	virtual void _bfme_ip_v42( void ) = 0;
	virtual void _bfme_ip_v43( void ) = 0;
	virtual Bool SetLocalIP( UnsignedInt localIP ) = 0;					///< retail vtable +0xB4
	virtual void SetLocalIP( AsciiString localIP ) = 0;					///< retail vtable +0xB8
};

void LANAPI::SetLocalIP( AsciiString localIP )
{
	// nested rather than through a named local: retail builds the resolved
	// address straight into the argument slot.
	((BfmeLANLocalIPView *)this)->SetLocalIP( ResolveIP( localIP ) );
}

// ?AmIHost@LANAPI@@UAE_NXZ present-unmatched
Bool LANAPI::AmIHost( void )
{
	return m_currentGame && m_currentGame->getIP(0) == m_localIP;
}

// ?setIsActive@LANAPI@@UAEX_N@Z present-unmatched
void LANAPI::setIsActive(Bool isActive) {
	DEBUG_LOG(("LANAPI::setIsActive - entering\n"));
	if (isActive != m_isActive) {
		DEBUG_LOG(("LANAPI::setIsActive - m_isActive changed to %s\n", isActive ? "TRUE" : "FALSE"));
		if (isActive == FALSE) {
			if ((m_inLobby == FALSE) && (m_currentGame != NULL)) {
				LANMessage msg;
				fillInLANMessage( &msg );
				msg.LANMessageType = LANMessage::MSG_INACTIVE;
				sendMessage(&msg);
				DEBUG_LOG(("LANAPI::setIsActive - sent an IsActive message\n"));
			}
		}
	}
	m_isActive = isActive;
}

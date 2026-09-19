// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/lanapi /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// partial score=0.17 date=2026-09-17
// stlport

// ?handleRequestJoin@LANAPI@@IAEXPAULANMessage@@I@Z
// Partial BFME bank for retail 0x0068C400, 2248 bytes.
// The ordered LANAPI dispatch table proves the request-join identity. The
// packed join payload, extra CRC and BFME LAN layouts are carried by the
// included BFME shim/source; the retail EH/string schedule is still open.
#include "../../Code/GameEngine/Source/GameNetwork/lanapi.cpp"

void LANAPI::handleRequestJoin( LANMessage *msg, UnsignedInt senderIP )
{
	UnsignedInt responseIP = senderIP;

	if (BFME_JOIN(msg)->gameIP != m_localIP)
	{
		return;
	}

	LANMessage reply;
	fillInLANMessage( &reply );
	if (!m_inLobby && m_currentGame && m_currentGame->getIP(0) == m_localIP)
	{
		if (m_currentGame->isGameInProgress())
		{
			reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
			reply.GameNotJoined.reason = LANAPIInterface::RET_GAME_STARTED;
			reply.GameNotJoined.gameIP = m_localIP;
			reply.GameNotJoined.playerIP = senderIP;
		}
		else
		{
			Int player;
			Bool canJoin = true;
			UnsignedInt localExeCRC = Rva0009B4B0(BFME_GDCRC->exeCRC,
				BFME_GDCRC->exeCRC);

			if (BFME_JOIN(msg)->iniCRC != BFME_GDCRC->iniCRC ||
				BFME_JOIN(msg)->exeCRC != localExeCRC ||
				BFME_JOIN(msg)->bfmeExtraCRC != BFME_GDCRC->bfmeExtraCRC)
			{
				reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
				reply.GameNotJoined.reason = LANAPIInterface::RET_CRC_MISMATCH;
				reply.GameNotJoined.gameIP = m_localIP;
				reply.GameNotJoined.playerIP = senderIP;
				canJoin = false;
			}

			AsciiString s;
			for (player = 0; canJoin && player < MAX_SLOTS; ++player)
			{
				LANGameSlot *slot = m_currentGame->getLANSlot(player);
				s.clear();
				if (player == 0)
				{
					GetStringFromRegistry("\\ergc", "", s);
				}
				else if (slot->isHuman())
				{
					s = slot->getSerial();
					if (s.isEmpty())
						s = "<Munkee>";
				}

				if (s.isNotEmpty() &&
					!strncmp(s.str(), BFME_JOIN(msg)->serial, g_maxSerialLength))
				{
					reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
					reply.GameNotJoined.reason = LANAPIInterface::RET_SERIAL_DUPE;
					reply.GameNotJoined.gameIP = m_localIP;
					reply.GameNotJoined.playerIP = senderIP;
					canJoin = false;
					break;
				}
			}

			for (player = 0; canJoin && player < MAX_SLOTS; ++player)
			{
				LANGameSlot *slot = m_currentGame->getLANSlot(player);
				if (slot->isHuman() && slot->getName().compare(msg->name) == 0)
				{
					reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
					reply.GameNotJoined.reason = LANAPIInterface::RET_DUPLICATE_NAME;
					reply.GameNotJoined.gameIP = m_localIP;
					reply.GameNotJoined.playerIP = senderIP;
					canJoin = false;
					break;
				}
			}

			Int numPlayers = 0;
			for (player = 0; player < MAX_SLOTS; ++player)
			{
				LANGameSlot *slot = m_currentGame->getLANSlot(player);
				if (slot->isOccupied() &&
					!(slot->getPlayerTemplate() == PLAYERTEMPLATE_OBSERVER))
				{
					++numPlayers;
				}
			}

			Int numStartingSpots = MAX_SLOTS;
			const MapMetaData *md = TheMapCache->findMap(m_currentGame->getMap());
			if (md != NULL)
			{
				numStartingSpots = md->m_numPlayers;
			}

			if (numPlayers < numStartingSpots)
			{
				for (player = 0; canJoin && player < MAX_SLOTS; ++player)
				{
					if (m_currentGame->getLANSlot(player)->isOpen())
					{
						reply.LANMessageType = LANMessage::MSG_JOIN_ACCEPT;
						wcsncpy(reply.GameJoined.gameName,
							m_currentGame->getName().str(), g_lanGameNameLength);
						reply.GameJoined.gameName[g_lanGameNameLength] = 0;
						reply.GameJoined.slotPosition = player;
						reply.GameJoined.gameIP = m_localIP;
						reply.GameJoined.playerIP = senderIP;

						LANGameSlot newSlot;
						newSlot.setState(SLOT_PLAYER, UnicodeString(msg->name));
						newSlot.setIP(senderIP);
						newSlot.setPort(NETWORK_BASE_PORT_NUMBER);
						newSlot.setLastHeard(timeGetTime());
						newSlot.setSerial(BFME_JOIN(msg)->serial);
						m_currentGame->setSlot(player, newSlot);
						OnPlayerJoin(player, UnicodeString(msg->name));
						responseIP = 0;
						break;
					}
				}
			}

			if (canJoin && player == MAX_SLOTS)
			{
				reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
				wcsncpy(reply.GameNotJoined.gameName,
					m_currentGame->getName().str(), g_lanGameNameLength);
				reply.GameNotJoined.gameName[g_lanGameNameLength] = 0;
				reply.GameNotJoined.reason = LANAPIInterface::RET_GAME_FULL;
				reply.GameNotJoined.gameIP = m_localIP;
				reply.GameNotJoined.playerIP = senderIP;
			}
		}
	}
	else
	{
		reply.LANMessageType = LANMessage::MSG_JOIN_DENY;
		reply.GameNotJoined.reason = LANAPIInterface::RET_GAME_GONE;
		reply.GameNotJoined.gameIP = m_localIP;
		reply.GameNotJoined.playerIP = senderIP;
	}

	sendMessage(&reply, responseIP);
	RequestGameOptions(GenerateGameOptionsString(), true);
}


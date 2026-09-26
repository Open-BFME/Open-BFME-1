// ?Rva0068BAC0@LANAPI@@QAEXPAULANMessage@@PAUBfmeNetAddress@@_N@Z
// partial score=0.58 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Reconstructed opaque LANAPI-family body at retail 0x0068BAC0.

#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	UnsignedByte m_header[0x22 - 4];
	union
	{
		WideChar name[13];
		WideChar m_gameName[17];
	};
};
#pragma pack(pop)

class LANPlayer
{
public:
	~LANPlayer();
	void setIP(BfmeNetAddress *address)
	{
		m_ip = address->m_ip;
		m_addressPadding = *(UnsignedInt *)((UnsignedByte *)address + 4);
	}
	void setName(UnicodeString name);
	void setHost(const AsciiString &name);
	void setLogin(const AsciiString &name);
	void setLastHeard(UnsignedInt time) { m_lastHeard = time; }

	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	UnsignedInt m_ip;
	UnsignedInt m_addressPadding;
};

typedef char LANPlayerSizeCheck[sizeof(LANPlayer) == 0x1c ? 1 : -1];

class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name,
		const GameSlotConnectInfo *connectInfo);
	UnsignedByte m_beforeAddress[0x30];
	BfmeNetAddress m_address;
	UnsignedByte m_afterAddress[0x0c];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot();
	LANGameSlot(const LANGameSlot &other);
	~LANGameSlot();

private:
	LANPlayer m_user;
	UnsignedByte m_serialStorage[sizeof(StringBase<char>)];
	UnsignedInt m_lastHeard;
};

typedef char LANGameSlotSizeCheck[sizeof(LANGameSlot) == 0x68 ? 1 : -1];

#pragma comment(linker, "/alternatename:??0LANGameSlot@@QAE@XZ=?j_0001de8a@@YAXXZ")

class LANGameInfo
{
public:
	Bool isGameInProgress(void) const;
	BfmeNetAddress *getIP(Int player);
	LANGameSlot *getLANSlot(Int player);
	UnicodeString getName(void) const;
	LANGameInfo *getNext(void) const;
	void resetAccepted(void);
	void setSlot(Int player, LANGameSlot slot);
	~LANGameInfo();
	UnsignedByte m_beforeSlots[0x58];
	LANGameSlot m_slots[8];
	LANGameInfo *m_next;
};

class LANAPI
{
public:
	virtual void slot00(void) = 0; virtual void slot01(void) = 0;
	virtual void slot02(void) = 0; virtual void slot03(void) = 0;
	virtual void slot04(void) = 0; virtual void slot05(void) = 0;
	virtual void slot06(void) = 0; virtual void slot07(void) = 0;
	virtual void slot08(void) = 0; virtual void slot09(void) = 0;
	virtual void slot10(void) = 0; virtual void slot11(void) = 0;
	virtual void slot12(void) = 0; virtual void slot13(void) = 0;
	virtual void slot14(void) = 0; virtual void slot15(void) = 0;
	virtual void slot16(void) = 0; virtual void slot17(void) = 0;
	virtual void slot18(void) = 0; virtual void slot19(void) = 0;
	virtual void slot20(void) = 0; virtual void slot21(void) = 0;
	virtual void slot22(void) = 0; virtual void slot23(void) = 0;
	virtual void slot24(void) = 0; virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void OnGameList(LANGameInfo *games) = 0;
	virtual void slot28(void) = 0; virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void OnHostLeave(void) = 0;
	virtual void OnPlayerLeave(UnicodeString name) = 0;
	virtual void slot33(void) = 0; virtual void slot34(void) = 0;
	virtual void slot35(void) = 0; virtual void slot36(void) = 0;
	virtual void slot37(void) = 0; virtual void slot38(void) = 0;
	virtual void slot39(void) = 0; virtual void slot40(void) = 0;
	virtual void slot41(void) = 0; virtual void slot42(void) = 0;
	virtual void slot43(void) = 0; virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual Bool AmIHost(void) = 0;
	virtual void slot47(void) = 0; virtual void slot48(void) = 0;
	virtual void slot49(void) = 0; virtual void slot50(void) = 0;
	virtual void slot51(void) = 0; virtual void slot52(void) = 0;
	virtual void slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *address) = 0;
	virtual BfmeNetAddress *getLocalAddress(void) = 0;

	void removeGame(LANGameInfo *game);
	void removePlayer(LANPlayer *player);
	void addPlayer(LANPlayer *player);
	AsciiString GenerateGameOptionsString(void);
	void RequestGameOptions(AsciiString options, Bool broadcast,
		BfmeNetAddress *address);
	void Rva0068BAC0(LANMessage *msg, BfmeNetAddress *sender,
		Bool removeLobbyGame);

	UnsignedByte m_head04[4];
	LANPlayer *m_lobbyPlayers;
	LANGameInfo *m_games;
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
	UnsignedByte m_head1c[0x3d - 0x1c];
	Bool m_inLobby;
	UnsignedByte m_head3e[2];
	LANGameInfo *m_currentGame;
	UnsignedByte m_tail44[8];
};

// The address remains in the method name until an independent identity witness
// names this body. Retail callers pass the message, its sender address, and a
// mode: network dispatch sets the mode, timeout synthesis clears it.
void LANAPI::Rva0068BAC0(LANMessage *msg, BfmeNetAddress *sender,
	Bool removeLobbyGame)
{
	if (!m_inLobby && m_currentGame &&
		!m_currentGame->isGameInProgress())
	{
		Int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slotAddress = m_currentGame->getIP(player);
			if (slotAddress->m_ip == sender->m_ip &&
				slotAddress->m_port == sender->m_port)
			{
				if (player == 0)
				{
					OnHostLeave();
					removeGame(m_currentGame);
					delete m_currentGame;
					m_currentGame = 0;

					BfmeNetAddress *localAddress = getLocalAddress();
					LANPlayer *localPlayer = LookupPlayer(localAddress);
					if (!localPlayer)
					{
						localPlayer = new LANPlayer;
						localPlayer->setIP(localAddress);
					}
					else
					{
						removePlayer(localPlayer);
					}
					localPlayer->setName(UnicodeString(m_name));
					localPlayer->setHost(m_hostName);
					localPlayer->setLogin(m_userName);
					localPlayer->setLastHeard(timeGetTime());
					addPlayer(localPlayer);
				}
				else
				{
					if (AmIHost())
					{
						LANGameSlot openSlot;
						UnicodeString slotName;
						openSlot.setState(SLOT_OPEN, slotName, 0);
						m_currentGame->setSlot(player, openSlot);
					}
					OnPlayerLeave(UnicodeString(msg->name));
					UnicodeString playerStateName;
					m_currentGame->getLANSlot(player)->setState(
						SLOT_OPEN, playerStateName, 0);
					m_currentGame->resetAccepted();
					AsciiString options = GenerateGameOptionsString();
					RequestGameOptions(options, false, sender);
				}
				break;
			}
		}
	}
	else if (m_inLobby)
	{
		LANGameInfo *game = m_games;
		while (game)
		{
			Bool gameNameMatches;
			{
				UnicodeString candidateName = game->getName();
				const unsigned short *candidate = candidateName.str();
				const unsigned short *requested = msg->m_gameName;
				while (*candidate && *candidate == *requested)
				{
					++candidate;
					++requested;
				}
				gameNameMatches = *candidate == *requested;
			}
			if (gameNameMatches)
			{
				if (removeLobbyGame)
				{
					removeGame(game);
					delete game;
					OnGameList(m_games);
				}
				break;
			}
			game = game->getNext();
		}
	}
}

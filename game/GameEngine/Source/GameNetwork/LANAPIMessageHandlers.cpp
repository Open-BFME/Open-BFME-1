// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib

// The three LANAPI handlers that decide what an incoming LANMessage means for
// the lobby or the game we are sitting in:
//
//   handleChat        0x0068B6A0, 392 bytes -- lobby chat by player address,
//                     game chat by matching the sender against a game slot.
//   handleGameOptions 0x0068B890, 106 bytes -- forward the packed options blob
//                     for the slot whose address pair matches the sender.
//   handleJoinDeny    0x0068B4C0, 101 bytes -- our own join request bounced.
//
// All three are protected (IAE) and all three take the sender as a
// TransportAddress pointer smuggled through an UnsignedInt parameter, so the
// message and the vtable are declared once here rather than once per body.
//
// LANMessage: every body agrees the payload starts at 0x22 and disagrees about
// what lives there, so the payload is a union and each arm keeps the field
// widths its own body proves. The chat and join-deny arms both open with the
// game name and size it differently (17 vs 20 WideChar); only the offsets after
// it are byte-proven, so neither length is promoted over the other.
//
// The vtable is cut at 56 slots, the last one this TU needs. Slots named by
// sibling TUs and not by these bodies -- 21 requestSerializedGameInfo,
// 34 OnHasMap, 46 AmIHost, 52 the BFME map-status callback -- stay placeholders
// here; LANAPIGames.cpp and LANAPILocalAddress.cpp hold their pins.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

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

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	WideChar name[13];
	char userName[2];
	char hostName[2];
	union
	{
		struct
		{
			WideChar gameName[17];
			Int chatType;
			WideChar message[101];
		} Chat;
		struct
		{
			WideChar gameName[20];
			UnsignedInt playerIP;
			UnsignedShort playerPort;
			UnsignedInt reason;
		} JoinDeny;
		char options[0x197];
		UnsignedByte m_bfmeRest[0x1BA];
	};
};
#pragma pack(pop)

// The slot-liveness predicate handleChat consults before it refreshes a slot's
// last-heard stamp; retail 0x00001079 off the slot record.
class BfmeM1079
{
public:
	char bfmeChk1079(void);
};

class LANPlayer
{
public:
	UnicodeString m_name;
	UnicodeString m_login;
	UnicodeString m_host;
	UnsignedInt m_lastHeard;
	LANPlayer *m_next;
	BfmeNetAddress m_address;
};

class GameSlot
{
public:
	Bool isHuman(void) const;

	UnsignedByte m_bfmeBeforeAddress[0x30];
	BfmeNetAddress m_address;				// +0x30
	UnsignedByte m_bfmeAfterAddress[0x0c];
};

class LANGameSlot : public GameSlot
{
public:
	UnsignedByte m_bfmeBeforeLastHeard[0x20];
	UnsignedInt m_lastHeard;				// +0x64
};

class GameInfo
{
public:
	Bool isGameInProgress(void) const { return m_bfmeInProgress != 0; }

protected:
	UnsignedByte m_bfmeBeforeInProgress[0x0d];
	UnsignedByte m_bfmeInProgress;				// +0x0d
	UnsignedByte m_bfmeAfterInProgress[0x58 - 0x0e];
};

class LANGameInfo : public GameInfo
{
public:
	LANGameSlot m_LANSlot[8];				// +0x58, 0x68 apart

	// Slot n's address pair therefore sits at +0x88 + 0x68n -- the offsets the
	// options walk steps through directly.
	BfmeNetAddress *getIP(Int player)
	{
		return &m_LANSlot[player].m_address;
	}

	LANGameSlot *getLANSlot(Int player)
	{
		return &m_LANSlot[player];
	}
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void OnGameJoin(UnsignedInt reason, LANGameInfo *game,
		LANMessage *message) = 0;			// slot 29, vtable+0x74
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void OnChat(UnicodeString player, BfmeNetAddress *address,
		UnicodeString message, Int chatType) = 0;	// slot 35, vtable+0x8C
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void OnGameOptions(BfmeNetAddress *sender, UnsignedInt player,
		AsciiString options) = 0;			// slot 38, vtable+0x98
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual LANGameInfo *LookupGame(UnicodeString gameName) = 0;	// slot 42, vtable+0xA8
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;	// slot 54, vtable+0xD8
	virtual BfmeNetAddress *getLocalAddress(void) = 0;		// slot 55, vtable+0xDC

protected:
	void handleChat(LANMessage *msg, UnsignedInt senderIP);
	void handleGameOptions(LANMessage *msg, UnsignedInt senderIP);
	void handleJoinDeny(LANMessage *msg, UnsignedInt senderIP);

	UnsignedByte m_bfmeHeadA[0x24 - 4];
	UnsignedInt m_pendingAction;				// +0x24
	UnsignedInt m_expiration;				// +0x28
	UnsignedByte m_bfmeHeadB[0x3d - 0x2c];
	Bool m_inLobby;						// +0x3d
	UnsignedByte m_bfmeHeadC[2];
	LANGameInfo *m_currentGame;				// +0x40
};

// ?handleChat@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleChat(LANMessage *msg, UnsignedInt senderIP)
{
	if (m_inLobby)
	{
		LANPlayer *player;
		if ((player = LookupPlayer((BfmeNetAddress *)senderIP)) != 0)
		{
			OnChat(UnicodeString(player->m_name), &player->m_address,
				UnicodeString(msg->Chat.message), msg->Chat.chatType);
			player->m_lastHeard = timeGetTime();
		}
	}
	else
	{
		if (LookupGame(UnicodeString((WideChar *)((UnsignedByte *)msg + 0x22))) != m_currentGame)
			return;

		int player;
		for (player = 0; player < 8; ++player)
		{
			BfmeNetAddress *slotAddress = m_currentGame->getIP(player);
			if (m_currentGame &&
				slotAddress->m_ip == ((BfmeNetAddress *)senderIP)->m_ip &&
				slotAddress->m_port == ((BfmeNetAddress *)senderIP)->m_port)
			{
				UnsignedInt now = timeGetTime();
				LANGameInfo *game = m_currentGame;
				if (((BfmeM1079 *)&game->m_LANSlot[player])->bfmeChk1079())
					game->m_LANSlot[player].m_lastHeard = now;

				LANMessage *chat = msg;
				OnChat(UnicodeString(chat->name),
					m_currentGame->getIP(player),
					UnicodeString(chat->Chat.message), chat->Chat.chatType);
				break;
			}
		}
	}
}

// ?handleGameOptions@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleGameOptions(LANMessage *msg, UnsignedInt senderIP)
{
	if (!m_inLobby && m_currentGame && !m_currentGame->isGameInProgress())
	{
		BfmeNetAddress *sender = (BfmeNetAddress *)senderIP;
		int player = 0;
		BfmeNetAddress *slot = m_currentGame->getIP(0);
		do
		{
			if (slot->m_ip == sender->m_ip &&
				slot->m_port == sender->m_port)
			{
				OnGameOptions(sender, player, AsciiString(msg->options));
				break;
			}
			++player;
			slot = (BfmeNetAddress *)((char *)slot + 0x68);
		}
		while (player < 8);
	}
}

// ?handleJoinDeny@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleJoinDeny(LANMessage *msg, UnsignedInt senderIP)
{
	BfmeNetAddress *address = getLocalAddress();
	if (msg->JoinDeny.playerIP != address->m_ip)
		return;

	address = getLocalAddress();
	if (msg->JoinDeny.playerPort != address->m_port)
		return;

	if (m_pendingAction == 1)
	{
		OnGameJoin(msg->JoinDeny.reason,
			LookupGame(UnicodeString(msg->JoinDeny.gameName)), msg);
		m_pendingAction = 0;
		m_expiration = 0;
	}
}

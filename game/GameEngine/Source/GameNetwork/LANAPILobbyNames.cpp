// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
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
// readable body of ?RequestSetName@LANAPI@@UAEXVUnicodeString@@@Z: game/GameEngine/Source/GameNetwork/lanapi.cpp
#define Matrix4x4 Matrix4  // BFME renamed it

// The two halves of BFME's lobby roster name path.
//
// RequestSetName (retail 0x00688220, vtable slot 24) is the local half: it
// announces our new name to the LAN and rebuilds our own LANPlayer entry.
// handleLobbyAnnounce (retail 0x0068B1E0) is the remote half: LANAPI::update
// dispatches MSG_LOBBY_ANNOUNCE (2) through table 0x00687A28 to arm
// 0x0068721B, whose call at 0x00687223 follows ILT 0x00046001 to it, passing
// a pointer to the sender address PAIR rather than the Zero Hour bare IP.
// Below the announce they are the same six statements -- look the player up by
// address, allocate one or unlink the existing entry, set the three strings,
// stamp lastHeard, re-add and call OnNameChange -- so they belong in one TU.
//
// LANPlayer is 0x1C bytes: name, login and host handles at +0x00, +0x04 and
// +0x08, lastHeard at +0x0C, next at +0x10 (what addPlayer at 0x00686FD0
// walks) and the address pair at +0x14.  The port is a word -- the constructor
// zeroes it with a 16-bit store -- but the whole eight-byte struct is assigned
// at once, which is why the copy writes +0x18 as a dword.
//
// The vtable dispatches at 0xA4/0xC4/0xD8/0xDC need every slot ahead of them
// declared, and the composable string shims give the StringBase delegation
// retail calls for trim, set, translate and the copy constructor.
//
// Original semantic bodies: lanapi.cpp and LANAPIhandlers.cpp.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

enum { LANMSG_LOBBY_ANNOUNCE = 2 };
enum { ACT_NONE = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
// Only the announce fields are named; both bodies rely on the 0x1DC size,
// which is what the 0x1E0 frame RequestSetName reserves fixes.
struct LANMessage
{
	Int LANMessageType;				// +0x00
	WideChar name[13];				// +0x04
	char userName[2];				// +0x1E
	char hostName[2];				// +0x20
	unsigned char m_bfmeRest[0x1DC - 0x22];
};

// The address pair vtable slot 55 hands back.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
public:
	LANPlayer()
	{
		m_lastHeard = 0;
		m_next = 0;
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}

	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANAPI
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
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
	virtual void RequestSetName(UnicodeString newName);			// slot 24
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void OnNameChange(BfmeNetAddress *from, UnicodeString newName) = 0;	// slot 41, vtable+0xA4
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;			// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual LANPlayer *LookupPlayer(BfmeNetAddress *who) = 0;		// slot 54, vtable+0xD8
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;			// slot 55, vtable+0xDC

protected:
	void handleLobbyAnnounce(LANMessage *msg, BfmeNetAddress *sender);
	void sendMessage(LANMessage *msg, UnsignedInt ip);			// ILT thunk 0x0002B599
	void removePlayer(LANPlayer *player);					// ILT thunk 0x0003BDF4
	void addPlayer(LANPlayer *player);					// ILT thunk 0x00045363

	unsigned char m_bfmeHeadA[0x10 - 4];
	UnicodeString m_name;				// +0x10
	AsciiString m_userName;				// +0x14
	AsciiString m_hostName;				// +0x18
	unsigned char m_bfmeHeadB[0x24 - 0x1C];
	Int m_pendingAction;				// +0x24
	unsigned char m_bfmeHeadC[0x38 - 0x28];
	UnsignedInt m_lastResendTime;			// +0x38
	unsigned char m_bfmeHeadD[0x3D - 0x3C];
	Bool m_inLobby;					// +0x3D
};

typedef char BfmeAddressSizeCheck[sizeof(BfmeNetAddress) == 8 ? 1 : -1];
typedef char BfmePlayerSizeCheck[sizeof(LANPlayer) == 0x1C ? 1 : -1];
typedef char BfmeMessageSizeCheck[sizeof(LANMessage) == 0x1DC ? 1 : -1];

// ?RequestSetName@LANAPI@@UAEXVUnicodeString@@@Z
void LANAPI::RequestSetName(UnicodeString newName)
{
	newName.trim();
	if (m_pendingAction != ACT_NONE)
	{
		// Can't change name while joining games
		OnNameChange(_bfme_localAddress(), newName);
		return;
	}

	// Set up timer
	m_lastResendTime = timeGetTime();

	if (m_inLobby && m_pendingAction == ACT_NONE)
	{
		m_name.set(newName);

		LANMessage msg;
		fillInLANMessage(&msg);
		msg.LANMessageType = LANMSG_LOBBY_ANNOUNCE;
		sendMessage(&msg, 0);

		// Update the interface
		LANPlayer *player = LookupPlayer(_bfme_localAddress());
		if (!player)
		{
			player = new LANPlayer;
			player->m_address = *_bfme_localAddress();
		}
		else
		{
			removePlayer(player);
		}

		player->m_name.set(m_name);
		player->m_host.translate(m_hostName);
		player->m_login.translate(m_userName);
		player->m_lastHeard = timeGetTime();

		addPlayer(player);

		OnNameChange(&player->m_address, player->m_name);
	}
}

// ?handleLobbyAnnounce@LANAPI@@IAEXPAULANMessage@@PAUBfmeNetAddress@@@Z
void LANAPI::handleLobbyAnnounce(LANMessage *msg, BfmeNetAddress *sender)
{
    LANPlayer *player = LookupPlayer(sender);
    if (!player) {
        player = new LANPlayer;
        player->m_address = *sender;
    } else {
        removePlayer(player);
    }
    player->m_name.set(UnicodeString(msg->name));
    player->m_host.translate(AsciiString(msg->hostName));
    player->m_login.translate(AsciiString(msg->userName));
    player->m_lastHeard = timeGetTime();
    addPlayer(player);
    OnNameChange(&player->m_address, player->m_name);
}

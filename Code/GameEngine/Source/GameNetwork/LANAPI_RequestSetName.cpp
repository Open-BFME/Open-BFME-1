// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/campaignmanagerascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib

// stlport
// readable body of ?RequestSetName@LANAPI@@UAEXVUnicodeString@@@Z: Code/GameEngine/Source/GameNetwork/lanapi.cpp
#define Matrix4x4 Matrix4  // BFME renamed it

// Retail 0x00688220, LANAPI vtable slot 24 -- Zero Hour's RequestSetName, whose
// ported body sits in lanapi.cpp marked present-unmatched. This is that body,
// with BFME's two substitutions: the callbacks take the address pair vtable slot
// 55 returns rather than a bare m_localIP, and the announce message type is 2.
//
// It also fixes LANPlayer at 0x1C bytes -- name, login and host handles at +0x00,
// +0x04 and +0x08, lastHeard at +0x0C, next at +0x10 (which is what addPlayer at
// 0x00686FD0 walks) and the address pair at +0x14 -- and confirms the LANAPI
// offsets ~LANAPI implied: UnicodeString m_name at +0x10 with the two AsciiStrings
// after it.
//
// Its own TU: the 0xA4/0xC4/0xD8/0xDC dispatches need the slots ahead of them
// declared, and the composable string shims give the StringBase delegation retail
// calls for trim, set and the copy constructor.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

enum { LANMSG_LOBBY_ANNOUNCE = 2 };
enum { ACT_NONE = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	Int LANMessageType;				// +0x00
	unsigned char m_bfmeRest[0x1DC - 4];
};

// The address pair vtable slot 55 hands back. The port is a word -- LANPlayer's
// constructor zeroes it with a 16-bit store -- but the whole eight-byte struct
// is assigned at once, which is why the copy writes +0x18 as a dword.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
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

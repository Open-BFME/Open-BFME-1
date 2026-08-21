// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib

// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

// Retail 0x00686850, LANAPI vtable slot 20 -- Zero Hour's RequestGameOptions,
// whose three by-value arguments give the ret 0xC the slot carries.
//
// Two things the body settles. The slot stride in LANGameInfo is 0x68 and the
// loop stops at 0x340, so MAX_SLOTS is 8 and the per-slot address pairs start at
// game+0x88 -- the same +0x88/+0x8C AmIHost compares for slot 0. And LANMessage
// is a union: the option string sits at +0x22 here where RequestGameAnnounce
// puts the wide game name, with its terminator at +0x1B8.
//
// isPublic is never read, exactly as in Zero Hour.

#include "PreRTS.h"
#include "Common/AsciiString.h"

extern "C" __declspec(dllimport) char *__cdecl strncpy(char *dest, const char *src, unsigned int count);

enum { LANMSG_GAME_OPTIONS = 0xF };
enum { LAN_MAX_OPTIONS_LENGTH = 0x196, LAN_MAX_SLOTS = 8 };

struct LANMessage
{
	Int LANMessageType;				// +0x00
	unsigned char m_bfmeHeader[0x22 - 4];		// filled in by fillInLANMessage
	char options[LAN_MAX_OPTIONS_LENGTH + 1];	// +0x22, terminator at +0x1B8
	unsigned char m_bfmeTail[0x1DC - 0x1B9];
};

// What LANAPI's vtable slot 55 hands back, and what OnGameOptions takes.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// One per-slot record, 0x68 apart: the loop steps edi by 0x68 and stops at
// 0x340, which is eight of them.
struct BfmeLANSlot
{
	BfmeNetAddress m_address;			// +0x00 of the slot
	unsigned char m_bfmeRest[0x68 - 8];
};

class LANGameInfo
{
public:
	unsigned char m_bfmeHead[0x88];
	BfmeLANSlot m_slot[LAN_MAX_SLOTS];		// +0x88
};

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
	virtual void RequestGameOptions(AsciiString gameOptions, Bool isPublic, UnsignedInt ip);	// slot 20
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
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
	virtual void OnGameOptions(BfmeNetAddress *from, Int playerSlot, AsciiString options) = 0;	// slot 38, vtable+0x98
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *msg) = 0;		// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;		// slot 55, vtable+0xDC

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip);		// ILT thunk 0x0002B599

	unsigned char m_bfmeHead[0x40 - 4];
	LANGameInfo *m_currentGame;					// +0x40
};

// ?RequestGameOptions@LANAPI@@UAEXVAsciiString@@_NI@Z
void LANAPI::RequestGameOptions(AsciiString gameOptions, Bool isPublic, UnsignedInt ip)
{
	if (!m_currentGame)
		return;

	LANMessage msg;
	fillInLANMessage(&msg);
	msg.LANMessageType = LANMSG_GAME_OPTIONS;
	strncpy(msg.options, gameOptions.str(), LAN_MAX_OPTIONS_LENGTH);
	msg.options[LAN_MAX_OPTIONS_LENGTH] = 0;
	sendMessage(&msg, ip);

	Int player;
	for (player = 0; player < LAN_MAX_SLOTS; ++player)
	{
		BfmeNetAddress *slot = &m_currentGame->m_slot[player].m_address;
		BfmeNetAddress *me = _bfme_localAddress();

		if (slot->m_ip == me->m_ip && slot->m_port == me->m_port)
		{
			OnGameOptions(_bfme_localAddress(), player, AsciiString(msg.options));
			break;
		}
	}
}

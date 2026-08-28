// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?RequestGameAnnounce@LANAPI@@UAEXXZ: Code/GameEngine/Source/GameNetwork/lanapi.cpp

// Retail 0x00685FC0, LANAPI vtable slot 23 -- between RequestGameOptions at 20
// and RequestGameCreate at 22, whose row is already ledgered, in Zero Hour's
// declaration order.
//
// No SEH frame at all despite a UnicodeString temporary with a destructor, so
// this TU is built /EHs-c-. Note the spelling: /EHsc- parses as /EHs plus
// /EHc-, which leaves handling ON and puts two unwind-state stores in the body.
//
// LANMessage's shape falls out of the offsets: the type word at +0x00, the
// wide game name at +0x22 with its terminator at +0x42 (sixteen characters),
// inProgress at +0x44, isDirectConnect at +0x45, and the option string filling
// +0x46 for 0x196 bytes, which lands exactly on the 0x1E0 the frame reserves.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef bool Bool;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar *dest, const WideChar *src, unsigned int count);

enum { LANMSG_GAME_ANNOUNCE = 1 };
enum { LAN_GAME_NAME_LENGTH = 16, LAN_MAX_OPTIONS_LENGTH = 0x196 };

struct BfmeUnicodeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	~UnicodeString() { releaseBuffer(); }

	const WideChar *str() const { return m_data ? (const WideChar *)(m_data + 1) : (const WideChar *)L""; }

protected:
	void releaseBuffer();				// retail 0x008881D0

	BfmeUnicodeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
struct LANMessage
{
	Int LANMessageType;				// +0x00
	unsigned char m_bfmeHeader[0x22 - 4];		// filled in by fillInLANMessage
	WideChar gameName[LAN_GAME_NAME_LENGTH + 1];	// +0x22
	Bool inProgress;				// +0x44
	Bool isDirectConnect;				// +0x45
	char options[LAN_MAX_OPTIONS_LENGTH];		// +0x46
};

// What LANAPI's vtable slot 55 hands back.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	UnicodeString getName(void);			// ILT thunk 0x00041FC9

	unsigned char m_bfmeHeadA[0x0D];
	Bool m_inProgress;				// +0x0D
	unsigned char m_bfmeHeadB[0x88 - 0x0E];
	UnsignedInt m_hostIP;				// +0x88
	UnsignedShort m_hostPort;			// +0x8C
	unsigned char m_bfmeTail[0x3A4 - 0x8E];
	Bool m_isDirectConnect;				// +0x3A4
};

void writeLANGameInfo(const LANGameInfo *game, char *buffer, UnsignedInt size);

class Network
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
	virtual Bool isPacketRouter(void) = 0;		// slot 35, vtable+0x8C
};

extern Network *TheNetwork;

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
	virtual void RequestGameAnnounce(void);		// slot 23
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
	virtual void _bfme_slot38(void) = 0;
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
	virtual void fillInLANMessage(LANMessage *msg) = 0;	// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;	// slot 55, vtable+0xDC

protected:
	void sendMessage(LANMessage *msg, UnsignedInt ip);	// ILT thunk 0x0002B599

	unsigned char m_bfmeHead[0x40 - 4];
	LANGameInfo *m_currentGame;			// +0x40
};

// ?RequestGameAnnounce@LANAPI@@UAEXXZ
void LANAPI::RequestGameAnnounce(void)
{
	LANGameInfo *game = m_currentGame;

	// In game - are we a game host?
	if (game && !game->m_isDirectConnect)
	{
		BfmeNetAddress *me = _bfme_localAddress();

		// if we are in game we should reply if we are the packet router
		if ((game->m_hostIP == me->m_ip && game->m_hostPort == me->m_port)
			|| (m_currentGame->m_inProgress && TheNetwork && TheNetwork->isPacketRouter()))
		{
			LANMessage reply;
			fillInLANMessage(&reply);
			reply.LANMessageType = LANMSG_GAME_ANNOUNCE;

			writeLANGameInfo(m_currentGame, reply.options, LAN_MAX_OPTIONS_LENGTH);
			wcsncpy(reply.gameName, m_currentGame->getName().str(), LAN_GAME_NAME_LENGTH);
			reply.gameName[LAN_GAME_NAME_LENGTH] = 0;
			reply.inProgress = m_currentGame->m_inProgress;
			reply.isDirectConnect = m_currentGame->m_isDirectConnect;

			sendMessage(&reply, 0);
		}
	}
}

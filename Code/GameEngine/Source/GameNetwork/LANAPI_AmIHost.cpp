// cl: /DNDEBUG /MD /GX

// Retail 0x006852E0, LANAPI vtable slot 46 (table at 0x0111AF50).
//
// Slot 43 is LookupGameByListOffset and slot 53 is OnInActive, both already in
// the ledger, and slots 44/45 are the two SetLocalIP overloads -- 0x00686C10
// takes the AsciiString and forwards to slot 45. That puts Zero Hour's AmIHost
// and GetMyName at 46 and 47, and slot 47 is the 32-byte body ledgered as
// GetMyName's duplicate. Zero Hour's AmIHost is the same test: no current game
// means no, otherwise compare the game's host address against our own.
//
// Its own TU: the answer comes back from vtable+0xDC, which is slot 55, and the
// compiler only encodes 0xDC if the 55 slots ahead of it are declared.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// What slot 55 hands back: retail compares its first dword and the word at +4
// against the game's fields at +0x88 and +0x8C.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	unsigned char m_bfmeHead[0x88];
	UnsignedInt m_hostIP;			// +0x88
	UnsignedShort m_hostPort;		// +0x8C
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
	virtual Int AmIHost(void);			// slot 46, and it really does return 32 bits
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;	// slot 55, vtable+0xDC

protected:
	unsigned char m_bfmeHead[0x40 - 4];	// after the vptr
	LANGameInfo *m_currentGame;		// +0x40
};

// Zero Hour returns Bool here, and BFME's Bool is bool -- ?RequestLobbyLeave@LANAPI@@UAEX_N@Z
// is a matched row taking one. This body is not: it sets the whole of eax
// (b8 01 00 00 00 / 33 c0) where a bool return gives mov al,1 / xor al,al, so
// the declared type is 32 bits wide. Hence the H in the symbol, not _N.
Int LANAPI::AmIHost(void)
{
	LANGameInfo *game = m_currentGame;
	if (game != 0)
	{
		BfmeNetAddress *me = _bfme_localAddress();
		if (game->m_hostIP == me->m_ip && game->m_hostPort == me->m_port)
			return 1;
	}

	return 0;
}

// cl: /DNDEBUG /MD /GX

// Retail 0x00685E90, LANAPI vtable slot 12 (table at 0x0111AF50).
// This is Zero Hour's RequestGameJoinDirectConnect flow with BFME's address
// pair in place of a bare IP and BFME's three-argument OnGameJoin callback.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar *dest, const WideChar *src, UnsignedInt count);
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

enum
{
	RET_GAME_GONE = 8,
	RET_BUSY = 9,
	ACT_NONE = 0,
	ACT_JOINDIRECTCONNECT = 2,
	LANMSG_REQUEST_GAME_INFO = 0x11,
	LAN_PLAYER_NAME_LENGTH = 12
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	unsigned short m_port;
};

struct BfmeUnicodeStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_len;
	unsigned short m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class Rva00685E90UnicodeString
{
public:
	const WideChar *str(void) const
	{
		return m_data ? (const WideChar *)(m_data + 1) : (const WideChar *)L"";
	}

private:
	BfmeUnicodeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
#pragma pack(push, 1)
struct LANMessage
{
	Int m_type;                              // +0x00
	unsigned char m_bfmeHeader[0x22 - 4];
	UnsignedInt m_addressIP;                 // +0x22
	unsigned short m_addressPort;            // +0x26
	WideChar m_playerName[LAN_PLAYER_NAME_LENGTH + 1]; // +0x28
	unsigned char m_bfmeTail[0x1DC - 0x42];
};
#pragma pack(pop)

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
	virtual void requestGameJoinDirectConnectAddress(BfmeNetAddress *address); // slot 12
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
	virtual void OnGameJoin(Int reason, void *game, void *extra) = 0; // slot 29, +0x74
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
	virtual void fillInLANMessage(LANMessage *msg) = 0; // slot 49, +0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0; // slot 55, +0xDC

protected:
	void sendMessage(LANMessage *msg, UnsignedInt address); // ILT 0x0002B599

	unsigned char m_bfmeHeadA[0x10 - 4];
	Rva00685E90UnicodeString m_name; // +0x10
	unsigned char m_bfmeHeadB[0x24 - 0x14];
	Int m_pendingAction;             // +0x24
	UnsignedInt m_expiration;        // +0x28
	UnsignedInt m_actionTimeout;     // +0x2C
	BfmeNetAddress m_directConnectRemoteAddress; // +0x30
};

void LANAPI::requestGameJoinDirectConnectAddress(BfmeNetAddress *address)
{
	if (m_pendingAction != ACT_NONE)
	{
		OnGameJoin(RET_BUSY, 0, 0);
		return;
	}

	if (address->m_ip == 0 && address->m_port == 0)
	{
		OnGameJoin(RET_GAME_GONE, 0, 0);
		return;
	}

	m_directConnectRemoteAddress = *address;

	LANMessage msg;
	msg.m_type = LANMSG_REQUEST_GAME_INFO;
	fillInLANMessage(&msg);
	msg.m_addressIP = _bfme_localAddress()->m_ip;
	msg.m_addressPort = _bfme_localAddress()->m_port;
	wcsncpy(msg.m_playerName, m_name.str(), LAN_PLAYER_NAME_LENGTH);
	msg.m_playerName[LAN_PLAYER_NAME_LENGTH] = 0;

	sendMessage(&msg, (UnsignedInt)address);

	m_pendingAction = ACT_JOINDIRECTCONNECT;
	m_expiration = timeGetTime() + m_actionTimeout;
}

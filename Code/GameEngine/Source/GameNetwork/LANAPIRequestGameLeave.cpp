// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// BFME LANAPI::RequestGameLeave, retail 0x00687CE0, 341 bytes.
// The local mirror keeps the BFME LANAPI offsets witnessed by
// tools/bfme_layout.py: m_name +0x10, m_pendingAction +0x24,
// m_inLobby +0x3D, m_currentGame +0x40, and m_memberObject +0x4C.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

#include "StringInline.h"

extern const char g_bfmeEmptyUnicode[];

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcsncpy(unsigned short *, const unsigned short *, unsigned int);

const unsigned short *UnicodeString::str(void) const
{
	return m_data ? m_data->m_text : (const unsigned short *)g_bfmeEmptyUnicode;
}

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANGameInfo
{
public:
	UnicodeString getName(void);
	~LANGameInfo(void);

	unsigned char m_pad0[0x88];
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct LANMessage
{
	Int LANMessageType;
	unsigned char m_bfmeRest[0x1DC - 4];
};

class LANAPIRequestPacket;

class LANAPIMemberObject
{
public:
	void flushQueue(void);
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
	virtual void RequestGameLeave(void);
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
	virtual void OnPlayerLeave(UnicodeString name) = 0;
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
	virtual void fillInLANMessage(LANMessage *msg) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;
	void queuePacket(LANAPIRequestPacket *packet, int ip);

protected:
	void removeGame(LANGameInfo *game);

	unsigned char m_bfmeHeadA[0x10 - 4];
	UnicodeString m_name;
	unsigned char m_bfmeHeadA2[0x24 - 0x14];
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	unsigned char m_bfmeHeadB[0x3D - 0x30];
	Bool m_inLobby;
	unsigned char m_bfmeHeadC[0x40 - 0x3E];
	LANGameInfo *m_currentGame;
	unsigned char m_bfmeHeadD[0x4C - 0x44];
	LANAPIMemberObject *m_memberObject;
};

// ?RequestGameLeave@LANAPI@@UAEXXZ
void LANAPI::RequestGameLeave(void)
{
	LANMessage msg;
	LANGameInfo *game = m_currentGame;

	if (game != 0) {
		BfmeNetAddress *local = _bfme_localAddress();
		msg.LANMessageType = (game->m_ip == local->m_ip && game->m_port == local->m_port) ? 8 : 6;
	} else {
		msg.LANMessageType = 6;
	}

	fillInLANMessage(&msg);

	game = m_currentGame;
	wcsncpy((unsigned short *)((char *)&msg + 0x22), game ? game->getName().str() : L"", 0x10);
	*((unsigned short *)((char *)&msg + 0x42)) = 0;

	queuePacket((LANAPIRequestPacket *)&msg, 0);
	m_memberObject->flushQueue();

	game = m_currentGame;
	if (game != 0) {
		BfmeNetAddress *local = _bfme_localAddress();
		if (game->m_ip == local->m_ip && game->m_port == local->m_port) {
			OnPlayerLeave(m_name);
			removeGame(m_currentGame);
			delete m_currentGame;
			m_currentGame = 0;
			m_inLobby = true;
			return;
		}
	}

	m_pendingAction = 3;
	m_expiration = timeGetTime() + m_actionTimeout;
}

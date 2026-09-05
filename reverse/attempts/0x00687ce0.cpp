// ?RequestGameLeave@LANAPI@@QAEXXZ
// partial score=0.6 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc

// LANAPI::RequestGameLeave, retail 0x00687CE0, 341 bytes.
//
// Structurally ZH's RequestGameLeave (reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameNetwork/LANAPI.cpp), adapted the same way BFME
// adapted RequestSetName (LANAPI_RequestSetName.cpp): the host check happens
// through the vtable+0xDC "local address" accessor rather than a bare
// m_localIP, the message is queued through queuePacket()/flushQueue() rather
// than a direct sendMessage(), and OnPlayerLeave gained an explicit
// UnsignedInt ip parameter (the departing game's stored address) ahead of the
// UnicodeString name, matching OnNameChange's two-parameter shape at +0xA4.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" unsigned short *__cdecl wcsncpy(unsigned short *, const unsigned short *, unsigned int);
#pragma intrinsic(wcsncpy)

extern const unsigned short g_bfmeEmptyUnicode[];

struct UnicodeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class UnicodeString
{
public:
	~UnicodeString();							// ?releaseBuffer@?$StringBase@G@@AAEXXZ
	const unsigned short *str() const { return m_data ? (const unsigned short *)(m_data + 1) : g_bfmeEmptyUnicode; }
private:
	UnicodeStringData *m_data;
};

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANAPI.h
class LANGameInfo
{
public:
	UnicodeString getName(void);				// ILT thunk 0x00041FC9

	unsigned char m_pad0[0x88];
	UnsignedInt m_ip;							// +0x88
	UnsignedShort m_port;						// +0x8C
};

struct LANMessage
{
	Int LANMessageType;							// +0x00
	unsigned char m_bfmeRest[0x1DC - 4];
};

class LANAPIMemberObject
{
public:
	void flushQueue(void);						// ILT thunk 0x00001EC4
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
	virtual void OnPlayerLeave(UnsignedInt ip, UnicodeString name) = 0;	// slot 32, vtable+0x80
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
	virtual void fillInLANMessage(LANMessage *msg) = 0;			// slot 49, vtable+0xC4
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0;			// slot 55, vtable+0xDC

	void RequestGameLeave(void);

protected:
	void queuePacket(LANMessage *packet, int ip);		// ILT thunk 0x0002B599
	void removeGame(LANGameInfo *game);					// ILT thunk 0x0001BBD0

	unsigned char m_bfmeHeadA[0x10 - 4];
	UnicodeString m_name;						// +0x10
	unsigned char m_bfmeHeadA2[0x24 - 0x14];
	Int m_pendingAction;						// +0x24
	UnsignedInt m_expiration;					// +0x28
	UnsignedInt m_actionTimeout;				// +0x2C
	unsigned char m_bfmeHeadB[0x3D - 0x30];
	Bool m_inLobby;								// +0x3D
	unsigned char m_bfmeHeadC[0x40 - 0x3E];
	LANGameInfo *m_currentGame;					// +0x40
	unsigned char m_bfmeHeadD[0x4C - 0x44];
	LANAPIMemberObject *m_memberObject;			// +0x4C
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
	const unsigned short *name = game ? game->getName().str() : g_bfmeEmptyUnicode;
	wcsncpy((unsigned short *)((char *)&msg + 0x26), name, 0x10);
	*((unsigned short *)((char *)&msg + 0x46)) = 0;

	queuePacket(&msg, 0);
	m_memberObject->flushQueue();

	game = m_currentGame;
	if (game != 0) {
		BfmeNetAddress *local = _bfme_localAddress();
		if (game->m_ip == local->m_ip && game->m_port == local->m_port) {
			OnPlayerLeave(game->m_ip, m_name);
			removeGame(game);
			m_currentGame = 0;
			m_inLobby = true;
			return;
		}
	}

	m_pendingAction = 3;
	m_expiration = timeGetTime() + m_actionTimeout;
}

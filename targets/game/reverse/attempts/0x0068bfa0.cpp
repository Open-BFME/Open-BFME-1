// ?handleGameStart@LANAPI@@IAEXPAULANMessage@@I@Z
// partial score=0.92 date=2026-09-21
// ?d_0068bfa0@@YAXXZ
// partial: every retail instruction reproduced in order; frame is one slot too big
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// BFME LANAPI::handleGameStart, retail 0x0068BFA0, 285 bytes.
//
// 2026-09-21: the handler is an if/ELSE, not the sequential flow the earlier
// bank had.  Retail's `eb 47 jmp +0xf9` at +0xb0 skips the OnPlayerLeave /
// removeGame / delete teardown when onSerializedGameInfo returns true, so the
// teardown is the else arm.  With that corrected every retail instruction,
// register and immediate is reproduced in order; only the frame differs.
// /FAsc listing: ours reads
//     _options$536 = -16 / __$EHRec$ = -12 / _msg$ = 8 / $T585 = 12 /
//     $T584 = 12 / _senderIP$ = 12
// Retail allocates NOTHING (`add esp,0xc`, no `push ecx`): it puts the
// long-lived string on _senderIP$ (esp+0x1c) and both short temporaries on
// _msg$ (esp+0x18).  VC7.1 hands dead incoming-argument homes to compiler
// TEMPORARIES before named locals and prefers the highest free home, so the
// two branch temporaries take senderIP's home first and `options` -- whose
// range covers the `mov eax,[esp+0x18]` read of msg -- can reach neither home
// and gets a fresh slot.  That extra `push ecx` is the whole 286-vs-285.
// The update jump table at 0x00A87A28 routes this handler through ILT
// 0x0001529E. The handler compares the sender's address pair, passes the
// serialized game-info payload through vtable slot 39, and tears down the
// game after the slot 36 start callback.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include "StringInline.h"

extern AsciiString GenerateGameOptionsString(void);

struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct LANMessage
{
	UnsignedByte m_bfmeHead[0x22];
	UnsignedByte m_serializedGameInfo[0x196];
};

class LANGameInfo
{
public:
	~LANGameInfo(void);

	UnsignedByte m_bfmeHead[0x0d];
	Bool m_inProgress;
	UnsignedByte m_bfmeBeforeHost[0x88 - 0x0e];
	BfmeNetAddress m_hostAddress;
};

class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void OnPlayerLeave(UnicodeString name) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void OnGameStart(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual Bool onSerializedGameInfo(BfmeNetAddress *sender, Int playerSlot,
		char *buffer, UnsignedInt size) = 0;

protected:
	void handleGameStart(LANMessage *msg, UnsignedInt senderIP);
	void removeGame(LANGameInfo *game);

	UnsignedByte m_bfmeHead[0x10 - 4];
	UnicodeString m_name;
	UnsignedByte m_bfmeBeforeLobby[0x24 - 0x14];
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	UnsignedByte m_bfmeBeforeLobbyFlag[0x3d - 0x30];
	Bool m_inLobby;
	UnsignedByte m_bfmeBeforeCurrentGame[0x40 - 0x3e];
	LANGameInfo *m_currentGame;
};

// ?handleGameStart@LANAPI@@IAEXPAULANMessage@@I@Z
void LANAPI::handleGameStart(LANMessage *msg, UnsignedInt senderIP)
{
	if (!m_inLobby && m_currentGame)
	{
		if (m_currentGame->m_hostAddress.m_ip == ((BfmeNetAddress *)senderIP)->m_ip
			&& m_currentGame->m_hostAddress.m_port == ((BfmeNetAddress *)senderIP)->m_port
			&& !m_currentGame->m_inProgress)
		{
			AsciiString options = GenerateGameOptionsString();
			if (((LANAPI *)this)->onSerializedGameInfo((BfmeNetAddress *)senderIP, 0,
				(char *)msg + 0x22, 0x196))
			{
				GenerateGameOptionsString();
				OnGameStart();
			}
			else
			{
				OnPlayerLeave(m_name);
				removeGame(m_currentGame);
				LANGameInfo *gameToDelete = m_currentGame;
				if (gameToDelete)
					delete gameToDelete;
				m_currentGame = 0;
				m_inLobby = true;
			}
		}
	}
}

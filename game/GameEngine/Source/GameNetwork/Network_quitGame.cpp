// cl: /DNDEBUG /MD /GX

// Retail 0x006822E0, Network vtable slot 30 (table at 0x0111A968).
//
// Its own TU: the body reaches TheMessageStream through vtable+0x34, the same
// slot ControlBarBeacon.cpp already models as BfmeMessageStream::appendMessage,
// and Network.cpp's include of Common/MessageStream.h would collide with that
// declaration.
//
// Slot 29 tail-calls sendLoadCompleteCommand and slot 31 takes an Int, so this
// is the 0-argument body between them. It asks the connection manager to send
// the local player's leave command, clears the game data, and parks the local
// status -- Zero Hour's quitGame in the same order, minus the MSG_SELF_DESTRUCT
// pair BFME dropped.

typedef int Int;
typedef unsigned int UnsignedInt;

// Zero Hour's enum; BFME's quitGame parks 3 where Zero Hour parks POSTGAME = 4,
// and isPlayerConnected (0x00681F30) tests 1 alone. Named for the value.
enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

// GameMessage::MSG_CLEAR_GAME_DATA in Zero Hour terms. Left as the retail
// literal: BFME's GameMessage::Type is renumbered and nothing in the tree fixes
// 0x1D to a name yet.
enum { BFME_MSG_CLEAR_GAME_DATA = 0x1D };

class GameMessage;

class BFMEConnectionManager
{
public:
	void sendRequestPlayerLeaveCommand(void);	// retail 0x006648A0
};

// appendMessage is vtable slot 0x34 of MessageStream.
class BfmeMessageStream
{
public:
	virtual void _ms_slot00(void) = 0;
	virtual void _ms_slot04(void) = 0;
	virtual void _ms_slot08(void) = 0;
	virtual void _ms_slot0C(void) = 0;
	virtual void _ms_slot10(void) = 0;
	virtual void _ms_slot14(void) = 0;
	virtual void _ms_slot18(void) = 0;
	virtual void _ms_slot1C(void) = 0;
	virtual void _ms_slot20(void) = 0;
	virtual void _ms_slot24(void) = 0;
	virtual void _ms_slot28(void) = 0;
	virtual void _ms_slot2C(void) = 0;
	virtual void _ms_slot30(void) = 0;
	virtual GameMessage *appendMessage(UnsignedInt type) = 0;
};

extern BfmeMessageStream *TheMessageStream;

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
	virtual void quitGame(void);			// slot 30

protected:
	void *m_subsystemName;				// SubsystemInterface::m_name, +0x04
	BFMEConnectionManager *m_conMgr;		// +0x08
	NetLocalStatus m_localStatus;			// +0x0C
};

void Network::quitGame(void)
{
	if (m_conMgr != 0)
		m_conMgr->sendRequestPlayerLeaveCommand();

	TheMessageStream->appendMessage(BFME_MSG_CLEAR_GAME_DATA);
	m_localStatus = NETLOCALSTATUS_LEFT;
}

// cl: /DNDEBUG /MD /GX

// Retail 0x00681F30, Network vtable slot 43 (table at 0x0111A968).
//
// Its own TU because of the vtable+0x98 dispatch: that is slot 38, and the only
// way to make the compiler encode 0x98 is to declare the 38 slots ahead of it.
// Slot 38 is getLocalPlayerID -- this body compares its result to the Int
// argument -- and Zero Hour declares getPlayerName straight after, which is what
// slot 39 turns out to be (0x006826C0).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// BFME's enum: quitGame (0x006822E0) parks 3 in this field, and this body tests
// it against 1 alone where Zero Hour tests INGAME or LEAVING.
enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	Bool isPlayerConnected(Int playerID);	// ILT thunk 0x0001514A
};

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
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual UnsignedInt getLocalPlayerID(void) = 0;		// slot 38, vtable+0x98
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual Bool isPlayerConnected(Int playerID);		// slot 43

protected:
	void *m_subsystemName;			// SubsystemInterface::m_name, +0x04
	ConnectionManager *m_conMgr;		// +0x08
	NetLocalStatus m_localStatus;		// +0x0C
};

Bool Network::isPlayerConnected(Int playerID)
{
	if (playerID == getLocalPlayerID())
		return m_localStatus == NETLOCALSTATUS_INGAME;

	return m_conMgr->isPlayerConnected(playerID);
}

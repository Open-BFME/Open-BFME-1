// cl: /DNDEBUG /MD /EHsc
// readable body of ?okToPlayRadarEdgeSound@Player@@QAE_NXZ: Code/GameEngine/Source/Common/RTS/Player.cpp

// Open-BFME5: Player::okToPlayRadarEdgeSound, retail 0x000C9A20, 75 bytes. The
// body carried only a machine byte-dump row; the name is the symbols.csv pin.
//
// Five conditions, all of which have to hold. The first is a virtual on the
// victory-conditions subsystem taking the player, at slot eleven of its table;
// the ledger's note on TheRadar already places that global at 0x012F079C, and
// the pin for it goes in alongside this body.
//
// The rest are flags: one on the player at +0x680, one on TheInGameUI at
// +0x12BE, and two readings of TheGameLogic -- the flag at +0x6B and the frame
// counter at +0x3C, which the already-ledgered OCLUpdate::getRemainingFrames
// names. Both come off one load of the global. The frame test is unsigned,
// which is what makes it a jbe rather than a je.

typedef unsigned int UnsignedInt;
typedef bool Bool;

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/VictoryConditions.h
class VictoryConditionsInterface
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
	virtual Bool bfmeIsPlayerOut(Player *player) = 0;	// slot 11, vtable+0x2C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	char m_bfmeHead[0x12BE];
	Bool m_bfmeSuppressed;					// +0x12BE
};

class GameLogicFrameSlice
{
public:
	char m_bfmeHeadA[0x3C];
	UnsignedInt m_bfmeFrame;				// +0x3C
	char m_bfmeHeadB[0x6B - 0x40];
	Bool m_bfmeStarted;					// +0x6B
};

extern VictoryConditionsInterface *TheVictoryConditions;	// 0x012F079C
extern InGameUI *TheInGameUI;					// 0x012F148C
extern GameLogicFrameSlice *TheGameLogic;			// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool okToPlayRadarEdgeSound(void);

private:
	char m_bfmeHead[0x680];
	Bool m_bfmeRadarEdgeSoundOff;				// +0x680
};

// ?okToPlayRadarEdgeSound@Player@@QAE_NXZ
Bool Player::okToPlayRadarEdgeSound(void)
{
	// One conjunction rather than a run of early returns: the chain is what
	// puts every failing test on a forward jump to a single xor at the end and
	// loads the one into eax on the way out of the last test.
	return !TheVictoryConditions->bfmeIsPlayerOut(this)
		&& !m_bfmeRadarEdgeSoundOff
		&& !TheInGameUI->m_bfmeSuppressed
		&& TheGameLogic->m_bfmeStarted
		&& TheGameLogic->m_bfmeFrame > 0;
}

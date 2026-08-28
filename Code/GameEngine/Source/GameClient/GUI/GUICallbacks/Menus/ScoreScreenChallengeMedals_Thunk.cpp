// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: updateChallengeMedals, retail 0x004E27E0, zh_sweep packet 004e27e0.
//
// The Zero Hour body (ScoreScreen.cpp) unchanged in shape. It lives in its own
// TU rather than next to the ported ScoreScreen.cpp because that file carries
// uw_* funclet rows keyed on $L labels, and inserting a body renumbers them.
//
// Three things the retail bytes settle that the Zero Hour source does not:
//
//  - GameInfo::isSkirmish and GameInfo::getLocalSlotNum are VIRTUAL in BFME.
//    Retail reaches them through [vtbl+0x28] and [vtbl+0x14], i.e. slots 10 and
//    5, where Zero Hour declares both as plain inline members. getConstSlot and
//    GameSlot::isAI stay direct calls (ILT 0x00029460 and 0x000422DF).
//  - GameSlot::m_state sits at +0x04 and m_teamNumber at +0x18. Retail spells
//    both accessors inline: `cmp [eax+4],4` for getState() == SLOT_BRUTAL_AI
//    and `mov ecx,[edi+0x18]` for getTeamNumber(), CSE'd across the two reads
//    the ally test makes of it.
//  - The challenge masks are 1,2,4,8,0x10,0x20,0x40 for one through seven
//    brutal AIs, matching Zero Hour's BH_CHALLENGE_MASK_n exactly. The seven
//    arms compile to the jump table at 0x008E2904.
//
// isSlotLocalAlly is static in Zero Hour and is inlined here at /O2, which is
// what retail did too -- the ally test appears open-coded between the isAI()
// call and the ++numAIs. Its two TRUE returns share the else-arm's block at
// 0x004E2860, so the second isAI() call retail makes there is the source's
// `else if (slot->isAI())`, not a re-test.

typedef bool Bool;
typedef int Int;

enum { TRUE = 1, FALSE = 0 };

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

enum
{
	BH_CHALLENGE_MASK_1 = 0x0001,
	BH_CHALLENGE_MASK_2 = 0x0002,
	BH_CHALLENGE_MASK_3 = 0x0004,
	BH_CHALLENGE_MASK_4 = 0x0008,
	BH_CHALLENGE_MASK_5 = 0x0010,
	BH_CHALLENGE_MASK_6 = 0x0020,
	BH_CHALLENGE_MASK_7 = 0x0040
};

static const Int MAX_SLOTS = 8;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isAI( void ) const;								///< ILT 0x000422DF

	SlotState getState( void ) const { return m_state; }
	Int getTeamNumber( void ) const { return m_teamNumber; }

private:
	Int m_head;												///< +0x00
	SlotState m_state;										///< +0x04
	Int m_between[4];										///< +0x08 .. +0x14
	Int m_teamNumber;										///< +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	// Only the two slots retail uses are named; the rest exist to place them.
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual Int getLocalSlotNum( void ) const = 0;			///< slot 5, [vtbl+0x14]
	virtual void slot6( void ) = 0;
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
	virtual void slot9( void ) = 0;
	virtual Bool isSkirmish( void ) = 0;					///< slot 10, [vtbl+0x28]

	const GameSlot *getConstSlot( Int index ) const;		///< ILT 0x00029460
};

extern GameInfo *TheGameInfo;								///< retail 0x012F708C

static Bool isSlotLocalAlly(GameInfo *game, const GameSlot *slot)
{
	const GameSlot *localSlot = game->getConstSlot(game->getLocalSlotNum());
	if (!localSlot)
		return TRUE;

	if (slot == localSlot)
		return TRUE;

	if (slot->getTeamNumber() < 0)
		return FALSE;

	return slot->getTeamNumber() == localSlot->getTeamNumber();
}

// ?updateChallengeMedals@@YAXAAH@Z
void updateChallengeMedals(Int& medals)
{
	if (!TheGameInfo->isSkirmish())
		return;

	Int numAIs = 0;
	Int numBrutals = 0;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		const GameSlot *slot = TheGameInfo->getConstSlot(i);
		if (slot->isAI() && !isSlotLocalAlly(TheGameInfo, slot))
		{
			++numAIs;
			if (TheGameInfo->getConstSlot(i)->getState() == SLOT_BRUTAL_AI)
				++numBrutals;
		}
		else if (slot->isAI())
		{
			// can't get challenge medals with AI helpers
			return;
		}
	}

	if (numAIs)
	{
		switch(numBrutals)
		{
		case 1:
			medals |= BH_CHALLENGE_MASK_1;
			break;
		case 2:
			medals |= BH_CHALLENGE_MASK_2;
			break;
		case 3:
			medals |= BH_CHALLENGE_MASK_3;
			break;
		case 4:
			medals |= BH_CHALLENGE_MASK_4;
			break;
		case 5:
			medals |= BH_CHALLENGE_MASK_5;
			break;
		case 6:
			medals |= BH_CHALLENGE_MASK_6;
			break;
		case 7:
			medals |= BH_CHALLENGE_MASK_7;
			break;
		}
	}
}

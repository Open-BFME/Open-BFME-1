// cl: /DNDEBUG /MD /EHsc
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

// ?isSlotLocalAlly@@YA_NPAVGameInfo@@PBVGameSlot@@@Z
__declspec(noinline) Bool isSlotLocalAlly(GameInfo *game, const GameSlot *slot)
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

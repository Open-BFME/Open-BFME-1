// cl: /DNDEBUG /MD /EHsc
// readable body of ?canPlayerGarrison@ActionManager@@QAE_NPBVPlayer@@PBVObject@@W4CommandSourceType@@@Z: Code/GameEngine/Source/Common/RTS/ActionManager.cpp

// FILE: ActionManagerCanPlayerGarrison.cpp //////////////////////////////////
//
// ActionManager::canPlayerGarrison, retail 0x000C5E40.
//
// ActionManager.cpp compiles the same body at the same 138 bytes, differing
// only where BFME moved Object's members and widened ContainModuleInterface:
//
//   getContain()        this+0x1fc   (ZH header: +0x190)
//   getTeam()           this+0x23c   (ZH header: +0x1d0)
//   isEffectivelyDead() this+0x344   (ZH header: +0x297)
//   getContainCount()   vtable 0x100 and it takes an argument
//                                    (ZH header: 0xa4, no argument)
//   isGarrisonable()    vtable 0x008, unchanged
//
// Those are four independent disagreements with the vendored header, so the
// body moved into its own TU with a local ABI slice: only the three Object
// members it reads, the two ContainModuleInterface slots it calls, and the two
// out-of-line Object/Player helpers, which resolve by mangled name against
// reverse/symbols.csv (isKindOf 0x0003251F, getControllingPlayer 0x00020824,
// getRelationship 0x0003E77A -- all three already pinned at the incremental-
// link thunks this call site encodes).
//
/////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;

enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI, CMD_FROM_SCRIPT };

// KINDOF_STRUCTURE is 7 in the retail enum: the isKindOf call site pushes 7.
enum KindOfType
{
	KINDOF_OBSTACLE = 0, KINDOF_SELECTABLE, KINDOF_IMMOBILE, KINDOF_CAN_ATTACK,
	KINDOF_STICK_TO_TERRAIN_SLOPE, KINDOF_CAN_CAST_REFLECTIONS,
	KINDOF_SHRUBBERY, KINDOF_STRUCTURE
};

// NEUTRAL is 1: the getRelationship result is compared against 1.
enum Relationship { ENEMIES = 0, NEUTRAL, ALLIES };

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Relationship getRelationship( const Team *that ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	virtual void slot_000();
	virtual void slot_004();
	virtual Bool isGarrisonable() const;				// slot 0x08
	virtual void slot_00c();
	virtual void slot_010();
	virtual void slot_014();
	virtual void slot_018();
	virtual void slot_01c();
	virtual void slot_020();
	virtual void slot_024();
	virtual void slot_028();
	virtual void slot_02c();
	virtual void slot_030();
	virtual void slot_034();
	virtual void slot_038();
	virtual void slot_03c();
	virtual void slot_040();
	virtual void slot_044();
	virtual void slot_048();
	virtual void slot_04c();
	virtual void slot_050();
	virtual void slot_054();
	virtual void slot_058();
	virtual void slot_05c();
	virtual void slot_060();
	virtual void slot_064();
	virtual void slot_068();
	virtual void slot_06c();
	virtual void slot_070();
	virtual void slot_074();
	virtual void slot_078();
	virtual void slot_07c();
	virtual void slot_080();
	virtual void slot_084();
	virtual void slot_088();
	virtual void slot_08c();
	virtual void slot_090();
	virtual void slot_094();
	virtual void slot_098();
	virtual void slot_09c();
	virtual void slot_0a0();
	virtual void slot_0a4();
	virtual void slot_0a8();
	virtual void slot_0ac();
	virtual void slot_0b0();
	virtual void slot_0b4();
	virtual void slot_0b8();
	virtual void slot_0bc();
	virtual void slot_0c0();
	virtual void slot_0c4();
	virtual void slot_0c8();
	virtual void slot_0cc();
	virtual void slot_0d0();
	virtual void slot_0d4();
	virtual void slot_0d8();
	virtual void slot_0dc();
	virtual void slot_0e0();
	virtual void slot_0e4();
	virtual void slot_0e8();
	virtual void slot_0ec();
	virtual void slot_0f0();
	virtual void slot_0f4();
	virtual void slot_0f8();
	virtual void slot_0fc();
	virtual Int getContainCount( Int arg ) const;	// slot 0x100
};

// isKindOf is Thing's, not Object's -- the pinned name is
// ?isKindOf@Thing@@QBE_NW4KindOfType@@@Z and the call passes `this' unadjusted,
// so Thing is the primary base.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType t ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:

	Player *getControllingPlayer() const;

	Bool isEffectivelyDead() const { return (m_statusBits & 1) != 0; }
	ContainModuleInterface *getContain() const { return m_contain; }
	Team *getTeam() const { return m_team; }

private:

	char m_bfmeHead[0x1fc];
	ContainModuleInterface *m_contain;			// @0x1fc
	char m_bfmeMiddle[0x23c - 0x200];
	Team *m_team;								// @0x23c
	char m_bfmeTail[0x344 - 0x240];
	unsigned int m_statusBits;					// @0x344

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	Bool canPlayerGarrison( const Player *player, const Object *target, CommandSourceType commandSource );
};

// ?canPlayerGarrison@ActionManager@@QAE_NPBVPlayer@@PBVObject@@W4CommandSourceType@@@Z
Bool ActionManager::canPlayerGarrison( const Player *player, const Object *target, CommandSourceType commandSource )
{
	if (!(player && target))
		return false;

	if (target->isEffectivelyDead()) {
		return false;
	}

	if (target->isKindOf(KINDOF_STRUCTURE) == false)
		return false;

	ContainModuleInterface *cmi = target->getContain();
	if (cmi == 0)
		return false;

	if (cmi->isGarrisonable() == false)
		return false;

	if (player == target->getControllingPlayer())
	{
		return true;
	}

	if (player->getRelationship(target->getTeam()) == NEUTRAL)
	{
		// needs to be empty if its not already ours.
		return cmi->getContainCount(0) == 0;
	}

	return false;
}

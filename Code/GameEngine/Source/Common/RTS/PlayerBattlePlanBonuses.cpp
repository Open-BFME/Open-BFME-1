// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?becomingTeamMember@Player@@QAEXPAVObject@@_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

// The Player battle-plan bonuses and the membership change that drives them:
//
//   0x000D5C20  removeBattlePlanBonusesForObject  196 bytes
//   0x000D7680  becomingTeamMember                238 bytes
//
// becomingTeamMember is what runs when an object joins or leaves this player's
// team, and one of the four things it does is apply or remove the battle-plan
// bonuses -- calling, for the removal, the function the other file defines.
// Definition and caller sat in separate files, so neither could state the
// block they share.
//
// They both reach the same four fields and disagreed about the last one.
// becomingTeamMember named the three battle-plan counters at +0x64, +0x68 and
// +0x6C and then declared the pointer after them as a bare void *;
// removeBattlePlanBonusesForObject spelled 0x70 bytes of padding and then
// declared the same pointer as BattlePlanBonuses *, the type it needs to copy
// the struct and invert it. One layout keeps the counters named AND the
// pointer typed, which is the pair of facts neither file could hold alone.
//
// The bonus file built with /DNDEBUG /MD and no exceptions; it byte-verifies
// unchanged under becomingTeamMember's flags, which is what let the two share
// a TU.
//
// Defining removeBattlePlanBonusesForObject in the same TU as a caller was the
// risk here: under /O2 MSVC may inline an out-of-line function whose body it
// can see. It did not, and both rows byte-verify.

#include <cstring>
#include <stdlib.h>

typedef bool Bool;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID
};

class Object;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0xC0];
	unsigned int m_kindOf;
};

#define BFME_VTABLE_SLOT(offset) virtual void slot##offset();

class BfmeHighSlotVTable
{
public:
	BFME_VTABLE_SLOT(000) BFME_VTABLE_SLOT(004) BFME_VTABLE_SLOT(008) BFME_VTABLE_SLOT(00C)
	BFME_VTABLE_SLOT(010) BFME_VTABLE_SLOT(014) BFME_VTABLE_SLOT(018) BFME_VTABLE_SLOT(01C)
	BFME_VTABLE_SLOT(020) BFME_VTABLE_SLOT(024) BFME_VTABLE_SLOT(028) BFME_VTABLE_SLOT(02C)
	BFME_VTABLE_SLOT(030) BFME_VTABLE_SLOT(034) BFME_VTABLE_SLOT(038) BFME_VTABLE_SLOT(03C)
	BFME_VTABLE_SLOT(040) BFME_VTABLE_SLOT(044) BFME_VTABLE_SLOT(048) BFME_VTABLE_SLOT(04C)
	BFME_VTABLE_SLOT(050) BFME_VTABLE_SLOT(054) BFME_VTABLE_SLOT(058) BFME_VTABLE_SLOT(05C)
	BFME_VTABLE_SLOT(060) BFME_VTABLE_SLOT(064) BFME_VTABLE_SLOT(068) BFME_VTABLE_SLOT(06C)
	BFME_VTABLE_SLOT(070) BFME_VTABLE_SLOT(074) BFME_VTABLE_SLOT(078) BFME_VTABLE_SLOT(07C)
	BFME_VTABLE_SLOT(080) BFME_VTABLE_SLOT(084) BFME_VTABLE_SLOT(088) BFME_VTABLE_SLOT(08C)
	BFME_VTABLE_SLOT(090) BFME_VTABLE_SLOT(094) BFME_VTABLE_SLOT(098) BFME_VTABLE_SLOT(09C)
	BFME_VTABLE_SLOT(0A0) BFME_VTABLE_SLOT(0A4) BFME_VTABLE_SLOT(0A8) BFME_VTABLE_SLOT(0AC)
	BFME_VTABLE_SLOT(0B0) BFME_VTABLE_SLOT(0B4) BFME_VTABLE_SLOT(0B8) BFME_VTABLE_SLOT(0BC)
	BFME_VTABLE_SLOT(0C0) BFME_VTABLE_SLOT(0C4) BFME_VTABLE_SLOT(0C8) BFME_VTABLE_SLOT(0CC)
	BFME_VTABLE_SLOT(0D0) BFME_VTABLE_SLOT(0D4) BFME_VTABLE_SLOT(0D8) BFME_VTABLE_SLOT(0DC)
	BFME_VTABLE_SLOT(0E0) BFME_VTABLE_SLOT(0E4) BFME_VTABLE_SLOT(0E8) BFME_VTABLE_SLOT(0EC)
	BFME_VTABLE_SLOT(0F0) BFME_VTABLE_SLOT(0F4) BFME_VTABLE_SLOT(0F8) BFME_VTABLE_SLOT(0FC)
	BFME_VTABLE_SLOT(100) BFME_VTABLE_SLOT(104) BFME_VTABLE_SLOT(108) BFME_VTABLE_SLOT(10C)
	BFME_VTABLE_SLOT(110) BFME_VTABLE_SLOT(114) BFME_VTABLE_SLOT(118) BFME_VTABLE_SLOT(11C)
	BFME_VTABLE_SLOT(120) BFME_VTABLE_SLOT(124) BFME_VTABLE_SLOT(128) BFME_VTABLE_SLOT(12C)
	BFME_VTABLE_SLOT(130) BFME_VTABLE_SLOT(134) BFME_VTABLE_SLOT(138) BFME_VTABLE_SLOT(13C)
	BFME_VTABLE_SLOT(140) BFME_VTABLE_SLOT(144) BFME_VTABLE_SLOT(148) BFME_VTABLE_SLOT(14C)
	BFME_VTABLE_SLOT(150) BFME_VTABLE_SLOT(154) BFME_VTABLE_SLOT(158) BFME_VTABLE_SLOT(15C)
	BFME_VTABLE_SLOT(160) BFME_VTABLE_SLOT(164) BFME_VTABLE_SLOT(168) BFME_VTABLE_SLOT(16C)
	BFME_VTABLE_SLOT(170) BFME_VTABLE_SLOT(174) BFME_VTABLE_SLOT(178)
};

#undef BFME_VTABLE_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public BfmeHighSlotVTable
{
public:
	virtual void slot17C();
	virtual Bool isIdle();
};

class Module;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void friend_adjustPowerForPlayer(Bool yes);

	UpdateModule *findUpdateModule(NameKeyType key) const
	{
		return (UpdateModule *)findModule(key);
	}

	Bool areModulesReady() const
	{
		return m_modulesReady;
	}

	unsigned int getKindOf() const
	{
		const ThingTemplate *thing = m_thingTemplate;
		if (thing && thing->m_nextOverride)
			thing = (const ThingTemplate *)thing->m_nextOverride->getFinalOverride();
		return thing->m_kindOf;
	}

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return m_aiUpdate;
	}

	Bool isUnderConstruction() const
	{
		return (m_statusBits & 0x04) != 0;
	}

protected:
	Module *findModule(NameKeyType key) const;

private:
	unsigned char m_unreconstructed_000[0x04];
	ThingTemplate *m_thingTemplate;
	unsigned char m_unreconstructed_008[0x88];
	unsigned char m_statusBits;
	unsigned char m_unreconstructed_091[0x173];
	AIUpdateInterface *m_aiUpdate;
	unsigned char m_unreconstructed_208[0x139];
	Bool m_modulesReady;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
class AutoDepositUpdate : public UpdateModule
{
public:
	void awardInitialCaptureBonus(Player *player);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getNeutralPlayer() const
	{
		return m_neutralPlayer;
	}

private:
	unsigned char m_unreconstructed_00[0x14];
	Player *m_neutralPlayer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI : public BfmeHighSlotVTable
{
public:
	virtual void addIdleWorker(Object *object);
	virtual void removeIdleWorker(Object *object, Int playerIndex);
};

void localApplyBattlePlanBonusesToObject(Object *object, void *bonuses);


struct KindOfMaskType
{
	unsigned m_bits[6];
	// The default ctor is a memset of the 0x18-byte / 192-bit mask; that inlines
	// as xor ecx / lea edx [eax+disp] / six stores, which member stores fold away.
	KindOfMaskType() { memset(this, 0, sizeof(*this)); }
};

struct BattlePlanBonuses
{
	float m_armorScalar;
	int m_bombardment;
	int m_searchAndDestroy;
	int m_holdTheLine;
	float m_sightRangeScalar;
	KindOfMaskType m_validKindOf;
	KindOfMaskType m_invalidKindOf;
};

extern float g_01076C24;
extern float g_bfmeDefaultBU;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void becomingTeamMember(Object *object, Bool yes);
	void removeBattlePlanBonusesForObject(Object *object) const;

	Int getNumBattlePlansActive() const
	{
		return m_bombardBattlePlans + m_holdTheLineBattlePlans + m_searchAndDestroyBattlePlans;
	}

	void applyBattlePlanBonusesForObject(Object *object) const
	{
		localApplyBattlePlanBonusesToObject(object, m_battlePlanBonuses);
	}

	Int getPlayerIndex() const
	{
		return m_playerIndex;
	}

private:
	unsigned char m_unreconstructed_00[0x24];
	Int m_playerIndex;					// this+0x24
	unsigned char m_unreconstructed_28[0x3C];
	Int m_bombardBattlePlans;				// this+0x64
	Int m_holdTheLineBattlePlans;				// this+0x68
	Int m_searchAndDestroyBattlePlans;			// this+0x6C
	BattlePlanBonuses *m_battlePlanBonuses;			// this+0x70
};

extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern InGameUI *TheInGameUI;

// ?removeBattlePlanBonusesForObject@Player@@QBEXPAVObject@@@Z
void Player::removeBattlePlanBonusesForObject(Object *obj) const
{
	BattlePlanBonuses *bonus = new BattlePlanBonuses;
	*bonus = *m_battlePlanBonuses;
	bonus->m_armorScalar = g_bfmeDefaultBU / __max(bonus->m_armorScalar, g_01076C24);
	bonus->m_sightRangeScalar = g_bfmeDefaultBU / __max(bonus->m_sightRangeScalar, g_01076C24);
	bonus->m_bombardment = -1000000;
	bonus->m_searchAndDestroy = -1000000;
	bonus->m_holdTheLine = -1000000;
	localApplyBattlePlanBonusesToObject(obj, bonus);
	delete bonus;
}

// ?becomingTeamMember@Player@@QAEXPAVObject@@_N@Z
void Player::becomingTeamMember(Object *object, Bool yes)
{
	if (!object)
		return;

	if (!object->isUnderConstruction())
		object->friend_adjustPowerForPlayer(yes);

	if (this != ThePlayerList->getNeutralPlayer() && yes)
	{
		NameKeyType key = TheNameKeyGenerator->nameToKey("AutoDepositUpdate");
		AutoDepositUpdate *update = (AutoDepositUpdate *)object->findUpdateModule(key);
		if (update)
			update->awardInitialCaptureBonus(this);
	}

	if (getNumBattlePlansActive() > 0 && object->areModulesReady())
	{
		if (yes)
			applyBattlePlanBonusesForObject(object);
		else
			removeBattlePlanBonusesForObject(object);
	}

	if ((object->getKindOf() & 0x4000) != 0 && object->getAIUpdateInterface() && object->getAIUpdateInterface()->isIdle())
	{
		if (yes)
			TheInGameUI->addIdleWorker(object);
		else
			TheInGameUI->removeIdleWorker(object, getPlayerIndex());
	}
}

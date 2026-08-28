// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?applyBattlePlanBonusesForObject@Player@@QBEXPAVObject@@@Z: Code/GameEngine/Source/Common/RTS/Player.cpp
// readable body of ?becomingTeamMember@Player@@QAEXPAVObject@@_N@Z: Code/GameEngine/Source/Common/RTS/Player.cpp

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
	Int m_playerIndex;
	unsigned char m_unreconstructed_28[0x3C];
	Int m_bombardBattlePlans;
	Int m_holdTheLineBattlePlans;
	Int m_searchAndDestroyBattlePlans;
	void *m_battlePlanBonuses;
};

extern PlayerList *ThePlayerList;
extern NameKeyGenerator *TheNameKeyGenerator;
extern InGameUI *TheInGameUI;

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

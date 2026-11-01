// ?initObject@Object@@QAEXXZ
// partial score=0.9936 date=2026-11-01
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?initObject@Object@@QAEXXZ: game/GameEngine/Source/GameLogic/Object/Object.cpp

// Object::initObject, retail 0x001C6870 (933 bytes, ret at +0x3A4).
//
// Identity: the present-unmatched Object.cpp body, its ThingFactory caller and
// the Zero Hour twin (GeneralsMD Object::initObject) name it. Retail keeps the
// Zero Hour order of the shared work (weapon-condition reset, upgrade modules,
// sendObjectCreated, difficulty bonus and battle plans, special-power mask,
// script notification, weapon set update) and adds the BFME work below the
// weapon set, read from the retail listing: two template-driven extra weapons,
// the emotion-system registration, the living-world campaign name copy and its
// one template-name special case, the experience-level gain, the tracker reset,
// the object-reference store update and the score keeper's objectBuilt count.
// Open BFME 2 Code/GameEngine/Source/GameLogic/Object/ObjectInitObject.cpp
// (45afcff3) has the same extra-weapon statement order; its other additions
// are BFME 2 only and are not used here.
//
// Every Object, Player, GameLogic and template offset below is read from this
// body; fields without a witnessed name keep their offset.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Object;
class WeaponTemplate;


class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	Overridable *friend_getFinalOverride();

	void *m_vtable;
	Overridable *m_next;
};

class ThingTemplateView
{
public:
	char m_pad000[0x20];
	AsciiString m_name;
	char m_pad024[0xC8 - 0x24];
	UnsignedInt m_kindOf[8];
	char m_pad0E8[0x4A0 - 0xE8];
	const WeaponTemplate *m_extraWeapon4A0;
	const WeaponTemplate *m_extraWeapon4A4;
	char m_pad4A8[0x4B4 - 0x4A8];
	Int m_influence4B4;
};

class SpecialPowerTemplate
{
public:
	char m_pad00[0x14];
	UnsignedInt m_type;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void s3(); virtual void s4(); virtual void s5();
	virtual const SpecialPowerTemplate *getSpecialPowerTemplate() const;
};

class BehaviorModuleInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual SpecialPowerModuleInterface *getSpecialPower();
};

class ObjectModuleView
{
public:
	virtual void s0();
	char m_pad04[0x0C - 0x04];
};

class BehaviorModule : public ObjectModuleView, public BehaviorModuleInterface
{
};

class Weapon
{
public:
	void loadAmmoNow(const Object *obj);

	char m_pad00[8];
	Int m_ownerID;
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};
extern WeaponStore *TheWeaponStore;

class WeaponSet
{
public:
	void updateWeaponSet(const Object *obj);
};

class ScoreKeeper
{
public:
	void addObjectBuilt(Object *obj, Int count);
};

class Player
{
public:
	void friend_applyDifficultyBonusesForObject(Object *obj, Bool apply);
	void applyBattlePlanBonusesForObject(Object *obj) const;
	void bfmeObjectEnteringInfluence(Object *obj);

	Int getNumBattlePlansActive() const { return m_battlePlans6C + m_battlePlans68 + m_battlePlans64; }
	ScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }

	char m_pad000[0x64];
	Int m_battlePlans64;
	Int m_battlePlans68;
	Int m_battlePlans6C;
	char m_pad070[0x348 - 0x70];
	ScoreKeeper m_scoreKeeper;
};

class Team
{
public:
	Player *getControllingPlayer() const;
};

class ExperienceTracker
{
public:
	void bfmeResetScalarBaseCount();
};

class Rva00364B10Summary;
class Rva00364B10LivingWorldPlayerArmyCollection
{
public:
	Int scanArmyGroups(Rva00364B10Summary *summary, Bool flag);
};

class GameLogic
{
public:
	void sendObjectCreated(Object *obj);
	Bool _bfme_isInLivingWorldCampaign();

	void updateObjectsChangedTriggerAreas() { m_frameObjectsChangedTriggerAreas = m_frame; }
	Rva00364B10LivingWorldPlayerArmyCollection *getArmies()
	{
		return reinterpret_cast<Rva00364B10LivingWorldPlayerArmyCollection *>(m_armies170);
	}

	char m_pad000[0x3C];
	UnsignedInt m_frame;
	char m_pad040[0x16C - 0x40];
	UnsignedInt m_frameObjectsChangedTriggerAreas;
	char m_armies170[4];
};
extern GameLogic *TheGameLogic;

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
	Bool getObjectsShouldReceiveDifficultyBonus() const { return m_objectsShouldReceiveDifficultyBonus; }

	char m_pad[0x17634];
	Bool m_objectsShouldReceiveDifficultyBonus;
};
extern ScriptEngine *TheScriptEngine;

class EmotionSystem
{
public:
	void rva0037CFF0(Object *obj);
};
extern EmotionSystem *TheEmotionSystem;

class LivingWorldLogic
{
public:
	char m_pad[0x30];
	AsciiString m_name30;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class ExperienceLevelSystem
{
public:
	void gainLevel(Object *obj, Bool flag);
};
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeObjectReferenceStore
{
public:
	void updateObjectReference(Object *obj, Bool flag);
};
struct RetailGlobalWeatherSystem;
extern RetailGlobalWeatherSystem *TheGlobalWeatherSystem;

enum
{
	KINDOF_PROJECTILE = 25,
	KINDOF_BIT_88 = 88,
	KINDOF_BIT_89 = 89,
	KINDOF_BIT_127 = 127,
	KINDOF_BIT_143 = 143
};

class Object
{
public:
	void initObject();
	void updateUpgradeModules();

	__forceinline const ThingTemplateView *getTemplate() const
	{
		const Overridable *tmpl = m_template;
		if (tmpl != 0 && tmpl->m_next != 0)
			tmpl = tmpl->m_next->getFinalOverride();
		return reinterpret_cast<const ThingTemplateView *>(tmpl);
	}
	__forceinline Int isKindOf(Int k) const
	{
		return (getTemplate()->m_kindOf[k >> 5] & (1U << (k & 0x1f))) != 0;
	}
	__forceinline Player *getControllingPlayer() const
	{
		Team *team = m_team;
		return team ? team->getControllingPlayer() : 0;
	}
	Bool getReceivingDifficultyBonus() const { return m_receivingDifficultyBonus; }
	__forceinline void setReceivingDifficultyBonus(Bool receive)
	{
		m_receivingDifficultyBonus = receive;
		Player *player = getControllingPlayer();
		if (player)
			player->friend_applyDifficultyBonusesForObject(this, m_receivingDifficultyBonus);
	}

private:
	char m_pad000[4];
	Overridable *m_template;
	char m_pad008[0x74 - 0x08];
	Int m_id;
	char m_pad078[0x1F0 - 0x78];
	BehaviorModule **m_behaviors;
	char m_pad1F4[0x210 - 0x1F4];
	ExperienceTracker *m_experienceTracker;
	char m_pad214[0x23C - 0x214];
	Team *m_team;
	char m_pad240[0x264 - 0x240];
	WeaponSet m_weaponSet;
	char m_pad265[0x2A4 - 0x265];
	Int m_lastWeaponCondition;
	char m_pad2A8[0x2B8 - 0x2A8];
	Weapon *m_extraWeapon2B8;
	Weapon *m_extraWeapon2BC;
	UnsignedInt m_specialPowerBits[2];
	char m_pad2C8[0x348 - 0x2C8];
	Bool m_receivingDifficultyBonus;
	char m_pad349[0x370 - 0x349];
	Int m_field370;
	char m_pad374[0x38C - 0x374];
	AsciiString m_name38C;
	char m_pad390[0x39C - 0x390];
	Bool m_influenceAdded39C;
};

static __forceinline UnsignedInt specialPowerTypeOf(const SpecialPowerTemplate *tmpl)
{
	Overridable *value = (Overridable *)tmpl;
	Overridable *next = value->m_next;
	if (next != 0)
	{
		if (next->m_next != 0)
			value = next->m_next->friend_getFinalOverride();
		else
			value = next;
	}
	return reinterpret_cast<const SpecialPowerTemplate *>(value)->m_type;
}

void Object::initObject()
{
	m_lastWeaponCondition = -1;

	updateUpgradeModules();

	TheGameLogic->sendObjectCreated(this);

	Player *controller = getControllingPlayer();
	if (controller)
	{
		if (!getReceivingDifficultyBonus() && TheScriptEngine->getObjectsShouldReceiveDifficultyBonus())
			setReceivingDifficultyBonus(true);

		if (controller->getNumBattlePlansActive() > 0)
			controller->applyBattlePlanBonusesForObject(this);

		if (!m_influenceAdded39C && getTemplate()->m_influence4B4 > 0)
		{
			controller->bfmeObjectEnteringInfluence(this);
			m_influenceAdded39C = true;
		}
	}

	for (BehaviorModule **m = m_behaviors; *m; ++m)
	{
		SpecialPowerModuleInterface *sp = (*m)->getSpecialPower();
		if (!sp)
			continue;

		const SpecialPowerTemplate *spTemplate = sp->getSpecialPowerTemplate();
		if (spTemplate)
		{
			UnsignedInt type = specialPowerTypeOf(spTemplate);
			m_specialPowerBits[type >> 5] |= 1U << (type & 0x1f);
		}
	}

	if (!isKindOf(KINDOF_PROJECTILE) && ((getTemplate()->m_kindOf[KINDOF_BIT_88 >> 5] & (1U << (KINDOF_BIT_88 & 0x1f))) ? false : true))
	{
		TheScriptEngine->notifyOfObjectCreationOrDestruction();
		TheGameLogic->updateObjectsChangedTriggerAreas();
	}

	m_weaponSet.updateWeaponSet(this);

	const WeaponTemplate *weaponTemplate = getTemplate()->m_extraWeapon4A0;
	if (weaponTemplate)
	{
		Weapon *weapon = TheWeaponStore->allocateNewWeapon(weaponTemplate, PRIMARY_WEAPON);
		Int id = m_id;
		m_extraWeapon2B8 = weapon;
		m_extraWeapon2B8->m_ownerID = id;
		m_extraWeapon2B8->loadAmmoNow(this);
	}
	weaponTemplate = getTemplate()->m_extraWeapon4A4;
	if (weaponTemplate)
	{
		Weapon *weapon = TheWeaponStore->allocateNewWeapon(weaponTemplate, PRIMARY_WEAPON);
		Int id = m_id;
		m_extraWeapon2BC = weapon;
		m_extraWeapon2BC->m_ownerID = id;
		m_extraWeapon2BC->loadAmmoNow(this);
	}

	if (isKindOf(KINDOF_BIT_143) || isKindOf(KINDOF_BIT_89))
		TheEmotionSystem->rva0037CFF0(this);

	if (isKindOf(KINDOF_BIT_127) && TheGameLogic->_bfme_isInLivingWorldCampaign())
	{
		m_name38C.set(TheLivingWorldLogic->m_name30);
		if (m_field370 == -1 && isKindOf(KINDOF_BIT_89))
		{
			const AsciiString &name = getTemplate()->m_name;
			Int length = name.getLength();
			const char *chars = name.str();
			Int result = memcmp(chars, "RohanSamWithFrodoPowers", length < 23 ? length : 23);
			if (result == 0)
				result = length - 23;
			if (result == 0)
				TheGameLogic->getArmies()->scanArmyGroups(reinterpret_cast<Rva00364B10Summary *>(this), true);
		}
	}

	TheExperienceLevelSystem->gainLevel(this, false);

	if (m_experienceTracker)
		m_experienceTracker->bfmeResetScalarBaseCount();

	reinterpret_cast<BfmeObjectReferenceStore *>(TheGlobalWeatherSystem)->updateObjectReference(this, false);

	getControllingPlayer()->getScoreKeeper()->addObjectBuilt(this, 1);
}

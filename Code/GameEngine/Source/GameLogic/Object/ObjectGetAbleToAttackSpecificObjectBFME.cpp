// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType
{
	KINDOF_STRUCTURE = 7,
	KINDOF_BFME_WEAPON_SOURCE = 109,
	KINDOF_BFME_CONTAINED_WEAPON = 163
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[0xC8 - 8];
	UnsignedInt m_kindOf[5];
	unsigned char m_pad0DC[0x4CC - 0xDC];
	unsigned char m_bfmeAttackFlag;
};

class BfmeTargetGate
{
public:
	virtual Bool bfmeAllowsAttack() const;
};

class BfmeTargetGateModule;

BfmeTargetGateModule *bfmeFindTargetGate(const Object *target);

class BfmeAttackQuery
{
public:
	Bool bfmeCanAttackTarget(const Object *source, const Coord3D *sourcePosition,
		const Object *target, const void *unused) const;
};

struct BfmeAIRoot
{
	BfmeAttackQuery *getAttackQuery() const { return m_attackQuery; }

	unsigned char m_pad000[0x0C];
	BfmeAttackQuery *m_attackQuery;
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;

class BfmeContainInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual const Object *bfmeGetWeaponSource() const;
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61();
	virtual const Object *bfmeFindWeaponSource(KindOfType kind) const;
};

class BfmeContainModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual BfmeContainInterface *bfmeGetContainInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponSet
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *source, const Object *target, CommandSourceType commandSource) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;

protected:
	void *m_vtable;
	ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource) const;

private:
	const ThingTemplate *getFinalTemplate() const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate;
	}

	BfmeContainInterface *getContain() const
	{
		if (m_containModule)
			return m_containModule->bfmeGetContainInterface();
		return 0;
	}

	unsigned char m_pad008[0x38 - 8];
	Coord3D m_position;
	unsigned char m_pad044[0x1FC - 0x44];
	BfmeContainModule *m_containModule;
	unsigned char m_pad200[0x264 - 0x200];
	WeaponSet m_weaponSet;
};

CanAttackResult Object::getAbleToAttackSpecificObject(AbleToAttackType attackType,
	const Object *target, CommandSourceType commandSource) const
{
	if (!target)
		return ATTACKRESULT_NOT_POSSIBLE;

	const ThingTemplate *sourceTemplate = getFinalTemplate();
	if ((sourceTemplate->m_kindOf[0] & 0x00000800) != 0)
	{
		if (!getFinalTemplate()->m_bfmeAttackFlag
			&& target->isKindOf(KINDOF_STRUCTURE)
			&& !TheAIParseDefinitionAI->getAttackQuery()->bfmeCanAttackTarget(
				this, &m_position, target, 0))
		{
			return ATTACKRESULT_NOT_POSSIBLE;
		}
	}

	const ThingTemplate *targetTemplate = target->getFinalTemplate();
	if ((targetTemplate->m_kindOf[4] & 0x00200000) != 0)
	{
		BfmeTargetGateModule *module = bfmeFindTargetGate(target);
		if (module)
		{
			const BfmeTargetGate *gate = reinterpret_cast<const BfmeTargetGate *>(
				reinterpret_cast<const unsigned char *>(module) + 0x24);
			if (!gate->bfmeAllowsAttack())
				return ATTACKRESULT_NOT_POSSIBLE;
		}
	}

	if ((getFinalTemplate()->m_kindOf[3] & 0x00001000) != 0)
	{
		register BfmeContainModule *module = m_containModule;
		BfmeContainInterface *contain;
		if (module
			&& (contain = module->bfmeGetContainInterface()) != 0)
		{
			const Object *weaponSource;
			if (isKindOf(KINDOF_BFME_WEAPON_SOURCE))
				weaponSource = contain->bfmeGetWeaponSource();
			else
				weaponSource = contain->bfmeFindWeaponSource(KINDOF_BFME_CONTAINED_WEAPON);

			if (weaponSource)
			{
				return weaponSource->m_weaponSet.getAbleToAttackSpecificObject(
					attackType, weaponSource, target, commandSource);
			}
		}

		return ATTACKRESULT_NOT_POSSIBLE;
	}

	return m_weaponSet.getAbleToAttackSpecificObject(attackType, this, target, commandSource);
}

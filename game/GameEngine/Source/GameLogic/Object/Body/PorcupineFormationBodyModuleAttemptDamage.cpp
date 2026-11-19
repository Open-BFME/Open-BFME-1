// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include

#include "Lib/Coord3D.h"

class DamageInfo;

typedef unsigned char Bool;

class PorcupineDamageCheckResult
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual Bool slot55();
};

class PorcupineDamageCheckResultSource
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual PorcupineDamageCheckResult *getResult();
};

class PorcupineDamageCheck
{
public:
	unsigned char m_data[0x1fc];
	PorcupineDamageCheckResultSource *m_resultSource;
};

#include "../../../../Include/Common/ScalarTypes/Real.h"

class Object
{
public:
	unsigned char m_data[0x38];
	Coord3D m_position;
	unsigned char m_data44[0x214 - 0x44];
	PorcupineDamageCheck *m_damageCheck;
};

class WeaponTemplate
{
public:
	Real getUnmodifiedAttackRange() const;
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *weapon,
		const Object *source, Object *target);
};

extern WeaponStore *TheWeaponStore;

// The two dwords the module data's constructor zeroes after its base.
class PorcupineFormationBodyModuleModuleData
{
public:
	unsigned char m_base[0x5c];
	const WeaponTemplate *m_weapon5C;
	const WeaponTemplate *m_weapon60;
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const PorcupineFormationBodyModuleModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *);
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37();
	virtual Bool rva002143B0(Object *target);
};

// The base body (ILT 0x0003B372 -> ActiveBody::attemptDamage 0x00211D40).
class ActiveBody : public BehaviorModule,
	public BehaviorModuleInterface,
	public BodyModuleInterface
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
};

class PorcupineFormationBodyModule : public ActiveBody
{
public:
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual Bool rva002143B0(Object *target);
};

class PorcupineDamageHelper
{
public:
	void apply(DamageInfo *);
	// Retail 0x00214350: reads only x/y of the two positions.
	Bool withinDistance00214350(Real distance,
		const Coord3D *a, const Coord3D *b);
};

// ?attemptDamage@PorcupineFormationBodyModule@@UAEXPAVDamageInfo@@@Z
void PorcupineFormationBodyModule::attemptDamage(DamageInfo *damageInfo)
{
	Object *object = m_object;
	PorcupineDamageCheckResult *result = 0;
	if (object != 0)
	{
		PorcupineDamageCheck *check = object->m_damageCheck;
		if (check != 0)
		{
			PorcupineDamageCheckResultSource *source = check->m_resultSource;
			if (source != 0)
				result = source->getResult();
		}
	}

	if (result == 0)
		goto fallback;
	if (!result->slot55())
		goto fallback;
	{
		PorcupineDamageHelper *helper = (PorcupineDamageHelper *)this;
		helper->apply(damageInfo);
		goto finish;
	}
fallback:
	{
		ActiveBody::attemptDamage(damageInfo);
		return;
	}
finish:
	{
		ActiveBody::attemptDamage(damageInfo);
	}
}

// BodyModuleInterface slot 38 (+0x98) of vtable 0x010A8E18, through ILT
// 0x0001CD0F. While the porcupine check holds, fires the second module
// weapon at the target when it is in range and reports false.
// ?rva002143B0@PorcupineFormationBodyModule@@UAEEPAVObject@@@Z
Bool PorcupineFormationBodyModule::rva002143B0(Object *target)
{
	Object *object = m_object;
	PorcupineDamageCheckResult *result = 0;
	if (object != 0)
	{
		PorcupineDamageCheck *check = object->m_damageCheck;
		if (check != 0)
		{
			PorcupineDamageCheckResultSource *source = check->m_resultSource;
			if (source != 0)
				result = source->getResult();
		}
	}

	if (result == 0)
		return 1;
	if (!result->slot55())
		return 1;

	Object *source = m_object;
	if (source != 0)
	{
		const PorcupineFormationBodyModuleModuleData *data = m_moduleData;
		if (data != 0 && data->m_weapon60 != 0)
		{
			PorcupineDamageHelper *helper = (PorcupineDamageHelper *)this;
			if (helper->withinDistance00214350(
					data->m_weapon60->getUnmodifiedAttackRange(),
					&source->m_position, &target->m_position))
				TheWeaponStore->createAndFireTempWeapon(data->m_weapon60, source, target);
		}
	}
	return 0;
}

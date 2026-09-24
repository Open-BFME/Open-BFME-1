// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// GarrisonUpgrade::upgradeRemovalImplementation, retail 0x002D54A0 (142 B).
// The GarrisonUpgrade constructor (0x002D5280) installs the UpgradeMux vtable
// 0x010CCA40 at +0x10; its slot 7 (+0x1c) reaches this body through ILT
// 0x00031E5D, the slot CommandSetUpgrade and CostModifierUpgrade land as
// upgradeRemovalImplementation. Slot 8 (+0x20) is setUpgradeExecuted.
//
// Bit 252 of Object's 40-byte model-condition mask at +0x110 (word +0x12c,
// bit 28) is UPGRADE_GARRISON in the shipped ModelCondition name table at
// VA 0x012A6918. It is cleared through native bitset accessor layers and a
// free inline conditional-update helper (docs/shape_levers.md, model-condition
// bit masks): a raw word expression gives the same instructions but swaps the
// ESI/EDI roles of the contain module and the object.
#include <bitset>

typedef bool Bool;
typedef unsigned int UnsignedInt;

class ProjectileUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02(int value);
};

class Object;

class BehaviorModule
{
public:
	virtual void slot00();

protected:
	Object *getObject() const
	{
		return m_object;
	}

	protected:
	void *m_moduleData;
	Object *m_object;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isGarrisonable() const;
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59() const;
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ContainModuleInterface *getContain();
};

class Rva002D54A0ConditionBits
{
public:
	Bool test(int bit) const { return m_bits.test(bit); }
	void reset(int bit) { m_bits.reset(bit); }
private:
	_STL::bitset<320> m_bits;
};

enum ModelConditionFlagType
{
	MODELCONDITION_UPGRADE_GARRISON = 252
};

class Object
{
public:
	void notifyModelConditionChanged();
	ProjectileUpdateInterface *getProjectileUpdateInterface() const;
	BehaviorModule **getBehaviorModules() const
	{
		return m_behaviors;
	}

	char m_padding000[0x110];
	Rva002D54A0ConditionBits m_modelConditionFlags;
	char m_padding138[0xb8];
	BehaviorModule **m_behaviors;
	char m_padding1f4[0x10];
	void *m_ai;
};

static __forceinline void clearCondition(Object *object, ModelConditionFlagType bit)
{
	if (object->m_modelConditionFlags.test(bit))
	{
		object->m_modelConditionFlags.reset(bit);
		object->notifyModelConditionChanged();
	}
}

class UpgradeMux
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void upgradeRemovalImplementation();
	virtual void setUpgradeExecuted(Bool enabled);

};

class ModuleInterface
{
public:
	virtual void slot00();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
};

class GarrisonUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
};

// ?upgradeRemovalImplementation@GarrisonUpgrade@@MAEXXZ
void GarrisonUpgrade::upgradeRemovalImplementation()
{
	Object *object = m_object;

	for (BehaviorModule **module = object->getBehaviorModules(); *module != 0; ++module)
	{
		BehaviorModuleInterface *behavior =
			(BehaviorModuleInterface *)((char *)*module + 0xc);
		ContainModuleInterface *contain = behavior->getContain();
		if (contain != 0 && contain->isGarrisonable())
		{
			clearCondition(object, MODELCONDITION_UPGRADE_GARRISON);
			contain->slot59();
		}
	}

	if (object->m_ai != 0)
	{
		ProjectileUpdateInterface *related = object->getProjectileUpdateInterface();
		if (related != 0)
			related->slot02(0);
	}

	setUpgradeExecuted(false);
}

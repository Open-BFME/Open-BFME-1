// ?upgradeRemovalImplementation@GarrisonUpgrade@@MAEXXZ
// partial score=0.98 date=2026-09-11
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef unsigned int UnsignedInt;

class BfmeY982
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02(int value);
	BfmeY982 *bfmeConv982B();
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

class Object
{
public:
	void notifyModelConditionChanged();
	BehaviorModule **getBehaviorModules() const
	{
		return m_behaviors;
	}

	char m_padding000[0x12c];
	UnsignedInt m_conditionFlags;
	char m_padding130[0xc0];
	BehaviorModule **m_behaviors;
	char m_padding1f4[0x10];
	void *m_ai;
};

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

#pragma comment(linker, "/alternatename:?bfmeConv982B@BfmeY982@@QAEPAV1@XZ=?j_0000de9f@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

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
			if ((object->m_conditionFlags & 0x10000000) != 0)
			{
				object->m_conditionFlags &= 0xefffffff;
				object->notifyModelConditionChanged();
			}
			contain->slot59();
		}
	}

	if (object->m_ai != 0)
	{
		BfmeY982 *related = ((BfmeY982 *)object)->bfmeConv982B();
		if (related != 0)
			related->slot02(0);
	}

	setUpgradeExecuted(false);
}

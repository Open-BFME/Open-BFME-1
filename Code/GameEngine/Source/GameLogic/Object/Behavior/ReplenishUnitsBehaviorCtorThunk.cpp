// cl: /DNDEBUG /MD /EHsc

typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

int largeGroupRandom(int low, int high, const char *file, int line);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
	}

	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0),
		  m_indexInLogic(-1),
		  m_updateState(-1)
	{
	}

	virtual ~UpdateModule() {}

protected:
	void setWakeFrame(Object *object, UnsignedInt sleepTime);

	UnsignedInt m_nextCallFrameAndPhase;
	int m_indexInLogic;
	UnsignedInt m_updateState;
};

class SpawnBehaviorFourthBase
{
public:
	SpawnBehaviorFourthBase();

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void setReplenishing(bool enabled);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
};

struct ReplenishUnitsBehaviorModuleDataView
{
	unsigned char m_pad00[0x88];
	int m_replenishDelay;
	bool m_primeSpawnBehavior;
};

class ReplenishUnitsBehavior : public UpdateModule, public SpawnBehaviorFourthBase
{
public:
	ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~ReplenishUnitsBehavior() {}
};

// ??0ReplenishUnitsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z
ReplenishUnitsBehavior::ReplenishUnitsBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	Object *object = m_object;
	const ReplenishUnitsBehaviorModuleDataView *data =
		reinterpret_cast<const ReplenishUnitsBehaviorModuleDataView *>(m_moduleData);

	if (data->m_primeSpawnBehavior)
	{
		SpawnBehaviorFourthBase *spawn = this;
		spawn->slot2c();
		spawn->slot34();
		spawn->slot24();
		spawn->setReplenishing(true);
		int replenishDelay =
			reinterpret_cast<const ReplenishUnitsBehaviorModuleDataView *>(m_moduleData)->m_replenishDelay;
		setWakeFrame(object, largeGroupRandom(
			1, replenishDelay,
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Behavior\\ReplenishUnitsBehavior.cpp", 116));
	}
	else
	{
		setWakeFrame(object, UPDATE_SLEEP_FOREVER);
	}
}

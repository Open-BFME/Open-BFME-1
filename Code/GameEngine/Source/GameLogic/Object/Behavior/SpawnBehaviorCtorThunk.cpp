// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0SpawnBehavior@@: Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior.cpp
#include <list>

typedef unsigned int UnsignedInt;
class Thing;
class ModuleData;
class ThingTemplate;
class AsciiString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData;
	Thing *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
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
	UnsignedInt m_nextCallFrameAndPhase;
	int m_indexInLogic;
	UnsignedInt m_updateState;
};

template <int Number>
class SpawnBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SpawnBehaviorFourthBase
{
public:
	SpawnBehaviorFourthBase();
	virtual void slot();
};

struct SpawnBehaviorModuleDataView
{
	unsigned char pad00[8];
	UnsignedInt m_spawnNumberData;
	unsigned char pad0c[4];
	UnsignedInt m_initialBurst;
	unsigned char m_isOneShotData;
	unsigned char pad15;
	unsigned char m_aggregateHealth;
	unsigned char pad17[9];
	AsciiString *m_spawnTemplateBegin;
};

class SpawnBehavior
	: public UpdateModule,
	  public SpawnBehaviorSecondaryBase<1>,
	  public SpawnBehaviorSecondaryBase<2>,
	  public SpawnBehaviorSecondaryBase<3>,
	  public SpawnBehaviorFourthBase
{
public:
	SpawnBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~SpawnBehavior() {}
private:
	void *m_unknown30;
	ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	UnsignedInt m_framesToWait;
	UnsignedInt m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<int> m_otherList;
	bool m_active;
	unsigned char m_aggregateHealth;
	bool m_initialBurstTimesInited;
	unsigned char m_pad4f;
	UnsignedInt m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
	UnsignedInt m_initialBurstCountdown;
	AsciiString *m_templateNameIterator;
};

SpawnBehavior::SpawnBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const SpawnBehaviorModuleDataView *md =
		reinterpret_cast<const SpawnBehaviorModuleDataView *>(m_moduleData);
	m_templateNameIterator = md->m_spawnTemplateBegin;
	m_spawnTemplate = TheThingFactory->findTemplate(*m_templateNameIterator);
	m_framesToWait = 0;
	m_firstBatchCount = 0;
	if (md->m_isOneShotData)
		m_oneShotCountdown = md->m_spawnNumberData;
	else
		m_oneShotCountdown = -1;
	m_active = true;
	m_replacementTimes.clear();
	m_initialBurstCountdown = md->m_initialBurst;
	m_initialBurstTimesInited = false;
	m_aggregateHealth = md->m_aggregateHealth;
	m_spawnCount = 0xffffffff;
	m_active = true;
	m_selfTaskingSpawnCount = 0;
}

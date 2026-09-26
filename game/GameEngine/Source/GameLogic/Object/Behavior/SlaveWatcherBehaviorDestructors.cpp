// cl: /DNDEBUG /MD /EHsc
// Constructor store at 0x00207341 writes UpdateModule+0x14; its independently
// matched setWakeFrame callee and layout witness name m_nextCallFrameAndPhase.
// Field +0x20 is passed to named findObjectByID by destructor 0x00207580;
// retain its offset because the object relationship is not independently proved.
// Complete destructor 0x00207580 also emits scalar wrapper 0x002076E0;
// constructor 0x00207300 and vtable 0x010A64DC identify this class.

class Thing;
class ModuleData;

enum DamageType
{
	DAMAGE_NORMAL = 0
};

enum DeathType
{
	DEATH_SLAVE_WATCHER_RELEASE = 13
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void kill(DamageType, DeathType);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int);
};

extern GameLogic *TheGameLogic;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

protected:
	void *m_p4;
	Object *m_object;
};

class SlaveWatcherBehaviorIface1
{
public:
	virtual void slot() = 0;
};

class SlaveWatcherBehaviorIface2
{
public:
	virtual void slot() = 0;
};

class SlaveWatcherUpdateModuleBase : public PB_DeepBase, public SlaveWatcherBehaviorIface1
{
public:
	virtual ~SlaveWatcherUpdateModuleBase() {}
};

class SlaveWatcherUpdateModule : public SlaveWatcherUpdateModuleBase, public SlaveWatcherBehaviorIface2
{
public:
	virtual ~SlaveWatcherUpdateModule() {}
};

class SlaveWatcherBehavior : public SlaveWatcherUpdateModule
{
public:
	virtual ~SlaveWatcherBehavior();

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_f18;
	int m_f1c;
	int m_objectID20;
};

SlaveWatcherBehavior::~SlaveWatcherBehavior()
{
	if (m_objectID20)
	{
		Object *slave = TheGameLogic->findObjectByID(m_objectID20);
		if (slave)
			slave->kill(DAMAGE_NORMAL, DEATH_SLAVE_WATCHER_RELEASE);
	}
}

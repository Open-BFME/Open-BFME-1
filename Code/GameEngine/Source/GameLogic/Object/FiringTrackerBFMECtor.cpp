// cl: /DNDEBUG /MD /EHsc

typedef int ObjectID;
typedef int AudioHandle;

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
protected:
	virtual ~Module();

private:
	const void *m_moduleData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Module
{
public:
	ObjectModule(Thing *thing, const ModuleData *data);

protected:
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) :
		ObjectModule(thing, data)
	{
	}
	virtual ~BehaviorModule() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *data) :
		BehaviorModule(thing, data),
		m_nextCallFrameAndPhase(0),
		m_indexInLogic(-1),
		m_pad(-1)
	{
	}
	virtual ~UpdateModule() {}

protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	float x;
	float y;
	float z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/FiringTracker.h
class FiringTracker : public UpdateModule
{
public:
	FiringTracker(Thing *thing, const ModuleData *data);

protected:
	virtual ~FiringTracker();

private:
	int m_consecutiveShots;
	ObjectID m_victimID;
	Coord3D m_victimPosition;
	bool m_victimIsPosition;
	unsigned char m_alignment_035[3];
	unsigned int m_value38;
	unsigned int m_value3c;
	unsigned int m_value40;
	unsigned int m_value44;
	Coord3D m_lastShotPosition;
	unsigned int m_value54;
	AudioHandle m_audioHandle;
};

FiringTracker::FiringTracker(Thing *thing, const ModuleData *data) :
	UpdateModule(thing, data)
{
	m_consecutiveShots = 0;
	m_victimID = 0;
	m_victimPosition.zero();
	m_lastShotPosition.zero();
	m_victimIsPosition = false;
	m_value38 = 0;
	m_value3c = 0;
	m_value40 = 0;
	m_value44 = 0;
	m_value54 = 0;
	m_audioHandle = 1;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class Thing;
class ModuleData;
class Object;

class Gen_dtor_00113d40
{
public:
	virtual ~Gen_dtor_00113d40();

private:
	const void *m_moduleData;
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
class ObjectModule : public Gen_dtor_00113d40
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
	BehaviorModule(Thing *thing, const ModuleData *data) : ObjectModule(thing, data) {}
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
		m_updateState(-1)
	{
	}
	virtual ~UpdateModule() {}

	void setWakeFrame(Object *object, unsigned int frame);

protected:

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;
};

class SiegeDockingBehaviorSecondaryBase
{
public:
	virtual void slot();
};

class SiegeDockingBehavior : public UpdateModule, public SiegeDockingBehaviorSecondaryBase
{
public:
	SiegeDockingBehavior(Thing *thing, const ModuleData *data);
	virtual ~SiegeDockingBehavior();

private:
	_STL::vector<int> m_vector;
	bool m_enabled;
};

SiegeDockingBehavior::SiegeDockingBehavior(Thing *thing, const ModuleData *data) :
	UpdateModule(thing, data),
	m_enabled(false)
{
	setWakeFrame(m_object, 1);
}

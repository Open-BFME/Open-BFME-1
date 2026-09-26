// cl: /DNDEBUG /MD /EHsc
// Retail 0x0027FB60: the ModuleFactory caller at 0x00117C40 constructs this
// class, and vtable 0x010BACD4 names its deleting destructor. BFME initializes
// the UpdateModule state and sets the wake frame to UPDATE_SLEEP_FOREVER;
// Zero Hour also initializes two laser pointers that retail does not store.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// Upstream layout: GameLogic/Module/ObjectModule.h.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	void *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorInterfaceAnchor();
};

// Upstream layout: GameLogic/Module/UpdateModule.h.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData),
		  m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_pad(-1)
	{
	}

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	Object *getObject() const { return m_object; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_pad;
};

// Upstream layout: GameLogic/Module/AssistedTargetingUpdate.h.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssistedTargetingUpdate.h
class AssistedTargetingUpdate : public UpdateModule
{
public:
	AssistedTargetingUpdate(Thing *, const ModuleData *);
	virtual ~AssistedTargetingUpdate();
};

AssistedTargetingUpdate::AssistedTargetingUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

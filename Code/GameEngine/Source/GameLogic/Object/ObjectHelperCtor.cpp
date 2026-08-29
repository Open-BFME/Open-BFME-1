// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

// Upstream layout: GameLogic/Module/ObjectModule.h.
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);
	virtual ~ObjectModule();

protected:
	void *m_moduleData;
	Object *m_object;
};

class UpdateModuleInterface
{
public:
	virtual void updateInterfaceAnchor();
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorInterfaceAnchor();
};

// Upstream layout: GameLogic/Module/UpdateModule.h.
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

// Upstream layout: GameLogic/Module/ObjectHelper.h.
class ObjectHelper : public UpdateModule
{
public:
	ObjectHelper(Thing *, const ModuleData *);
	virtual ~ObjectHelper();
};

ObjectHelper::ObjectHelper(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

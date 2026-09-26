// cl: /DNDEBUG /MD /EHsc
// Retail 0x001ECF40: the matched factory at 0x00115130 constructs this class,
// and vtable 0x010A1A24 routes to its named deleting destructor. The constructor
// initializes UpdateModule, clears an as-yet unnamed byte at +0x20, and sets
// the wake frame to UPDATE_SLEEP_NONE.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
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

// BFME-specific subclass; the retail constructor and factory prove this view.
class AimWeaponBehavior : public UpdateModule
{
public:
	AimWeaponBehavior(Thing *, const ModuleData *);
	virtual ~AimWeaponBehavior();

private:
	bool m_unreconstructed_20;
};

AimWeaponBehavior::AimWeaponBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	m_unreconstructed_20 = false;
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

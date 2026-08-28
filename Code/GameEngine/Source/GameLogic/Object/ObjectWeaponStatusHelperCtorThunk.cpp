// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ObjectWeaponStatusHelper module ctor.
//
// Zero Hour has this one inline in ObjectWeaponStatusHelper.h and BFME kept it:
// delegate to the ObjectHelper base, then wake the helper up immediately, since
// unlike the other helpers this one has to run every frame.
//
// Base call then three most-derived vtbls at +0/+0xC/+0x10, so the class carries
// two single-virtual interface bases behind the module base. getObject() reads
// this+8, and UPDATE_SLEEP_NONE is the pushed 1.

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	Object *m_object;							///< retail this+0x08
};

class __declspec(novtable) ObjectWeaponStatusHelperIface1
{
public:
	virtual void objectWeaponStatusIface1Anchor();
};

class __declspec(novtable) ObjectWeaponStatusHelperIface2
{
public:
	virtual void objectWeaponStatusIface2Anchor();
};

class ObjectWeaponStatusHelperBase : public BehaviorModule
{
public:
	ObjectWeaponStatusHelperBase(Thing *thing, const ModuleData *moduleData);

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime when);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectWeaponStatusHelper.h
class ObjectWeaponStatusHelper : public ObjectWeaponStatusHelperBase,
	public ObjectWeaponStatusHelperIface1,
	public ObjectWeaponStatusHelperIface2
{
public:
	ObjectWeaponStatusHelper(Thing *thing, const ModuleData *moduleData);

protected:
	Object *getObject(void) const { return m_object; }
};

// ??0ObjectWeaponStatusHelper@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectWeaponStatusHelper::ObjectWeaponStatusHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectWeaponStatusHelperBase(thing, moduleData)
{
	// Unlike other helpers, this one needs to start active.
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: ObjectSMCHelper constructor, retail 0x001C54A0.
//
// The identity is fixed by the three ObjectSMCHelper vftables installed here,
// the timer-list member at +0x20 used by setModelConditionState, and the
// matched ObjectSMCHelper destructor that clears that same list.

#include <list>

class Thing;
class ModuleData;

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();

private:
	unsigned char m_moduleData[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
};

class ObjectHelper : public ModuleInterface,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	ObjectHelper(Thing *, const ModuleData *);
	virtual ~ObjectHelper();
	virtual void moduleInterfaceAnchor();
	virtual void behaviorModuleInterfaceAnchor();
	virtual void updateModuleInterfaceAnchor();

private:
	unsigned char m_helperData[0xc];
};

struct ObjectSMCTimer
{
	unsigned int m_condition;
	unsigned int m_frame;
};

class ObjectSMCHelper : public ObjectHelper
{
public:
	ObjectSMCHelper(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectSMCHelper();
	virtual void moduleInterfaceAnchor();
	virtual void behaviorModuleInterfaceAnchor();
	virtual void updateModuleInterfaceAnchor();

private:
	_STL::list<ObjectSMCTimer> m_timers;
};

ObjectSMCHelper::ObjectSMCHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
}

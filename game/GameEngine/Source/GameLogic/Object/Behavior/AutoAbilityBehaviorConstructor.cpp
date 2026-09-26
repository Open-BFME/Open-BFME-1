// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x001ED8A0: the matched factory at 0x00114F10 constructs this class,
// and vtable 0x010A1BC4 belongs to its matched destructor. The command-ready
// predicate reads the AsciiString at +0x20; this constructor initializes it
// from the empty literal before scheduling UPDATE_SLEEP_FOREVER.

class Thing;
class ModuleData;
class Object;
#include "ascii_string.h"

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
class AutoAbilityBehavior : public UpdateModule
{
public:
	AutoAbilityBehavior(Thing *, const ModuleData *);
	virtual ~AutoAbilityBehavior();

private:
	AsciiString m_command;
};

AutoAbilityBehavior::AutoAbilityBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	((StringBase<char> *)&m_command)->set("", 0);
	setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}

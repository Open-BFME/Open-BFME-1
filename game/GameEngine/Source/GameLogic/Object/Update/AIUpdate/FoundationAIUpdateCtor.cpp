// cl: /DNDEBUG /MD /EHsc
//
// FoundationAIUpdate::FoundationAIUpdate, retail 0x002BA040 (190 B).
//
// The body is the most-derived constructor of the class whose vtable is
// 0x010C734C: it calls the out-of-line ObjectModule constructor through ILT
// 0x000170E4, inlines the intermediate UpdateModule constructor (which installs
// the 0x0109C9D0 / 0x0109CBA0 ctor vtables and clears +0x14, +0x18, +0x1c), then
// inlines the FoundationAIUpdateIface3 base constructor (0x010C722C at +0x20),
// re-installs the four derived ctor vtables, constructs the 0x70-byte
// AudioEventRTS member at +0x24 from the global empty AsciiString, clears
// +0x94, sets the +0x98 flag, and finishes with
// UpdateModule::setWakeFrame(m_object, UPDATE_SLEEP_NONE).
//
// The destructor at 0x002B9D60 (game/.../FoundationAIUpdateDestructors.cpp)
// supplies the other half of the layout: it destroys the same +0x24 subobject
// through the AudioEventRTS destructor ILT 0x00026F35, and
// FoundationAIUpdate::handle (0x002BA940) reads +0x74 from the interface
// subobject at +0x20, i.e. +0x94 in the complete object, which is the
// m_pendingFoundation cleared here.

class Thing;
class ModuleData;
class Object;
class AsciiString;

typedef int Int;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AudioEvent.h
class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &name, Int forceRtMix);
	virtual ~AudioEventRTS();

private:
	unsigned char m_padding[0x6c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class Module
{
protected:
	virtual ~Module();

private:
	const void *m_moduleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule : public Module
{
public:
	ObjectModule(Thing *thing, const ModuleData *data);

protected:
	Object *m_object;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void getBehaviorModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterface() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *data) :
		ObjectModule(thing, data)
	{
	}
	virtual ~BehaviorModule() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class FoundationAIUpdateIface3
{
public:
	virtual void iface3Slot00() = 0;
	virtual void iface3Slot04() = 0;
	virtual void iface3Slot08() = 0;
	virtual void iface3Slot0c() = 0;
	virtual void iface3Slot10() = 0;
	virtual void iface3Slot14() = 0;
	virtual void iface3Slot18() = 0;
	virtual void handle() = 0;
};

// 0x01336E50, the shared empty AsciiString
extern const AsciiString Rva01336E50EmptyString;

class FoundationAIUpdate : public UpdateModule, public FoundationAIUpdateIface3
{
public:
	FoundationAIUpdate(Thing *thing, const ModuleData *data);
	virtual ~FoundationAIUpdate();

private:
	AudioEventRTS m_sound;
	void *m_pendingFoundation;
	Bool m_pendingFlag;
};

FoundationAIUpdate::FoundationAIUpdate(Thing *thing, const ModuleData *data) :
	UpdateModule(thing, data),
	FoundationAIUpdateIface3(),
	m_sound(Rva01336E50EmptyString, 0),
	m_pendingFoundation(0),
	m_pendingFlag(true)
{
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

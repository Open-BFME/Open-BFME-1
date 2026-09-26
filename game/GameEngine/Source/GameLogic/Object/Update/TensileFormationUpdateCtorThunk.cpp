// cl: /DNDEBUG /MD /EHsc

#include <string.h>

class Thing;
class ModuleData;
class BodyModuleInterface;

class Module
{
public:
	virtual ~Module();

private:
	const void *m_moduleData;
};

class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() = 0;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class ObjectModule : public Module
{
public:
	ObjectModule(Thing *, const ModuleData *);

private:
	void *m_object;
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
protected:
	BehaviorModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
	}

public:
	virtual ~BehaviorModule() {}
};

// Retail teardown restores a distinct +0x10 vtable instead of the one shared by
// the other UpdateModule-derived classes, so this intermediate stays unnamed.
class TensileFormationUpdateBase : public BehaviorModule, public UpdateModuleInterface
{
protected:
	TensileFormationUpdateBase(Thing *thing, const ModuleData *moduleData)
		: BehaviorModule(thing, moduleData)
	{
	}

	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	unsigned int m_updateState;

public:
	virtual ~TensileFormationUpdateBase() {}
};

class TensileFormationUpdateMember
{
public:
	TensileFormationUpdateMember()
		: m_begin(0), m_end(0), m_capacity(0)
	{
	}

	~TensileFormationUpdateMember();

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class TensileFormationUpdate : public TensileFormationUpdateBase
{
public:
	TensileFormationUpdate(Thing *, const ModuleData *);
	virtual ~TensileFormationUpdate();

private:
	unsigned char m_pad[0xb4];
	TensileFormationUpdateMember m_member;
};

TensileFormationUpdate::TensileFormationUpdate(Thing *thing, const ModuleData *moduleData)
	: TensileFormationUpdateBase(thing, moduleData)
{
	// Retail clears the three witnessed base words and contiguous derived storage
	// in one operation.
	memset(&m_nextCallFrameAndPhase, 0, 0xc0);
}

TensileFormationUpdate::~TensileFormationUpdate()
{
}

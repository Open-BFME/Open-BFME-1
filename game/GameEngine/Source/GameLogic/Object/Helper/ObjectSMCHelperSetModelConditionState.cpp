// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef unsigned int UnsignedInt;

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	virtual void updateModuleAnchor();

protected:
	void *m_moduleData;
	Object *m_object;
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
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

class ModelConditionFlags
{
public:
	bool test(int condition) const
	{
		return m_bits._Unchecked_test(condition);
	}

	void set(int condition)
	{
		m_bits._Unchecked_set(condition);
	}

private:
	_STL::bitset<320> m_bits;
};

#define BFME_HAVE_MODELCONDITIONFLAGS
#include "../object.h"

// Retail routes these three member calls through ILT thunks.
extern void j_00007d74();
extern void j_0002191d();
extern void j_000157da();

struct Rva002571A0Elem
{
	UnsignedInt m_condition;
	UnsignedInt m_frame;
};

struct Rva002571A0Node
{
	Rva002571A0Node *m_next;
	Rva002571A0Node *m_previous;
	Rva002571A0Elem m_value;
};

class Rva002571A0List
{
public:
	void push_back(Rva002571A0Elem const &value);
	Rva002571A0Node *sentinel() const
	{
		return m_node;
	}

private:
	Rva002571A0Node *m_node;
};

class ObjectSMCHelper : public ObjectHelper,
	public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	void setModelConditionState(int condition, UnsignedInt frames);

private:
	unsigned char m_padding[0xc];
	Rva002571A0List m_timers;
};

class GameLogicFrameSource
{
private:
	unsigned char m_padding[0x3c];

public:
	UnsignedInt m_frame;
};

class GameLogic;
extern GameLogic *TheGameLogic;
static inline GameLogicFrameSource *TheBfmeGameLogicView() { return (GameLogicFrameSource *)TheGameLogic; }

template <typename T>
const T &maximum(const T &left, const T &right)
{
	return left > right ? left : right;
}

// Route classes: retail's three calls go through ILT thunks, so the receiver is
// only ever used to set ecx.
class Route007d74 {};
class Route0157da {};

static __forceinline int callFramesUntilNext(ObjectSMCHelper *self)
{
	typedef int (Route007d74::*FramesUntilNext)();
	union { void (*fn)(); FramesUntilNext call; } u = { j_00007d74 };
	return ((Route007d74 *)self->*u.call)();
}

static __forceinline void callSetWakeFrame(UpdateModule *self, Object *object,
	UpdateSleepTime sleepTime)
{
	typedef void (Route0157da::*SetWakeFrame)(Object *, UpdateSleepTime);
	union { void (*fn)(); SetWakeFrame call; } u = { j_000157da };
	((Route0157da *)self->*u.call)(object, sleepTime);
}

void ObjectSMCHelper::setModelConditionState(int condition,
	UnsignedInt frames)
{
	if (condition < 0 || condition >= 0x130)
	{
		return;
	}

	UnsignedInt frame = TheBfmeGameLogicView()->m_frame;
	Rva002571A0Node *sentinel = m_timers.sentinel();
	Rva002571A0Node *node = sentinel->m_next;
	while (node != sentinel)
	{
		if ((int)node->m_value.m_condition == condition)
		{
			goto update_timer;
		}
		node = node->m_next;
	}

	Rva002571A0Elem value = {(UnsignedInt)condition, frame + frames};
	m_timers.push_back(value);
	goto set_condition;

update_timer:
	UnsignedInt endFrame = frame + frames;
	node->m_value.m_frame = maximum(node->m_value.m_frame, endFrame);
	goto set_wake;

set_condition:
	Object *object = m_object;
	if (!object->m_modelConditionFlags.test(condition))
	{
		object->m_modelConditionFlags.set(condition);
		typedef void (Object::*Notify)();
		union { void (*fn)(); Notify call; } notify = { j_0002191d };
		(object->*notify.call)();
	}

set_wake:
	int framesUntilNextValue = callFramesUntilNext(this);
	callSetWakeFrame(this, m_object, (UpdateSleepTime)framesUntilNextValue);
}

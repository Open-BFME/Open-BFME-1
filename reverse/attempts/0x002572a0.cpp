// ?d_002572a0@@YAXXZ
// partial score=0.98 date=2026-09-10
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef unsigned int UnsignedInt;

class Object;
class Thing;
class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class UpdateModule
{
public:
	virtual void updateInterfaceAnchor();

protected:
	void setWakeFrame(Object *, UpdateSleepTime);
	void *m_moduleData;
	Object *m_object;
	unsigned char m_padding[0x14];
};

class ObjectHelper : public UpdateModule
{
public:
	virtual ~ObjectHelper();
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

class Object
{
public:
	void notifyModelConditionChanged();
	unsigned char m_padding[0x110];
	ModelConditionFlags m_modelConditionFlags;
};

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

class Rva002572A0ObjectSMCHelper : public ObjectHelper
{
public:
	void setModelConditionState(int condition, UnsignedInt frames);

private:
	int framesUntilNext();
	Rva002571A0List m_timers;
};

class GameLogicFrameSource
{
private:
	unsigned char m_padding[0x3c];

public:
	UnsignedInt m_frame;
};

#define TheBfmeGameLogic (*(GameLogicFrameSource **)0x012F0898)

template <typename T>
const T &maximum(const T &left, const T &right)
{
	return left > right ? left : right;
}

#pragma comment(linker, "/alternatename:?framesUntilNext@Rva002572A0ObjectSMCHelper@@AAEHXZ=?j_00007d74@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?setWakeFrame@UpdateModule@@IAEXPAVObject@@W4UpdateSleepTime@@@Z=?j_000157da@@YAXXZ")

void Rva002572A0ObjectSMCHelper::setModelConditionState(int condition,
	UnsignedInt frames)
{
	if (condition < 0 || condition >= 0x130)
	{
		return;
	}

	UnsignedInt frame = TheBfmeGameLogic->m_frame;
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
	goto set_flags;

update_timer:
	UnsignedInt endFrame = frame + frames;
	node->m_value.m_frame = maximum(node->m_value.m_frame, endFrame);

set_flags:

	Object *object = m_object;
	if (!object->m_modelConditionFlags.test(condition))
	{
		object->m_modelConditionFlags.set(condition);
		object->notifyModelConditionChanged();
	}

	setWakeFrame(m_object, (UpdateSleepTime)framesUntilNext());
}

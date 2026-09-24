// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// The constructor at 0x001C54A0 installs 0x002571F0 in the
// ObjectSMCHelper UpdateModuleInterface vtable at 0x0109EAEC.
// The timer list at +0x20 and the framesUntilNext call tie this body to that class.

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
	void setWakeFrame(Object *, UpdateSleepTime);
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
	virtual UpdateSleepTime update();
};

class ModelConditionFlags
{
public:
	bool test(int condition) const
	{
		return m_bits._Unchecked_test(condition);
	}

	void reset(int condition)
	{
		m_bits._Unchecked_reset(condition);
	}

private:
	_STL::bitset<320> m_bits;
};

#define BFME_HAVE_MODELCONDITIONFLAGS
#define OBJECT_TU_MEMBERS \
	void notifyModelConditionChanged();
#include "../object.h"

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
	virtual UpdateSleepTime update();

private:
	int framesUntilNext();
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

#define TheBfmeGameLogic (*(GameLogicFrameSource **)0x012F0898)

template <bool threads, int instance>
class BfmeNodeAllocator
{
public:
	static void __cdecl deallocate(void *node, UnsignedInt bytes);
};

#pragma comment(linker, "/alternatename:?deallocate@?$BfmeNodeAllocator@$00$0A@@@SAXPAXI@Z=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

#pragma comment(linker, "/alternatename:?framesUntilNext@ObjectSMCHelper@@AAEHXZ=?j_00007d74@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")

UpdateSleepTime ObjectSMCHelper::update()
{
	UnsignedInt frame = TheBfmeGameLogic->m_frame;
	Rva002571A0Node *node = m_timers.sentinel()->m_next;
	while (node != m_timers.sentinel())
	{
		UnsignedInt endFrame = node->m_value.m_frame;
		int condition = node->m_value.m_condition;
		Rva002571A0Node *old = node;
		node = node->m_next;
		if (frame <= endFrame)
		{
			continue;
		}
		{
			Object *object = m_object;
			if (object->m_modelConditionFlags.test(condition))
			{
				object->m_modelConditionFlags.reset(condition);
				object->notifyModelConditionChanged();
			}

			Rva002571A0Node *next = old->m_next;
			Rva002571A0Node *previous = old->m_previous;
			previous->m_next = next;
			next->m_previous = previous;
			BfmeNodeAllocator<true, 0>::deallocate(old, 0x10);
		}
	}
	return (UpdateSleepTime)framesUntilNext();
}

// cl: /DNDEBUG /MD /EHsc /Igame
//
// AIGiantBirdSwoopState::onExit, retail RVA 0x002BE320.  The constructor at
// 0x002BE230 stores vtable 0x010C7868, whose slot 5 thunk 0x0044AEC6 jumps
// here.

typedef int Int;
typedef unsigned int UnsignedInt;

enum StateExitType
{
	STATE_EXIT_UNKNOWN = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

// The condition-change notification is Object's own member: the call goes
// through ILT 0x0002191D, whose thunk jumps to
// ?notifyModelConditionChanged@Object@@QAEXXZ (0x001BE1C0).  The body reaches
// the object as a raw pointer, so the real header supplies the spelling and no
// AIUpdateInterface stands in for it.
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged(void);
#include "GameEngine/Source/GameLogic/Object/object.h"

class Pathfinder
{
public:
	void removeGoal(Object *object);
	void updateGoal(Object *object, const Coord3D *position, int layer,
		const char *file, Int line);
};

class AI
{
public:
	Pathfinder *pathfinder()
	{
		return *(Pathfinder **)((unsigned char *)this + 0x0c);
	}
};

extern AI *TheAI;

class State
{
public:
	virtual void stateAnchor() = 0;

	Object *getMachineOwner()
	{
		unsigned char *machine = *(unsigned char **)((unsigned char *)this + 0x1c);
		return *(Object **)(machine + 0x10);
	}
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class Locomotor : public BfmeVirtualSlots<127>
{
public:
	virtual void clearFlightState(int value) = 0;
};

class AIGiantBirdSwoopState : public State
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@AIGiantBirdSwoopState@@UAEXW4StateExitType@@@Z
void AIGiantBirdSwoopState::onExit(StateExitType status)
{
	Object *object = getMachineOwner();
	if (object != 0)
	{
		UnsignedInt flags = *(UnsignedInt *)((unsigned char *)object + 0x114);
		if (flags & 0x10000000)
		{
			flags &= 0xefffffff;
			*(UnsignedInt *)((unsigned char *)object + 0x114) = flags;
			((Object *)object)->notifyModelConditionChanged();
		}
		if (*(unsigned char *)((unsigned char *)object + 0x11c) & 0x40)
		{
			flags = *(UnsignedInt *)((unsigned char *)object + 0x11c) & 0xffffffbf;
			*(UnsignedInt *)((unsigned char *)object + 0x11c) = flags;
			((Object *)object)->notifyModelConditionChanged();
		}
		if ((*(unsigned char *)((unsigned char *)object + 0x118) >> 7) != 0)
		{
			flags = *(UnsignedInt *)((unsigned char *)object + 0x118) & 0xffffff7f;
			*(UnsignedInt *)((unsigned char *)object + 0x118) = flags;
			((Object *)object)->notifyModelConditionChanged();
		}

		Locomotor *locomotor = *(Locomotor **)((unsigned char *)object + 0x204);
		if (locomotor != 0)
			locomotor->clearFlightState(0);
	}

	TheAI->pathfinder()->removeGoal(object);
#line 784 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal(object,
		(const Coord3D *)((const unsigned char *)object + 0x38), 1, __FILE__, __LINE__);
}

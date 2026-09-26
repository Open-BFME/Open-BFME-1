// cl: /DNDEBUG /MD /EHsc
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

class Object;

class AIUpdateInterface
{
public:
	void notifyModelConditionChanged();
};

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
			((AIUpdateInterface *)object)->notifyModelConditionChanged();
		}
		if (*(unsigned char *)((unsigned char *)object + 0x11c) & 0x40)
		{
			flags = *(UnsignedInt *)((unsigned char *)object + 0x11c) & 0xffffffbf;
			*(UnsignedInt *)((unsigned char *)object + 0x11c) = flags;
			((AIUpdateInterface *)object)->notifyModelConditionChanged();
		}
		if ((*(unsigned char *)((unsigned char *)object + 0x118) >> 7) != 0)
		{
			flags = *(UnsignedInt *)((unsigned char *)object + 0x118) & 0xffffff7f;
			*(UnsignedInt *)((unsigned char *)object + 0x118) = flags;
			((AIUpdateInterface *)object)->notifyModelConditionChanged();
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

// cl: /DNDEBUG /MD /EHsc
//
// Address-derived recovery for the GiantBird-family state exit body at
// retail RVA 0x002BDF10.

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

class Rva002BDF10Base
{
public:
	virtual void onExit(StateExitType status);
};

class AIUpdateInterface
{
public:
	void notifyModelConditionChanged();
};

class Object;

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

class Rva002BDF10State : public Rva002BDF10Base
{
public:
	virtual void onExit(StateExitType status);
};

void Rva002BDF10State::onExit(StateExitType status)
{
	Rva002BDF10Base::onExit(status);

	unsigned char *machine = *(unsigned char **)((unsigned char *)this + 0x1c);
	unsigned char *ai = *(unsigned char **)(machine + 0x10);
	unsigned char *locomotor = *(unsigned char **)(ai + 0x204);
	if (locomotor != 0)
		*(UnsignedInt *)(locomotor + 0x3f0) &= 0xffffff7f;

	UnsignedInt flags = *(UnsignedInt *)(ai + 0x114);
	if (flags & 0x10000000)
	{
		flags &= 0xefffffff;
		*(UnsignedInt *)(ai + 0x114) = flags;
		((AIUpdateInterface *)ai)->notifyModelConditionChanged();
	}
	if (*(unsigned char *)(ai + 0x11c) & 0x40)
	{
		flags = *(UnsignedInt *)(ai + 0x11c) & 0xffffffbf;
		*(UnsignedInt *)(ai + 0x11c) = flags;
		((AIUpdateInterface *)ai)->notifyModelConditionChanged();
	}
	if (*(unsigned char *)(ai + 0x118) & 0x80)
	{
		flags = *(UnsignedInt *)(ai + 0x118) & 0xffffff7f;
		*(UnsignedInt *)(ai + 0x118) = flags;
		((AIUpdateInterface *)ai)->notifyModelConditionChanged();
	}

	TheAI->pathfinder()->removeGoal((Object *)ai);
#line 278 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal((Object *)ai, (const Coord3D *)(ai + 0x38),
		1, __FILE__, __LINE__);
}

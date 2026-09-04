// cl: /DNDEBUG /MD /EHsc
//
// Address-derived recovery of the GiantBird state exit body at retail RVA
// 0x002BEE90.  The state clears all four flight-condition groups, rebuilds
// the ground goal, then resets the attached locomotor's landing state.

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

class Rva002BEE90State
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@Rva002BEE90State@@UAEXW4StateExitType@@@Z
void Rva002BEE90State::onExit(StateExitType status)
{
	unsigned char *machine = *(unsigned char **)((unsigned char *)this + 0x1c);
	unsigned char *object = *(unsigned char **)(machine + 0x10);

	UnsignedInt flags = *(UnsignedInt *)(object + 0x114);
	if (flags & 0x10000000)
	{
		flags &= 0xefffffff;
		*(UnsignedInt *)(object + 0x114) = flags;
		((AIUpdateInterface *)object)->notifyModelConditionChanged();
	}
	if (*(unsigned char *)(object + 0x11c) & 0x40)
	{
		flags = *(UnsignedInt *)(object + 0x11c) & 0xffffffbf;
		*(UnsignedInt *)(object + 0x11c) = flags;
		((AIUpdateInterface *)object)->notifyModelConditionChanged();
	}
	if ((*(unsigned char *)(object + 0x118) >> 7) != 0)
	{
		flags = *(UnsignedInt *)(object + 0x118) & 0xffffff7f;
		*(UnsignedInt *)(object + 0x118) = flags;
		((AIUpdateInterface *)object)->notifyModelConditionChanged();
	}
	flags = *(UnsignedInt *)(object + 0x120);
	if (flags & 0x20000)
	{
		flags &= 0xfffdffff;
		*(UnsignedInt *)(object + 0x120) = flags;
		((AIUpdateInterface *)object)->notifyModelConditionChanged();
	}

	TheAI->pathfinder()->removeGoal((Object *)object);
#line 1256 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal((Object *)object,
		(const Coord3D *)(object + 0x38), 1, __FILE__, __LINE__);

	unsigned char *locomotor = *(unsigned char **)(object + 0x204);
	if (locomotor != 0)
	{
		*(unsigned char *)(locomotor + 0x490) = 0;
		*(UnsignedInt *)(locomotor + 0x494) = 2;
	}
}

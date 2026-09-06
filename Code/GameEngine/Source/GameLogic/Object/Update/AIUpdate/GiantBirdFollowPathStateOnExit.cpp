// cl: /DNDEBUG /MD /EHsc
//
// GiantBirdFollowPathState::onExit, retail RVA 0x002BDF10, from
// GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp (the retail __FILE__
// literal this body passes to Pathfinder::updateGoal).
//
// Identity: the state's constructor at 0x002BDB30 stores vftable 0x010C7778
// and passes the literal "GiantBirdFollowPathState" to its base; slot 5 of
// that vftable is this body.  The base is AIFollowPathState -- slot 6 of the
// base vftable at 0x00C9A9F0 is ?update@AIFollowPathState@@.

typedef int Int;
typedef unsigned int UnsignedInt;

enum StateExitType
{
	STATE_EXIT_UNKNOWN = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class AIFollowPathState
{
public:
	virtual void onExit(StateExitType status);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	void notifyModelConditionChanged();
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void removeGoal(Object *object);
	void updateGoal(Object *object, const Coord3D *position, int layer,
		const char *file, Int line);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder()
	{
		return *(Pathfinder **)((unsigned char *)this + 0x0c);
	}
};

extern AI *TheAI;

class GiantBirdFollowPathState : public AIFollowPathState
{
public:
	virtual void onExit(StateExitType status);
};

void GiantBirdFollowPathState::onExit(StateExitType status)
{
	AIFollowPathState::onExit(status);

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

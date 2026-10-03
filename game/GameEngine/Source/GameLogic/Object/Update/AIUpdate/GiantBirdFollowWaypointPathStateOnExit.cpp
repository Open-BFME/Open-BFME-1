// cl: /DNDEBUG /MD /EHsc /Igame
//
// GiantBirdFollowWaypointPathState::onExit at retail RVA 0x002BF3A0.
// The constructor at 0x002BEFA0 stores the state name, and its vtable at
// 0x010C79E0 places this body in slot 5 beside the matched update at 0x002BF250.

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

extern void j_00015d02();
class Pathfinder
{
public:
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

class GiantBirdFollowWaypointPathState
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@GiantBirdFollowWaypointPathState@@UAEXW4StateExitType@@@Z
void GiantBirdFollowWaypointPathState::onExit(StateExitType status)
{
	unsigned char *machine = *(unsigned char **)((unsigned char *)this + 0x1c);
	unsigned char *object = *(unsigned char **)(machine + 0x10);

	unsigned char *locomotor = *(unsigned char **)(object + 0x204);
	if (locomotor != 0)
		*(UnsignedInt *)(locomotor + 0x3f0) &= 0xffffff7f;

	UnsignedInt flags = *(UnsignedInt *)(object + 0x114);
	if (flags & 0x10000000)
	{
		flags &= 0xefffffff;
		*(UnsignedInt *)(object + 0x114) = flags;
		((Object *)object)->notifyModelConditionChanged();
	}
	if (*(unsigned char *)(object + 0x11c) & 0x40)
	{
		flags = *(UnsignedInt *)(object + 0x11c) & 0xffffffbf;
		*(UnsignedInt *)(object + 0x11c) = flags;
		((Object *)object)->notifyModelConditionChanged();
	}
	if ((*(unsigned char *)(object + 0x118) >> 7) != 0)
	{
		flags = *(UnsignedInt *)(object + 0x118) & 0xffffff7f;
		*(UnsignedInt *)(object + 0x118) = flags;
		((Object *)object)->notifyModelConditionChanged();
	}

	// Retail calls the incremental-link thunk 0x00015D02 (-> 0x003E3D20).
	typedef void (Pathfinder::*RemoveGoalFn)(Object *);
	union { void (*fn)(); RemoveGoalFn call; } removeGoal = { j_00015d02 };
	(TheAI->pathfinder()->*removeGoal.call)((Object *)object);
#line 1516 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal((Object *)object,
		(const Coord3D *)(object + 0x38), 1, __FILE__, __LINE__);
}

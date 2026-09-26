// cl: /DNDEBUG /MD /EHsc
//
// AIGiantBirdAttackState::onExit, retail RVA 0x002BEB50.  Vtable
// 0x010C78D8 slot 5 reaches this body through thunk 0x0003A201.  The
// constructor at 0x002BE400 installs that vtable and the update body at
// 0x002BEA50 reads the same current-weapon and firing-condition fields.

typedef int Int;
typedef unsigned int UnsignedInt;

enum StateExitType
{
	STATE_EXIT_UNKNOWN = 0
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class Weapon
{
public:
	void reloadAmmo(const Object *object);
};

class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void notifyModelConditionChanged();
};

class Pathfinder
{
public:
	void removeGoal(Object *object);
	void updateGoal(Object *object, const Coord3D *position,
		PathfindLayerEnum layer, const char *file, Int line);
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

class AIGiantBirdAttackState
{
public:
	virtual void onExit(StateExitType status);
};

// ?onExit@AIGiantBirdAttackState@@UAEXW4StateExitType@@@Z
void AIGiantBirdAttackState::onExit(StateExitType status)
{
	unsigned char *machine = *(unsigned char **)((unsigned char *)this + 0x1c);
	unsigned char *object = *(unsigned char **)(machine + 0x10);

	UnsignedInt flags = *(UnsignedInt *)(object + 0x120);
	if (flags & 0x20000)
	{
		flags &= 0xfffdffff;
		*(UnsignedInt *)(object + 0x120) = flags;
		((Object *)object)->notifyModelConditionChanged();
	}

	unsigned char *ai = *(unsigned char **)(object + 0x204);
	if (ai != 0)
		*(UnsignedInt *)(ai + 0x3f0) &= 0xffffffdf;

	Weapon *weapon = ((Object *)object)->getCurrentWeapon((WeaponSlotType *)0);
	if (weapon != 0)
		weapon->reloadAmmo((const Object *)object);

	TheAI->pathfinder()->removeGoal((Object *)object);
#line 1080 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
	TheAI->pathfinder()->updateGoal((Object *)object,
		(const Coord3D *)(object + 0x38), LAYER_GROUND, __FILE__, __LINE__);

	if (ai != 0)
		*(unsigned char *)(ai + 0x490) = 0;
}

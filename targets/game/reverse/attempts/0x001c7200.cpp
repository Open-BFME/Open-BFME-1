// ?rva001c7200@Object@@QAEXXZ
// partial score=0.69 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /MD /EHsc- /D_STLP_USE_STATIC_LIB
// stlport
// 
// Open-BFME: opaque Object body at retail 0x001C7200, 289 bytes.
// The matched 0x001CFF30 caller proves the Object receiver and no-argument ABI.
// GameLogicFindObjectByID.cpp proves the ObjectID hash_map at GameLogic+0xB0.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned char Bool;
typedef int ObjectID;

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

template <int N>
class Rva001C7200ObjectSlots : public Rva001C7200ObjectSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva001C7200ObjectSlots<0>
{
};

template <int N>
class Rva001C7200AISlots : public Rva001C7200AISlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class Rva001C7200AISlots<0>
{
};

class PhysicsBehavior
{
public:
	unsigned char m_unreconstructed_000[0x5c];
	unsigned char m_byte5C;
};

class AIUpdateInterface : public Rva001C7200AISlots<122>
{
public:
	virtual void setLocomotorGoalNone(void) = 0;
};

class Pathfinder
{
public:
	typedef int (Pathfinder::*CollectCall)(Object *, const Coord3D *, ObjectID *);
	void removeGoal(Object *object);
};

class BfmeIdlePathfinder : public Pathfinder
{
public:
	void updateGoal(Object *object, const Coord3D *position, int layer,
		const char *reason, int flags);
};

class AI
{
public:
	BfmeIdlePathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed_000[0x0c];
	BfmeIdlePathfinder *m_pathfinder;
};

#define TheAI (*(AI **)0x012EF214)

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>,
	_STL::equal_to<ObjectID> > ObjectPtrHash;

class Rva00367E30Logic
{
public:
	unsigned char m_unreconstructed_000[0xb0];
	ObjectPtrHash m_objHash;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

class Object : public Rva001C7200ObjectSlots<24>
{
public:
	virtual void slot24(void) = 0;

	void rva001c7200(void);

private:
	unsigned char m_unreconstructed_004[0x38 - 0x04];
	Coord3D m_position;
	unsigned char m_unreconstructed_044[0x90 - 0x44];
	unsigned int m_status;
	unsigned char m_unreconstructed_094[0x204 - 0x94];
	AIUpdateInterface *m_ai;
	PhysicsBehavior *m_physics;
	unsigned char m_unreconstructed_20c[0x314 - 0x20c];
	int m_layer;
	unsigned char m_unreconstructed_318[0x344 - 0x318];
	Bool m_privateStatus;
	unsigned char m_unreconstructed_345[0x3a8 - 0x345];
	Bool m_forceGroundLayer;
};

extern void j_00027ab6(void);

static __forceinline int rva001c7200Collect(Pathfinder *pathfinder, Object *object,
	const Coord3D *position, ObjectID *objects)
{
	union { void (*address)(void); Pathfinder::CollectCall member; } route;
	route.address = j_00027ab6;
	return (pathfinder->*route.member)(object, position, objects);
}

void Object::rva001c7200(void)
{
	register Object &self = *this;
	ObjectID objects[16];
	volatile int objectCount = rva001c7200Collect(TheAI->pathfinder(), &self,
		&self.m_position, objects);

	int layer = 1;
	if (!self.m_forceGroundLayer)
	{
		layer = self.m_layer;
		TheAI->pathfinder()->updateGoal(&self, &self.m_position, layer,
			(const char *)0x0109ec20, 0x6a4);
	}

	if (objectCount <= 0)
		goto afterObjects;

	Rva00367E30Logic *logic = TheBfmeGameLogic;
	for (register int i = 0; i < objectCount; ++i)
	{
		ObjectID key = objects[i];
		if (key == 0)
			continue;

		ObjectPtrHash::iterator node = logic->m_objHash.find(key);
		if (node == logic->m_objHash.end())
			continue;
		Object *candidate = (*node).second;
		if (candidate == 0 || (candidate->m_status & 0x10000000) != 0
			|| (candidate->m_privateStatus & 1) != 0)
			continue;
		PhysicsBehavior *physics = candidate->m_physics;
		if (physics != 0 && physics->m_byte5C == 0)
		{
			TheAI->pathfinder()->removeGoal(candidate);
			candidate->slot24();
			logic = TheBfmeGameLogic;
		}
	}

afterObjects:
	AIUpdateInterface *ai = self.m_ai;
	if (ai != 0)
		ai->setLocomotorGoalNone();
}

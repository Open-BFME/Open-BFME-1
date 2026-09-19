// ?rva001C7200@Object@@QAEXXZ
// partial score=0.17 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc-
// 
// Open-BFME: opaque Object body at retail 0x001C7200, 289 bytes.

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

class Rva001C7200Gate
{
public:
	unsigned char m_unreconstructed_000[0x5c];
	Bool m_reject;
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
	typedef void (Pathfinder::*UpdateGoalCall)(Object *, const Coord3D *, int,
		const char *, int);
};

class BfmeItemGK;

class BfmeAgentGK
{
public:
	typedef void (BfmeAgentGK::*NoteCall)(BfmeItemGK *);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed_000[0x0c];
	Pathfinder *m_pathfinder;
};

#define TheAI (*(AI **)0x012EF214)

struct Rva001C7200Node
{
	Rva001C7200Node *m_next;
	ObjectID m_id;
	Object *m_object;
};

class Rva00367E30Logic
{
public:
	Rva001C7200Node *findNodeByID(ObjectID id)
	{
		unsigned int bucketCount = (unsigned int)(m_bucketsEnd - m_buckets);
		Rva001C7200Node *node = m_buckets[(unsigned int)id % bucketCount];
		while (node != 0)
		{
			if (node->m_id == id)
				break;
			node = node->m_next;
		}
		if (node == 0)
			return 0;
		return node;
	}

	unsigned char m_unreconstructed_000[0xb4];
	Rva001C7200Node **m_buckets;
	Rva001C7200Node **m_bucketsEnd;
};

#define TheBfmeGameLogic (*(Rva00367E30Logic **)0x012F0898)

class Object : public Rva001C7200ObjectSlots<24>
{
public:
	virtual void rva001C7200Notify(void) = 0;

	void rva001C7200(void);

private:
	unsigned char m_unreconstructed_004[0x38 - 0x04];
	Coord3D m_position;
	unsigned char m_unreconstructed_044[0x90 - 0x44];
	unsigned int m_status;
	unsigned char m_unreconstructed_094[0x204 - 0x94];
	AIUpdateInterface *m_ai;
	Rva001C7200Gate *m_gate;
	unsigned char m_unreconstructed_20c[0x314 - 0x20c];
	int m_layer;
	unsigned char m_unreconstructed_318[0x344 - 0x318];
	Bool m_reject;
	unsigned char m_unreconstructed_345[0x3a8 - 0x345];
	Bool m_forcedGround;
};

extern void j_00015d02(void);
extern void j_00027ab6(void);
extern void j_000294e2(void);

static __forceinline int rva001C7200Collect(Pathfinder *pathfinder, Object *object,
	const Coord3D *position, ObjectID *objects)
{
	union { void (*address)(void); Pathfinder::CollectCall member; } route;
	route.address = j_00027ab6;
	return (pathfinder->*route.member)(object, position, objects);
}

static __forceinline void rva001C7200UpdateGoal(Pathfinder *pathfinder, Object *object,
	const Coord3D *position, int layer, const char *reason, int flags)
{
	union { void (*address)(void); Pathfinder::UpdateGoalCall member; } route;
	route.address = j_000294e2;
	(pathfinder->*route.member)(object, position, layer, reason, flags);
}

static __forceinline void rva001C7200Note(BfmeAgentGK *agent, BfmeItemGK *item)
{
	union { void (*address)(void); BfmeAgentGK::NoteCall member; } route;
	route.address = j_00015d02;
	(agent->*route.member)(item);
}

void Object::rva001C7200(void)
{
	register Object &self = *this;
	ObjectID objects[16];
	int objectCount = rva001C7200Collect(TheAI->pathfinder(), &self,
		&self.m_position, objects);

	int layer = 1;
	if (!self.m_forcedGround)
	{
		layer = self.m_layer;
		rva001C7200UpdateGoal(TheAI->pathfinder(), &self, &self.m_position, layer,
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

		Rva001C7200Node *node = logic->findNodeByID(key);
		if (node == 0)
			continue;
		Object *candidate = node->m_object;
		if (candidate == 0 || (candidate->m_status & 0x10000000) != 0
			|| (candidate->m_reject & 1) != 0)
			continue;
		Rva001C7200Gate *gate = candidate->m_gate;
		if (gate != 0 && gate->m_reject == 0)
		{
			rva001C7200Note(reinterpret_cast<BfmeAgentGK *>(TheAI->pathfinder()),
				reinterpret_cast<BfmeItemGK *>(candidate));
			candidate->rva001C7200Notify();
			logic = TheBfmeGameLogic;
		}
	}

afterObjects:
	AIUpdateInterface *ai = self.m_ai;
	if (ai != 0)
		ai->setLocomotorGoalNone();
}

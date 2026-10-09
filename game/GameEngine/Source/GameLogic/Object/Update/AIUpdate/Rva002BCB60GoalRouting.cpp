// cl: /DNDEBUG /MD
//
// Address-derived recovery for the Giant Bird goal-routing body at retail
// RVA 0x002BCB60.  The selector call is the adjacent 0x002BC9C0 body; the
// two goal sinks and the height adjustment call their retail ILT thunks
// (?j_*) directly through function-local member-pointer unions.

struct Coord3D
{
	float x;
	float y;
	float z;
};


class Rva002BCB60Thing
{
private:
	unsigned char m_unreconstructed000[0x40];

	public:
	float m_height40;
	unsigned char m_unreconstructed044[0x7c];
	float m_heightC0;
};

class Rva002BCB60QueryObject
{
	unsigned char m_unreconstructed000[0x24];
};

class Rva002BCB60AerialPathfinder
{
public:
};

class Rva002BCB60Owner
{
public:
	int choose(void *mode, int fullRange);
	void route(void *mode, Coord3D *position, int source);

private:
	unsigned char m_unreconstructed000[8];
	Rva002BCB60Thing *m_thing;
	unsigned char m_unreconstructed00c[0x1c0];
	void *m_heightData1cc;
	unsigned char m_unreconstructed1d0[0x230];
	Rva002BCB60QueryObject m_queryObject400;
	unsigned char m_continue424;
	unsigned char m_unreconstructed425[0x43];
	float m_height468;
	unsigned char m_unreconstructed46c[0x0c];
	float m_goalRange478;
	Coord3D m_goalPosition47c;
};

class Rva002BC260GoalOwner
{
};

// Retail ILT thunks the retail callers route through.
extern void j_0002fcd9();	// ?query@Rva002BCB60AerialPathfinder
extern void j_0003e13a();	// ?tryQuery@Rva002BCB60AerialPathfinder
extern void j_0004539f();	// ?checkHeight@Rva002BCB60Owner
extern void j_000281ff();	// ?setHeight@Rva002BCB60Thing
extern void j_0000795a();	// ?run@Rva002BC260GoalOwner

typedef bool (Rva002BCB60AerialPathfinder::*QueryFn)(Rva002BCB60Thing *thing,
	Rva002BCB60QueryObject *queryObject, float range, void *mode);
typedef bool (Rva002BCB60AerialPathfinder::*TryQueryFn)(Rva002BCB60QueryObject *queryObject,
	float range, Coord3D *result);
typedef unsigned char (Rva002BCB60Owner::*CheckHeightFn)();
typedef void (Rva002BCB60Thing::*SetHeightFn)(float height);
typedef void (Rva002BC260GoalOwner::*RunFn)(void *position, void *goalData,
	void *unused, void *source);

class AerialPathfinder;
extern AerialPathfinder *TheAerialPathfinder;
int g_012F02D4;
int g_012F02D8;

// ?choose@Rva002BCB60Owner@@QAEHPAXH@Z
int Rva002BCB60Owner::choose(void *mode, int fullRange)
{
	Rva002BCB60Thing *thing = m_thing;
	if (thing == 0 || m_heightData1cc == 0)
		return 0;
	if (m_continue424 == 0)
		return 2;

	if ((unsigned char)fullRange != 0)
	{
		union { void (*fn)(); QueryFn call; } query = { j_0002fcd9 };
		float range = thing->m_heightC0 + thing->m_heightC0 + m_height468;
		if (!(((Rva002BCB60AerialPathfinder *)TheAerialPathfinder)->*query.call)(thing,
			&m_queryObject400, range, mode))
			return 1;
	}
	else
	{
		union { void (*fn)(); QueryFn call; } query = { j_0002fcd9 };
		float twiceHeight = m_height468 + m_height468;
		if (!(((Rva002BCB60AerialPathfinder *)TheAerialPathfinder)->*query.call)(thing,
			&m_queryObject400,
			twiceHeight
				- thing->m_heightC0 * 0.5f, mode))
			return 1;
		if ((((Rva002BCB60AerialPathfinder *)TheAerialPathfinder)->*query.call)(thing,
			&m_queryObject400, twiceHeight, mode))
		{
			// Continue to the height check below.
		}
		else
		{
			return 1;
		}
	}

	{
		union { void (*fn)(); CheckHeightFn call; } checkHeight = { j_0004539f };
		if (!(this->*checkHeight.call)())
			return 0;
	}

	// Preserve the retail x87 load of the current height before the offset.
	Coord3D result;
	{
		union { void (*fn)(); TryQueryFn call; } tryQuery = { j_0003e13a };
		if (!(((Rva002BCB60AerialPathfinder *)TheAerialPathfinder)->*tryQuery.call)(
			&m_queryObject400, (volatile float &)m_height468 + 10.0f, &result))
			return 0;
	}
	if (result.z - 2.0f > thing->m_height40)
	{
		if (m_goalRange478 < thing->m_height40)
			return 2;
	}
	return 0;
}

// ?route@Rva002BCB60Owner@@QAEXPAXPAUCoord3D@@H@Z
void Rva002BCB60Owner::route(void *mode, Coord3D *position, int source)
{
	union { void (*fn)(); SetHeightFn call; } setHeight = { j_000281ff };
	union { void (*fn)(); RunFn call; } run = { j_0000795a };

	int state = choose(mode, 0);
	if (state == 0)
		return;

	Coord3D goal;
	if (position != 0)
		goal = *position;
	else
		goal = m_goalPosition47c;

	if (state == 1)
	{
		Rva002BCB60Thing *thing = m_thing;
		(thing->*setHeight.call)(thing->m_height40 + 5.0f);
		(((Rva002BC260GoalOwner *)this)->*run.call)(&goal,
			&g_012F02D8, 0, (void *)source);
	}
	else if (state == 2)
	{
		Rva002BCB60Thing *thing = m_thing;
		(thing->*setHeight.call)(thing->m_height40 - 1.0f);
		(((Rva002BC260GoalOwner *)this)->*run.call)(&goal,
			&g_012F02D4, 0, (void *)source);
	}
}

// Two more: a second ten word mask with the same intersection, and an axis
// classifier.

class BfmeBitsNB
{
public:
	void bfmeAndWith(const BfmeBitsNB *other);
private:
	unsigned int m_bfmeWords[10];
};

void BfmeBitsNB::bfmeAndWith(const BfmeBitsNB *other)
{
	m_bfmeWords[0] &= other->m_bfmeWords[0];
	m_bfmeWords[1] &= other->m_bfmeWords[1];
	m_bfmeWords[2] &= other->m_bfmeWords[2];
	m_bfmeWords[3] &= other->m_bfmeWords[3];
	m_bfmeWords[4] &= other->m_bfmeWords[4];
	m_bfmeWords[5] &= other->m_bfmeWords[5];
	m_bfmeWords[6] &= other->m_bfmeWords[6];
	m_bfmeWords[7] &= other->m_bfmeWords[7];
	m_bfmeWords[8] &= other->m_bfmeWords[8];
	m_bfmeWords[9] &= other->m_bfmeWords[9];
}

extern "C" double fabs(double value);
#pragma intrinsic(fabs)

class BfmePointNC
{
public:
	float m_bfmeX;								// +0x00
	float m_bfmeY;								// +0x04
};

// Which way the offset leans, and which side of nothing it sits on.
int bfmeAxisOf(const BfmePointNC *offset)
{
	if ((float)fabs(offset->m_bfmeX) > (float)fabs(offset->m_bfmeY))
	{
		if (offset->m_bfmeX > 0.0f)
			return 1;
		return 2;
	}

	if (offset->m_bfmeY > 0.0f)
		return 0;
	return 3;
}

typedef int Int;
typedef unsigned short UnsignedShort;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Data
	{
		Int m_refCount;
		UnsignedShort m_length;
		UnsignedShort m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void __cdecl format(AsciiString fmt, ...);
	const char *str() const { return m_data ? m_data->m_text : ""; }
};

class Waypoint;

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual Waypoint *getWaypointByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;

// The caller at retail 0x00360400 uses this member after the InitialWalkOn
// lookup fails. The two format strings and TerrainLogic slot 31 identify the
// axis-specific SpawnPoint and GatherPoint lookup.
class BfmeFirstWalkOnArmy
{
public:
	bool lookupWaypoints(const BfmePointNC *point, Waypoint **outSpawn, Waypoint **outGather);
	void armyNameFromIndex(unsigned int index, AsciiString *out);
	void moveObjects(class BfmeObjectList *objects, const BfmePointNC *point, bool initial);
};

bool BfmeFirstWalkOnArmy::lookupWaypoints(
	const BfmePointNC *point, Waypoint **outSpawn, Waypoint **outGather)
{
	int axis = bfmeAxisOf(point);
	AsciiString name;
	armyNameFromIndex(axis, &name);
	AsciiString spawnPoint;
	AsciiString gatherPoint;
	spawnPoint.format(AsciiString("%sSpawnPoint"), name.str());
	gatherPoint.format(AsciiString("%sGatherPoint"), name.str());
	*outSpawn = TheTerrainLogic->getWaypointByName(spawnPoint);
	*outGather = TheTerrainLogic->getWaypointByName(gatherPoint);
	if (*outSpawn != 0)
	{
		if (*outGather != 0)
			return true;
	}
	return false;
}

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Waypoint
{
private:
	unsigned char m_beforeLocation[12];
public:
	Coord3D m_location;
};

class Object {};
class AIGroup {};
class AI {};

namespace _STL
{
	template <bool threads, int instance>
	class __node_alloc
	{
	public:
		static void _M_deallocate(void *node, unsigned int bytes);
	};
}

struct BfmeObjectNode
{
	BfmeObjectNode *next;
	BfmeObjectNode *previous;
	Object *object;
};

class BfmeObjectList
{
public:
	BfmeObjectNode *sentinel;

	void clear()
	{
		BfmeObjectNode *current = sentinel->next;
		while (current != sentinel)
		{
			BfmeObjectNode *old = current;
			current = current->next;
			_STL::__node_alloc<true, 0>::_M_deallocate(old, sizeof(BfmeObjectNode));
		}
		sentinel->next = sentinel;
		sentinel->previous = sentinel;
	}
};

extern AI *TheAI;
extern void j_00011833();
extern void j_00030cb0();
extern void j_0003b570();
extern void j_0002b7e2();
extern void j_0002059a();
extern void j_00003918();
extern void j_00015f69();

typedef bool (BfmeFirstWalkOnArmy::*LookupInitialWaypointsCall)(Waypoint **, Waypoint **);
typedef bool (BfmeFirstWalkOnArmy::*LookupWaypointsCall)(const BfmePointNC *, Waypoint **, Waypoint **);
typedef AIGroup *(AI::*CreateGroupCall)();
typedef void (AIGroup::*AddObjectCall)(Object *);
typedef void (AIGroup::*PrepareWalkOnCall)(const Coord3D *, const Coord3D *, int);
typedef void (AIGroup::*MoveWalkOnCall)(const Coord3D *, int, int, int);
typedef void (AI::*DestroyGroupCall)(AIGroup *);

void BfmeFirstWalkOnArmy::moveObjects(
	BfmeObjectList *objects, const BfmePointNC *point, bool initial)
{
	Waypoint *spawn;
	Waypoint *gather;
	union { void *raw; LookupInitialWaypointsCall call; } initialLookup;
	initialLookup.raw = (void *)j_00011833;
	union { void *raw; LookupWaypointsCall call; } axisLookup;
	axisLookup.raw = (void *)j_00030cb0;
	if ((!initial || !(this->*initialLookup.call)(&spawn, &gather)) &&
		!(this->*axisLookup.call)(point, &spawn, &gather))
	{
		return;
	}

	union { void *raw; CreateGroupCall call; } create;
	create.raw = (void *)j_0003b570;
	AIGroup *group = (TheAI->*create.call)();
	if (group == 0)
		return;

	union { void *raw; AddObjectCall call; } add;
	add.raw = (void *)j_0002b7e2;
	for (BfmeObjectNode *it = objects->sentinel->next; it != objects->sentinel; it = it->next)
	{
		if (it->object != 0)
			(group->*add.call)(it->object);
	}

	union { void *raw; PrepareWalkOnCall call; } prepare;
	prepare.raw = (void *)j_0002059a;
	const Coord3D *gatherLocation = &gather->m_location;
	(group->*prepare.call)(&spawn->m_location, gatherLocation, 2);
	union { void *raw; MoveWalkOnCall call; } move;
	move.raw = (void *)j_00003918;
	(group->*move.call)(gatherLocation, 2, 0, 1);
	objects->clear();
	union { void *raw; DestroyGroupCall call; } destroy;
	destroy.raw = (void *)j_00015f69;
	(TheAI->*destroy.call)(group);
}

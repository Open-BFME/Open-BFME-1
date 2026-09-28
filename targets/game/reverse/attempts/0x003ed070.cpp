// ?validMovement@BfmeAttackQuery@@QAE_NHHGPBX@Z
// partial score=0.8 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// opus-5.5 2026-09-28: 1671B vs retail 1708, shape 0.966 with 17 structural
// differences (the 0.72 body was 1434B, shape 0.705, 54 structural). Fixes
// with retail evidence: both early exits return FALSE (they jump to the
// xor al,al epilogue at +0x693); profile byte +4 is template-flag==0 and +5
// is bfmeIsComputerControlled, all four profile stores follow that call;
// getTemplate is re-read for 0x444 and 0x4cc; the zone step is equal_range
// with the iterator advanced before the links are walked; getLink(i) is
// bounds-checked (0..7) inside i < getNumLinks(); the linked waypoint is
// looked up with find() and the zone is visited only if the set does not
// contain it (find, then insert, then push_back); _STLP_NO_EXCEPTIONS gives
// retail's 0x88 aligned frame. Still wrong: container slots. Retail puts
// set 0x38, maps 0x44/0x50, profile 0x5c, deque 0x68 (esp after the three
// pushes); ours puts deque 0x14, set 0x3c, maps 0x4c/0x58, profile 0x7c, so
// constant 0 takes edi early and acceptableSurfaces spills. Block-scoping the
// deque/set and moving the profile after the maps did not move them.
//
// Retail 0x003ED070.  The body is the zone-graph transition test reached by
// BfmeAttackQuery::checkCandidate through ILT 0x0002F798.  The waypoint
// fields at +0x48, +0x60, +0x20 and +0x4c are kept address-derived here: the
// retail bytes prove their offsets and use, but not a semantic field name.

#define _STLP_NO_EXCEPTIONS 1
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <deque>
#include <map>
#include <set>

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool terrainOnly;
	Bool crusher;
	unsigned char padding[2];
	Int layer;
};

class PathfindCell
{
public:
	void *m_info;
	Int m_field04;
	unsigned short m_zone;
	unsigned short m_pad0a;
	unsigned char m_pad0c[4];
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;
};

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *position, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class Rva001BF140ByteField
{
public:
	unsigned char get() const;
};

class Object
{
public:
	Bool bfmeIsComputerControlled() const;
};

class Waypoint
{
public:
	Bool gate(Object *object);

	Coord3D *getLocation() const
	{
		return (Coord3D *)((const unsigned char *)this + 0x0c);
	}

	Waypoint *getNext() const
	{
		return *(Waypoint **)((const unsigned char *)this + 0x1c);
	}

	Int getNumLinks() const
	{
		return *(const Int *)((const unsigned char *)this + 0x4c);
	}

	Waypoint *getLink(Int index) const
	{
		if (index >= 0 && index < 8)
			return *(Waypoint **)((const unsigned char *)this + 0x20 + index * 4);
		return 0;
	}
};

class TerrainLogic
{
public:
	virtual void _slot00() = 0;
	virtual void _slot04() = 0;
	virtual void _slot08() = 0;
	virtual void _slot0c() = 0;
	virtual void _slot10() = 0;
	virtual void _slot14() = 0;
	virtual void _slot18() = 0;
	virtual void _slot1c() = 0;
	virtual void _slot20() = 0;
	virtual void _slot24() = 0;
	virtual void _slot28() = 0;
	virtual void _slot2c() = 0;
	virtual void _slot30() = 0;
	virtual void _slot34() = 0;
	virtual void _slot38() = 0;
	virtual void _slot3c() = 0;
	virtual void _slot40() = 0;
	virtual void _slot44() = 0;
	virtual void _slot48() = 0;
	virtual void _slot4c() = 0;
	virtual void _slot50() = 0;
	virtual void _slot54() = 0;
	virtual void _slot58() = 0;
	virtual void _slot5c() = 0;
	virtual void _slot60() = 0;
	virtual void _slot64() = 0;
	virtual void _slot68() = 0;
	virtual void _slot6c() = 0;
	virtual void _slot70() = 0;
	virtual void _slot74() = 0;
	virtual Waypoint *getFirstWaypoint() = 0;
	virtual void _slot7c() = 0;
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

extern void j_000022bb();
extern void j_00042a37();
extern void j_0003aba7();
extern void j_00010ea1();
extern void j_000171e8();
extern void j_00020671();
extern void j_0001c675();
extern void j_0004375c();

static unsigned char forceGround(Object *object)
{
	union
	{
		void (*raw)(void);
		unsigned char (Rva001BF140ByteField::*member)() const;
	} call;
	call.raw = j_00042a37;
	return (((Rva001BF140ByteField *)object)->*call.member)();
}

static const Overridable *getFinalOverride(const Overridable *object)
{
	union
	{
		void (*raw)(void);
		const Overridable *(Overridable::*member)() const;
	} call;
	call.raw = j_000022bb;
	return (object->*call.member)();
}

static Bool isComputerControlled(const Object *object)
{
	union
	{
		void (*raw)(void);
		Bool (Object::*member)() const;
	} call;
	call.raw = j_00010ea1;
	return (object->*call.member)();
}

static PathfindLayerEnum layerForDestination(TerrainLogic *terrain,
	Object *object, const Coord3D *position)
{
	union
	{
		void (*raw)(void);
		PathfindLayerEnum (TerrainLogic::*member)(Object *, const Coord3D *);
	} call;
	call.raw = j_0001c675;
	return (terrain->*call.member)(object, position);
}

static Bool worldToCell(Pathfinder *pathfinder, const Coord3D *position,
	ICoord2D *cell)
{
	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*member)(const Coord3D *, ICoord2D *);
	} call;
	call.raw = j_000171e8;
	return (pathfinder->*call.member)(position, cell);
}

static PathfindCell *getCell(Pathfinder *pathfinder, PathfindLayerEnum layer,
	Int x, Int y)
{
	union
	{
		void (*raw)(void);
		PathfindCell *(Pathfinder::*member)(PathfindLayerEnum, Int, Int);
	} call;
	call.raw = j_00020671;
	return (pathfinder->*call.member)(layer, x, y);
}

static zoneStorageType effectiveZone(const PathfindZoneManager *manager,
	const PathfindMovementProfile &profile, zoneStorageType zone)
{
	union
	{
		void (*raw)(void);
		zoneStorageType (PathfindZoneManager::*member)(
			const PathfindMovementProfile &, zoneStorageType) const;
	} call;
	call.raw = j_0004375c;
	return (manager->*call.member)(profile, zone);
}

typedef Bool (Waypoint::*WaypointGateCall)(Object *);

static Bool waypointGate(Waypoint *waypoint, Object *object)
{
	union
	{
		void (*raw)(void);
		WaypointGateCall member;
	} call;
	call.raw = j_0003aba7;
	return (waypoint->*call.member)(object);
}

class BfmeAttackQuery
{
public:
	Bool validMovement(Int layer, Int fromZone, zoneStorageType toZone,
		const void *extra);

private:
	unsigned char m_prefix[0xc9c];
	PathfindZoneManager m_zoneManager;
};

static unsigned char readByte(const void *object, unsigned int offset)
{
	return *((const unsigned char *)object + offset);
}

static Int readInt(const void *object, unsigned int offset)
{
	return *((const Int *)((const unsigned char *)object + offset));
}

static const unsigned char *finalTemplate(const unsigned char *thingTemplate)
{
	if (thingTemplate != 0)
	{
		const Overridable *next = *(const Overridable **)(thingTemplate + 4);
		if (next != 0)
			return (const unsigned char *)getFinalOverride(next);
	}
	return thingTemplate;
}

typedef _STL::multimap<Int, Waypoint *> RvaWaypointByZone;
typedef _STL::map<Waypoint *, Int> RvaWaypointToZone;

Bool BfmeAttackQuery::validMovement(Int layer, Int fromZone,
	zoneStorageType toZone, const void *extra)
{
	BfmeAttackQuery *query = this;
	Object *object = (Object *)layer;

	if (forceGround(object))
		return false;

	const unsigned char *ai = *(const unsigned char **)((const unsigned char *)object + 0x204);
	if (ai == 0 && extra == 0)
		return false;

	Int acceptableSurfaces;
	if (extra != 0)
		acceptableSurfaces = readInt(extra, 0x10);
	else
		acceptableSurfaces = readInt(ai, 0x1b8);

	Int effectiveLayer = readInt(finalTemplate(
		*(const unsigned char **)((const unsigned char *)object + 4)), 0x444) - 1;
	unsigned char templateFlag = readByte(finalTemplate(
		*(const unsigned char **)((const unsigned char *)object + 4)), 0x4cc);
	Bool computerControlled = isComputerControlled(object);
	PathfindMovementProfile profile;
	profile.acceptableSurfaces = acceptableSurfaces;
	profile.terrainOnly = templateFlag == 0;
	profile.crusher = computerControlled;
	profile.layer = effectiveLayer;

	RvaWaypointByZone zoneToWaypoint;
	RvaWaypointToZone waypointToZone;

	for (Waypoint *waypoint = TheTerrainLogic->getFirstWaypoint();
		waypoint != 0; waypoint = waypoint->getNext())
	{
		unsigned char active = readByte(waypoint, 0x48);
		if (active != 0)
		{
			Int kind = readInt(waypoint, 0x60);
			if (kind == 1 || kind == 2 || kind == 3 || kind == 4)
			{
				if (waypointGate(waypoint, object))
				{
					PathfindLayerEnum destinationLayer = layerForDestination(
						TheTerrainLogic, 0, waypoint->getLocation());
					ICoord2D cell;
					if (!worldToCell((Pathfinder *)query,
						waypoint->getLocation(), &cell))
					{
						PathfindCell *pathCell = getCell((Pathfinder *)query,
							destinationLayer, cell.x, cell.y);
						if (pathCell != 0)
						{
							zoneStorageType zone = effectiveZone(&query->m_zoneManager,
								profile, pathCell->m_zone);
							zoneToWaypoint.insert(
								RvaWaypointByZone::value_type((Int)zone, waypoint));
							waypointToZone[waypoint] = (Int)zone;
						}
					}
				}
			}
		}
	}

	_STL::deque<Int> pending;
	_STL::set<Int> visited;
	pending.push_back(fromZone);
	visited.insert(fromZone);

	while (!pending.empty())
	{
		Int currentZone = pending.front();
		pending.pop_front();
		if (currentZone == (Int)toZone)
			return true;

		_STL::pair<RvaWaypointByZone::iterator, RvaWaypointByZone::iterator> range =
			zoneToWaypoint.equal_range(currentZone);
		RvaWaypointByZone::iterator it = range.first;
		while (it != range.second)
		{
			Waypoint *waypoint = it->second;
			++it;
			for (Int index = 0; index < waypoint->getNumLinks(); ++index)
			{
				Waypoint *linked = waypoint->getLink(index);
				RvaWaypointToZone::iterator found = waypointToZone.find(linked);
				if (found == waypointToZone.end())
					continue;
				Int linkedZone = found->second;
				if (visited.find(linkedZone) != visited.end())
					continue;
				visited.insert(linkedZone);
				pending.push_back(linkedZone);
			}
		}
	}

	return false;
}

// ?d_003df580@@YAXXZ
// partial score=0.3 date=2026-09-17
// cl: /DNDEBUG /MD
//
// Retail 0x003DF580: the BFME-extended Pathfinder destination predicate.
// The string at 0x010EEA60 names CheckDestination and the 0x003E6E90
// Pathfinder wrapper supplies the eight-argument ABI.  The class and method
// keep the address token because the added BFME arguments do not yet prove a
// canonical public signature.

typedef int Int;
typedef unsigned int ObjectID;
typedef unsigned char Bool;
typedef unsigned char UByte;

enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct Rva003DF580ThingTemplate
{
	void *m_vtable;
	Rva003DF580ThingTemplate *m_next;
	unsigned char m_pad08[0x18];
	char *m_nameData;
	unsigned char m_pad24[0xa4];
	unsigned int m_flagsC8;
	unsigned int m_padCC;
	unsigned int m_flagsD0;
	unsigned int m_flagsD4;
};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;

	void *m_vtable;
	Rva003DF580ThingTemplate *m_template;
	unsigned char m_pad08[0x6c];
	ObjectID m_id;
	unsigned char m_pad78[0x18c];
	void *m_ai;
};

struct Rva003DF580CellInfo
{
	unsigned char m_pad00[0x14];
	ObjectID m_goalUnit;
	unsigned char m_pad18[4];
	ObjectID m_goalAircraft;
	ObjectID m_obstacle;
};

struct Rva003DF580PathfindCell
{
	Rva003DF580CellInfo *m_info;
	Int m_field04;
	Int m_field08;
	unsigned int m_packed;
};

struct Rva003DF580PathfindLayer
{
	unsigned char m_body[0x44];
};

class Rva003DF580OverrideCall
{
};

class Rva003DF580LayerCall
{
};

class Rva003DF580AICall
{
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID);
};

extern GameLogic *TheGameLogic;

class Rva003DF580ObjectCall
{
};

extern void j_000022bb();
extern void j_000105cd();
extern void j_00010ea1();
extern void j_0001a36b();
extern void j_00024c99();
extern void j_0003251f();
extern void j_0003a17a();
extern void j_000420aa();

static __forceinline Rva003DF580ThingTemplate *rva003df580Final(
	Rva003DF580ThingTemplate *value)
{
	typedef Rva003DF580ThingTemplate *
		(Rva003DF580OverrideCall::*Function)();
	union { void (*raw)(); Function member; } call;
	call.raw = j_000022bb;
	return (reinterpret_cast<Rva003DF580OverrideCall *>(value)->*call.member)();
}

static __forceinline Rva003DF580PathfindCell *rva003df580LayerCell(
	Rva003DF580PathfindLayer *layer, Int x, Int y)
{
	typedef Rva003DF580PathfindCell *
		(Rva003DF580LayerCall::*Function)(Int, Int);
	union { void (*raw)(); Function member; } call;
	call.raw = j_000105cd;
	return (reinterpret_cast<Rva003DF580LayerCall *>(layer)->*call.member)(x, y);
}

static __forceinline Bool rva003df580IsComputerControlled(Object *object)
{
	typedef Bool (Rva003DF580ObjectCall::*Function)() const;
	union { void (*raw)(); Function member; } call;
	call.raw = j_00010ea1;
	return (reinterpret_cast<Rva003DF580ObjectCall *>(object)->*call.member)();
}

static __forceinline Int rva003df580IgnoredObstacle(void *ai)
{
	typedef Int (Rva003DF580AICall::*Function)();
	union { void (*raw)(); Function member; } call;
	call.raw = j_0001a36b;
	return (reinterpret_cast<Rva003DF580AICall *>(ai)->*call.member)();
}

static __forceinline Bool rva003df580AircraftDestination(void *ai)
{
	typedef Bool (Rva003DF580AICall::*Function)();
	union { void (*raw)(); Function member; } call;
	call.raw = j_00024c99;
	return (reinterpret_cast<Rva003DF580AICall *>(ai)->*call.member)();
}

static __forceinline Bool rva003df580CanCrush(Object *object, Object *other)
{
	typedef Bool (Rva003DF580ObjectCall::*Function)(Object *, Int) const;
	union { void (*raw)(); Function member; } call;
	call.raw = j_000420aa;
	return (reinterpret_cast<Rva003DF580ObjectCall *>(object)->*call.member)(other, 2);
}

static __forceinline Bool rva003df580KindOf(Object *object, Int kind)
{
	typedef Bool (Rva003DF580ObjectCall::*Function)(Int) const;
	union { void (*raw)(); Function member; } call;
	call.raw = j_0003251f;
	return (reinterpret_cast<Rva003DF580ObjectCall *>(object)->*call.member)(kind);
}

typedef void (__cdecl *Rva003DF580Log)(void *, const char *, ...);

class Rva003DF580TerrainLogic
{
};

static __forceinline float rva003df580TerrainFloat(
	Rva003DF580TerrainLogic *terrain, float x, float y)
{
	typedef float (Rva003DF580TerrainLogic::*Function)(float, float);
	union { void (*raw)(); Function member; } call;
	call.raw = (void (*)())(*(void ***)terrain)[7];
	return (terrain->*call.member)(x, y);
}

static __forceinline Bool rva003df580TerrainCheck(
	Rva003DF580TerrainLogic *terrain, void *value)
{
	typedef Bool (Rva003DF580TerrainLogic::*Function)(void *);
	union { void (*raw)(); Function member; } call;
	call.raw = (void (*)())(*(void ***)terrain)[47];
	return (terrain->*call.member)(value);
}

class Pathfinder
{
public:
	Bool bfmeInnerE6E90(void *, void *, void *, void *, void *, void *,
		void **, Int);

	unsigned char m_head[0x10];
	Rva003DF580PathfindCell **m_map;
	IRegion2D m_extent;
	IRegion2D m_logicalExtent;
	unsigned char m_opaque[0x85c - 0x34];
	Rva003DF580PathfindLayer m_layers[16];
};

Bool Pathfinder::bfmeInnerE6E90(void *a1, void *a2, void *a3,
	void *a4, void *a5, void *a6, void **a7, Int a8)
{
	Object *object = (Object *)a1;
	Int cellX = (Int)a2;
	Int cellY = (Int)a3;
	Int layer = (Int)a4;
	Int radius = (Int)a5;
	Int centerInCell = (Int)a6;
	Rva003DF580ThingTemplate *thing = object->m_template;
	Rva003DF580ThingTemplate *finalThing;
	ObjectID objectID;
	const char *name;
	void *crc;

	if (*(UByte *)0x012F0239 != 0 &&
		(crc = *(void **)0x012ED4FC) != 0)
	{
		Rva003DF580Log log = (Rva003DF580Log)j_0003a17a;
		const char *label = centerInCell != 0 ? (const char *)0x0107FA58 :
			(const char *)0x01080180;
		objectID = object->m_id;
		finalThing = thing;
		if (finalThing != 0 && finalThing->m_next != 0)
			finalThing = rva003df580Final(finalThing->m_next);
		if (finalThing != 0 && finalThing->m_nameData != 0)
			name = finalThing->m_nameData + 8;
		else
			name = (const char *)0x0107388B;
		log(crc, (const char *)0x010EEA60, name, objectID, cellX, cellY,
			layer, radius, label);
	}

	Bool allowGoal = 0;
	Bool allowMoving = 0;
	Rva003DF580ThingTemplate *currentThing = object->m_template;
	if (currentThing != 0 && currentThing->m_next != 0)
		currentThing = rva003df580Final(currentThing->m_next);

	if (currentThing != 0 && (currentThing->m_flagsD4 & 0x01000000) != 0)
	{
		if (*(UByte *)0x012F0239 != 0 &&
			(crc = *(void **)0x012ED4FC) != 0)
			((Rva003DF580Log)j_0003a17a)(crc, (const char *)0x010EEA48);

		if (layer == 1 && centerInCell == 0)
		{
			Rva003DF580TerrainLogic *terrain =
				*(Rva003DF580TerrainLogic **)0x012EF4CC;
			float x = (float)cellX;
			float y = (float)centerInCell;
			x += *(const float *)0x0107533C;
			x *= *(const float *)0x01075C74;
			y += *(const float *)0x0107533C;
			y *= *(const float *)0x01075C74;
			if (rva003df580TerrainFloat(terrain, x, y) != 0.0f)
			{
				unsigned char terrainProbe[8];
				if (rva003df580TerrainCheck(terrain, terrainProbe) != 0)
				{
					if (*(UByte *)0x012F0239 != 0 &&
						(crc = *(void **)0x012ED4FC) != 0)
						((Rva003DF580Log)j_0003a17a)(crc,
							(const char *)0x010EE9FC);
					radius = 1;
					centerInCell = 1;
					allowGoal = 1;
				}
				else
					return 0;
			}
		}
		else
		{
			if (*(UByte *)0x012F0239 != 0 &&
				(crc = *(void **)0x012ED4FC) != 0)
				((Rva003DF580Log)j_0003a17a)(crc,
					(const char *)0x010EE9C8, layer);
			radius = 1;
			centerInCell = 1;
			allowGoal = 1;
		}
	}

	currentThing = object->m_template;
	if (currentThing != 0 && currentThing->m_next != 0)
		currentThing = rva003df580Final(currentThing->m_next);
	if (currentThing != 0 &&
		(currentThing->m_flagsD4 & 0x10000000) != 0)
	{
		if (*(UByte *)0x012F0239 != 0 &&
			(crc = *(void **)0x012ED4FC) != 0)
			((Rva003DF580Log)j_0003a17a)(crc,
				(const char *)0x010EE990);
		allowMoving = 1;
	}

	currentThing = object->m_template;
	if (currentThing != 0 && currentThing->m_next != 0)
		currentThing = rva003df580Final(currentThing->m_next);
	if (currentThing != 0 && (currentThing->m_flagsC8 & 0x00000100) != 0 &&
		layer != 1)
	{
		radius = 1;
		centerInCell = 0;
	}

	Int numCellsAbove = radius;
	if (centerInCell != 0)
		numCellsAbove++;

	Bool checkForAircraft = 0;
	ObjectID ignoreID = 0;
	objectID = 0;
	if (object->m_ai != 0)
	{
		ignoreID = (ObjectID)rva003df580IgnoredObstacle(object->m_ai);
		checkForAircraft = rva003df580AircraftDestination(object->m_ai);
		objectID = object->m_id;
	}
	*a7 = 0;

	if (objectID != 0 && object->m_ai != 0 &&
		*(UByte *)0x012F0239 != 0 &&
		(crc = *(void **)0x012ED4FC) != 0)
	{
		((Rva003DF580Log)j_0003a17a)(crc, (const char *)0x010EE8D0,
			cellX - radius, cellX + numCellsAbove,
			cellY - radius, cellY + numCellsAbove);
	}

	Int i = cellX - radius;
	Int iEnd = cellX + numCellsAbove;
	Int jStart = cellY - radius;
	Int jEnd = cellY + numCellsAbove;
	for (; i < iEnd; ++i)
	{
		if (i < m_logicalExtent.lo.x || i > m_logicalExtent.hi.x ||
			jStart < m_logicalExtent.lo.y || jStart > m_logicalExtent.hi.y ||
			jEnd > m_logicalExtent.hi.y)
		{
		if (*(UByte *)0x012F0239 != 0 &&
				(crc = *(void **)0x012ED4FC) != 0)
				((Rva003DF580Log)j_0003a17a)(crc,
					(const char *)0x010EE94C);
			return 0;
		}

		Rva003DF580PathfindCell *cell = 0;
		for (Int j = jStart; j < jEnd; ++j)
		{
			if (i < m_extent.lo.x || i > m_extent.hi.x ||
				j < m_extent.lo.y || j > m_extent.hi.y)
			{
			if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE7D0, i, j);
				return 0;
			}

			if (layer > 1 && layer <= 15)
			{
				cell = rva003df580LayerCell(
					&m_layers[layer], i, j);
				if (cell == 0)
					cell = m_map[i] + j;
			}
			else
				cell = m_map[i] + j;
			if (cell == 0)
			{
				if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE788, i, j);
				return 0;
			}

			if (checkForAircraft)
			{
				if (((cell->m_packed >> 19) & 1) == 0)
					continue;
				Rva003DF580CellInfo *info = cell->m_info;
				ObjectID aircraft = info != 0 ? info->m_goalAircraft : 0;
				if (aircraft == objectID)
					continue;
				if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE884, i, j);
				return 0;
			}

			unsigned int packed = cell->m_packed;
			Int type = (Int)(packed & 7);
			if (type == 5)
				return 0;
			if (((packed >> 21) & 1) != 0 &&
				rva003df580IsComputerControlled(object) != 0)
				return 0;
			if (type == 2)
				return 0;
			if (type == 4)
			{
				Rva003DF580CellInfo *info = cell->m_info;
				if (info != 0 && info->m_obstacle == ignoreID)
					continue;
				if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE83C, i, j);
				return 0;
			}
			if ((packed & 0x38) == 0)
				continue;

			Rva003DF580CellInfo *info = cell->m_info;
			ObjectID goal = info != 0 ? info->m_goalUnit : 0;
			if (goal == objectID || goal == ignoreID || goal == 0)
				continue;
			if (a8 != 0)
				continue;
			Object *unit = TheGameLogic->findObjectByID(goal);
			if (unit == 0)
				continue;
			if (object->getRelationship(unit) == ALLIES)
			{
				if (allowGoal == 0)
				{
					if (*(UByte *)0x012F0239 != 0 &&
						(crc = *(void **)0x012ED4FC) != 0)
						((Rva003DF580Log)j_0003a17a)(crc,
							(const char *)0x010EE6F0, i, j);
					return 0;
				}
				++*(Int *)a7;
				continue;
			}
			if ((packed & 0x38) != 0x18)
				continue;
			if (rva003df580CanCrush(object, unit) != 0)
				continue;
			if (allowMoving == 0)
			{
				if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE6A8, i, j);
				return 0;
			}
			if (rva003df580KindOf(unit, 8) == 0)
			{
				if (*(UByte *)0x012F0239 != 0 &&
					(crc = *(void **)0x012ED4FC) != 0)
					((Rva003DF580Log)j_0003a17a)(crc,
						(const char *)0x010EE658, i, j);
				return 0;
			}
		}
		jStart++;
	}
	return 1;
}

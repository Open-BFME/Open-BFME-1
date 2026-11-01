// ?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// partial score=0.9807 date=2026-11-01
// ?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// Open-BFME reconstruction of the BFME Pathfinder ground-path builder.
// The surrounding layout follows the GPLv3 GeneralsMD reference tree; the
// retail-specific path smoothing is reconstructed from the BFME body at RVA
// 0x003E6B80 and its matched Pathfinder::findGroundPath caller.
//
// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// 2026-10-17 (claude-opus-5-5): snapLine and worldToCell visible as
// never-inlined bodies (retail's pathfinder TU defines them beside this one)
// let VC7.1 prove adjustedPosition does not escape: 96 -> 16 differing bytes.
// Left: the order of the two squares under sqrt (+0xEC, retail squares dirX
// first), the cross-product fxch (+0x133) and offset.x + adjusted.x load order
// (+0x1E5); declaration order, operand order, dir struct, sqrt casts and the
// Coord3D copy constructor do not move them.

#include <math.h>

typedef int Int;
typedef float Real;

extern const Real BfmeZeroRange;
extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

class Pathfinder;

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

extern "C" __declspec(dllimport) double __cdecl floor( double );

__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

struct Rva003D61C0Vec
{
	Int a, b, c;
};

struct Rva003DE480Struct;

class AI
{
public:
	Pathfinder *pathfinder(void) const { return m_pathfinder; }

private:
	char m_beforePathfinder[0x14];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
	void scale(Real s) { x *= s; y *= s; z *= s; }
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
};

class PathNode
{
public:
	PathNode *getNextOptimized(void) const { return m_nextOptimized; }
	const Coord3D *getPosition(void) const { return &m_position; }
	Coord3D *getPosition(void) { return &m_position; }

private:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
};

class PathfindCell;

class Path
{
public:
	Path();
	void optimizeGroundPath(Int pathDiameter);
	PathNode *getFirstNode(void) const { return m_path; }

protected:
	~Path(void);

private:
	char m_prefix[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	char m_state[0x18];
};

struct Coord3DPlain
{
	float x, y, z;
};

class Rva003D61C0
{
public:
	Rva003D61C0 &set(Int a, Int b, const Rva003D61C0Vec *p);

	Int m_00;
	Int m_04;
	Coord3DPlain m_pos;
};

class Pathfinder
{
public:
	__declspec(noinline) bool worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex);
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003DE480Struct *userData);
protected:
	Path *buildGroundPath(const Coord3D *fromPos, PathfindCell *goalCell,
		bool center, Int pathDiameter);

public:
	void prependCells(Path *path, const Coord3D *fromPos,
		PathfindCell *goalCell, bool center);
	__declspec(noinline) void snapLine(const Coord3D *sourcePosition, Coord3D *destinationPosition);

	char m_before14[0x14];
	IRegion2D m_extent;
	char m_beforeFieldA0[0xa0 - 0x24];
	Real m_fieldA0;
};

inline bool Pathfinder::worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex)
{
	cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/10);
	cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/10);
	bool overflow = false;
	if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
	if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
	if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
	if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
	return overflow;
}

inline void Pathfinder::snapLine(const Coord3D *sourcePosition, Coord3D *destinationPosition)
{
	Rva003D61C0 info;
	info.set((Int)this, 4, (const Rva003D61C0Vec *)sourcePosition);
	ICoord2D start;
	worldToCell(sourcePosition, &start);
	ICoord2D end;
	worldToCell(destinationPosition, &end);
	if (iterateCellsAlongLine(start, end, LAYER_GROUND, (Rva003DE480Struct *)&info)) {
		destinationPosition->x = info.m_pos.x;
		destinationPosition->y = info.m_pos.y;
		destinationPosition->z = info.m_pos.z;
	}
}

// ?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
Path *Pathfinder::buildGroundPath(const Coord3D *fromPos,
	PathfindCell *goalCell, bool center, Int pathDiameter)
{
	Path *path = new Path;
	prependCells(path, fromPos, goalCell, center);
	path->optimizeGroundPath(pathDiameter);

	PathNode *node = path->getFirstNode();
	bool havePrevious = false;
	Coord3D previousPosition;
	while (node != 0)
	{
		if (node->getNextOptimized() == 0)
			break;

		Coord3D originalPosition;
		originalPosition.x = node->getPosition()->x;
		Coord3D *currentPosition = node->getPosition();
		originalPosition.y = currentPosition->y;
		originalPosition.z = currentPosition->z;
		if (havePrevious)
		{
			const Coord3D *nextPosition = node->getNextOptimized()->getPosition();
			Coord3D prevDir;
			Coord3D nextDir;
			prevDir.set(currentPosition);
			prevDir.sub(&previousPosition);
			nextDir.set(nextPosition);
			nextDir.sub(currentPosition);
			Real dirX = prevDir.x + nextDir.x;
			Real dirY = nextDir.y + prevDir.y;
			Real lenSq = dirX * dirX;
			lenSq += dirY * dirY;
			Real scale = g_bfmeDefaultBU / sqrt(lenSq);
			Coord3D offset;
			offset.x = scale * dirX;
			offset.y = scale * dirY;
			Real width = TheAI->pathfinder()->m_fieldA0;
			width += width;
			offset.x *= width;
			offset.y *= width;

			Coord3D adjustedPosition;
			adjustedPosition.set(currentPosition);
			if (prevDir.x * nextDir.y - nextDir.x * prevDir.y < BfmeZeroRange)
			{
				adjustedPosition.x -= offset.y;
				adjustedPosition.y += offset.x;
			}
			else
			{
				adjustedPosition.x += offset.y;
				adjustedPosition.y -= offset.x;
			}

			snapLine(currentPosition, &adjustedPosition);

			offset = adjustedPosition;
			offset.sub(currentPosition);
			offset.x *= g_bfmeK1253;
			offset.y *= g_bfmeK1253;
			offset.z *= g_bfmeK1253;
			adjustedPosition = *currentPosition;
			adjustedPosition.add(&offset);
			*currentPosition = adjustedPosition;
		}

		havePrevious = true;
		previousPosition = originalPosition;
		node = node->getNextOptimized();
	}

	return path;
}

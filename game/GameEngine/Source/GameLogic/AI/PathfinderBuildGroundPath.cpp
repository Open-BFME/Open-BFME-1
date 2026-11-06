// ?rva003E6B80@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath
//
// Pathfinder::rva003E6B80 (retail 0x003E6B80, 623 bytes; Zero Hour's
// buildGroundPath shape) and
// Pathfinder::snapLine (retail 0x003E6AF0, 110 bytes).
//
// Identity: the matched Pathfinder::findGroundPath caller (0x003F2160 +0x7DC)
// calls this body with the Pathfinder receiver; the Zero Hour AIPathfind.cpp
// buildGroundPath (prependCells, optimizeGroundPath, then a corner-smoothing
// pass) is the structural guide, and the BFME smoothing is reconstructed from
// retail. Retail's pathfinder TU defines worldToCell, snapLine and this body
// together, so worldToCell and snapLine are visible never-inlined bodies here:
// with them opaque the body is 85 bytes off (adjustedPosition escapes).
//
// The summed direction is a Coord3D built with set/add and the perpendicular
// offset with Coord3D::set/scale: MSVC 7.1 orders a commutative x87 operation by
// when each field is first accessed directly in the source, and direct field
// writes commute the cross product (+0x133) and the offset.x + adjusted.x sum
// (+0x1E5). Handoff: targets/game/reverse/attempt_support/
// 20261106-003e6b80-buildgroundpath-field-first-access.md.

#include "coord.h"

#undef REAL_TO_INT_FLOOR
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))
extern "C" __declspec(dllimport) double __cdecl floor(double);

extern const Real g_rva01075350;
extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

class Pathfinder;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Rva003D61C0Vec
{
	Int a, b, c;
};

struct Rva003DE480Struct;

// AI+0x14 holds the TAiData the AI constructor (0x0014C170) builds and
// AI::parseAiDataDefinition (0x0014E580) fills from the FieldParse table at VA
// 0x01094B00, whose FormationColumnWidth record writes a float at +0xA0
// (targets/game/reverse/identity_evidence/0x003e6b80-retry-layout-and-abi.md;
// ai.cpp and TAiDataCtor.cpp use the same field name).
class TAiData
{
public:
	char m_beforeFormationColumnWidth[0xa0];
	Real m_formationColumnWidth;
};

class AI
{
public:
	const TAiData *getAiData(void) const { return m_aiData; }

private:
	char m_beforeAiData[0x14];
	TAiData *m_aiData;
};

extern AI *TheAI;


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
	// Zero Hour's buildGroundPath. The method keeps its address: retail's ILT
	// contradicts every ?...@Pathfinder@@ decoration (tools/ilt_oracle.py), and
	// the matched findGroundPath caller binds this pinned spelling.
	Path *rva003E6B80(const Coord3D *fromPos, PathfindCell *goalCell,
		bool center, Int pathDiameter);

public:
	void prependCells(Path *path, const Coord3D *fromPos,
		PathfindCell *goalCell, bool center);
	__declspec(noinline) void snapLine(const Coord3D *sourcePosition, Coord3D *destinationPosition);

	char m_before14[0x14];
	IRegion2D m_extent;
};

// One ANY-COMDAT copy per TU: every emission of worldToCell (retail 0x003D7EC0)
// is this same inline, never-inlined body (PathfinderRva003D84A0.cpp holds the row).
inline __declspec(noinline) bool Pathfinder::worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex)
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

// ?snapLine@Pathfinder@@QAEXPBUCoord3D@@PAU2@@Z
// Moved here from PathfinderLineQueries.cpp: buildGroundPath needs the body
// visible (never inlined), as in retail's single pathfinder TU.
void Pathfinder::snapLine(const Coord3D *sourcePosition, Coord3D *destinationPosition)
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

// ?rva003E6B80@Pathfinder@@QAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
Path *Pathfinder::rva003E6B80(const Coord3D *fromPos,
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
			Coord3D dir;
			dir.set(&prevDir);
			dir.add(&nextDir);
			Real lenSq = dir.x * dir.x;
			lenSq += dir.y * dir.y;
			Real scale = g_bfmeDefaultBU / sqrt(lenSq);
			Coord3D offset;
			offset.set(&dir);
			offset.scale(scale);
			Real width = TheAI->getAiData()->m_formationColumnWidth;
			offset.scale(width + width);

			Coord3D adjustedPosition;
			adjustedPosition.set(currentPosition);
			if (prevDir.x * nextDir.y - prevDir.y * nextDir.x < g_rva01075350)
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

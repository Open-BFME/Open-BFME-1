// ?computePointOnPath@Rva003FD7D0Path@@QAEXPAVObject@@PAVLocomotor@@PAURva003FD7D0Point@@_N@Z
// partial score=0.62 date=2026-09-10
// BFME Path::computePointOnPath candidate, retail RVA 0x003FD7D0.
// This file is an evidence copy of the complete C++ attempt in AIPathfind.cpp.

#include <math.h>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;

struct Coord3D { Real x; Real y; Real z; };
struct Coord2D { Real x; Real y; };
enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };
class Object;
class Locomotor;
class PathNode
{
public:
	const Coord3D *getPosition(void) const;
	PathNode *getNextOptimized(Coord2D *, Real *);
	PathNode *getNextOptimized(void);
	PathfindLayerEnum getLayer(void) const;
};
class Pathfinder;
class AI { public: Pathfinder *pathfinder(void); };
extern AI *TheAI;
class TerrainLogic
{
public:
	void *getWaypointByID(UnsignedInt);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva003FD7D0Point
{
	Real m_distAlongPath;
	Coord3D m_posOnPath;
	Coord3D m_nextPos;
	PathfindLayerEnum m_layer;
	Int m_waypointID;
};
struct BlockRva003D5C60BlockAssign { UnsignedInt m_dword[3]; };
class Rva003D5C60BlockAssign
{
public:
	void set(const BlockRva003D5C60BlockAssign &value);
};
extern Real g_bfmeScaleBK;
extern double g_bfmeFactorBW;
extern Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;
extern void j_0000e359(void);
extern void j_0002ecad(void);
extern void j_0000a56a(void);

class Rva003FD7D0Path
{
public:
	void computePointOnPath(Object *object, Locomotor *locomotor,
		Rva003FD7D0Point *point, Bool useCache);
private:
	void *m_vtable;
	PathNode *m_path;
	PathNode *m_pathTail;
	UnsignedInt m_unused0C;
	PathNode *m_cachedNode;
	Coord3D m_cachedPosition;
	Real m_cachedDistance;
};

void Rva003FD7D0Path::computePointOnPath(Object *object, Locomotor *locomotor,
	Rva003FD7D0Point *point, Bool useCache)
{
	(void)object;
	Real height = 40.0f;
	if (locomotor)
	{
		typedef Real (Locomotor::*PreferredHeightCall)(void) const;
		union { void (*raw)(void); PreferredHeightCall member; } preferred;
		preferred.raw = j_0002ecad;
		height = (locomotor->*preferred.member)();
		if (height < g_bfmeScaleBK)
			height = useCache ? 0.1f : 1.0f;
	}
	point->m_distAlongPath = 0.0f;
	point->m_posOnPath.x = 0.0f;
	point->m_posOnPath.y = 0.0f;
	point->m_posOnPath.z = 0.0f;
	point->m_nextPos.x = 0.0f;
	point->m_nextPos.y = 0.0f;
	point->m_nextPos.z = 0.0f;
	point->m_layer = LAYER_GROUND;
	point->m_waypointID = 0x7fffffff;
	if (m_path == NULL)
		return;
	if (m_cachedNode == NULL)
	{
		m_cachedNode = m_path;
		m_cachedDistance = 0.0f;
		m_cachedPosition = *m_path->getPosition();
	}
	PathNode *current = m_cachedNode;
	Coord2D direction;
	Real segmentLength;
	PathNode *next;
	{
		typedef PathNode *(PathNode::*NextCall)(Coord2D *, Real *);
		union { void (*raw)(void); NextCall member; } call;
		call.raw = j_0000e359;
		next = (current->*call.member)(&direction, &segmentLength);
	}
	if (next == NULL)
	{
		point->m_nextPos = *current->getPosition();
		point->m_layer = current->getLayer();
		point->m_waypointID = *(const Int *)((const char *)current + 0x20);
		if (useCache)
		{
			m_cachedPosition = point->m_nextPos;
			m_cachedDistance = 0.0f;
		}
		return;
	}
	point->m_nextPos = *next->getPosition();
	point->m_layer = next->getLayer();
	point->m_waypointID = *(const Int *)((const char *)next + 0x20);
	Real zDelta = point->m_nextPos.z - current->getPosition()->z;
	if (point->m_waypointID != 0x7fffffff)
	{
		TerrainLogic *terrain = TheTerrainLogic;
		if (terrain)
		{
			void *waypoint = terrain->getWaypointByID(point->m_waypointID);
			if (waypoint)
				zDelta += *(const Real *)((const char *)waypoint + 0x60) == 3
					? height : 0.0f;
		}
	}
	Real along = m_cachedDistance;
	if (segmentLength > 0.0f)
	{
		along += segmentLength;
		point->m_posOnPath.x = m_cachedPosition.x + direction.x * segmentLength;
		point->m_posOnPath.y = m_cachedPosition.y + direction.y * segmentLength;
		point->m_posOnPath.z = m_cachedPosition.z + zDelta;
	}
	point->m_distAlongPath = (Real)sqrt(
		point->m_posOnPath.x * point->m_posOnPath.x +
		point->m_posOnPath.y * point->m_posOnPath.y +
		point->m_posOnPath.z * point->m_posOnPath.z);
	if (point->m_distAlongPath > along && along > 0.0f)
		point->m_distAlongPath = along;
	if (useCache)
	{
		m_cachedNode = current;
		m_cachedDistance = along;
		m_cachedPosition = point->m_posOnPath;
		Rva003D5C60BlockAssign *pathfinder =
			(Rva003D5C60BlockAssign *)TheAI->pathfinder();
		BlockRva003D5C60BlockAssign value;
		value.m_dword[0] = *(const UnsignedInt *)&point->m_posOnPath.x;
		value.m_dword[1] = *(const UnsignedInt *)&point->m_posOnPath.y;
		value.m_dword[2] = *(const UnsignedInt *)&point->m_posOnPath.z;
		pathfinder->set(value);
	}
	if (m_cachedNode != NULL && m_cachedNode->getNextOptimized() != NULL)
	{
		Real zero = 0.0f;
		typedef PathNode *(PathNode::*NextCall)(Coord2D *, Real *);
		union { void (*raw)(void); NextCall member; } call;
		call.raw = j_0000e359;
		PathNode *advanced = (m_cachedNode->getNextOptimized()->*call.member)(
			&direction, &zero);
		if (advanced == NULL)
			m_cachedDistance += zero;
	}
}

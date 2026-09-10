// ?bfmeOptimizeDir@Path@@QAEXPBVObject@@PBUCoord3D@@H_N@Z
// partial score=0.18 date=2026-09-10
// BFME's second path pass rebuilds the optimized chain while respecting the
// direction supplied by the unit.  The method is called immediately after
// Path::optimize by Pathfinder::buildActualPath (retail 0x003E10F0).

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;

	Real lengthSquared(void) const { return x * x + y * y; }
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	const Coord3D *getPosition(void) const { return &m_position; }
	const PathNode *getNext(void) const { return m_next; }
	const PathNode *getPrevious(void) const { return m_previous; }

	// This is the existing named retail helper at 0x003FD6E0.  Keeping the
	// direction and distance as typed outputs also preserves its ABI evidence.
	const PathNode *getNextOptimized(Coord2D *direction, Real *distance) const;

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	Int m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	void appendNode(const PathNode *source);

	void bfmeOptimizeDir(const Object *obj, const Coord3D *direction,
		Int acceptableSurfaces, Bool blocked);

	char m_bfmeHead[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

extern const Real BfmeShadowScale;
extern const Real BfmeZeroRange;
extern const Real g_bfmeK1266A;

static __forceinline Real horizontalDistanceSquared(const Coord3D &from, const Coord3D &to)
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	return dx * dx + dy * dy;
}

static __forceinline Bool followsDirection(const Coord3D &from, const Coord3D &to,
	const Coord3D &direction, Real tolerance)
{
	Real dx = to.x - from.x;
	Real dy = to.y - from.y;
	Real length = dx * dx + dy * dy;
	if (length <= BfmeZeroRange)
		return true;

	Real dot = dx * direction.x + dy * direction.y;
	if (dot < BfmeZeroRange)
		return false;

	Real cross = dx * direction.y - dy * direction.x;
	return cross * cross <= length * tolerance;
}

// ?bfmeOptimizeDir@Path@@QAEXPBVObject@@PBUCoord3D@@H_N@Z
void Path::bfmeOptimizeDir(const Object *obj, const Coord3D *direction,
	Int acceptableSurfaces, Bool blocked)
{
	(void)obj;
	(void)acceptableSurfaces;
	(void)blocked;

	PathNode *oldHead = m_path;
	m_isOptimized = true;
	m_path = 0;
	m_pathTail = 0;

	if (oldHead == 0 || direction == 0)
		return;

	Coord3D desired = *direction;
	Real desiredLength = desired.x * desired.x + desired.y * desired.y;
	if (desiredLength > BfmeZeroRange)
	{
		Real scale = BfmeShadowScale / desiredLength;
		desired.x *= scale;
		desired.y *= scale;
	}

	// The first pass already left the optimized links in retail order.  Copy
	// that chain, retaining a waypoint whenever it changes layer or turns away
	// from the requested unit direction.  appendNode is the real named BFME
	// helper at 0x003FE250 and copies the complete PathNode payload.
	PathNode *anchor = oldHead;
	Coord2D segmentDirection;
	Real segmentLength;
	while (anchor)
	{
		const PathNode *next = anchor->getNextOptimized(&segmentDirection,
			&segmentLength);
		if (m_pathTail == 0 ||
			m_pathTail->m_layer != anchor->m_layer ||
			followsDirection(m_pathTail->m_position, anchor->m_position,
				desired, g_bfmeK1266A * segmentLength))
		{
			appendNode(anchor);
		}

		if (next == 0)
			break;
		anchor = const_cast<PathNode *>(next);
	}

	// BFME removes tiny middle segments after the directional pass.  Keep the
	// end points and splice only a node whose two-dimensional distance is below
	// the retail tolerance; the ordinary list remains the ownership list.
	for (PathNode *node = m_path; node && node->m_nextOptimized; )
	{
		PathNode *middle = node->m_nextOptimized;
		PathNode *next = middle->m_nextOptimized;
		if (next && horizontalDistanceSquared(node->m_position,
			middle->m_position) < g_bfmeK1266A)
		{
			node->m_nextOptimized = next;
			continue;
		}
		node = middle;
	}
}

// ?bfmeOptimizeDir@Path@@QAEXPBVObject@@PBUCoord3D@@H_N@Z
// partial score=0.349 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00401070 (ILT 0x00049DEB): Path::bfmeOptimizeDir, the BFME-only
// second pass Pathfinder::buildActualPath, AIUpdateInterface::computeQuickPath
// and the AIUpdate path rebuild run after Path::optimize with the unit's
// direction vector.  It rebuilds the optimized chain from the old node list
// through the locomotor's turn helpers, then frees the old nodes.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef int LocomotorSurfaceTypeMask;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	void scale(Real scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	Real x;
	Real y;
	Real z;
};

// STLport's min/max: both return a reference to the chosen operand.
template <class T>
inline const T &stlMin(const T &a, const T &b)
{
	return b < a ? b : a;
}

template <class T>
inline const T &stlMax(const T &a, const T &b)
{
	return b > a ? b : a;
}

class Object;
class Thing;

enum
{
	INVALID_WAYPOINT_ID = 0x7fffffff
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathNode
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	const PathNode *getNextOptimized(Coord2D *dir, Real *dist) const;

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOpti;
	Coord3D m_pos;
	Int m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return (T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

// Offsets from the retail LocomotorTemplate FieldParse table; +0x3C and +0x80
// have no parse entry and keep their offsets.
class LocomotorTemplate : public Overridable
{
public:
	Real getFloat03c() const { return m_float03c; }
	Real getFloat080() const { return m_float080; }

	char m_pad08[0x3c - 0x08];
	Real m_float03c;
	char m_pad40[0x6c - 0x40];
	Int m_behaviorZ;
	char m_pad70[0x80 - 0x70];
	Real m_float080;
	char m_pad84[0xd4 - 0x84];
	Int m_canMoveBackward;
};

// The matched accessors this body reaches keep their landed spellings.
class Rva001BDFF0
{
public:
	int get();
};

class Rva001B59FloatView
{
public:
	float getFirstFloat(void) const;
	float getSecondFloat(void) const;
};

class Locomotor
{
public:
	Bool queryBelowQuarter(const Object *obj);
	Bool bfmeIsPositionBehind(const Thing *thing, const Coord3D *pos) const;

	Real getFirstFloat() const { return ((const Rva001B59FloatView *)this)->getFirstFloat(); }
	Real getSecondFloat() const { return ((const Rva001B59FloatView *)this)->getSecondFloat(); }

	virtual ~Locomotor();

	OVERRIDE<LocomotorTemplate> m_template;
};

// The per-call options the 0x003FFB50 helper reads.
struct Rva003FFB50Options
{

	Bool m_flag0;
	Bool m_flag1;
	Real m_value;
	Bool m_flag8;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Path
{
public:
	void appendNode(const PathNode *source);
	void bfmeFinishTurnArc(PathNode *prev, PathNode *node, PathNode *next, Real dist);
	Bool rva003FFB50(const Object *obj, PathNode *node, const Coord3D *dir,
		Rva003FFB50Options *options, LocomotorSurfaceTypeMask acceptableSurfaces,
		Real limit, Bool blocked);
	void rva004005D0(const Object *obj, PathNode *prev, PathNode *node,
		const Coord3D *dir, Real radius);

	void bfmeOptimizeDir(const Object *obj, const Coord3D *direction,
		LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked);

private:
	char m_head[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

void Path::bfmeOptimizeDir(const Object *obj, const Coord3D *direction,
	LocomotorSurfaceTypeMask acceptableSurfaces, Bool blocked)
{
	Rva003FFB50Options options;
	PathNode *oldHead = m_path;
	m_isOptimized = true;
	m_path = 0;
	m_pathTail = 0;

	Coord3D dir = *direction;
	Real locoValue = 0.0f;
	Real dist = 5.0f;
	Locomotor *loco = (Locomotor *)((Rva001BDFF0 *)obj)->get();
	Bool reversed = false;
	Bool farEnough = false;
	Real radius = 5.0f;
	if (loco)
	{
		locoValue = loco->queryBelowQuarter(obj) ? loco->getSecondFloat() : loco->getFirstFloat();

		Bool behind = false;
		if (loco->m_template->m_canMoveBackward)
		{
			Coord2D segment;
			const PathNode *next = oldHead->getNextOptimized(&segment, &dist);
			if (next && loco->bfmeIsPositionBehind((const Thing *)obj, next->getPosition()))
				behind = true;
		}
		if (behind)
		{
			dir.scale(-1.0f);
			reversed = true;
			Real first = loco->getFirstFloat();
			radius = stlMax(first, loco->getSecondFloat());
			if (radius * 3.0f < dist)
				farEnough = true;
		}
		dist = loco->getSecondFloat();
	}

	PathNode *prev = oldHead;
	PathNode *node = oldHead->m_nextOpti;
	if (reversed && farEnough)
	{
		rva004005D0(obj, prev, node, direction, radius);
	}
	else if (locoValue > 0.0f)
	{
		options.m_flag0 = true;
		options.m_flag1 = false;
		options.m_value = locoValue;
		options.m_flag8 = false;

		Real limit = loco->m_template->getFloat080();
		if (loco->queryBelowQuarter(obj))
			limit = stlMin(loco->m_template->getFloat03c(), limit);

		Bool ok = rva003FFB50(obj, oldHead, &dir, &options, acceptableSurfaces, limit, blocked);
		if (loco->m_template->m_behaviorZ != 8 && !ok)
		{
			options.m_flag1 = true;
			if (!rva003FFB50(obj, oldHead, &dir, &options, acceptableSurfaces, limit, blocked))
			{
				options.m_flag1 = false;
				options.m_value = 5.0f;
			}
		}
		options.m_flag0 = false;
		rva003FFB50(obj, oldHead, &dir, &options, acceptableSurfaces, limit, blocked);
	}
	else
	{
		appendNode(prev);
	}

	while (node)
	{
		PathNode *next = node->m_nextOpti;
		if (next && node->m_waypointID == INVALID_WAYPOINT_ID &&
			next->m_waypointID == INVALID_WAYPOINT_ID)
			bfmeFinishTurnArc(prev, node, next, dist);
		else
			appendNode(node);
		prev = node;
		node = next;
	}

	while (oldHead)
	{
		PathNode *next = oldHead->m_next;
		delete oldHead;
		oldHead = next;
	}
}

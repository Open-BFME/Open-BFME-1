// Compute the normalized direction and distance to the next optimized Path
// node. BFME clamps degenerate segments to 0.01, matching the callers' path
// traversal contract.

#include <math.h>

typedef float Real;

struct Coord2D
{
	Real x;
	Real y;

	Real length() const { return (Real)sqrt(x * x + y * y); }
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	const PathNode *getNextOptimized(Coord2D *dir, Real *dist) const;

private:
	void *m_opaque0;
	void *m_opaque4;
	PathNode *m_nextOpti;
	Coord3D m_pos;
};

// ?getNextOptimized@PathNode@@QBEPBV1@PAUCoord2D@@PAM@Z
const PathNode *PathNode::getNextOptimized(Coord2D *dir, Real *dist) const
{
	if (m_nextOpti == 0)
	{
		dir->x = dir->y = 0.0f;
		*dist = 0.01f;
		return 0;
	}

	dir->x = m_nextOpti->m_pos.x - m_pos.x;
	dir->y = m_nextOpti->m_pos.y - m_pos.y;
	*dist = dir->length();
	if (*dist < 0.01f)
		*dist = 0.01f;
	Real invDist = 1.0f / *dist;
	dir->x *= invDist;
	dir->y *= invDist;
	return m_nextOpti;
}

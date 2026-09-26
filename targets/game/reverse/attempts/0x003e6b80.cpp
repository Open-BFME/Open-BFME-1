// ?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// partial score=0.9 date=2026-09-24
// Open-BFME reconstruction of the BFME Pathfinder ground-path builder.
// The surrounding layout follows the GPLv3 GeneralsMD reference tree; the
// retail-specific path smoothing is reconstructed from the BFME body at RVA
// 0x003E6B80 and its matched Pathfinder::findGroundPath caller.
//
// cl: /DNDEBUG /DWIN32 /MD /EHsc

#include <math.h>

typedef int Int;
typedef float Real;

extern const Real BfmeZeroRange;
extern const Real g_bfmeDefaultBU;
extern const Real g_bfmeK1253;

class Pathfinder;

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

class Pathfinder
{
protected:
	Path *buildGroundPath(const Coord3D *fromPos, PathfindCell *goalCell,
		bool center, Int pathDiameter);

public:
	void prependCells(Path *path, const Coord3D *fromPos,
		PathfindCell *goalCell, bool center);
	void snapLine(const Coord3D *from, Coord3D *to);

private:
	char m_beforeFieldA0[0xa0];
	Real m_fieldA0;
};

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
			Real scale = g_bfmeDefaultBU / sqrt(dirX * dirX + dirY * dirY);
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

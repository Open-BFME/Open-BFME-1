// ?buildGroundPath@Pathfinder@@IAEPAVPath@@PBUCoord3D@@PAVPathfindCell@@_NH@Z
// partial score=0.88 date=2026-09-10
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
			Coord3D adjustedPosition = *currentPosition;

			Real dy = currentPosition->y;
			Real dx = currentPosition->x - previousPosition.x;
			dy -= previousPosition.y;
			Real nextDy = nextPosition->y;
			Real nextDx = nextPosition->x - currentPosition->x;
			nextDy -= currentPosition->y;
			Real totalDx = dx + nextDx;
			Real totalDy = dy + nextDy;
			Real scale = g_bfmeDefaultBU /
				sqrt(totalDx * totalDx + totalDy * totalDy);
			Real offsetX = scale * totalDx;
			Real offsetY = scale * totalDy;
			Real width = TheAI->pathfinder()->m_fieldA0;
			width += width;
			offsetX *= width;
			offsetY *= width;

			if (dx * nextDy - nextDx * dy < BfmeZeroRange)
			{
				adjustedPosition.x = currentPosition->x + offsetY;
				adjustedPosition.y = currentPosition->y - offsetX;
			}
			else
			{
				adjustedPosition.x = currentPosition->x - offsetY;
				adjustedPosition.y = currentPosition->y + offsetX;
			}

			snapLine(currentPosition, &adjustedPosition);

			Coord3D delta = adjustedPosition;
			delta.x -= currentPosition->x;
			delta.y -= currentPosition->y;
			delta.z -= currentPosition->z;
			currentPosition->x += delta.x * g_bfmeK1253;
			currentPosition->y += delta.y * g_bfmeK1253;
			currentPosition->z += delta.z * g_bfmeK1253;
		}

		previousPosition = originalPosition;
		node = node->getNextOptimized();
		havePrevious = true;
	}

	return path;
}

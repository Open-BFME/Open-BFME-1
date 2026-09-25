// BFME's member-ified tighten-path callback, retail 0x003F1840 (127 bytes).
// cl: /DNDEBUG /MD

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

struct Coord3D { Real x, y, z; };

class Object;
class LocomotorSet;
class PathfindCell;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Bool checkForAdjust(Object *object, const LocomotorSet &locomotorSet, Bool isHuman,
		Int cellX, Int cellY, Int layer, Int radius, Bool centerInCell, Coord3D *destination,
		const Coord3D *groupDestination, Real originalZ,
		PathfindCell **previousCellSlot, Int onlyIfLayer);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	Int getLayer(void) const { return (m_word >> 6) & 0x3f; }

private:
	char m_pad[0x0c];
	unsigned int m_word;
};

class TightenPathCallbackInfo
{
public:
	Int cellCallback(PathfindCell *previousCell, PathfindCell *candidateCell, Int cellX, Int cellY);

	Pathfinder *m_pathfinder;
	Object *m_object;
	const LocomotorSet *m_locomotorSet;
	Int m_radius;
	Bool m_centerInCell;
	char m_pad11[3];
	Int m_layer;
	Bool m_foundDest;
	char m_pad19[3];
	Coord3D m_candidatePosition;
	Coord3D m_destination;
};

Int TightenPathCallbackInfo::cellCallback(PathfindCell *previousCell,
	PathfindCell *candidateCell, Int cellX, Int cellY)
{
	if (previousCell == 0)
		return 0;

	if (m_layer != candidateCell->getLayer())
		return 0;

	if (!m_pathfinder->checkForAdjust(m_object, *m_locomotorSet, 1,
		cellX, cellY, candidateCell->getLayer(), m_radius, m_centerInCell, &m_candidatePosition,
		0, 0.0f, &previousCell, 0))
		return 0;

	if (previousCell != 0)
		return 0;

	m_foundDest = 1;
	m_destination = m_candidatePosition;
	return 0;
}

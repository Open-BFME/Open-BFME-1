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
	Bool checkForAdjust(Object *obj, const LocomotorSet &set, Bool human,
		Int x, Int y, Int layer, Int radius, Bool center, Coord3D *dest,
		const Coord3D *groupDest, const Coord3D *originalDest,
		PathfindCell **fromSlot, Bool onlyIfLayer);
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
	Int cellCallback(PathfindCell *from, PathfindCell *to, Int to_x, Int to_y);

	Pathfinder *m_pathfinder;
	Object *m_obj;
	const LocomotorSet *m_locomotorSet;
	Int m_radius;
	Bool m_center;
	char m_pad11[3];
	Int m_layer;
	Bool m_foundDest;
	char m_pad19[3];
	Coord3D m_scratch;
	Coord3D m_dest;
};

Int TightenPathCallbackInfo::cellCallback(PathfindCell *from,
	PathfindCell *to, Int to_x, Int to_y)
{
	if (from == 0)
		return 0;

	if (m_layer != to->getLayer())
		return 0;

	if (!m_pathfinder->checkForAdjust(m_obj, *m_locomotorSet, 1,
		to_x, to_y, to->getLayer(), m_radius, m_center, &m_scratch,
		0, 0, &from, 0))
		return 0;

	if (from != 0)
		return 0;

	m_foundDest = 1;
	m_dest = m_scratch;
	return 0;
}

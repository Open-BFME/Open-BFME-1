// BFME's member-ified tighten-path callback, retail 0x003F1840 (127 bytes).
// cl: /DNDEBUG /MD

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class LocomotorSet;
class PathfindCell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
// The call at 0x3F1890 reaches the incremental-link thunk at retail 0x0002AA04,
// the ledger's 5-byte row ?j_0002aa04@@YAXXZ (game/gen_small/thunks_020.cpp),
// whose body at 0x003F0F40 is the matched gen dump ?d_003f0f40@@YAXXZ
// (game/gen_asm/d_003eeb90.asm), as tools/callees.py 0x3f1840 127 prints for
// the callee.  Nothing defines a member named checkForAdjust, so the call names
// the thunk the ledger owns; the bridge sits at the call site, and Pathfinder
// stays only the receiver view so no body is emitted under the pinned name.
void j_0002aa04();

class Pathfinder {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
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

	union
	{
		void (*raw)(void);
		Bool (Pathfinder::*typed)(Object *, const LocomotorSet &, Bool, Int, Int, Int, Int, Bool,
			Coord3D *, const Coord3D *, Real, PathfindCell **, Int);
	} checkForAdjust;
	checkForAdjust.raw = &j_0002aa04;
	if (!(m_pathfinder->*checkForAdjust.typed)(m_object, *m_locomotorSet, 1,
		cellX, cellY, candidateCell->getLayer(), m_radius, m_centerInCell, &m_candidatePosition,
		0, 0.0f, &previousCell, 0))
		return 0;

	if (previousCell != 0)
		return 0;

	m_foundDest = 1;
	m_destination = m_candidatePosition;
	return 0;
}

// ?getShroudStatusForPlayer@PartitionManager@@QBE?AW4CellShroudStatus@@HPBUCoord3D@@@Z
// BFME PartitionManager::getShroudStatusForPlayer, RVA 0x008F7430, 8 bytes: tail call into the shroud grid at +0x0C.
// The grid lookup is Gen_008F7CD0::bfmeCheckFD in BfmeConv1757.cpp.

struct Coord3D
{
	float x, y, z;
};

struct BfmePointFD;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

class Gen_008F7CD0
{
public:
	int bfmeCheckFD(int index, const BfmePointFD *point);
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *loc) const;
	char m_lead[0x0C];
	Gen_008F7CD0 *m_shroudGrid;
};

CellShroudStatus PartitionManager::getShroudStatusForPlayer(int playerIndex, const Coord3D *loc) const
{
	return (CellShroudStatus)m_shroudGrid->bfmeCheckFD(playerIndex, (const BfmePointFD *)loc);
}

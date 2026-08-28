// cl: /EHsc /Ireference/shims/pathfind
// readable body of ?clip@Pathfinder@@QAEXPAUCoord3D@@0@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?getCell@PathfindLayer@@QAEPAVPathfindCell@@HH@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
#include "GameLogic/AIPathfind.h"

// Retail rejects type==5 (CELL_BRIDGE_IMPASSABLE in this tree's ordinal - see
// PathfindCell::getRawType's comment) rather than ZH's CELL_IMPASSABLE(6).
PathfindCell *PathfindLayer::getCell(Int x, Int y)
{
	if (m_layerCells == 0)
		return 0;
	x -= m_xOrigin;
	y -= m_yOrigin;
	if (x < 0 || x >= m_width)
		return 0;
	if (y < 0 || y >= m_height)
		return 0;
	PathfindCell *cell = &m_layerCells[x][y];
	if (cell->getRawType() == 5)
		return 0;
	return cell;
}

PathfindCell *Pathfinder::getCell(PathfindLayerEnum layer, Int x, Int y)
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell(x, y);
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}

Bool Pathfinder::worldToCell(const Coord3D *pos, ICoord2D *cell)
{
	cell->x = REAL_TO_INT_FLOOR(pos->x/PATHFIND_CELL_SIZE);
	cell->y = REAL_TO_INT_FLOOR(pos->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cell->x < m_extent.lo.x) {overflow = true; cell->x = m_extent.lo.x;}
	if (cell->y < m_extent.lo.y) {overflow = true; cell->y = m_extent.lo.y;}
	if (cell->x > m_extent.hi.x) {overflow = true; cell->x = m_extent.hi.x;}
	if (cell->y > m_extent.hi.y) {overflow = true; cell->y = m_extent.hi.y;}
	return overflow;
}

void Pathfinder::clip( Coord3D *from, Coord3D *to )
{
	ICoord2D fromCell, toCell;
	ICoord2D clipFromCell, clipToCell;
	fromCell.x = REAL_TO_INT_FLOOR(from->x/PATHFIND_CELL_SIZE);
	fromCell.y = REAL_TO_INT_FLOOR(from->y/PATHFIND_CELL_SIZE);
	toCell.x = REAL_TO_INT_FLOOR(to->x/PATHFIND_CELL_SIZE);
	toCell.y = REAL_TO_INT_FLOOR(to->y/PATHFIND_CELL_SIZE);
	if (ClipLine2D(&fromCell, &toCell, &clipFromCell, &clipToCell,&m_extent)) {
		if (fromCell.x!=clipFromCell.x || fromCell.y != clipFromCell.y) {
			from->x = clipFromCell.x*PATHFIND_CELL_SIZE + 0.05f;
			from->y = clipFromCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
		if (toCell.x!=clipToCell.x || toCell.y != clipToCell.y) {
			to->x = clipToCell.x*PATHFIND_CELL_SIZE + 0.05f;
			to->y = clipToCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
	}
}

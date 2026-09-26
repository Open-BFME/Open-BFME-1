// cl: /EHsc /Iinputs/reference/shims/pathfind
// readable body of ?clip@Pathfinder@@QAEXPAUCoord3D@@0@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?getCell@PathfindLayer@@QAEPAVPathfindCell@@HH@Z: game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
#include "GameLogic/AIPathfind.h"

// Retail rejects type==5 (CELL_BRIDGE_IMPASSABLE in this tree's ordinal - see
// PathfindCell::getRawType's comment) rather than ZH's CELL_IMPASSABLE(6).
PathfindCell *PathfindLayer::getCell(Int cellX, Int cellY)
{
	if (m_layerCells == 0)
		return 0;
	cellX -= m_xOrigin;
	cellY -= m_yOrigin;
	if (cellX < 0 || cellX >= m_width)
		return 0;
	if (cellY < 0 || cellY >= m_height)
		return 0;
	PathfindCell *cell = &m_layerCells[cellX][cellY];
	if (cell->getRawType() == 5)
		return 0;
	return cell;
}

PathfindCell *Pathfinder::getCell(PathfindLayerEnum layer, Int cellX, Int cellY)
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell(cellX, cellY);
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
}

Bool Pathfinder::worldToCell(const Coord3D *worldPosition, ICoord2D *cellIndex)
{
	cellIndex->x = REAL_TO_INT_FLOOR(worldPosition->x/PATHFIND_CELL_SIZE);
	cellIndex->y = REAL_TO_INT_FLOOR(worldPosition->y/PATHFIND_CELL_SIZE);
	Bool overflow = false;
	if (cellIndex->x < m_extent.lo.x) {overflow = true; cellIndex->x = m_extent.lo.x;}
	if (cellIndex->y < m_extent.lo.y) {overflow = true; cellIndex->y = m_extent.lo.y;}
	if (cellIndex->x > m_extent.hi.x) {overflow = true; cellIndex->x = m_extent.hi.x;}
	if (cellIndex->y > m_extent.hi.y) {overflow = true; cellIndex->y = m_extent.hi.y;}
	return overflow;
}

void Pathfinder::clip( Coord3D *startPosition, Coord3D *endPosition )
{
	ICoord2D fromCell, toCell;
	ICoord2D clipFromCell, clipToCell;
	fromCell.x = REAL_TO_INT_FLOOR(startPosition->x/PATHFIND_CELL_SIZE);
	fromCell.y = REAL_TO_INT_FLOOR(startPosition->y/PATHFIND_CELL_SIZE);
	toCell.x = REAL_TO_INT_FLOOR(endPosition->x/PATHFIND_CELL_SIZE);
	toCell.y = REAL_TO_INT_FLOOR(endPosition->y/PATHFIND_CELL_SIZE);
	if (ClipLine2D(&fromCell, &toCell, &clipFromCell, &clipToCell,&m_extent)) {
		if (fromCell.x!=clipFromCell.x || fromCell.y != clipFromCell.y) {
			startPosition->x = clipFromCell.x*PATHFIND_CELL_SIZE + 0.05f;
			startPosition->y = clipFromCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
		if (toCell.x!=clipToCell.x || toCell.y != clipToCell.y) {
			endPosition->x = clipToCell.x*PATHFIND_CELL_SIZE + 0.05f;
			endPosition->y = clipToCell.y*PATHFIND_CELL_SIZE + 0.05f;
		}
	}
}

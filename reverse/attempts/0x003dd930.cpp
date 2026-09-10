// ?prependCells@Pathfinder@@IAEXPAVPath@@PBUCoord3D@@PAVPathfindCell@@_N@Z
// partial score=0.36 date=2026-09-10
// ?prependCells@Pathfinder@@IAEXPAVPath@@PBUCoord3D@@PAVPathfindCell@@_N@Z
// Complete canonical Pathfinder::prependCells candidate from AIPathfind.cpp.
void Pathfinder::prependCells( Path *path, const Coord3D *fromPos,
																		PathfindCell *goalCell, Bool center )
{
	// traverse path cells in REVERSE order, creating path in desired order
	// skip the LAST node, as that will be in the same cell as the unit itself - so use the unit's position
	Coord3D pos;
	PathfindCell *cell, *prevCell = NULL;
	Bool goalCellNull = (goalCell->getParentCell()==NULL);
	for( cell = goalCell; cell->getParentCell(); cell = cell->getParentCell() )
	{
		m_zoneManager.setPassable(cell->getXIndex(), cell->getYIndex(), true);
		adjustCoordToCell(cell->getXIndex(), cell->getYIndex(), center, pos, cell->getLayer());
		if (prevCell && cell->getXIndex()==prevCell->getXIndex() && cell->getYIndex()==prevCell->getYIndex()) {
			// transitioning layers.
			PathfindLayerEnum layer = cell->getLayer();
			if (layer==LAYER_GROUND) {
				layer = prevCell->getLayer();
			}
			DEBUG_ASSERTCRASH(layer!=LAYER_GROUND, ("Should have at 1 non-ground layer. jba"));
			path->getFirstNode()->setLayer(layer);
			continue;
		}
		
		Bool canOptimize = true;
		if (cell->getType() == PathfindCell::CELL_CLIFF) {
			if (prevCell && prevCell->getType() != PathfindCell::CELL_CLIFF) {
				if (path->getFirstNode()) {
					path->getFirstNode()->setCanOptimize(false);
				}
			}
		}	else {
			if (prevCell && prevCell->getType() == PathfindCell::CELL_CLIFF) {
				canOptimize = false;
			}
		}

		path->prependNode( &pos, cell->getLayer() );
		path->getFirstNode()->setCanOptimize(canOptimize);
		if (cell->isBlockedByAlly()) {
			path->setBlockedByAlly(true);
		}
		if (prevCell) {
			prevCell->clearParentCell();
		}
		prevCell = cell;
	}
	m_zoneManager.setPassable(cell->getXIndex(), cell->getYIndex(), true);
	if (goalCellNull) {
		// Very short path.
		adjustCoordToCell(cell->getXIndex(), cell->getYIndex(), center, pos, cell->getLayer());
		path->prependNode( &pos, cell->getLayer() );
	}
	// put actual start position as first node on the path, so it begins right at the unit's feet
	if (fromPos->x != path->getFirstNode()->getPosition()->x || fromPos->y != path->getFirstNode()->getPosition()->y) {
		path->prependNode( fromPos, cell->getLayer() );
	}

}

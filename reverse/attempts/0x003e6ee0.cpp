// ?examineNeighboringCells@Pathfinder@@IAEHPAVPathfindCell@@0ABVLocomotorSet@@_N2HABUICoord2D@@PBVObject@@H@Z
// partial score=0.2 date=2026-09-17
// Extracted best available source body for the partial at 0x003E6EE0.
// The owning TU remains the Zero Hour twin under Code/GameEngine/Source/GameLogic/AI.
+Int Pathfinder::examineNeighboringCells(PathfindCell *parentCell, PathfindCell *goalCell, const LocomotorSet& locomotorSet, 
																				 Bool isHuman, Bool centerInCell, Int radius, const ICoord2D &startCellNdx,
																				 const Object *obj, Int attackDistance)
{
		Bool canPathThroughUnits = false;
		if (obj && obj->getAIUpdateInterface()) {
			canPathThroughUnits = obj->getAIUpdateInterface()->canPathThroughUnits();
		}
		Bool isCrusher = obj ? obj->getCrusherLevel() > 0 : false;
		if (attackDistance==NO_ATTACK && !m_isTunneling && !locomotorSet.isDownhillOnly() && goalCell) {
			ExamineCellsStruct info;
			info.thePathfinder = this;
			info.theLoco = &locomotorSet;
			info.centerInCell = centerInCell;
			info.radius = radius;
			info.obj = obj;
			info.isHuman = isHuman;
			info.goalCell = goalCell;
			ICoord2D start, end;
			start.x = parentCell->getXIndex();
			start.y = parentCell->getYIndex();
			end.x = goalCell->getXIndex();
			end.y = goalCell->getYIndex();
			iterateCellsAlongLine(start, end, parentCell->getLayer(), examineCellsCallback, &info);
		}

		Int cellCount = 0;
		// expand search to neighboring orthogonal cells
		static ICoord2D delta[] = 
		{ 
			{ 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 }, 
			{ 1, 1 }, { -1, 1 }, { -1, -1 }, { 1, -1 } 
		};
		const Int numNeighbors = 8;
		const Int firstDiagonal = 4;
		ICoord2D newCellCoord;
		PathfindCell *newCell;
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8] = {false, false, false, false, false, false, false};

		UnsignedInt newCostSoFar;



		for( int i=0; i<numNeighbors; i++ )
		{
			neighborFlags[i] = false;
			// determine neighbor cell to try
			newCellCoord.x = parentCell->getXIndex() + delta[i].x;
			newCellCoord.y = parentCell->getYIndex() + delta[i].y;

			// get the neighboring cell
			newCell = getCell(parentCell->getLayer(), newCellCoord.x, newCellCoord.y );

			// check if cell is on the map
			if (newCell == NULL)
				continue;

			Bool notZonePassable = false;
			if ((newCell->getLayer()==LAYER_GROUND) && !m_zoneManager.isPassable(newCellCoord.x, newCellCoord.y)) {
				notZonePassable = true;
			}
			if (isHuman) {
				// check if new cell is in logical map.	(computer can move off logical map)
				if (newCellCoord.x < m_logicalExtent.lo.x) continue;
				if (newCellCoord.y < m_logicalExtent.lo.y) continue; 
				if (newCellCoord.x > m_logicalExtent.hi.x) continue; 
				if (newCellCoord.y > m_logicalExtent.hi.y) continue; 
			}

			// check if this neighbor cell is already on the open (waiting to be tried) 
			// or closed (already tried) lists
			Bool onList = false;
			if (newCell->hasInfo()) {
				if (newCell->getOpen() || newCell->getClosed())
				{
					// already on one of the lists 
					onList = true;
				}
			}
			if (onList) {
				// we have already examined this one, so continue.
				continue;
			}
			if (i>=firstDiagonal) {
				// make sure one of the adjacent sides is open.
				if (!neighborFlags[adjacent[i-4]] && !neighborFlags[adjacent[i-3]]) {
					continue;
				}
			}

			// do the gravity check here
			if ( locomotorSet.isDownhillOnly() )
			{
				Coord3D fromPos;
				fromPos.x = parentCell->getXIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.y = parentCell->getYIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.z = TheTerrainLogic->getGroundHeight(fromPos.x , fromPos.y);

				Coord3D toPos;
				toPos.x = newCellCoord.x * PATHFIND_CELL_SIZE_F ;
				toPos.y = newCellCoord.y * PATHFIND_CELL_SIZE_F ;
				toPos.z = TheTerrainLogic->getGroundHeight(toPos.x , toPos.y);

				if ( fromPos.z < toPos.z )
					continue;
			}



			Bool movementValid = true;
			Bool dozerHack = false;
			if (validMovementPosition( isCrusher, locomotorSet.getValidSurfaces(), newCell, parentCell )) {
			}	else {
				movementValid = false;
				if (obj->isKindOf(KINDOF_DOZER)) {
					if (newCell->getType()==PathfindCell::CELL_OBSTACLE) {
						Object *obstacle = TheGameLogic->findObjectByID(newCell->getObstacleID());
						if (obstacle && !(obj->getRelationship(obstacle)==ENEMIES)) {
							movementValid = true;
							dozerHack = true;
						}
					}
				}
				if (!movementValid && !m_isTunneling) {
					continue;
				}
			}	
			if (!dozerHack) 
				neighborFlags[i] = true;

			TCheckMovementInfo info;
			info.cell = newCellCoord;
			info.layer = parentCell->getLayer();
			info.centerInCell = centerInCell;
			info.radius = radius;
			info.considerTransient = false;
			info.acceptableSurfaces = locomotorSet.getValidSurfaces();
			Int dx = newCellCoord.x-startCellNdx.x;
			Int dy = newCellCoord.y-startCellNdx.y;
			if (dx<0) dx = -dx;
			if (dy<0) dy = -dy;
			if (dx>1+radius) info.considerTransient = false;
			if (dy>1+radius) info.considerTransient = false;
			if (!checkForMovement(obj, info) || info.enemyFixed) {
				if (!m_isTunneling) {
					continue;
				}
				movementValid = false;
			}	
			if (movementValid && !newCell->getPinched()) {
				//Note to self - only turn off tunneling after check for movement.jba. 
				m_isTunneling = false;
			}
			if (!newCell->hasInfo()) {
				if (!newCell->allocateInfo(newCellCoord)) {
					// Out of cells for pathing...
 					return cellCount;
				}								
				cellCount++;
			}

			newCostSoFar = newCell->costSoFar( parentCell );
			if (info.allyMoving && dx<10 && dy<10) {
				newCostSoFar += 3*COST_DIAGONAL;
			}
			if (newCell->getType() == PathfindCell::CELL_CLIFF && !newCell->getPinched() ) {
				Coord3D fromPos;
				fromPos.x = parentCell->getXIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.y = parentCell->getYIndex() * PATHFIND_CELL_SIZE_F ;
				fromPos.z = TheTerrainLogic->getGroundHeight(fromPos.x , fromPos.y);

				Coord3D toPos;
				toPos.x = newCellCoord.x * PATHFIND_CELL_SIZE_F ;
				toPos.y = newCellCoord.y * PATHFIND_CELL_SIZE_F ;
				toPos.z = TheTerrainLogic->getGroundHeight(toPos.x , toPos.y);

				if ( fabs(fromPos.z - toPos.z)<PATHFIND_CELL_SIZE_F) {
					newCostSoFar += 7*COST_DIAGONAL;
				}
			} else if (newCell->getPinched()) {
				newCostSoFar += COST_ORTHOGONAL;
			}
			newCell->setBlockedByAlly(false);
			if (info.allyFixedCount>0) {
				Int costFactor = 3*COST_DIAGONAL;
				if (attackDistance != NO_ATTACK) {
					costFactor = 3*COST_DIAGONAL;
				}
				if (canPathThroughUnits) {
					newCostSoFar += costFactor;
				}	else {
					newCell->setBlockedByAlly(true);
					newCostSoFar += costFactor;
				}
			} 
			Int costRemaining = 0;
			if (goalCell) {
				if (attackDistance == NO_ATTACK)  {
					costRemaining = newCell->costToGoal( goalCell );
				}	else {
					dx = newCellCoord.x - goalCell->getXIndex();
					dy = newCellCoord.y - goalCell->getYIndex();
					costRemaining = COST_ORTHOGONAL*sqrt(dx*dx + dy*dy);
					costRemaining -= attackDistance/2;
					if (costRemaining<0) costRemaining=0;
					if (info.allyGoal) {
						if (obj->isKindOf(KINDOF_VEHICLE)) {
							newCostSoFar += 3*COST_ORTHOGONAL; 
						}	else {
							// Infantry can pass through infantry.
							newCostSoFar += COST_ORTHOGONAL;
						}
					}
				}
			}
			if (notZonePassable) {
				newCostSoFar += 100*COST_ORTHOGONAL;
			}
			if (newCell->getType()==PathfindCell::CELL_OBSTACLE) {
				newCostSoFar += 100*COST_ORTHOGONAL;
			}
			// check if this neighbor cell is already on the open (waiting to be tried) 
			// or closed (already tried) lists
			if (onList)
			{
				// already on one of the lists - if existing costSoFar is less, 
				// the new cell is on a longer path, so skip it
				if (newCell->getCostSoFar() <= newCostSoFar)
					continue;
			}
			if (m_isTunneling) {
				if (!validMovementPosition( isCrusher, locomotorSet.getValidSurfaces(), newCell, parentCell )) {
					newCostSoFar += 10*COST_ORTHOGONAL;
				}
			}
			newCell->setCostSoFar(newCostSoFar);
			// keep track of path we're building - point back to cell we moved here from
			newCell->setParentCell(parentCell) ;
			if (m_isTunneling) {
				costRemaining = 0; // find the closest valid cell.
			}
			newCell->setTotalCost(newCell->getCostSoFar() + costRemaining) ;

			//DEBUG_LOG(("Cell (%d,%d), Parent cost %d, newCostSoFar %d, cost rem %d, tot %d\n", 
			//	newCell->getXIndex(), newCell->getYIndex(), 
			//	newCell->costSoFar(parentCell), newCostSoFar, costRemaining, newCell->getCostSoFar() + costRemaining));

			// if newCell was on closed list, remove it from the list
			if (newCell->getClosed())
				m_closedList = newCell->removeFromClosedList( m_closedList );

			// if the newCell was already on the open list, remove it so it can be re-inserted in order
			if (newCell->getOpen())
				m_openList = newCell->removeFromOpenList( m_openList );

			// insert newCell in open list such that open list is sorted, smallest total path cost first
			m_openList = newCell->putOnSortedOpenList( m_openList );
		}
	return cellCount;
}




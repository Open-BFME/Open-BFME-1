// ?adjustToPossibleDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z
// partial score=0.25 date=2026-09-10
// ?adjustToPossibleDestination@Pathfinder@@QAE_NPAVObject@@ABVLocomotorSet@@PAUCoord3D@@@Z
// Complete semantic candidate used for the Round45 first probe.  The BFME
// retail ABI/layout probe disproved this existing ZH-shaped implementation.
Bool Pathfinder::adjustToPossibleDestination(Object *obj, const LocomotorSet& locomotorSet,
                                             Coord3D *dest)
{
	Int radius;
	Bool center;
	getRadiusAndCenter(obj, radius, center);
	ICoord2D goalCellNdx;
	Coord3D adjustDest = *dest;
	if (!center) {
		adjustDest.x += PATHFIND_CELL_SIZE_F/2;
		adjustDest.y += PATHFIND_CELL_SIZE_F/2;
	}
	if (worldToCell(&adjustDest, &goalCellNdx)) {
		return false;
	}

	PathfindLayerEnum destinationLayer = TheTerrainLogic->getLayerForDestination(dest);
	PathfindCell *goalCell = getCell(destinationLayer, goalCellNdx.x, goalCellNdx.y);

	Coord3D from = *obj->getPosition();
	ICoord2D startCellNdx;
	worldToCell(&from, &startCellNdx);
	PathfindLayerEnum layer = LAYER_GROUND;
	if (obj) {
		layer = obj->getLayer();
	}
	PathfindCell *parentCell = getClippedCell(layer, &from);
	if (parentCell == NULL) {
		return false;
	}

	Int zone1;
	Int zone2;
	Bool isCrusher = obj ? obj->getCrusherLevel() > 0 : false;
	zone1 = m_zoneManager.getEffectiveZone(locomotorSet.getValidSurfaces(), isCrusher,
	                                       parentCell->getZone());
	Bool isObstacle = false;
	if (parentCell->getType() == PathfindCell::CELL_OBSTACLE) {
		isObstacle = true;
	}
	if (isObstacle) {
		zone1 = m_zoneManager.getEffectiveTerrainZone(zone1);
		zone1 = m_zoneManager.getEffectiveZone(locomotorSet.getValidSurfaces(), isCrusher, zone1);
	}

	zone2 = m_zoneManager.getEffectiveZone(locomotorSet.getValidSurfaces(), isCrusher,
	                                      goalCell->getZone());
	if (zone1 == zone2) {
		if (checkDestination(obj, goalCellNdx.x, goalCellNdx.y, destinationLayer, radius, center)) {
			return true;
		}
	}

	enum { MAX_CELLS_TO_TRY = 400 };
	Int limit = MAX_CELLS_TO_TRY;
	Int i = goalCellNdx.x;
	Int j = goalCellNdx.y;
	Int delta = 1;
	Int count;
	while (limit > 0) {
		for (count = delta; count > 0; count--) {
			i++;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet, i, j,
			                    destinationLayer, dest, isObstacle) &&
			    checkDestination(obj, i, j, destinationLayer, radius, center)) {
				return true;
			}
		}
		for (count = delta; count > 0; count--) {
			j++;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet, i, j,
			                    destinationLayer, dest, isObstacle) &&
			    checkDestination(obj, i, j, destinationLayer, radius, center)) {
				return true;
			}
		}
		delta++;
		for (count = delta; count > 0; count--) {
			i--;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet, i, j,
			                    destinationLayer, dest, isObstacle) &&
			    checkDestination(obj, i, j, destinationLayer, radius, center)) {
				return true;
			}
		}
		for (count = delta; count > 0; count--) {
			j--;
			limit--;
			if (checkForPossible(isCrusher, zone1, center, locomotorSet, i, j,
			                    destinationLayer, dest, isObstacle) &&
			    checkDestination(obj, i, j, destinationLayer, radius, center)) {
				return true;
			}
		}
		delta++;
	}
	return false;
}

// ?updatePos@Pathfinder@@QAEXPAVObject@@PBUCoord3D@@@Z
// partial score=0.27 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
//
// Complete typed source candidate copied from the existing Pathfinder owner in
// Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp.  Identity is not guessed:
// full retail boundary is 0x003E9D80..0x003EA23D (1213 bytes), and four named
// callers (Object::setLayer, two OpenContain exits, and AIUpdateInterface's
// load post-process) establish the same Pathfinder::updatePos identity.  The
// corrected extent has 11 named callees and no unnamed targets.  The candidate
// is banked because the
// owning ZH-derived TU emits a different ABI/layout shape for BFME: retail
// begins with the inline Object flag test at +0x344 and the direct BFME field
// layout, while the probe emits a call-based isKindOf path and a different
// frame.  The probe also leaves releaseInfo/setPosUnit unresolved.
//
// This is evidence only; it is not a production source claim.

/** Updates the position cell for an AI unit. */
void Pathfinder::updatePos( Object *obj, const Coord3D *newPos )
{
	if (obj->isKindOf(KINDOF_IMMOBILE))
	{
		return;
	}
	if (!m_isMapReady)
		return;

	AIUpdateInterface *ai = obj->getAIUpdateInterface();
	if (!ai)
		return;
	volatile ObjectID objectID = obj->getID();

	ICoord2D curCell = *ai->getCurPathfindCell();
	if (!ai->isDoingGroundMovement())
	{
		if (curCell.x >= 0 && curCell.y >= 0)
			removePos(obj);
		return;
	}

	Bool centerInCell;
	Int radius;
	ICoord2D newCell;
	getRadiusAndCenter(obj, radius, centerInCell);
	Int numCellsAbove = radius;
	if (centerInCell)
		numCellsAbove++;
	if (centerInCell)
	{
		newCell.x = REAL_TO_INT_FLOOR(newPos->x / PATHFIND_CELL_SIZE_F);
		newCell.y = REAL_TO_INT_FLOOR(newPos->y / PATHFIND_CELL_SIZE_F);
	}
	else
	{
		newCell.x = REAL_TO_INT_FLOOR(0.5f + newPos->x / PATHFIND_CELL_SIZE_F);
		newCell.y = REAL_TO_INT_FLOOR(0.5f + newPos->y / PATHFIND_CELL_SIZE_F);
	}
	if (newCell.x == curCell.x && newCell.y == curCell.y)
		return;

	PathfindLayerEnum layer = obj->getLayer();
	Bool doGround = false;
	Bool doLayer = false;
	if (layer == LAYER_GROUND)
	{
		doGround = true;
	}
	else
	{
		doLayer = true;
		if (TheTerrainLogic->objectInteractsWithBridgeEnd(obj, layer))
			doGround = true;
	}

	ai->setCurPathfindCell(newCell);
	Int i, j;
	ICoord2D cellNdx;
	if (curCell.x >= 0 && curCell.y >= 0)
	{
		for (i = curCell.x - radius; i < curCell.x + numCellsAbove; ++i)
		{
			for (j = curCell.y - radius; j < curCell.y + numCellsAbove; ++j)
			{
				cellNdx.x = i;
				cellNdx.y = j;
				PathfindCell *cell = getCell(layer, i, j);
				if (cell && cell->getPosUnit() == objectID)
					cell->setPosUnit(INVALID_ID, cellNdx);
				if (layer != LAYER_GROUND)
				{
					cell = getCell(LAYER_GROUND, i, j);
					if (cell && cell->getPosUnit() == objectID)
						cell->setPosUnit(INVALID_ID, cellNdx);
				}
			}
		}
	}
	for (i = newCell.x - radius; i < newCell.x + numCellsAbove; ++i)
	{
		for (j = newCell.y - radius; j < newCell.y + numCellsAbove; ++j)
		{
			PathfindCell *cell;
			cellNdx.x = i;
			cellNdx.y = j;
			if (doLayer)
			{
				cell = getCell(layer, i, j);
				if (cell)
					cell->setPosUnit(objectID, cellNdx);
			}
			if (doGround)
			{
				cell = getCell(LAYER_GROUND, i, j);
				if (cell)
					cell->setPosUnit(objectID, cellNdx);
			}
		}
	}
}

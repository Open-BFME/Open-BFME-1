// ?d_003ec8c0@@YAXXZ
// partial score=0.35 date=2026-09-10
/*
 * Banked attempt for retail Pathfinder::findSafePath at 0x003EC8C0 (750 B).
 *
 * The retained Zero Hour source below is the semantic twin, but this body was
 * not a production conversion: the BFME image has a different Pathfinder
 * layout and a different open-cell walk.  The notes at the bottom preserve
 * the useful boundary/ABI evidence for the next converter.
 */

Path *Pathfinder::findSafePath(const Object *obj,
	const LocomotorSet &locomotorSet, const Coord3D *from,
	const Coord3D *repulsorPos1, const Coord3D *repulsorPos2,
	Real repulsorRadius)
{
	const Int MAX_CELLS = 2000;
	Bool centerInCell;
	Int radius;
	getRadiusAndCenter(obj, radius, centerInCell);
	Real repulsorDistSqr = repulsorRadius * repulsorRadius;
	Int cellCount = 0;
	Bool isHuman = true;
	if (obj && obj->getControllingPlayer() &&
		obj->getControllingPlayer()->getPlayerType() == PLAYER_COMPUTER)
		isHuman = false;

	m_zoneManager.setAllPassable();
	ICoord2D startCellNdx;
	worldToCell(obj->getPosition(), &startCellNdx);
	PathfindCell *parentCell = getClippedCell(obj->getLayer(),
		obj->getPosition());
	if (!parentCell || !obj->getAIUpdateInterface())
		return 0;
	if (!parentCell->allocateInfo(startCellNdx))
		return 0;
	parentCell->startPathfind(0);
	m_openList = parentCell;
	m_closedList = 0;

	Real farthestDistanceSqr = 0;
	while (m_openList != 0)
	{
		parentCell = m_openList;
		m_openList = parentCell->removeFromOpenList(m_openList);
		Coord3D cellCenter;
		adjustCoordToCell(parentCell->getXIndex(), parentCell->getYIndex(),
			centerInCell, cellCenter, parentCell->getLayer());
		Real dx = cellCenter.x - repulsorPos1->x;
		Real dy = cellCenter.y - repulsorPos1->y;
		Bool ok = false;
		Real distSqr = dx * dx + dy * dy;
		dx = cellCenter.x - repulsorPos2->x;
		dy = cellCenter.y - repulsorPos2->y;
		Real distSqr2 = dx * dx + dy * dy;
		if (distSqr2 < distSqr)
			distSqr = distSqr2;
		if (distSqr > repulsorDistSqr)
			ok = true;
		if (m_openList == 0 && cellCount > 0)
			ok = true;
		if (distSqr > farthestDistanceSqr)
		{
			farthestDistanceSqr = distSqr;
			if (cellCount > MAX_CELLS)
				ok = true;
		}
		if (ok && checkDestination(obj, parentCell->getXIndex(),
			parentCell->getYIndex(), parentCell->getLayer(), radius,
			centerInCell))
		{
			Path *path = buildActualPath(obj, locomotorSet.getValidSurfaces(),
				obj->getPosition(), parentCell, centerInCell, false);
			parentCell->releaseInfo();
			cleanOpenAndClosedLists();
			return path;
		}
		m_closedList = parentCell->putOnClosedList(m_closedList);
		checkChangeLayers(parentCell);
		cellCount += examineNeighboringCells(parentCell, 0, locomotorSet,
			isHuman, centerInCell, radius, startCellNdx, obj, NO_ATTACK);
	}

	*reinterpret_cast<unsigned char *>(reinterpret_cast<char *>(this) + 0x83C) = 0;
	cleanOpenAndClosedLists();
	return 0;
}

/*
 * Retail boundary/ABI evidence:
 *   0x003EC8C0, 750 bytes, ret 0x18; entry tests this+0x08.
 *   Direct fields are this+0x2470C/+0x24710 (12-byte vector), this+0xC9C
 *   (zone manager), this+0x0838 and this+0x083C (walk state).
 *   The body calls ILTs 0x0000DBE8 -> 0x003D7C90 (12-byte __copy),
 *   0x00010FA5 -> 0x00403140, 0x000171E8 -> 0x003D7EC0,
 *   0x0003A391 -> 0x001BEC20, 0x00020671 -> 0x003D4E80,
 *   0x0003D1A9 -> 0x003F6AD0, 0x00021DA0 -> 0x003D7DB0,
 *   0x0003E9F5 -> 0x003F6940, 0x00024EF1 -> 0x003D6400,
 *   0x0003D3ED -> 0x003D6490, 0x000411D2 -> 0x003D6040,
 *   0x00028844 -> 0x003D6440, 0x00049F3F -> 0x003DF580,
 *   0x00005E48 -> 0x003F6C30, 0x0001264D -> 0x003DAE40,
 *   0x000127A6 -> 0x003E6EE0, and 0x00032B5F -> 0x003D5FC0.
 * The source twin above emits the ZH linked-list algorithm, starts with
 * this+0x38, and has none of the BFME array-walk/vector operations; it is
 * therefore a complete failed candidate, not a production claim.
 */

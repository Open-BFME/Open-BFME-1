// ?d_0021daa0@@YAXXZ
// partial score=0.94 date=2026-09-09
// Partial clean C++ reconstruction for retail RVA 0x0021DAA0.
// The owner is GarrisonContain::xfer.  The surrounding source file carries
// the TU-local BFME Xfer ABI and field view used to compile this body.

void GarrisonContain::xfer(Xfer *xfer)
{
	BfmeGarrisonXferTarget *target =
		reinterpret_cast<BfmeGarrisonXferTarget *>(xfer);
	BfmeGarrisonXferView *self =
		reinterpret_cast<BfmeGarrisonXferView *>(this);
	Int i;

	OpenContain::xfer(xfer);
	if (target->isLightCRC())
		return;

	BfmeGarrisonXferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	target->xferVersion(&version);

	UnsignedInt teamID = self->m_originalTeam ? self->m_originalTeam->getID() : 0;
	target->xferUnsignedInt(&teamID);
	if (target->isLoading())
	{
		if (teamID)
		{
			self->m_originalTeam = reinterpret_cast<BfmeGarrisonXferTeamFactory *>(
				TheTeamFactory)->findTeamByID(teamID);
			if (self->m_originalTeam == NULL)
			{
				BfmeGarrisonXferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
			}
		}
		else
			self->m_originalTeam = NULL;
	}

	target->xferBool(&self->m_hideState);
	UnsignedShort pointDataCount = MAX_GARRISON_POINTS;
	target->xferUnsignedShort(&pointDataCount);
	i = 0;
	if (pointDataCount <= i)
		goto garrison_point_done;
	{
		UnsignedInt *point = &self->m_pointData[0].targetID;
		do
		{
			bfmeHandOver_0000C9B4(target, point - 1);
			bfmeHandOver_0000C9B4(target, point);
			target->xferUnsignedInt(point + 1);
			target->xferUnsignedInt(point + 2);
			bfmeHandOver_0000C9B4(target, point + 3);
			point += 5;
			++i;
		} while (i < pointDataCount);
	}
garrison_point_done:

	target->xferInt(&self->m_pointsInUse);
	for (i = 0; i < 3; ++i)
	{
		for (Int j = 0; j < MAX_GARRISON_POINTS; ++j)
			target->xferCoord3D(&self->m_points[i][j]);
	}
	target->xferBool(&self->m_pointsInitialized);
	target->xferBool(&self->m_rallyValid);
	target->xferCoord3D(&self->m_exitRallyPoint);
}

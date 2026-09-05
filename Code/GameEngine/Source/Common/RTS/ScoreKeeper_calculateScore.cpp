// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// ScoreKeeper::calculateScore at 0x000E8D90 (377B).
// GlobalData multipliers: docs/ini_schema.md ScoreKeeper_* at +0x1224..+0x1250.
// Callees: countMissionObjectives (ILT 0x00033E4C -> 0x000E8930),
//          getTimeTakenScore (ILT 0x00048437 -> 0x000E8A00).

typedef int Int;

class GlobalData
{
public:
	char m_pad[0x1224];
	Int m_unitsBuiltMultiplier;			// +0x1224 ScoreKeeper_UnitsBuiltMultiplier
	Int m_unitsDestroyedMultiplier;			// +0x1228
	Int m_structuresBuiltMultiplier;		// +0x122C
	Int m_structuresDestroyedMultiplier;		// +0x1230
	Int m_heroesVettedMultiplier;			// +0x1234
	Int m_unitsVettedMultiplier;			// +0x1238
	Int m_objectivesCompletedMultiplier;		// +0x123C
	Int m_suppliesCollectedMultiplier;		// +0x1240
	Int m_powerPointsMultiplier;			// +0x1244
	Int m_regionCommandPointsMultiplier;		// +0x1248
	Int m_regionResourcesMultiplier;		// +0x124C
	Int m_regionPowerPointsMultiplier;		// +0x1250
};

extern GlobalData *TheWritableGlobalData;

class ScoreKeeper
{
public:
	Int countMissionObjectives(Int *outTotal);
	Int getTimeTakenScore(void);
	Int calculateScore(void);

private:
	void *m_vtable;					// +0x00
	Int m_totalMoneyEarned;				// +0x04 supplies collected
	Int m_totalMoneySpent;				// +0x08
	Int m_totalUnitsDestroyed[32];			// +0x0C
	Int m_totalUnitsBuilt;				// +0x8C
	Int m_totalUnitsLost;				// +0x90
	Int m_totalBuildingsDestroyed[32];		// +0x94
	Int m_totalBuildingsBuilt;			// +0x114
	Int m_totalBuildingsLost;			// +0x118
	Int m_heroesVetted;				// +0x11C
	Int m_unitsVetted;				// +0x120
	Int m_powerPoints;				// +0x124
	Int m_pad128;					// +0x128
	Int m_regionCommandPoints;			// +0x12C
	Int m_regionResources;				// +0x130
	Int m_regionPowerPoints;			// +0x134
	Int m_currentScore;				// +0x138
	unsigned int m_frameOverride;			// +0x13C
	Int m_myPlayerIdx;				// +0x140
};

// ?calculateScore@ScoreKeeper@@QAEHXZ
Int ScoreKeeper::calculateScore(void)
{
	Int heroesMult = TheWritableGlobalData->m_heroesVettedMultiplier;
	Int score = m_powerPoints * TheWritableGlobalData->m_powerPointsMultiplier;
	score += m_unitsVetted * TheWritableGlobalData->m_unitsVettedMultiplier;
	score += m_heroesVetted * heroesMult;
	score += m_totalBuildingsBuilt * TheWritableGlobalData->m_structuresBuiltMultiplier;
	score += m_totalUnitsBuilt * TheWritableGlobalData->m_unitsBuiltMultiplier;
	score += m_totalMoneyEarned * TheWritableGlobalData->m_suppliesCollectedMultiplier;

	score += countMissionObjectives(0) * TheWritableGlobalData->m_objectivesCompletedMultiplier;
	GlobalData *gd = TheWritableGlobalData;
	score += getTimeTakenScore();

	for (Int i = 0; i < 32; ++i)
	{
		if (i == m_myPlayerIdx)
			continue;
		score += m_totalUnitsDestroyed[i] * gd->m_unitsDestroyedMultiplier;
		score += m_totalBuildingsDestroyed[i] * gd->m_structuresDestroyedMultiplier;
	}

	score += m_regionResources * gd->m_regionResourcesMultiplier;
	score += m_regionPowerPoints * gd->m_regionPowerPointsMultiplier;
	score += m_regionCommandPoints * gd->m_regionCommandPointsMultiplier;
	m_currentScore = score;
	return m_currentScore;
}

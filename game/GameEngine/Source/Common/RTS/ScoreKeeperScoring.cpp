// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// The ScoreKeeper score: what it is made of, and what it is then judged
// against.
//
//   0x000E8930  countMissionObjectives  106B  an input, and a victory test
//   0x000E8A00  getTimeTakenScore        87B  an input
//   0x000E8D90  calculateScore          377B  the sum
//   0x000E8F70  getVictoryType          118B  the verdict on the sum
//
// calculateScore calls the first two through ILT thunks (0x00033E4C and
// 0x00048437) and getVictoryType calls calculateScore and
// countMissionObjectives, so all four were already one call graph living in
// four files.
//
// What they were really hiding is a run of GlobalData. Three of the four
// declared their own GlobalData with a different padding prefix, each naming
// only the fields it read:
//
//   +0x1224 .. +0x1250  the twelve score multipliers   (calculateScore)
//   +0x1254 .. +0x125C  the three time-taken settings  (getTimeTakenScore)
//   +0x1260 .. +0x1268  the three victory thresholds   (getVictoryType)
//
// Those are not three regions. They are eighteen consecutive Ints, +0x1224
// through +0x1268 with no gap anywhere, and no single file could see that
// because each one padded over the other two. Declared once, the whole
// ScoreKeeper block of GlobalData is visible and the next body that reaches
// into it has somewhere to look.
//
// ScoreKeeper itself had drifted the ordinary way: the full member layout in
// calculateScore, the frame override alone at +0x13C in getTimeTakenScore --
// which agrees with it -- and no members at all in the other two.
//
// Note /Ob1: only functions marked inline are inlined, so putting these four
// definitions in one TU does not let the compiler inline the three that are
// called from here.

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
// The ScoreKeeper block, contiguous. INI names in docs/ini_schema.md.
class GlobalData
{
public:
	char m_pad[0x1224];
	Int m_unitsBuiltMultiplier;				// +0x1224 ScoreKeeper_UnitsBuiltMultiplier
	Int m_unitsDestroyedMultiplier;				// +0x1228
	Int m_structuresBuiltMultiplier;			// +0x122C
	Int m_structuresDestroyedMultiplier;			// +0x1230
	Int m_heroesVettedMultiplier;				// +0x1234
	Int m_unitsVettedMultiplier;				// +0x1238
	Int m_objectivesCompletedMultiplier;			// +0x123C
	Int m_suppliesCollectedMultiplier;			// +0x1240
	Int m_powerPointsMultiplier;				// +0x1244
	Int m_regionCommandPointsMultiplier;			// +0x1248
	Int m_regionResourcesMultiplier;			// +0x124C
	Int m_regionPowerPointsMultiplier;			// +0x1250
	Int m_timeTakenMultiplier;				// +0x1254
	Int m_timeTakenMaximumScore;				// +0x1258
	Int m_timeTakenMinimumScore;				// +0x125C
	Int m_totalVictoryRequiredScore;			// +0x1260
	Int m_normalVictoryRequiredScore;			// +0x1264
	Int m_normalVictoryRequiredObjectivesPercentage;	// +0x1268
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	char m_pad[0x3c];
	UnsignedInt m_frame;					// +0x3C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/CampaignManager.h
class CampaignManager
{
public:
	Int getMissionObjectiveCount(void);
	unsigned char isMissionObjectiveEligible(Int index);
	unsigned char isMissionObjectiveIndexed(Int index);
	unsigned char isMissionObjectiveComplete(Int index);
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
// countMissionObjectives loads 0x012F1028. GameEngine::init names that slot
// TheLivingWorldLogic (tag after TheLivingWorldCampaignManager at 0x012F1024).
// TheCampaignManager is the GameClient global at 0x012F4CB0. Type stays
// CampaignManager* so the four objective-query callees keep their pins.
extern CampaignManager *TheLivingWorldLogic;		///< retail 0x012F1028

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScoreKeeper.h
class ScoreKeeper
{
public:
	Int countMissionObjectives(Int *outTotal);
	Int getTimeTakenScore(void);
	Int calculateScore(void);
	Int getVictoryType(void);

private:
	void *m_vtable;						// +0x00
	Int m_totalMoneyEarned;					// +0x04 supplies collected
	Int m_totalMoneySpent;					// +0x08
	Int m_totalUnitsDestroyed[32];				// +0x0C
	Int m_totalUnitsBuilt;					// +0x8C
	Int m_totalUnitsLost;					// +0x90
	Int m_totalBuildingsDestroyed[32];			// +0x94
	Int m_totalBuildingsBuilt;				// +0x114
	Int m_totalBuildingsLost;				// +0x118
	Int m_heroesVetted;					// +0x11C
	Int m_unitsVetted;					// +0x120
	Int m_powerPoints;					// +0x124
	// The layout witness places m_totalBuildingsBuilt here, but its sole reset
	// witness is misaligned: retail calculateScore and reset both use +0x114
	// for that counter. Keep this address-derived name until +0x128 is proven.
	Int m_pad128;						// +0x128
	Int m_regionCommandPoints;				// +0x12C
	Int m_regionResources;					// +0x130
	Int m_regionPowerPoints;				// +0x134
	Int m_currentScore;					// +0x138
	UnsignedInt m_frameOverride;				// +0x13C
	Int m_myPlayerIdx;					// +0x140
};

// ?countMissionObjectives@ScoreKeeper@@QAEHPAH@Z
Int ScoreKeeper::countMissionObjectives(Int *outTotal)
{
	Int completed = 0;
	Int total = 0;
	CampaignManager *mgr = TheLivingWorldLogic;

	if (mgr)
	{
		Int n = mgr->getMissionObjectiveCount();
		Int i = 0;
		if (n > 0)
		{
			do
			{
				if (TheLivingWorldLogic->isMissionObjectiveEligible(i))
				{
					if (TheLivingWorldLogic->isMissionObjectiveIndexed(i))
					{
						++total;
						if (TheLivingWorldLogic->isMissionObjectiveComplete(i))
							++completed;
					}
				}
				++i;
			} while (i < n);
		}
	}

	if (outTotal)
		*outTotal = total;
	return completed;
}

// ?getTimeTakenScore@ScoreKeeper@@QAEHXZ
Int ScoreKeeper::getTimeTakenScore(void)
{
	UnsignedInt frames = m_frameOverride;
	Int score = TheWritableGlobalData->m_timeTakenMaximumScore;

	if (frames == 0)
		frames = TheGameLogic->m_frame;

	score += ((Int)(frames / 5U) / -60) * TheWritableGlobalData->m_timeTakenMultiplier;
	if (score < TheWritableGlobalData->m_timeTakenMinimumScore)
		score = TheWritableGlobalData->m_timeTakenMinimumScore;
	return score;
}

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

// ?getVictoryType@ScoreKeeper@@QAEHXZ
// 0 = none, 1 = normal victory, 2 = total victory.
Int ScoreKeeper::getVictoryType(void)
{
	Int score = calculateScore();
	Int total = 0;
	Int completed = countMissionObjectives(&total);
	GlobalData *gd = TheWritableGlobalData;
	Int tier = 2;

	if (score < gd->m_totalVictoryRequiredScore || completed < total)
		tier = 1;

	if (score < gd->m_normalVictoryRequiredScore)
		tier = 0;
	else if (completed < (gd->m_normalVictoryRequiredObjectivesPercentage * total) / 100)
		tier = 0;

	return tier;
}

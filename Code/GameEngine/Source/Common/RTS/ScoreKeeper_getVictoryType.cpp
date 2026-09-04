// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// ScoreKeeper::getVictoryType at 0x000E8F70 (118B).
// 0 = none, 1 = normal victory, 2 = total victory.

typedef int Int;

class GlobalData
{
public:
	char m_pad[0x1260];
	Int m_totalVictoryRequiredScore;			// +0x1260
	Int m_normalVictoryRequiredScore;			// +0x1264
	Int m_normalVictoryRequiredObjectivesPercentage;	// +0x1268
};

extern GlobalData *TheWritableGlobalData;

class ScoreKeeper
{
public:
	Int calculateScore(void);
	Int countMissionObjectives(Int *outTotal);
	Int getVictoryType(void);
};

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

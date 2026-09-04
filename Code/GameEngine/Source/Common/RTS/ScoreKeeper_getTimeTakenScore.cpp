// cl: /DNDEBUG /MD /Gy /O2 /Ob1
// ScoreKeeper time-taken score leaf at 0x000E8A00 (87B).

typedef int Int;
typedef unsigned int UnsignedInt;

class GlobalData
{
public:
	char m_pad[0x1254];
	Int m_timeTakenMultiplier;		// +0x1254
	Int m_timeTakenMaximumScore;	// +0x1258
	Int m_timeTakenMinimumScore;	// +0x125c
};

class GameLogic
{
public:
	char m_pad[0x3c];
	UnsignedInt m_frame;			// +0x3c
};

extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

class ScoreKeeper
{
public:
	Int getTimeTakenScore(void);

private:
	char m_pad0[0x13c];
	UnsignedInt m_frameOverride;	// +0x13c
};

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

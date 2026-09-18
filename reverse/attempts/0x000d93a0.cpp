// ?addSkillPoints@Player@@QAE_NM_N@Z
// partial score=0.85 date=2026-09-17
// cl: /DNDEBUG /MD /EHsc
// BFME's floating-point skill-point update at retail RVA 0x000D93A0.

typedef int Int;
typedef float Real;
typedef bool Bool;

class AsciiString
{
private:
	void *m_data;
};

class GameLogic
{
public:
	Bool _bfme_isInLivingWorldCampaign();
};

class RankInfo
{
public:
	Int getSkillPointsNeeded(const AsciiString &side) const;
};

class RankInfoStore
{
public:
	const RankInfo *getRankInfo(Int level) const;
};

struct SkillPointMultipliers
{
	Real *begin;
	Real *end;

	__forceinline Int size() const
	{
		return (Int)(end - begin);
	}

	__forceinline Real *beginPtr() const
	{
		return begin;
	}
};

struct BfmePlayerSkillFields
{
	char m_beforeRank[0x258];
	Int m_rankLevel;
	Real m_skillPoints;
	Int m_unused260;
	Int m_unused264;
	Int m_levelUp;
	char m_beforeCampaignData[0x430];
	SkillPointMultipliers *m_campaignMultipliers;
	Int m_campaignRankBase;
};

class Player
{
public:
	Int getRankLevelCap();
	Bool setRankLevel(Int level);
	Bool addSkillPoints(Real delta, Bool fromScript);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)
#define TheRankInfoStore (*(RankInfoStore **)0x012F1014)
#define BfmeZeroRange (*(const Real *)0x01075350)

extern "C" __declspec(dllimport) double BfmeFloorER(double value);

Bool Player::addSkillPoints(Real delta, Bool fromScript)
{
	BfmePlayerSkillFields *state = (BfmePlayerSkillFields *)this;
	Real adjustedDelta;
	volatile Real newSkillPoints;
	Int pointCap;
	Int points;
	adjustedDelta = delta * *(Real *)((char *)this + 0x298);

	if (fromScript)
	{
		if (!TheBfmeGameLogic->_bfme_isInLivingWorldCampaign())
			return false;

		SkillPointMultipliers *multipliers;
		Real *end;
		Real *begin;
		Int count;
		Int index;
		multipliers = state->m_campaignMultipliers;
		end = multipliers->end;
		begin = multipliers->begin;
		count = (Int)(end - begin);
		index = state->m_rankLevel - state->m_campaignRankBase;
		if (index < count)
			--index;
		else
			index = count - 1;
		if (index < 0)
			return false;

		adjustedDelta *= multipliers->beginPtr()[index];
	}

	Int levelCap = getRankLevelCap();
	const RankInfo *rank = TheRankInfoStore->getRankInfo(levelCap);
	pointCap = rank->getSkillPointsNeeded(
		*(const AsciiString *)((const char *)this + 0x28));
	newSkillPoints = state->m_skillPoints + adjustedDelta;
	if (newSkillPoints < (Real)pointCap)
		newSkillPoints = (Real)pointCap;
	state->m_skillPoints = newSkillPoints;

	points = (Int)(Real)BfmeFloorER((double)newSkillPoints);
	Bool levelGained = false;
	while (points >= state->m_levelUp)
	{
		Bool changed = setRankLevel(state->m_rankLevel + 1);
		levelGained |= changed;
		if (!changed)
			return levelGained;
	}
	return levelGained;
}

#undef TheBfmeGameLogic
#undef TheRankInfoStore
#undef BfmeZeroRange

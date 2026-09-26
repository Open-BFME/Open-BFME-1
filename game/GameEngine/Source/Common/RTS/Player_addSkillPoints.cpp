// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME Player::addSkillPoints at retail RVA 0x000D93A0.

typedef int Int;
typedef float Real;
typedef bool Bool;

#include "ascii_string.h"

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

namespace _STL
{
template <class Type>
class vector
{
public:
	Type *begin()
	{
		return m_start;
	}

	Type *end()
	{
		return m_finish;
	}

	Int size() const
	{
		return (Int)(m_finish - m_start);
	}

private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};
}

typedef _STL::vector<Real> SkillPointMultipliers;

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

	__forceinline SkillPointMultipliers *campaignMultipliers()
	{
		return m_campaignMultipliers;
	}
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

__forceinline Int bfmeFloatToInt(Real input)
{
	Int result;
	__asm
	{
		fld [input]
		fistp [result]
	}
	return result;
}

__forceinline const Real &bfmeMax(const Real &left, const Real &right)
{
	return left < right ? left : right;
}

Bool Player::addSkillPoints(Real delta, Bool fromScript)
{
	BfmePlayerSkillFields *state = (BfmePlayerSkillFields *)this;
	Real adjustedDelta;
	Real newSkillPoints;
	Real pointCapReal;
	Int pointCap;
	Int points;
	adjustedDelta = delta * *(Real *)((char *)this + 0x298);

	if (fromScript)
	{
		if (TheBfmeGameLogic->_bfme_isInLivingWorldCampaign())
		{
			Int count = state->campaignMultipliers()->size();
			Int index = state->m_rankLevel - state->m_campaignRankBase;
			if (index >= count)
				index = state->campaignMultipliers()->size() - 1;

			if (index >= 0)
				adjustedDelta *= state->campaignMultipliers()->begin()[index];
		}
	}
	if (adjustedDelta == BfmeZeroRange)
		return false;

	Int levelCap = getRankLevelCap();
	pointCap = TheRankInfoStore->getRankInfo(levelCap)
		->getSkillPointsNeeded(*(const AsciiString *)((const char *)this + 0x28));
	Bool levelGained = false;
	newSkillPoints = state->m_skillPoints + adjustedDelta;
	pointCapReal = (Real)pointCap;
	newSkillPoints = bfmeMax(pointCapReal, newSkillPoints);
	state->m_skillPoints = newSkillPoints;

	Real floorSkillPoints = (Real)BfmeFloorER((double)newSkillPoints);
	points = bfmeFloatToInt(floorSkillPoints);
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

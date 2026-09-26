// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME Player::setRankLevel at retail RVA 0x000D7E30.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum ScienceType {};

#include "ascii_string.h"

struct ScienceRange
{
	ScienceType *begin;
	ScienceType *end;
	ScienceType *capacity;
};

class RankInfo
{
public:
	Int getSkillPointsNeeded(const AsciiString &side) const;

	char m_prefix[0x28];
	Int m_sciencePurchasePointsGranted;
	ScienceRange m_sciencesGranted;
};

class RankInfoStore
{
public:
	const RankInfo *getRankInfo(Int level) const;
	Int getRankLevelCount() const;
};

class Player;

struct Coord3D
{
};

class ControlBar
{
public:
	void onPlayerRankChanged(const Player *player);
	void onPlayerSciencePurchasePointsChanged(Player *player);
};

struct BfmePlayerList
{
	char m_prefix[0x0c];
	Player *m_localPlayer;
};

enum EvaMessage
{
	EVA_GENERAL_LEVEL_UP = 4
};

class Eva
{
public:
	Bool setShouldPlay(EvaMessage message, const Coord3D *position);
};

class BfmeAcademyPointRecorder
{
public:
	void _bfme_recordPointsEarned(Int points);
};

extern RankInfoStore *TheRankInfoStore;
extern ControlBar *TheControlBar;
extern Eva *TheEva;
extern BfmePlayerList *Rva002EE330ThePlayers;
extern "C" __declspec(dllimport) double BfmeFloorER(double value);

__forceinline long fast_float2long_round(Real input)
{
	long result;
	__asm
	{
		fld [input]
		fistp [result]
	}
	return result;
}

struct BfmePlayerRankFields
{
	char m_prefix[0x28];
	AsciiString m_side;
	char m_beforeSciences[0x208];
	char m_sciences[0x24];
	Int m_rankLevel;
	Real m_skillPoints;
	Int m_retailPadding;
	Int m_sciencePurchasePoints;
	Int m_levelUp;
	Int m_levelDown;
	char m_beforePointRecorder[0xd8];
	BfmeAcademyPointRecorder m_pointRecorder;
};

class Player
{
public:
	Int getRankLevelCap();
	Bool setRankLevel(Int newLevel);
	void resetRank();

private:
	Bool addScience(ScienceType science);
};

Bool Player::setRankLevel(Int newLevel)
{
	BfmePlayerRankFields *state = (BfmePlayerRankFields *)this;

	if (newLevel < 1)
		newLevel = 1;
	else if (newLevel > TheRankInfoStore->getRankLevelCount())
		newLevel = TheRankInfoStore->getRankLevelCount();

	Int rankLevelCap = getRankLevelCap();
	if (newLevel > rankLevelCap)
		newLevel = rankLevelCap;

	if (newLevel == state->m_rankLevel)
		return false;

	Int oldSPP = state->m_sciencePurchasePoints;
	if (newLevel < state->m_rankLevel)
		resetRank();

	for (Int level = state->m_rankLevel + 1; level <= newLevel; ++level)
	{
		const RankInfo *rank = TheRankInfoStore->getRankInfo(level);
		if (rank)
		{
			Int skillPointsNeeded = rank->getSkillPointsNeeded(state->m_side);
			state->m_sciencePurchasePoints += rank->m_sciencePurchasePointsGranted;
			state->m_pointRecorder._bfme_recordPointsEarned(
				rank->m_sciencePurchasePointsGranted);
			if (state->m_sciencePurchasePoints < 0)
				state->m_sciencePurchasePoints = 0;

			Real currentSkillPoints = (Real)BfmeFloorER(state->m_skillPoints);
			if (fast_float2long_round(currentSkillPoints) < skillPointsNeeded)
				state->m_skillPoints = (Real)skillPointsNeeded;

			for (ScienceType *science = rank->m_sciencesGranted.begin;
				science != rank->m_sciencesGranted.end; ++science)
			{
				addScience(*science);
			}

			state->m_levelDown = skillPointsNeeded;
		}
	}

	const RankInfo *nextRank = TheRankInfoStore->getRankInfo(newLevel + 1);
	state->m_levelUp = nextRank
		? nextRank->getSkillPointsNeeded(state->m_side)
		: 0x7fffffff;
	state->m_rankLevel = newLevel;

	if (TheControlBar)
	{
		if (state->m_levelUp && this == Rva002EE330ThePlayers->m_localPlayer)
			TheEva->setShouldPlay(EVA_GENERAL_LEVEL_UP, 0);

		TheControlBar->onPlayerRankChanged(this);
		if (oldSPP != state->m_sciencePurchasePoints)
			TheControlBar->onPlayerSciencePurchasePointsChanged(this);
	}

	return true;
}

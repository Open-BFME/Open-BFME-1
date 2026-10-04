// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ?_bfme_updateSkirmishBattleHonors@@YAXPAVPlayer@@@Z
// Retail 0x000A41F0, 1932 bytes.  Identity: the score-screen row helper
// BfmeAptScreenScoreScreen::Rva00576C20 calls it at 0x00576ECC with the local
// Player* when its game type (+0x25C) is skirmish; the body is the BFME
// per-side form of the skirmish block in Zero Hour ScoreScreen.cpp
// populatePlayerInfo (see ScoreScreen_populatePlayerInfo.cpp for the same
// statements matched inside BFME's populatePlayerInfo at 0x004E5DF0).

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#define TRUE true
#define FALSE false

enum { MAX_SLOTS = 8 };

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

template <class T> inline const T &max(const T &a, const T &b) { return a > b ? a : b; }

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }

private:
	char m_unmodelled_00[8];
	AsciiString m_side;
};

class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }
	Bool isPlayerActive() const;

private:
	void *m_vtable;
	const PlayerTemplate *m_playerTemplate;
};

class GameSlot
{
public:
	SlotState getState() const { return m_state; }
	Int getTeamNumber() const { return m_teamNumber; }
	Bool isOccupied() const;
	Bool isAI() const;

private:
	void *m_unmodelled_00;
	SlotState m_state;
	char m_unmodelled_08[0x10];
	Int m_teamNumber;
};

class GameInfo
{
public:
	virtual void rvaSlot00() = 0;
	virtual void rvaSlot04() = 0;
	virtual void rvaSlot08() = 0;
	virtual void rvaSlot0C() = 0;
	virtual void rvaSlot10() = 0;
	virtual Int getLocalSlotNum() = 0;
	virtual void rvaSlot18() = 0;
	virtual void rvaSlot1C() = 0;
	virtual void rvaSlot20() = 0;
	virtual void rvaSlot24() = 0;
	virtual void rvaSlot28() = 0;
	virtual void rvaSlot2C() = 0;
	virtual Bool isSandbox() = 0;
	const GameSlot *getConstSlot(Int slotNum) const;
	Int _bfme_getMapIsOfficial() const;
};

class VictoryConditionsInterface
{
public:
	virtual void rvaSlot00() = 0;
	virtual void rvaSlot04() = 0;
	virtual void rvaSlot08() = 0;
	virtual void rvaSlot0C() = 0;
	virtual void rvaSlot10() = 0;
	virtual void rvaSlot14() = 0;
	virtual void rvaSlot18() = 0;
	virtual void rvaSlot1C() = 0;
	virtual void rvaSlot20() = 0;
	virtual void rvaSlot24() = 0;
	virtual void rvaSlot28() = 0;
	virtual void rvaSlot2C() = 0;
	virtual void rvaSlot30() = 0;
	virtual Bool isLocalAlliedVictory() = 0;
	virtual Bool isLocalAlliedDefeat() = 0;
	virtual Bool isLocalDefeat() = 0;
	virtual Bool amIObserver() = 0;
	virtual UnsignedInt getEndFrame() = 0;
};

class SkirmishPreferences
{
public:
	SkirmishPreferences();
	virtual ~SkirmishPreferences();
	UnicodeString getUserName();

private:
	char m_unmodelled_04[0x14];
};

class SkirmishBattleHonors
{
public:
	SkirmishBattleHonors(UnicodeString userName);
	virtual ~SkirmishBattleHonors();
	virtual Bool write();

	Real getTimePlayed(AsciiString side) const;
	void setTimePlayed(AsciiString side, Real val);
	Int getPoints(AsciiString side) const;
	void setPoints(AsciiString side, Int val);
	Int getWins(AsciiString side) const;
	void setWins(AsciiString side, Int val);
	Int getLosses(AsciiString side) const;
	void setLosses(AsciiString side, Int val);
	Int getWinStreak(AsciiString side) const;
	void setWinStreak(AsciiString side, Int val);
	Int getBestWinStreak(AsciiString side) const;
	void setBestWinStreak(AsciiString side, Int val);
	Int getLossStreak(AsciiString side) const;
	void setLossStreak(AsciiString side, Int val);
	Int getWorstLossStreak(AsciiString side) const;
	void setWorstLossStreak(AsciiString side, Int val);
	Int getOverallWinStreak() const;
	void setOverallWinStreak(Int val);
	Int getOverallBestWinStreak() const;
	void setOverallBestWinStreak(Int val);
	Int getOverallLossStreak() const;
	void setOverallLossStreak(Int val);
	Int getOverallWorstLossStreak() const;
	void setOverallWorstLossStreak(Int val);
	AsciiString getLastGeneral() const;
	void setLastGeneral(AsciiString val);
	Int getNumGamesLoyal() const;
	void setNumGamesLoyal(Int val);

private:
	char m_unmodelled_04[0x38];
};

// The "FavoriteSide" preference accessors are matched under address-derived
// owners (Open2Twins002.cpp); both are UserPreferences members on the same
// object, so the honors object is viewed through them.
class Open2Pref09D260
{
public:
	AsciiString fetch() const;
};

class Open2Pref09D1C0
{
public:
	void store(AsciiString value);
};

extern GameInfo *TheGameInfo;
extern VictoryConditionsInterface *TheVictoryConditions;

// BFME endurance-medal update (StatsReporter.cpp).
void bfmeRva000A3820(SkirmishBattleHonors &stats);

static Bool isSlotLocalAlly(GameInfo *game, const GameSlot *slot)
{
	const GameSlot *localSlot = game->getConstSlot(game->getLocalSlotNum());
	if (!localSlot)
		return TRUE;

	if (slot == localSlot)
		return TRUE;

	if (slot->getTeamNumber() < 0)
		return FALSE;

	return slot->getTeamNumber() == localSlot->getTeamNumber();
}

void _bfme_updateSkirmishBattleHonors(Player *player)
{
	if (TheGameInfo->isSandbox() || !(TheVictoryConditions->isLocalAlliedDefeat() || TheVictoryConditions->isLocalAlliedVictory()))
	{
		if (player->isPlayerActive())
			return;
	}

	SkirmishPreferences prefs;
	SkirmishBattleHonors stats(prefs.getUserName());
	AsciiString side = player->getPlayerTemplate()->getSide();
	Real duration = TheVictoryConditions->getEndFrame() * (1.0f / 5.0f);
	stats.setTimePlayed(side, stats.getTimePlayed(side) + duration);

	if (TheVictoryConditions->isLocalAlliedVictory())
	{
		Bool anyEasy = FALSE;
		Bool anyMedium = FALSE;
		Bool anyBrutal = FALSE;
		Int numBrutal = 0;
		Bool anyAlliedAI = FALSE;
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			const GameSlot *slot = TheGameInfo->getConstSlot(i);
			SlotState state = slot->getState();
			if (slot->isAI() && !isSlotLocalAlly(TheGameInfo, slot))
			{
				if (slot->isOccupied() && state == SLOT_EASY_AI)
					anyEasy = TRUE;
				if (slot->isOccupied() && state == SLOT_MED_AI)
					anyMedium = TRUE;
				if (slot->isOccupied() && state == SLOT_BRUTAL_AI)
				{
					anyBrutal = TRUE;
					++numBrutal;
				}
			}
			else if (slot->isAI())
			{
				anyAlliedAI = TRUE;
			}
		}

		if (!anyAlliedAI)
		{
			if (TheGameInfo->_bfme_getMapIsOfficial() - 1 == numBrutal)
				stats.setPoints(side, stats.getPoints(side) + 4);
			else if (anyBrutal)
				stats.setPoints(side, stats.getPoints(side) + 3);
			else if (anyMedium)
				stats.setPoints(side, stats.getPoints(side) + 2);
			else if (anyEasy)
				stats.setPoints(side, stats.getPoints(side) + 1);
		}

		stats.setWins(side, stats.getWins(side) + 1);
		stats.setWinStreak(side, stats.getWinStreak(side) + 1);
		stats.setBestWinStreak(side, max(stats.getBestWinStreak(side), stats.getWinStreak(side)));
		stats.setOverallWinStreak(stats.getOverallWinStreak() + 1);
		stats.setOverallBestWinStreak(max(stats.getOverallBestWinStreak(), stats.getOverallWinStreak()));
		stats.setLossStreak(side, 0);
		stats.setOverallLossStreak(0);
		bfmeRva000A3820(stats);
	}
	else
	{
		stats.setLosses(side, stats.getLosses(side) + 1);
		stats.setLossStreak(side, stats.getLossStreak(side) + 1);
		stats.setWorstLossStreak(side, max(stats.getWorstLossStreak(side), stats.getLossStreak(side)));
		stats.setOverallLossStreak(stats.getOverallLossStreak() + 1);
		stats.setOverallWorstLossStreak(max(stats.getOverallWorstLossStreak(), stats.getOverallLossStreak()));
		stats.setWinStreak(side, 0);
		stats.setOverallWinStreak(0);
	}

	AsciiString favorite = ((const Open2Pref09D260 &)stats).fetch();
	if (favorite.compare(AsciiString::TheEmptyString) == 0)
	{
		((Open2Pref09D1C0 &)stats).store(side);
	}
	else
	{
		Int oldGames = stats.getWins(favorite) + stats.getLosses(favorite);
		Int newGames = stats.getWins(side) + stats.getLosses(side);
		if (newGames > oldGames)
			((Open2Pref09D1C0 &)stats).store(side);
	}

	AsciiString lastGeneral = stats.getLastGeneral();
	stats.setLastGeneral(player->getPlayerTemplate()->getSide());
	if (lastGeneral.compare(stats.getLastGeneral()) != 0)
		stats.setNumGamesLoyal(0);
	else
		stats.setNumGamesLoyal(stats.getNumGamesLoyal() + 1);

	stats.write();
}

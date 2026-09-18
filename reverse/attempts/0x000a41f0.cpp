// ?_bfme_updateSkirmishBattleHonors@@YAXPAVPlayer@@@Z
// partial score=0.34 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME score-screen update helper at retail 0x000A41F0.  The caller at
// 0x00576ECC passes a Player* cdecl-style and the body constructs the BFME
// preferences and per-user honors objects before updating the side-keyed
// counters.  The small member-pointer adapters below deliberately refer to
// the retail ILT names printed by tools/callees.py; they are not guesses at
// new callee identities.

typedef int Int;
typedef float Real;
typedef bool Bool;

#define TRUE 1
#define FALSE 0

class BFMERetailAsciiString
{
protected:
	void *m_data;
	void releaseBuffer();

	BFMERetailAsciiString(void) : m_data(0) {}
};

// The retail GameSpyGroupRoom copy body is the ICF'd by-value string-copy
// helper used throughout this function.  Its first dword is the shared string
// data pointer; length is the unsigned-short at +4 and text starts at +8.
class GameSpyGroupRoom : private BFMERetailAsciiString
{
public:
	GameSpyGroupRoom(void) : BFMERetailAsciiString() {}
	GameSpyGroupRoom(const GameSpyGroupRoom &other);

	~GameSpyGroupRoom(void)
	{
		releaseBuffer();
	}

	Bool operator==(const GameSpyGroupRoom &other) const
	{
		const unsigned char *left = m_data ? (const unsigned char *)m_data + 8 :
			(const unsigned char *)0x0107388B;
		const unsigned char *right = other.m_data ?
			(const unsigned char *)other.m_data + 8 :
			(const unsigned char *)0x0107388B;
		Int leftLength = m_data ? *(const unsigned short *)((const char *)m_data + 4) : 0;
		Int rightLength = other.m_data ?
			*(const unsigned short *)((const char *)other.m_data + 4) : 0;
		Int length = leftLength < rightLength ? leftLength : rightLength;
		for (Int i = 0; i < length; ++i)
		{
			if (left[i] != right[i])
				return FALSE;
		}
		return leftLength == rightLength;
	}

	Bool operator!=(const GameSpyGroupRoom &other) const
	{
		return !(*this == other);
	}
};

extern void j_000016fe(void);
extern void j_000017d0(void);
extern void j_0000387d(void);
extern void j_000040f7(void);
extern void j_00008602(void);
extern void j_0000939f(void);
extern void j_000095ca(void);
extern void j_0000f4d4(void);
extern void j_00010898(void);
extern void j_00014754(void);
extern void j_000149e3(void);
extern void j_0001532a(void);
extern void j_00016950(void);
extern void j_00016bd0(void);
extern void j_000179bd(void);
extern void j_0001aff5(void);
extern void j_0001b720(void);
extern void j_0001ce18(void);
extern void j_00022273(void);
extern void j_000222e1(void);
extern void j_00023d53(void);
extern void j_0002681e(void);
extern void j_00026a30(void);
extern void j_00027a3e(void);
extern void j_00029460(void);
extern void j_0002eed3(void);
extern void j_0003314f(void);
extern void j_00039eaf(void);
extern void j_0003a6cf(void);
extern void j_0003f472(void);
extern void j_0003f6d4(void);
extern void j_00040192(void);
extern void j_00040593(void);
extern void j_00041510(void);
extern void j_000422df(void);
extern void j_00043d8d(void);
extern void j_000454ad(void);
extern void j_00045656(void);
extern void j_00046b82(void);
extern void j_00047767(void);
extern void j_00048d6f(void);
extern void j_0004af9d(void);

class SkirmishPreferences
{
public:
	SkirmishPreferences(void)
	{
		union
		{
			void (*raw)(void);
			void (SkirmishPreferences::*member)(void);
		} call;
		call.raw = j_00047767;
		(this->*call.member)();
	}

	~SkirmishPreferences(void)
	{
		union
		{
			void (*raw)(void);
			void (SkirmishPreferences::*member)(void);
		} call;
		call.raw = j_00046b82;
		(this->*call.member)();
	}

	GameSpyGroupRoom getUserName(void)
	{
		union
		{
			void (*raw)(void);
			GameSpyGroupRoom (SkirmishPreferences::*member)(void);
		} call;
		call.raw = j_00010898;
		return (this->*call.member)();
	}

	char m_unmodelled[0x1c];
};

class SkirmishBattleHonors
{
public:
	SkirmishBattleHonors(GameSpyGroupRoom userName)
	{
		union
		{
			void (*raw)(void);
			void (SkirmishBattleHonors::*member)(GameSpyGroupRoom);
		} call;
		call.raw = j_00008602;
		(this->*call.member)(userName);
	}

	~SkirmishBattleHonors(void)
	{
		union
		{
			void (*raw)(void);
			void (SkirmishBattleHonors::*member)(void);
		} call;
		call.raw = j_0003f6d4;
		(this->*call.member)();
	}

#define BFME_STATS_GET_REAL(name, thunk) \
	Real name(GameSpyGroupRoom key) const \
	{ \
		union { void (*raw)(void); Real (SkirmishBattleHonors::*member)(GameSpyGroupRoom) const; } call; \
		call.raw = thunk; \
		return (this->*call.member)(key); \
	}

#define BFME_STATS_SET_REAL(name, thunk) \
	void name(GameSpyGroupRoom key, Real value) \
	{ \
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(GameSpyGroupRoom, Real); } call; \
		call.raw = thunk; \
		(this->*call.member)(key, value); \
	}

#define BFME_STATS_GET_INT(name, thunk) \
	Int name(GameSpyGroupRoom key) const \
	{ \
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(GameSpyGroupRoom) const; } call; \
		call.raw = thunk; \
		return (this->*call.member)(key); \
	}

#define BFME_STATS_SET_INT(name, thunk) \
	void name(GameSpyGroupRoom key, Int value) \
	{ \
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(GameSpyGroupRoom, Int); } call; \
		call.raw = thunk; \
		(this->*call.member)(key, value); \
	}

	BFME_STATS_SET_REAL(setTimePlayed, j_00043d8d)
	BFME_STATS_GET_REAL(getTimePlayed, j_00023d53)
	BFME_STATS_SET_INT(setPoints, j_00039eaf)
	BFME_STATS_GET_INT(getPoints, j_00041510)
	BFME_STATS_SET_INT(setWins, j_00016950)
	BFME_STATS_GET_INT(getWins, j_00040192)
	BFME_STATS_SET_INT(setLosses, j_00026a30)
	BFME_STATS_GET_INT(getLosses, j_0001ce18)
	BFME_STATS_SET_INT(setWinStreak, j_00027a3e)
	BFME_STATS_GET_INT(getWinStreak, j_00022273)
	BFME_STATS_SET_INT(setLossStreak, j_00014754)
	BFME_STATS_GET_INT(getLossStreak, j_000095ca)
	BFME_STATS_SET_INT(setBestWinStreak, j_0000939f)
	BFME_STATS_GET_INT(getBestWinStreak, j_0003f472)
	BFME_STATS_SET_INT(setWorstLossStreak, j_0001aff5)
	BFME_STATS_GET_INT(getWorstLossStreak, j_0003a6cf)

	void setOverallWinStreak(Int value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(Int); } call;
		call.raw = j_000040f7;
		(this->*call.member)(value);
	}

	Int getOverallWinStreak(void) const
	{
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_000222e1;
		return (this->*call.member)();
	}

	void setOverallBestWinStreak(Int value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(Int); } call;
		call.raw = j_0002681e;
		(this->*call.member)(value);
	}

	Int getOverallBestWinStreak(void) const
	{
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_000454ad;
		return (this->*call.member)();
	}

	void setOverallLossStreak(Int value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(Int); } call;
		call.raw = j_00048d6f;
		(this->*call.member)(value);
	}

	Int getOverallLossStreak(void) const
	{
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_0004af9d;
		return (this->*call.member)();
	}

	void setOverallWorstLossStreak(Int value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(Int); } call;
		call.raw = j_0002eed3;
		(this->*call.member)(value);
	}

	Int getOverallWorstLossStreak(void) const
	{
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_0003314f;
		return (this->*call.member)();
	}

	GameSpyGroupRoom getLastGeneral(void) const
	{
		union { void (*raw)(void); GameSpyGroupRoom (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_000017d0;
		return (this->*call.member)();
	}

	void setLastGeneral(GameSpyGroupRoom value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(GameSpyGroupRoom); } call;
		call.raw = j_00016bd0;
		(this->*call.member)(value);
	}

	GameSpyGroupRoom fetchFavorite(void) const
	{
		union { void (*raw)(void); GameSpyGroupRoom (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_0000f4d4;
		return (this->*call.member)();
	}

	void storeFavorite(GameSpyGroupRoom value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(GameSpyGroupRoom); } call;
		call.raw = j_00045656;
		(this->*call.member)(value);
	}

	Int getNumGamesLoyal(void) const
	{
		union { void (*raw)(void); Int (SkirmishBattleHonors::*member)(void) const; } call;
		call.raw = j_000149e3;
		return (this->*call.member)();
	}

	void setNumGamesLoyal(Int value)
	{
		union { void (*raw)(void); void (SkirmishBattleHonors::*member)(Int); } call;
		call.raw = j_0001532a;
		(this->*call.member)(value);
	}

	Bool write(void)
	{
		union { void (*raw)(void); Bool (SkirmishBattleHonors::*member)(void); } call;
		call.raw = j_000016fe;
		return (this->*call.member)();
	}

	char m_unmodelled[0x40];
};

class GameSlot
{
public:
	void *m_unmodelled_00;
	Int m_state;
	char m_unmodelled_08[0x10];
	Int m_teamNumber;
};

class GameInfo
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual Int getLocalSlotNum(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual Bool slot30(void) = 0;

	Int mapIsOfficial(void) const
	{
		union { void (*raw)(void); Int (GameInfo::*member)(void) const; } call;
		call.raw = j_0001b720;
		return (this->*call.member)();
	}
};

class VictoryConditions
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(void) = 0;
	virtual Bool localVictory(void) = 0;
	virtual Bool localDefeat(void) = 0;
	virtual void slot3c(void) = 0;
	virtual void slot40(void) = 0;
	virtual Int getEndFrame(void) = 0;
};

class PlayerTemplate
{
public:
	char m_unmodelled[8];
	GameSpyGroupRoom m_side;
};

class Player
{
public:
	void *m_vtable;
	PlayerTemplate *m_playerTemplate;

	Bool isPlayerActive(void) const
	{
		union { void (*raw)(void); Bool (Player::*member)(void) const; } call;
		call.raw = j_000179bd;
		return (this->*call.member)();
	}
};

static __forceinline GameInfo *bfmeTheGameInfo(void)
{
	return *(GameInfo **)0x012F708C;
}

static __forceinline VictoryConditions *bfmeTheVictoryConditions(void)
{
	return *(VictoryConditions **)0x012F079C;
}

static __forceinline GameSlot *bfmeGetConstSlot(GameInfo *game, Int slot)
{
	union
	{
		void (*raw)(void);
		GameSlot *(GameInfo::*member)(Int) const;
	} call;
	call.raw = j_00029460;
	return (game->*call.member)(slot);
}

static __forceinline Bool bfmeSlotIsAI(const GameSlot *slot)
{
	union { void (*raw)(void); Bool (GameSlot::*member)(void) const; } call;
	call.raw = j_000422df;
	return (slot->*call.member)();
}

static __forceinline Bool bfmeSlotIsOccupied(const GameSlot *slot)
{
	union { void (*raw)(void); Bool (GameSlot::*member)(void) const; } call;
	call.raw = j_00040593;
	return (slot->*call.member)();
}

static __forceinline void bfmeUpdateEndurance(SkirmishBattleHonors *stats)
{
	typedef void (__cdecl *Call)(SkirmishBattleHonors *);
	union { void (*raw)(void); Call typed; } call;
	call.raw = j_0000387d;
	call.typed(stats);
}

static Bool bfmeIsSlotLocalAlly(GameInfo *game, const GameSlot *slot)
{
	const GameSlot *localSlot = bfmeGetConstSlot(game, game->getLocalSlotNum());
	if (!localSlot)
		return TRUE;
	if (slot == localSlot)
		return TRUE;
	if (slot->m_teamNumber < 0)
		return FALSE;
	return slot->m_teamNumber == localSlot->m_teamNumber;
}

// ?_bfme_updateSkirmishBattleHonors@@YAXPAVPlayer@@@Z
void _bfme_updateSkirmishBattleHonors(Player *player)
{
	if (!bfmeTheGameInfo()->slot30())
	{
		if (!bfmeTheVictoryConditions()->localDefeat() &&
			!bfmeTheVictoryConditions()->localVictory() &&
			(*(Player * volatile *)&player)->isPlayerActive())
			return;
	}

	SkirmishPreferences preferences;
	SkirmishBattleHonors stats(preferences.getUserName());

	GameSpyGroupRoom side = player->m_playerTemplate->m_side;
	Int endFrame = bfmeTheVictoryConditions()->getEndFrame();
	Real duration = (Real)endFrame;
	if (endFrame < 0)
		duration += *(const Real *)0x01075358;
	duration *= *(const Real *)0x01080BBC;
	stats.setTimePlayed(side, stats.getTimePlayed(side) + duration);

	if (bfmeTheVictoryConditions()->localVictory())
	{
		Bool anyAlliedAI = FALSE;
		Bool hasEasy = FALSE;
		Bool hasMedium = FALSE;
		Bool hasBrutal = FALSE;
		Int numBrutal = 0;

		for (Int i = 0; i < 8; ++i)
		{
			GameSlot *slot = bfmeGetConstSlot(bfmeTheGameInfo(), i);
			if (bfmeSlotIsAI(slot) &&
				!bfmeIsSlotLocalAlly(bfmeTheGameInfo(), slot))
			{
				if (bfmeSlotIsOccupied(slot))
				{
					if (slot->m_state == 2)
						hasEasy = TRUE;
					if (slot->m_state == 3)
						hasMedium = TRUE;
					if (slot->m_state == 4)
					{
						hasBrutal = TRUE;
						++numBrutal;
					}
				}
			}
			else if (bfmeSlotIsAI(slot))
			{
				anyAlliedAI = TRUE;
			}
		}

		if (!anyAlliedAI)
		{
			Int points = 0;
			if (bfmeTheGameInfo()->mapIsOfficial() - 1 == numBrutal)
				points = 4;
			else if (hasBrutal)
				points = 3;
			else if (hasMedium)
				points = 2;
			else if (hasEasy)
				points = 1;

			if (points)
				stats.setPoints(side, stats.getPoints(side) + points);
		}

		Int wins = stats.getWins(side) + 1;
		stats.setWins(side, wins);
		Int winStreak = stats.getWinStreak(side) + 1;
		stats.setWinStreak(side, winStreak);
		if (winStreak > stats.getBestWinStreak(side))
			stats.setBestWinStreak(side, winStreak);
		Int overallWinStreak = stats.getOverallWinStreak() + 1;
		stats.setOverallWinStreak(overallWinStreak);
		if (overallWinStreak > stats.getOverallBestWinStreak())
			stats.setOverallBestWinStreak(overallWinStreak);
		stats.setLossStreak(side, 0);
		stats.setOverallLossStreak(0);
		bfmeUpdateEndurance(&stats);
	}
	else
	{
		stats.setLosses(side, stats.getLosses(side) + 1);
		Int lossStreak = stats.getLossStreak(side) + 1;
		stats.setLossStreak(side, lossStreak);
		if (lossStreak > stats.getWorstLossStreak(side))
			stats.setWorstLossStreak(side, lossStreak);
		Int overallLossStreak = stats.getOverallLossStreak() + 1;
		stats.setOverallLossStreak(overallLossStreak);
		if (overallLossStreak > stats.getOverallWorstLossStreak())
			stats.setOverallWorstLossStreak(overallLossStreak);
		stats.setWinStreak(side, 0);
		stats.setOverallWinStreak(0);
	}

	GameSpyGroupRoom favorite = stats.fetchFavorite();
	if (favorite == *(const GameSpyGroupRoom *)0x01336E50)
	{
		stats.storeFavorite(side);
	}
	else
	{
		Int oldGames = stats.getWins(favorite) + stats.getLosses(favorite);
		Int newGames = stats.getWins(side) + stats.getLosses(side);
		if (newGames > oldGames)
			stats.storeFavorite(side);
	}

	GameSpyGroupRoom lastGeneral = stats.getLastGeneral();
	stats.setLastGeneral(side);
	if (lastGeneral != stats.getLastGeneral())
		stats.setNumGamesLoyal(0);
	else
		stats.setNumGamesLoyal(stats.getNumGamesLoyal() + 1);
	stats.write();
}

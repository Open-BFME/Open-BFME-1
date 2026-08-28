// cl: /DNDEBUG /MD /EHsc

// FILE: SkirmishBattleHonorsOverallStreaks.cpp //////////////////////////////
//
// Five more SkirmishBattleHonors setters, retail 0x0009CE70 through
// 0x0009CFF0, 36 bytes each.  Same three lines as setNumGamesLoyal next door:
// build an AsciiString key from a literal and hand it to the base class's
// setInt.  The scaffolding is that file's, declared rather than defined here
// so nothing is claimed twice.
//
// THE CLASS IS NOT A GUESS.  All five sit inside the SkirmishBattleHonors run
// -- setChallengeMedals at 0x0009D570 is the same 36 bytes with the same
// shape, and the five interleave one-for-one with bodies already landed in
// this address range -- and all five reach the same UserPreferences::setInt at
// 0x000A96F0 that setNumGamesLoyal and setChallengeMedals reach, through the
// same ILT thunk at 0x00009B3D.
//
// THE KEYS ARE CERTAIN, read out of retail and re-checked by the build's
// string-reference gate.  THE NAMES ARE READ FROM THE KEYS, which is weaker:
// Zero Hour pairs setWinStreak with "WinStreak" and setBestWinStreak with
// "BestWinStreak", so the mapping is the obvious one for four of the five --
// but the same file also pairs setChallengeMedals with "Challenge" and
// setNumGamesLoyal with "LoyalGames", so it is not always literal.  These
// five keys are BFME additions with no Zero Hour counterpart to check against.
//
/////////////////////////////////////////////////////////////////////////////

typedef int Int;

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	AsciiString() { m_text = 0; }

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~AsciiString();

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	void setInt(AsciiString key, Int val);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
class SkirmishBattleHonors : public UserPreferences
{
public:
	void setOverallWinStreak(Int val);		///< 0x0009CE70
	void setOverallBestWinStreak(Int val);	///< 0x0009CED0
	void setOverallLossStreak(Int val);		///< 0x0009CF30
	void setOverallWorstLossStreak(Int val);	///< 0x0009CF90
	void setPreferredSide(Int val);		///< 0x0009CFF0
};

void SkirmishBattleHonors::setOverallWinStreak(Int val)
{
	setInt("OverallWinStreak", val);
}

void SkirmishBattleHonors::setOverallBestWinStreak(Int val)
{
	setInt("OverallBestWinStreak", val);
}

void SkirmishBattleHonors::setOverallLossStreak(Int val)
{
	setInt("OverallLossStreak", val);
}

void SkirmishBattleHonors::setOverallWorstLossStreak(Int val)
{
	setInt("OverallWorstLossStreak", val);
}

void SkirmishBattleHonors::setPreferredSide(Int val)
{
	setInt("PreferredSide", val);
}

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// FILE: SkirmishBattleHonorsPlayerStats.cpp
// Per-player SkirmishBattleHonors getters/setters.  Each concatenates a
// fixed key onto the by-value name and hands the result to UserPreferences.
// getWorstLossStreak reads the retail typo "WorstLostStreak".

#include <string.h>

#include "../../Include/Common/ScalarTypes.h"


#include "ascii_string.h"
// Retail calls the length-aware StringBase concat from each accessor below.
// Keep the real forwarding body visible and call the base directly, avoiding
// a competing TU-local AsciiString::concat COMDAT.
template<> inline void StringBase<char>::concat(const char *s)
{
    concat(s, s ? (int)strlen(s) : 0);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	void setInt(AsciiString key, Int val);
	Int getInt(AsciiString key, Int defaultValue) const;
	void setReal(AsciiString key, Real val);
	Real getReal(AsciiString key, Real defaultValue) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
class SkirmishBattleHonors : public UserPreferences
{
public:
	void setTimePlayed(AsciiString name, Real val);
	Real getTimePlayed(AsciiString name) const;
	void setPoints(AsciiString name, Int val);
	Int getPoints(AsciiString name) const;
	void setWins(AsciiString name, Int val);
	Int getWins(AsciiString name) const;
	void setLosses(AsciiString name, Int val);
	Int getLosses(AsciiString name) const;
	void setWinStreak(AsciiString name, Int val);
	Int getWinStreak(AsciiString name) const;
	void setLossStreak(AsciiString name, Int val);
	Int getLossStreak(AsciiString name) const;
	void setBestWinStreak(AsciiString name, Int val);
	Int getBestWinStreak(AsciiString name) const;
	void setWorstLossStreak(AsciiString name, Int val);
	Int getWorstLossStreak(AsciiString name) const;
};

void SkirmishBattleHonors::setTimePlayed(AsciiString name, Real val)
{
	name.StringBase<char>::concat("TimePlayed");
	setReal(AsciiString(name.str()), val);
}

Real SkirmishBattleHonors::getTimePlayed(AsciiString name) const
{
	name.StringBase<char>::concat("TimePlayed");
	return getReal(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setPoints(AsciiString name, Int val)
{
	name.StringBase<char>::concat("Points");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getPoints(AsciiString name) const
{
	name.StringBase<char>::concat("Points");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWins(AsciiString name, Int val)
{
	name.StringBase<char>::concat("Wins");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWins(AsciiString name) const
{
	name.StringBase<char>::concat("Wins");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setLosses(AsciiString name, Int val)
{
	name.StringBase<char>::concat("Losses");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getLosses(AsciiString name) const
{
	name.StringBase<char>::concat("Losses");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWinStreak(AsciiString name, Int val)
{
	name.StringBase<char>::concat("WinStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWinStreak(AsciiString name) const
{
	name.StringBase<char>::concat("WinStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setLossStreak(AsciiString name, Int val)
{
	name.StringBase<char>::concat("LossStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getLossStreak(AsciiString name) const
{
	name.StringBase<char>::concat("LossStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setBestWinStreak(AsciiString name, Int val)
{
	name.StringBase<char>::concat("BestWinStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getBestWinStreak(AsciiString name) const
{
	name.StringBase<char>::concat("BestWinStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWorstLossStreak(AsciiString name, Int val)
{
	name.StringBase<char>::concat("WorstLossStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWorstLossStreak(AsciiString name) const
{
	name.StringBase<char>::concat("WorstLostStreak");
	return getInt(AsciiString(name.str()), 0);
}

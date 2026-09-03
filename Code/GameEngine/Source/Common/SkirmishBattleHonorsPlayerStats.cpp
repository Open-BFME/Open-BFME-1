// cl: /DNDEBUG /MD /EHsc

// FILE: SkirmishBattleHonorsPlayerStats.cpp
// Per-player SkirmishBattleHonors getters/setters.  Each concatenates a
// fixed key onto the by-value name and hands the result to UserPreferences.
// getWorstLossStreak reads the retail typo "WorstLostStreak".

#include <string.h>

typedef int Int;
typedef float Real;

template <class Type>
class StringBase
{
public:
	void concat(const char *s, int len);

private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	~StringBase();
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

	void concat(const char *s)
	{
		((StringBase<char> *)this)->concat(s, (int)strlen(s));
	}

	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->~StringBase();
	}

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

private:
	void *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	void setInt(AsciiString key, Int val);
	Int getInt(AsciiString key, Int defaultValue) const;
	void setReal(AsciiString key, Real val);
	Real getReal(AsciiString key, Real defaultValue) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
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
	name.concat("TimePlayed");
	setReal(AsciiString(name.str()), val);
}

Real SkirmishBattleHonors::getTimePlayed(AsciiString name) const
{
	name.concat("TimePlayed");
	return getReal(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setPoints(AsciiString name, Int val)
{
	name.concat("Points");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getPoints(AsciiString name) const
{
	name.concat("Points");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWins(AsciiString name, Int val)
{
	name.concat("Wins");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWins(AsciiString name) const
{
	name.concat("Wins");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setLosses(AsciiString name, Int val)
{
	name.concat("Losses");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getLosses(AsciiString name) const
{
	name.concat("Losses");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWinStreak(AsciiString name, Int val)
{
	name.concat("WinStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWinStreak(AsciiString name) const
{
	name.concat("WinStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setLossStreak(AsciiString name, Int val)
{
	name.concat("LossStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getLossStreak(AsciiString name) const
{
	name.concat("LossStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setBestWinStreak(AsciiString name, Int val)
{
	name.concat("BestWinStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getBestWinStreak(AsciiString name) const
{
	name.concat("BestWinStreak");
	return getInt(AsciiString(name.str()), 0);
}

void SkirmishBattleHonors::setWorstLossStreak(AsciiString name, Int val)
{
	name.concat("WorstLossStreak");
	setInt(AsciiString(name.str()), val);
}

Int SkirmishBattleHonors::getWorstLossStreak(AsciiString name) const
{
	name.concat("WorstLostStreak");
	return getInt(AsciiString(name.str()), 0);
}

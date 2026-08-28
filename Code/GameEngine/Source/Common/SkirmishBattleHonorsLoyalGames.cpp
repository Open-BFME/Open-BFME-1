// cl: /DNDEBUG /MD /EHsc
// readable body of ?setBool@UserPreferences@@QAEXVAsciiString@@_N@Z: Code/GameEngine/Source/Common/UserPreferences.cpp
// readable body of ?setInt@UserPreferences@@QAEXVAsciiString@@H@Z: Code/GameEngine/Source/Common/UserPreferences.cpp

// FILE: SkirmishBattleHonorsLoyalGames.cpp ///////////////////////////////////
//
// SkirmishBattleHonors::setNumGamesLoyal, retail 0x0009DA60, and
// getNumGamesLoyal, retail 0x0009DA90.
//
// No port of SkirmishBattleHonors.cpp exists under Code/.  Both bodies were
// found by the string they push -- "LoyalGames" appears in exactly one
// reference source, and the function enclosing it names them.  Each is three
// lines: build an AsciiString key from the literal and hand it to the base
// class's setInt or getInt.
//
// AsciiString is spelled here with its constructor delegating to
// StringBase<char>, which is what BFME's really does and what
// reference/shims/campaignmanagerascii carries.  It is not cosmetic: a
// declared-only constructor leaves the by-value temporary opaque and MSVC then
// emits `mov ecx,esp' before the frame store rather than after, which is six
// bytes wrong in a thirty-six byte function.  See
// docs/lessons-archive.md on the by-value temporary transposition.
//
///////////////////////////////////////////////////////////////////////////////

typedef int Int;
// bool, not unsigned char: the retail symbols spell it _N, and E would be a
// different setBool and getBool entirely.
typedef bool Bool;

#define TRUE 1
#define FALSE 0

template <class Type>
class StringBase
{
private:
	// Private, not public: the ledger already names this body
	// decorated ??0?$StringBase@D@@AAE@PBD@Z, and a public declaration spells the
	// symbol QAE and need a pin of its own for no reason.
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

	// Declared so the temporary is built straight into the argument slot rather
	// than materialised somewhere else and re-pushed.
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~AsciiString();

	static AsciiString TheEmptyString;

	// Inline, not the shim's out-of-line delegation: retail inlines this to a
	// null test, a +8 and a fallback pointer.
	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

	// The format string is an AsciiString BY VALUE, not a const char *:
	// retail builds a temporary from the literal and passes it.
	void __cdecl format(AsciiString fmt, ...);

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:

	// setAsciiString is VIRTUAL in BFME and the int and bool accessors are not:
	// retail reaches it as mov edx,[esi] / call [edx+0x1c] while setInt, getInt,
	// setBool and getBool are all direct calls.  Seven anonymous slots put it on
	// 0x1c; what they hold this file does not say.
	virtual void bfmeSlot00() = 0;
	virtual void bfmeSlot04() = 0;
	virtual void bfmeSlot08() = 0;
	virtual void bfmeSlot0C() = 0;
	virtual void bfmeSlot10() = 0;
	virtual void bfmeSlot14() = 0;
	virtual AsciiString getAsciiString(AsciiString key, AsciiString defaultValue) const = 0;	// @0x18
	virtual void setAsciiString(AsciiString key, AsciiString val) = 0;		// @0x1c

	Bool getBool(AsciiString key, Bool defaultValue) const;
	Int getInt(AsciiString key, Int defaultValue) const;
	void setBool(AsciiString key, Bool val);
	void setInt(AsciiString key, Int val);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SkirmishBattleHonors.h
class SkirmishBattleHonors : public UserPreferences
{
public:
	void setLastGeneral(AsciiString val);
	AsciiString getLastGeneral(void) const;
	void setBuiltSCUD(void);
	Bool builtSCUD(void) const;
	void setBuiltParticleCannon(void);
	Bool builtParticleCannon(void) const;
	void setBuiltNuke(void);
	Bool builtNuke(void) const;
	void setChallengeMedals(Int val);
	Int getChallengeMedals(void) const;
	void setHonors(Int which);
	Int getHonors(void) const;
	void setEnduranceMedal(AsciiString mapName, Int difficulty, int numAIs);
	Int getEnduranceMedal(AsciiString mapName, Int difficulty) const;
	void setNumGamesLoyal(Int val);
	Int getNumGamesLoyal(void) const;
};

static AsciiString intAsStr(Int value)
{
	AsciiString result;
	result.format("%d", value);
	return result;
}

static AsciiString boolAsStr(Bool value)
{
	AsciiString result;
	result.format("%d", value);
	return result;
}

void UserPreferences::setBool(AsciiString key, Bool value)
{
	setAsciiString(key, boolAsStr(value));
}

void UserPreferences::setInt(AsciiString key, Int value)
{
	setAsciiString(key, intAsStr(value));
}

void SkirmishBattleHonors::setBuiltSCUD(void)
{
	setBool("SCUD", TRUE);
}

Bool SkirmishBattleHonors::builtSCUD(void) const
{
	return getBool("SCUD", FALSE);
}

void SkirmishBattleHonors::setBuiltParticleCannon(void)
{
	setBool("PPC", TRUE);
}

Bool SkirmishBattleHonors::builtParticleCannon(void) const
{
	return getBool("PPC", FALSE);
}

void SkirmishBattleHonors::setBuiltNuke(void)
{
	setBool("Nuke", TRUE);
}

Bool SkirmishBattleHonors::builtNuke(void) const
{
	return getBool("Nuke", FALSE);
}

void SkirmishBattleHonors::setChallengeMedals(Int val)
{
	setInt("Challenge", val);
}

Int SkirmishBattleHonors::getChallengeMedals(void) const
{
	return getInt("Challenge", 0);
}

void SkirmishBattleHonors::setHonors(Int which)
{
	Int honors = getInt("Honors", 0);
	setInt("Honors", honors | which);
}

Int SkirmishBattleHonors::getHonors(void) const
{
	return getInt("Honors", 0);
}

void SkirmishBattleHonors::setNumGamesLoyal(Int val)
{
	setInt("LoyalGames", val);
}

Int SkirmishBattleHonors::getNumGamesLoyal(void) const
{
	return getInt("LoyalGames", 0);
}

void SkirmishBattleHonors::setLastGeneral(AsciiString val)
{
	setAsciiString("LastHouse", val);
}

AsciiString SkirmishBattleHonors::getLastGeneral(void) const
{
	return getAsciiString("LastHouse", AsciiString::TheEmptyString);
}

void SkirmishBattleHonors::setEnduranceMedal(AsciiString mapName, Int difficulty, int numAIs)
{
	AsciiString key;
	key.format("%s_%d", mapName.str(), difficulty);
	setInt(key, numAIs);
}

Int SkirmishBattleHonors::getEnduranceMedal(AsciiString mapName, Int difficulty) const
{
	AsciiString key;
	key.format("%s_%d", mapName.str(), difficulty);
	return getInt(key, 0);
}

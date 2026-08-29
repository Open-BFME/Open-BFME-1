// cl: /DNDEBUG /MD /EHsc
//
// Eight preference accessors landed as relocation-blind twins of
// Code/GameEngine/Source/Common/SkirmishBattleHonorsLoyalGames.cpp.  Each
// differs from its model in exactly one .rdata slot -- the key literal it
// pushes -- plus the per-function EH table address, which is a different
// symbol for every function and so never a conflict.
//
// The declarations below are the model's, unchanged: the same AsciiString
// whose constructor delegates to StringBase<char> (a declared-only
// constructor moves `mov ecx,esp` across the frame store and is six bytes
// wrong in a thirty-six byte body), and the same UserPreferences with
// setAsciiString virtual at slot 0x1c while setInt and getInt are direct.

// cl: /DNDEBUG /MD /EHsc
// readable body of ?setBool@UserPreferences@@QAEXVAsciiString@@_N@Z: Code/GameEngine/Source/Common/UserPreferences.cpp
// readable body of ?setInt@UserPreferences@@QAEXVAsciiString@@H@Z: Code/GameEngine/Source/Common/UserPreferences.cpp

// (declarations carried over from that file)
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


// The twin accessors.  One key literal each; nothing else differs.


class Open2Pref0A9850 : public UserPreferences
{
public:
	void store( Int value );
};

// @?store@Open2Pref0A9850@@QAEXH@Z 0x000A9850
void Open2Pref0A9850::store( Int value )
{
	setInt( "Highest1vs1Rank", value );
}

class Open2Pref0A98B0 : public UserPreferences
{
public:
	void store( Int value );
};

// @?store@Open2Pref0A98B0@@QAEXH@Z 0x000A98B0
void Open2Pref0A98B0::store( Int value )
{
	setInt( "Highest2vs2Rank", value );
}

class Open2Pref0A9910 : public UserPreferences
{
public:
	void store( Int value );
};

// @?store@Open2Pref0A9910@@QAEXH@Z 0x000A9910
void Open2Pref0A9910::store( Int value )
{
	setInt( "StartingSupplies", value );
}

class Open2Pref0A9940 : public UserPreferences
{
public:
	void store( Int value );
};

// @?store@Open2Pref0A9940@@QAEXH@Z 0x000A9940
void Open2Pref0A9940::store( Int value )
{
	setInt( "MaxFPS", value );
}

class Open2Pref0A9970 : public UserPreferences
{
public:
	void store( Int value );
};

// @?store@Open2Pref0A9970@@QAEXH@Z 0x000A9970
void Open2Pref0A9970::store( Int value )
{
	setInt( "FPSSlider", value );
}

class Open2Pref09D050 : public UserPreferences
{
public:
	void store( AsciiString value );
};

// @?store@Open2Pref09D050@@QAEXVAsciiString@@@Z 0x0009D050
void Open2Pref09D050::store( AsciiString value )
{
	setAsciiString( "PreferredSideName", value );
}

class Open2Pref09D1C0 : public UserPreferences
{
public:
	void store( AsciiString value );
};

// @?store@Open2Pref09D1C0@@QAEXVAsciiString@@@Z 0x0009D1C0
void Open2Pref09D1C0::store( AsciiString value )
{
	setAsciiString( "FavoriteSide", value );
}

class Open2Pref09D260 : public UserPreferences
{
public:
	AsciiString fetch( void ) const;
};

// @?fetch@Open2Pref09D260@@QBE?AVAsciiString@@XZ 0x0009D260
AsciiString Open2Pref09D260::fetch( void ) const
{
	return getAsciiString( "FavoriteSide", AsciiString::TheEmptyString );
}

// ?bfmeApply@BfmeConsumerED@@QAEXVBfmeArgED@@@Z
// partial score=0.0661746617 date=2026-09-16
// Candidate: retail copies the consumer's preference tail into a local
// SkirmishPreferences-shaped object, then formats the complete four-faction
// battle-honors profile into the APT fields.

template <typename T> class StringBase
{
private:
	StringBase();
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void set( const StringBase<T> &other );
	void concat( const T *text, int length );

	void *m_data;

	friend class AsciiString;
	friend class UnicodeString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text )
		: StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}

	void format( UnicodeString format, ... );
	void translate( const AsciiString &text );
	void set( const UnicodeString &other )
	{
		StringBase<unsigned short>::set( other );
	}
	int compare( const UnicodeString &other ) const;
	void concat( const unsigned short *text, int length )
	{
		StringBase<unsigned short>::concat( text, length );
	}

	const unsigned short *str() const
	{
		return m_data ? (const unsigned short *)((const char *)m_data + 8)
			: (const unsigned short *)0x0107388C;
	}
};

class Rva005672C0Map
{
public:
	virtual void slot0();
	Rva005672C0Map &operator=( const Rva005672C0Map &other );

	void *m_head;
};

class Rva005673A0Vec
{
public:
	Rva005673A0Vec &operator=( const Rva005673A0Vec &other );

private:
	void *m_head;
};

// The direct getUserName thunk reads the preference map at this+4.  The
// consumer has a four-byte prefix before this same tail, which puts its map,
// username and list at +8, +14 and +18, exactly as the retail stores show.
class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	virtual void slot1();
	virtual bool load();
	virtual bool write();

	UnicodeString getUserName();

public:
	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	Rva005673A0Vec m_userNames;
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;
extern "C" __declspec(dllimport) unsigned int __cdecl bfmeLenVGI(
	const unsigned short *text );

class SkirmishBattleHonors
{
public:
	SkirmishBattleHonors( UnicodeString userName );
	virtual ~SkirmishBattleHonors();
	virtual void slot1();
	virtual bool load();
	virtual bool write();

	AsciiString getProfileCreatedDate();
	int getWins() const;
	int getLosses() const;
	int getOverallWinStreak() const;
	int getOverallBestWinStreak() const;
	int getOverallWorstLossStreak() const;
	UnicodeString getFavoriteSideName();

	int getWins( AsciiString side ) const;
	int getLosses( AsciiString side ) const;
	int getWinStreak( AsciiString side ) const;
	int getLossStreak( AsciiString side ) const;
	int getBestWinStreak( AsciiString side ) const;

	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	int m_values[ 10 ];
};

class BfmeArgED
{
public:
	BfmeArgED( const BfmeArgED &other );
	virtual ~BfmeArgED();

	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	Rva005673A0Vec m_userNames;
};

class BfmeConsumerED
{
public:
	void bfmeApply( BfmeArgED value );

private:
	char m_unmodelled_prefix[ 4 ];
	SkirmishPreferences m_preferences;
};

static __forceinline UnicodeString rva005674F0NumberText( int value )
{
	static const unsigned short decimalFormat[] = { '%', 'd', 0 };
	UnicodeString text;
	text.format( UnicodeString( decimalFormat ), value );
	return text;
}

static __forceinline void rva005674F0SetNumber( const char *name, int value )
{
	UnicodeString text = rva005674F0NumberText( value );
	AsciiString variableName( name );
	g_theWindowManager->bfme_setAptText( variableName, text );
}

static __forceinline void rva005674F0SetText( const char *name,
	const UnicodeString &source )
{
	AsciiString variableName( name );
	UnicodeString text( source );
	g_theWindowManager->bfme_setAptText( variableName, text );
}

static __forceinline void rva005674F0SetStreakText(
	const char *name, const UnicodeString &kind )
{
	UnicodeString textFormat = TheGameText->fetch( "APT:CurrentStreakStrFormat" );
	UnicodeString text;
	text.format( textFormat, kind.str() );
	g_theWindowManager->bfme_setAptText( AsciiString( name ), text );
}

static __forceinline void rva005674F0SetFaction(
	SkirmishBattleHonors &honors, AsciiString side,
	const UnicodeString &winFormat, const UnicodeString &lossFormat,
	const char *winsName, const char *lossesName, const char *streakName,
	const char *streakNumName, const char *bestName )
{
	rva005674F0SetNumber( winsName, honors.getWins( side ) );
	rva005674F0SetNumber( lossesName, honors.getLosses( side ) );

	if( honors.getLossStreak( side ) != 0 )
	{
		UnicodeString kind( lossFormat );
		rva005674F0SetStreakText( streakName, kind );
		rva005674F0SetNumber( streakNumName, honors.getLossStreak( side ) );
	}
	else
	{
		UnicodeString kind( winFormat );
		rva005674F0SetStreakText( streakName, kind );
		rva005674F0SetNumber( streakNumName, honors.getWinStreak( side ) );
	}

	rva005674F0SetNumber( bestName, honors.getBestWinStreak( side ) );
}

// ?bfmeApply@BfmeConsumerED@@QAEXVBfmeArgED@@@Z
void BfmeConsumerED::bfmeApply( BfmeArgED value )
{
	Rva005672C0Map &currentMap = m_preferences.m_map;
	currentMap = value.m_map;
	UnicodeString &currentName = m_preferences.m_userName;
currentName.set( value.m_userName );
	m_preferences.m_userNames = value.m_userNames;

	SkirmishBattleHonors honors(
		((SkirmishPreferences *)&value)->getUserName() );
	AsciiString sideA( "Gondor" );
	AsciiString sideB( "Rohan" );
	AsciiString sideD( "Isengard" );
	AsciiString sideC( "Mordor" );
	UnicodeString winFormat = TheGameText->fetch( "Apt:Win" );
	UnicodeString lossFormat = TheGameText->fetch( "Apt:Loss" );

	{
		UnicodeString profileDate;
		profileDate.translate( honors.getProfileCreatedDate() );
		rva005674F0SetText( "APT:ProfileCreatedNum", profileDate );
	}
	rva005674F0SetNumber( "APT:OverallCareerWinsNum", honors.getWins() );
	rva005674F0SetNumber( "APT:OverallCareerLossesNum", honors.getLosses() );
	rva005674F0SetNumber( "APT:CurrentWinStreakNum", honors.getOverallWinStreak() );
	rva005674F0SetNumber( "APT:BestWinStreakNum", honors.getOverallBestWinStreak() );
	rva005674F0SetNumber( "APT:WorstLossStreakNum", honors.getOverallWorstLossStreak() );

	{
		UnicodeString playerName;
		playerName.format( ((SkirmishPreferences *)&value)->getUserName() );
		rva005674F0SetText( "APT:PlayerNameNum", playerName );
	}

	{
		UnicodeString favorite;
		favorite.set( honors.getFavoriteSideName() );
		if( favorite.compare( UnicodeString::TheEmptyString ) != 0 )
			;
		else
		{
			static const unsigned short emptyFavorite[] = { '-', '-', 0 };
			favorite.concat( emptyFavorite, bfmeLenVGI( emptyFavorite ) );
		}
		rva005674F0SetText( "APT:FavoriteSideNum", favorite );
	}

	rva005674F0SetNumber( "APT:TotalGamesPlayedNum",
		honors.getLosses() + honors.getWins() );

	rva005674F0SetFaction( honors, sideA, winFormat, lossFormat,
		"APT:WinsANum", "APT:LossesANum", "APT:CurrentStreakA",
		"APT:CurrentStreakANum", "APT:BestWinStreakANum" );
	rva005674F0SetFaction( honors, sideB, winFormat, lossFormat,
		"APT:WinsBNum", "APT:LossesBNum", "APT:CurrentStreakB",
		"APT:CurrentStreakBNum", "APT:BestWinStreakBNum" );
	rva005674F0SetFaction( honors, sideD, winFormat, lossFormat,
		"APT:WinsCNum", "APT:LossesCNum", "APT:CurrentStreakC",
		"APT:CurrentStreakCNum", "APT:BestWinStreakCNum" );
	rva005674F0SetFaction( honors, sideC, winFormat, lossFormat,
		"APT:WinsDNum", "APT:LossesDNum", "APT:CurrentStreakD",
		"APT:CurrentStreakDNum", "APT:BestWinStreakDNum" );

}

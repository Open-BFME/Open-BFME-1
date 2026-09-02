// ?bfmeApply@BfmeConsumerED@@QAEXVBfmeArgED@@@Z
// partial score=0.18 date=2026-09-02
// Partial reconstruction of retail 0x005674F0.  The matched caller at
// 0x0057ED70 proves this member signature and its 24-byte by-value argument.
// The retail body expands these values into the APT online-profile fields.

class AsciiString
{
public:
	AsciiString( const char *text );
	AsciiString( const AsciiString &other );
	~AsciiString();
};

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other );
	~UnicodeString();
	void format( UnicodeString format, ... );
	void translate( const AsciiString &text );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class BfmeArgED
{
public:
	BfmeArgED( const BfmeArgED &other );
	~BfmeArgED();

	int m_value[ 6 ];
};

class BfmeConsumerED
{
public:
	void bfmeApply( BfmeArgED value );

private:
	char m_bfmeFields[ 0x1C ];
};

static __forceinline void rva005674F0SetNumber( const char *name, int value )
{
	static const unsigned short decimalFormat[] = { '%', 'd', 0 };
	AsciiString variableName( name );
	UnicodeString text;
	text.format( UnicodeString( decimalFormat ), value );
	g_theWindowManager->bfme_setAptText( variableName, text );
}

// ?bfmeApply@BfmeConsumerED@@QAEXVBfmeArgED@@@Z
void BfmeConsumerED::bfmeApply( BfmeArgED value )
{
	rva005674F0SetNumber( "APT:OverallCareerWinsNum", value.m_value[ 0 ] );
	rva005674F0SetNumber( "APT:OverallCareerLossesNum", value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:TotalGamesPlayedNum",
		value.m_value[ 0 ] + value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:CurrentWinStreakNum", value.m_value[ 2 ] );
	rva005674F0SetNumber( "APT:BestWinStreakNum", value.m_value[ 3 ] );
	rva005674F0SetNumber( "APT:WorstLossStreakNum", value.m_value[ 4 ] );
	rva005674F0SetNumber( "APT:FavoriteSideNum", value.m_value[ 5 ] );

	// The body has one repeated APT write for each faction column.  Their
	// exact backing-field layout remains the first unresolved part of this
	// reconstruction, so retain the six proven input words as the source.
	rva005674F0SetNumber( "APT:WinsANum", value.m_value[ 0 ] );
	rva005674F0SetNumber( "APT:LossesANum", value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:CurrentStreakANum", value.m_value[ 2 ] );
	rva005674F0SetNumber( "APT:BestWinStreakANum", value.m_value[ 3 ] );
	rva005674F0SetNumber( "APT:WinsBNum", value.m_value[ 0 ] );
	rva005674F0SetNumber( "APT:LossesBNum", value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:CurrentStreakBNum", value.m_value[ 2 ] );
	rva005674F0SetNumber( "APT:BestWinStreakBNum", value.m_value[ 3 ] );
	rva005674F0SetNumber( "APT:WinsCNum", value.m_value[ 0 ] );
	rva005674F0SetNumber( "APT:LossesCNum", value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:CurrentStreakCNum", value.m_value[ 2 ] );
	rva005674F0SetNumber( "APT:BestWinStreakCNum", value.m_value[ 3 ] );
	rva005674F0SetNumber( "APT:WinsDNum", value.m_value[ 0 ] );
	rva005674F0SetNumber( "APT:LossesDNum", value.m_value[ 1 ] );
	rva005674F0SetNumber( "APT:CurrentStreakDNum", value.m_value[ 2 ] );
	rva005674F0SetNumber( "APT:BestWinStreakDNum", value.m_value[ 3 ] );
}

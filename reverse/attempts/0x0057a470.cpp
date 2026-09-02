// ?_bfme_updateProfileDisplay@BfmeAptScreenSkirmish@@QAEXXZ
// partial score=0.47 date=2026-09-02
// cl: /O2 /Ob1 /DNDEBUG /MD
//
// BFME-only Skirmish.apt profile/career display refresh.  The Zero Hour tree
// has no APT Skirmish screen; the labels and object layout below come from the
// retail BFME call sites and string references.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
protected:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
};

struct SkirmishProfileSnapshot
{
	UnicodeString profileCreated;
	UnicodeString playerName;
	int wins;
	int losses;
	int games;
	int currentWinStreak;
	int bestWinStreak;
	int totalTimePlayed;
	int faction;
	int currentLevel;
	int nextLevelWins;
	int progress;
	char m_unmodelled[ 0xFC ];
};

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

class SkirmishProfileDisplayState
{
public:
	bool hasProfileData( void );
	bool readProfileData( SkirmishProfileSnapshot &snapshot );
};

class BfmeAptScreenSkirmish
{
public:
	void _bfme_updateProfileDisplay( void );
private:
	char m_unmodelled[ 0x3AC ];
	SkirmishProfileDisplayState m_profileDisplayState;
};

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;

void BfmeAptScreenSkirmish::_bfme_updateProfileDisplay( void )
{
	register unsigned int zero = 0;
	register BfmeAptScreenSkirmish *screen = this;
	SkirmishProfileSnapshot profile;
	UnicodeString dash;
	dash.format( TheGameText->fetch( "APT:DashDash", (bool *)zero ) );
	register SkirmishProfileDisplayState *profileState =
		&screen->m_profileDisplayState;

	if( !profileState->hasProfileData() )
	{
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:SkirmishProfileCreatedNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:PlayerNameNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerWinsNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerLossesNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerGamesNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurrentWinStreakNumA" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:BestWinStreakNumA" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalTimePlayedNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurFactionNameStr" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:NextWinsNumber" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurrentLevelFormat" ), dash );
		return;
	}

	if( !profileState->readProfileData( profile ) )
	{
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:SkirmishProfileCreatedNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:PlayerNameNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerWinsNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerLossesNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalCareerGamesNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurrentWinStreakNumA" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:BestWinStreakNumA" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:TotalTimePlayedNum" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurFactionNameStr" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:NextWinsNumber" ), dash );
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CurrentLevelFormat" ), dash );
		return;
	}

	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:SkirmishProfileCreatedNum" ), profile.profileCreated );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:PlayerNameNum" ), profile.playerName );

	UnicodeString text;
	text.format( TheGameText->fetch( "APT:TotalCareerWinsNum" ), profile.wins );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:TotalCareerWinsNum" ), text );
	text.format( TheGameText->fetch( "APT:TotalCareerLossesNum" ), profile.losses );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:TotalCareerLossesNum" ), text );
	text.format( TheGameText->fetch( "APT:TotalCareerGamesNum" ), profile.games );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:TotalCareerGamesNum" ), text );
	text.format( TheGameText->fetch( "APT:CurrentWinStreakNumA" ), profile.currentWinStreak );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:CurrentWinStreakNumA" ), text );
	text.format( TheGameText->fetch( "APT:BestWinStreakNumA" ), profile.bestWinStreak );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:BestWinStreakNumA" ), text );
	text.format( TheGameText->fetch( "APT:TotalTimePlayedNum" ), profile.totalTimePlayed );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:TotalTimePlayedNum" ), text );

	const char *factionLabel = "APT:GondorCaps";
	if( profile.faction == zero + 1 ) factionLabel = "APT:RohanCaps";
	else if( profile.faction == zero + 2 ) factionLabel = "APT:IsengardCaps";
	else if( profile.faction == zero + 3 ) factionLabel = "APT:MordorCaps";
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:CurFactionNameStr" ), TheGameText->fetch( factionLabel ) );

	text.format( TheGameText->fetch( "APT:CurrentLevelNumFormat" ), profile.currentLevel );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:CurrentLevelFormat" ), text );
	text.format( TheGameText->fetch( profile.nextLevelWins == 1
		? "APT:WinsNumFormatForOnePoint" : "APT:WinsNumFormat" ), profile.nextLevelWins );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:NextWinsNumber" ), text );
}

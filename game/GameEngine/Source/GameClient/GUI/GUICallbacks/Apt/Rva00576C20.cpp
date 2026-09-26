// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Score-screen row helper, retail 0x00576C20, 775 bytes.

#include <utility>
#include <vector>

typedef int Int;
typedef bool Bool;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;
	friend class StringBaseNarrowAI;

public:
	void set( const StringBase<T> &other );

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const AsciiString &other )
	{
		((StringBase<char> *)this)->set( *(const StringBase<char> *)&other );
		return *this;
	}
};

class AsciiStringAI;
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void set( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other );
	}
	void translate( const AsciiString &source );
	void translate( const AsciiStringAI &source );
};

class StringBaseNarrowAI
{
public:
	StringBaseNarrowAI( void ) { m_bfmeNarrowAI = 0; }
	StringBaseNarrowAI( const char *text );
	StringBaseNarrowAI( const StringBaseNarrowAI &other );
	~StringBaseNarrowAI()
	{
		((StringBase<char> *)this)->StringBase<char>::~StringBase();
	}

protected:
	char *m_bfmeNarrowAI;
};

class AsciiStringAI : public StringBaseNarrowAI
{
public:
	AsciiStringAI( void ) {}
	AsciiStringAI( const char *text ) : StringBaseNarrowAI( text ) {}
	AsciiStringAI( const AsciiStringAI &other ) : StringBaseNarrowAI( other ) {}
	~AsciiStringAI( void ) {}
};

void UnicodeString::translate( const AsciiStringAI &source )
{
	translate( *(const AsciiString *)&source );
}

class BfmeTableAI
{
public:
	AsciiStringAI bfmeNumberedAI( Int number );
};

class ScoreKeeper
{
public:
	Int getTotalUnitsDestroyed( void );
	Int getTotalBuildingsDestroyed( void );

	void *m_vtable;
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[ 32 ];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[ 32 ];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
};

class Player
{
public:
	UnicodeString getPlayerDisplayName( void );
	Bool isLocalPlayer( void ) const;
	ScoreKeeper *getScoreKeeper( void )
	{
		return (ScoreKeeper *)( (char *)this + 0x348 );
	}
};

class GameSlot
{
public:
	Bool isOccupied( void ) const;
	Int getApparentColor( void ) const;
};

class MultiplayerColorDefinition
{
public:
	char m_pad[ 0x10 ];
	Int m_color;
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int which );
};

class GameSpyStagingRoom;
extern MultiplayerSettings *TheMultiplayerSettings;
extern GameSpyStagingRoom *TheGameSpyGame;
extern void _bfme_updateSkirmishBattleHonors( Player *player );
extern void _bfme_updateOnlinePlayerStats( Player *player );

struct Gen_t_005758b0_p8cd { int a[2]; Gen_t_005758b0_p8cd(); Gen_t_005758b0_p8cd(const Gen_t_005758b0_p8cd&); ~Gen_t_005758b0_p8cd(); Gen_t_005758b0_p8cd& operator=(const Gen_t_005758b0_p8cd&); };
struct BfmeScoreScreenPlayerRow
{
	Int color;
	AsciiString faction;
};

class BfmeAptScreenScoreScreen
{
public:
	void Rva00576C20( Player *player, GameSlot *slot, Int row );
	void _bfme_setPlayerTable( Int row, Int field, const UnicodeString &text );

private:
	char m_unmodelled_prefix[ 0x25c ];
	Int m_gameType;
	char m_unmodelled_middle[ 4 ];
	_STL::vector<Gen_t_005758b0_p8cd> m_playerTable;
};

// ?Rva00576C20@BfmeAptScreenScoreScreen@@QAEXPAVPlayer@@PAVGameSlot@@H@Z
void BfmeAptScreenScoreScreen::Rva00576C20(
	Player *player, GameSlot *slot, Int row )
{
	if( player == 0 )
		return;
	if( slot == 0 )
		return;
	if( !slot->isOccupied() )
		return;
	if( row > 8 )
		return;

	ScoreKeeper *scoreKeeper = player->getScoreKeeper();
	if( scoreKeeper == 0 )
		return;

	Int number;
	UnicodeString text;
	text.set( player->getPlayerDisplayName() );
	_bfme_setPlayerTable( row, 0, text );

	number = scoreKeeper->m_totalUnitsBuilt;
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 1, text );

	number = scoreKeeper->m_totalUnitsLost;
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 2, text );

	number = scoreKeeper->getTotalUnitsDestroyed();
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 3, text );

	number = scoreKeeper->m_totalBuildingsBuilt;
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 4, text );

	number = scoreKeeper->m_totalBuildingsLost;
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 5, text );

	number = scoreKeeper->getTotalBuildingsDestroyed();
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 6, text );

	number = scoreKeeper->m_totalMoneyEarned;
	text.translate( ((BfmeTableAI *)this)->bfmeNumberedAI( number ) );
	_bfme_setPlayerTable( row, 7, text );

	BfmeScoreScreenPlayerRow playerRow;
	playerRow.color = TheMultiplayerSettings->getColor(
		slot->getApparentColor() )->m_color;
	// Retail copies Player+0x28 directly into the AsciiString row member.
	playerRow.faction = *(const AsciiString *)( (const char *)player + 0x28 );
	// The vector's retail payload is pair<Int, AsciiString>; this local keeps
	// the first dword uninitialized until the color is read, as retail does.
	m_playerTable.push_back( *(const Gen_t_005758b0_p8cd *)&playerRow );

	if( player->isLocalPlayer() )
	{
		if( m_gameType == 1 )
			_bfme_updateSkirmishBattleHonors( player );
		if( m_gameType == 3 && *( (unsigned char *)TheGameSpyGame + 0x43c ) )
			_bfme_updateOnlinePlayerStats( player );
	}
}

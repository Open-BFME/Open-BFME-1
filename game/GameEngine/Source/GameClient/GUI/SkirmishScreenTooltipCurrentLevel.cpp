// ?tooltipPlayerLevelIcon@BfmeAptScreenSkirmish@@QAEXPAX@Z
// Retail 0x0057A200.  The constructor at 0x0057DA50 registers this callback
// as Skirmish/tooltipPlayerLevelIcon.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
extern const unsigned short BFMEEmptyUnicodeString;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;

public:
	void concat( const StringBase<T> &other );
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const char *text );
	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
	const unsigned short *str() const
	{
		return m_data ? m_data->m_text : &BFMEEmptyUnicodeString;
	}
};

class GameSlot
{
public:
	char m_pad[ 0x14 ];
	int m_playerTemplate;
};

class GameInfo
{
public:
	GameSlot *getSlot( int index );
};

class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

class PlayerTemplate
{
public:
	char m_pad[ 8 ];
	AsciiString m_side;
	char m_unmodelled[ 0x10c ];
	unsigned char m_isEvil;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate( int index ) const;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class SkirmishBattleHonors
{
public:
	int getRank( AsciiString name ) const;
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
	virtual UnicodeString fetch( AsciiString label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, int delay,
		const RGBColor *color, float width );
};

extern Mouse *TheMouse;

// Rank-name tables indexed by getRank(): evil sides at 0x012B8018, good at 0x012B7FF0.
extern const char *g_012B8018[];
extern const char *g_012B7FF0[];

class BfmeAptScreenSkirmish
{
public:
	void tooltipPlayerLevelIcon( void *argument );

private:
	char m_pad[ 0x3c4 ];
	SkirmishBattleHonors m_honors;
};

void BfmeAptScreenSkirmish::tooltipPlayerLevelIcon( void * )
{
	GameInfo *current = reinterpret_cast<GameInfo *>(TheSkirmishGameInfo);
	if( current == 0 )
		return;
	GameSlot *slot = current->getSlot( 0 );
	if( slot == 0 )
		return;

	const PlayerTemplate *player =
		ThePlayerTemplateStore->getNthPlayerTemplate( slot->m_playerTemplate );
	if( player != 0 )
	{
		AsciiString tooltipKey( "TOOLTIP:" );
		const AsciiString *sideSource = &player->m_side;
		AsciiString side = *sideSource;
		int rank = m_honors.getRank( side );
		AsciiString rankName;
		if( player->m_isEvil )
			rankName = g_012B8018[ rank ];
		else
			rankName = g_012B7FF0[ rank ];
		((StringBase<char> *)&tooltipKey)->concat(
			*(const StringBase<char> *)&rankName );

		UnicodeString currentLevel = TheGameText->fetch( tooltipKey );
		UnicodeString tooltip;
		tooltip.format( TheGameText->fetch( "APT:CurrentLevelStringFormat" ),
			currentLevel.str() );
		TheMouse->setCursorTooltip( tooltip, -1, 0, 1.0f );
	}
	else
		TheMouse->setCursorTooltip(
			TheGameText->fetch( "Tooltip:NoCurrentLevel" ), -1, 0, 1.0f );
}

extern const char *g_012B8018[11];
extern "C" const char *__identifier("?g_012B8018@@3PAPBDA")[11] =
{
	"Wizard", "Scum", "Vermin", "Beast", "Goblin", "Orc",
	"MountainTroll", "Berserker", "DarkWizard", "RingWraith", "DarkLord"
};

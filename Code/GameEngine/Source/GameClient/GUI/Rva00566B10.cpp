// The Skirmish options constructor registers this body for the four faction
// tooltip selectors at 0x0110A2E4, 0x0110A2B8, 0x0110A288, and 0x0110A258.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> struct StringInlineData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_reserved;
	T m_text[ 1 ];
};

class AsciiString;
class UnicodeString;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	void set( const T *text, int length );
	void concat( const T *text, int length );

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	AsciiString &operator=( const char *text );
	void set( const char *text, int length )
	{
		StringBase<char>::set( text, length );
	}
	void concat( const char *text, int length )
	{
		StringBase<char>::concat( text, length );
	}
	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}
	int length() const
	{
		return m_data ? m_data->m_length : 0;
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
		return m_data ? m_data->m_text : (const unsigned short *)0x0107388C;
	}
};

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
	UnicodeString getUserName();
};

class Rva005672C0Map
{
public:
	virtual void slot0();

private:
	void *m_head;
};

struct SkirmishBattleHonorsValues
{
	int m_value[ 10 ];
};

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
	SkirmishBattleHonors( UnicodeString userName );
	int getRank( AsciiString side ) const;

private:
	Rva005672C0Map m_map;
	char m_unmodelled_0c[ 4 ];
	UnicodeString m_userName;
	SkirmishBattleHonorsValues m_values;
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

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, int delay,
		const RGBColor *color, float width );
};

class Rva00566B10
{
public:
	void method( void *selector );

private:
	void *m_vftable;
	SkirmishPreferences m_preferences;
};

extern GameTextInterface *TheGameText;
extern Mouse *TheMouse;

#include <string.h>

void Rva00566B10::method( void *selector )
{
	AsciiString side;
	SkirmishBattleHonors honors( m_preferences.getUserName() );
	bool evilSide = false;
	const char *selectorName = (const char *)selector;
	if( strcmp( selectorName,
		"Skirmish/tooltipPlayerLevelIconGondor" ) == 0 )
		side.set( (const char *)0x010804D8, 6 );
	else if( strcmp( selectorName,
		"Skirmish/tooltipPlayerLevelIconRohan" ) == 0 )
		side.set( (const char *)0x010804D0, 5 );
	else if( strcmp( selectorName,
		"Skirmish/tooltipPlayerLevelIconIsengard" ) == 0 )
	{
		side = (const char *)0x010804C4;
		evilSide = true;
	}
	else if( strcmp( selectorName,
		"Skirmish/tooltipPlayerLevelIconMordor" ) == 0 )
	{
		side = (const char *)0x010804BC;
		evilSide = true;
	}
	else
		return;

	AsciiString tooltipKey( (const char *)0x010F7308 );
	int rank = honors.getRank( side );
	AsciiString rankName;
	if( evilSide )
	{
		const char *rankNameText = ((const char **)0x012B7DD0)[ rank ];
		rankName.set( rankNameText,
			rankNameText ? (int)strlen( rankNameText ) : 0 );
	}
	else
	{
		const char *rankNameText = ((const char **)0x012B7DA8)[ rank ];
		rankName.set( rankNameText,
			rankNameText ? (int)strlen( rankNameText ) : 0 );
	}

	tooltipKey.concat( rankName.str(), rankName.length() );

	UnicodeString currentLevel = TheGameText->fetch( tooltipKey );
	UnicodeString tooltip;
	tooltip.format(
		TheGameText->fetch( (const char *)0x01107C04 ), currentLevel.str() );
	TheMouse->setCursorTooltip( tooltip, -1, 0, 1.0f );
}

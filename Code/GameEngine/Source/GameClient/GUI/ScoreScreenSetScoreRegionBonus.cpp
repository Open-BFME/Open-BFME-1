// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenScoreScreen score-region binding, retail 0x00571280, 275 bytes.
// The single-player score screen supplies the next APT index, a string label,
// and a signed bonus. Positive bonuses use the translated label and negative
// bonuses clear the field with one space.
extern "C" void _WriteBarrier( void );
#pragma intrinsic( _WriteBarrier )

typedef char Bool;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class BfmeAptScreenScoreScreen
{
public:
	void _bfme_setScoreRegionBonus( int *index, const AsciiString &label, int value );
};

// ?_bfme_setScoreRegionBonus@BfmeAptScreenScoreScreen@@QAEXPAHABVAsciiString@@H@Z
void BfmeAptScreenScoreScreen::_bfme_setScoreRegionBonus(
	int *index, const AsciiString &label, int value )
{
	AsciiString variableName;
	variableName.format( (AsciiString)"APT:ScoreRegionBonus%d", *index );
	if( value > 0 )
	{
		UnicodeString text;
		text.format( TheGameText->fetch( label ), value );
		g_theWindowManager->bfme_setAptText( variableName, text );
		_WriteBarrier();
		++*index;
	}
	else if( value < 0 )
	{
		{
			UnicodeString text( L" " );
			g_theWindowManager->bfme_setAptText( variableName, text );
		}
		++*index;
	}
}

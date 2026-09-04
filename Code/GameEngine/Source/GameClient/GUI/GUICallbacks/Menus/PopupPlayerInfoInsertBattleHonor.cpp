// cl: /DNDEBUG /MD /EHsc
// Open-BFME: InsertBattleHonor, retail 0x004D9800, 352 bytes.
// Converted from gen-dump d_004d9800. ZH twin is static in PopupPlayerInfo.cpp;
// that TU already owns BattleHonorTooltip / overlay rows, so this lives here.
// RankPoints ctor (0x004D9DF0) names this body. BFME scales 50x51 (not ZH
// 40x41), drops the extra SetItemData, and keeps the unused by-value
// UnicodeString so the EH frame matches.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
};

class GameWindow;
class Image;

class Display
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
	virtual void slot24();
	virtual void slot28();
	virtual UnsignedInt getWidth();
	virtual UnsignedInt getHeight();
};

extern Display *TheDisplay;

Int GadgetListBoxAddEntryImage( GameWindow *listbox, const Image *image,
	Int row, Int column, Int height, Int width, Bool overwrite, Int color );
void GadgetListBoxSetItemData( GameWindow *listbox, void *data, Int row, Int column );
Int GadgetListBoxGetNumColumns( GameWindow *listbox );

enum { BATTLE_HONOR_NOT_GAINED = 0x08000000 };

static Int rowsToSkip = 0;

static inline Int GameMakeColor( unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha )
{
	return ( alpha << 24 ) | ( red << 16 ) | ( green << 8 ) | blue;
}

// ?InsertBattleHonor@@YAXPAVGameWindow@@PBVImage@@_NHAAH3VUnicodeString@@H@Z
void InsertBattleHonor( GameWindow *list, const Image *image, Bool enabled,
	Int itemData, Int &row, Int &column, UnicodeString text, Int extra )
{
	Int width = 50 * ( TheDisplay->getWidth() / 800.0f );
	Int height = 51 * ( TheDisplay->getHeight() / 600.0f );

	static Int enabledColor = 0xFFFFFFFF;
	static Int disabledColor = GameMakeColor( 80, 80, 80, 255 );
	Int color;
	if ( enabled )
		color = enabledColor;
	else
	{
		Int updated = itemData;
		color = disabledColor;
		updated |= BATTLE_HONOR_NOT_GAINED;
		itemData = updated;
	}

	GadgetListBoxAddEntryImage( list, image, row, column, height, width, true, color );
	GadgetListBoxSetItemData( list, (void *)itemData, row, column );

	if ( ++column >= GadgetListBoxGetNumColumns( list ) )
	{
		column = 0;
		row = row + 1 + rowsToSkip;
		Int dec = rowsToSkip - 1;
		Int zero = 0;
		rowsToSkip = *( dec > 0 ? &dec : &zero );
	}
}

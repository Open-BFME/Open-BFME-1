// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// IMECandidateTextAreaDraw, retail 0x004C4BD0 (838 bytes).
//
// Identity: retail FunctionLexicon row (table 0x012A93F8) pairs literal
// 0x01087930 "IMECandidateTextAreaDraw" with ILT 0x00428C9A -> 0x004C4BD0.
// Zero Hour's IMECandidate.cpp body with BFME's changes: the text area gets a
// 0xFFDA9650 frame plus a black fill inset by one pixel, and each line sets
// its colour once through DisplayString::setTextColor before two drop-shadow
// draws.  Dstring is IMECandidate.cpp's file static (retail 0x012F38F8),
// created by IMECandidateWindowSystem.
//
// Local ABI-slice replica, as in IMECandidateMainDraw_Thunk.cpp, so no shared
// header moves.  The IME manager's slots follow BFME's nine-slot
// SubsystemInterface (IMEManagerInit.cpp); DisplayString's follow the matched
// W3D gadget draw TUs (setTextColor +0x28, draw +0x38, setClipRegion +0x50).

#include "string_base.h"
typedef unsigned short wchar_t;

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;
typedef unsigned char Bool;
typedef unsigned short WideChar;

enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATE_HILITED = 0x00000002 };

inline Color GameMakeColor( UnsignedInt red, UnsignedInt green, UnsignedInt blue, UnsignedInt alpha )
{
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// Retail's UnicodeString is a StringBase<wchar_t> wrapper
// (reference/shims/stringbaseunicode), with the destructor inline.
class UnicodeString
{
public:
	UnicodeString() { m_text = 0; }
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase( *(const StringBase<wchar_t> *)&that );
	}
	explicit UnicodeString( const wchar_t *str )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase( str );
	}
	~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

	void __cdecl format( UnicodeString fmt, ... );

private:
	wchar_t *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameFont.h
class GameFont
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Int height;											///< retail this+0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnsignedInt getState( void ) const { return m_state; }

private:
	unsigned char m_unreconstructed_00[0x08];
	UnsignedInt m_state;								///< retail this+0x08
};

class GameWindow
{
public:
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus( void );
	Color winGetEnabledTextColor( void );
	Color winGetEnabledTextBorderColor( void );
	Color winGetDisabledTextColor( void );
	Color winGetDisabledTextBorderColor( void );
	Color winGetHiliteTextColor( void );
	Color winGetHiliteTextBorderColor( void );
	GameFont *winGetFont( void );
	void *winGetUserData( void );
};

// Only the two rect calls are reconstructed; the slots ahead of them place them.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
#define BFME_WM_PAD( N ) virtual void unused##N();
	BFME_WM_PAD( 00 ) BFME_WM_PAD( 01 ) BFME_WM_PAD( 02 ) BFME_WM_PAD( 03 )
	BFME_WM_PAD( 04 ) BFME_WM_PAD( 05 ) BFME_WM_PAD( 06 ) BFME_WM_PAD( 07 )
	BFME_WM_PAD( 08 ) BFME_WM_PAD( 09 ) BFME_WM_PAD( 10 ) BFME_WM_PAD( 11 )
	BFME_WM_PAD( 12 ) BFME_WM_PAD( 13 ) BFME_WM_PAD( 14 ) BFME_WM_PAD( 15 )
	BFME_WM_PAD( 16 ) BFME_WM_PAD( 17 ) BFME_WM_PAD( 18 ) BFME_WM_PAD( 19 )
	BFME_WM_PAD( 20 ) BFME_WM_PAD( 21 ) BFME_WM_PAD( 22 ) BFME_WM_PAD( 23 )
	BFME_WM_PAD( 24 ) BFME_WM_PAD( 25 ) BFME_WM_PAD( 26 ) BFME_WM_PAD( 27 )
	BFME_WM_PAD( 28 ) BFME_WM_PAD( 29 ) BFME_WM_PAD( 30 ) BFME_WM_PAD( 31 )
	BFME_WM_PAD( 32 ) BFME_WM_PAD( 33 ) BFME_WM_PAD( 34 ) BFME_WM_PAD( 35 )
	BFME_WM_PAD( 36 ) BFME_WM_PAD( 37 ) BFME_WM_PAD( 38 ) BFME_WM_PAD( 39 )
	BFME_WM_PAD( 40 ) BFME_WM_PAD( 41 ) BFME_WM_PAD( 42 ) BFME_WM_PAD( 43 )
	BFME_WM_PAD( 44 ) BFME_WM_PAD( 45 ) BFME_WM_PAD( 46 ) BFME_WM_PAD( 47 )
	BFME_WM_PAD( 48 ) BFME_WM_PAD( 49 ) BFME_WM_PAD( 50 ) BFME_WM_PAD( 51 )
	BFME_WM_PAD( 52 ) BFME_WM_PAD( 53 ) BFME_WM_PAD( 54 ) BFME_WM_PAD( 55 )
	BFME_WM_PAD( 56 ) BFME_WM_PAD( 57 ) BFME_WM_PAD( 58 ) BFME_WM_PAD( 59 )
	BFME_WM_PAD( 60 ) BFME_WM_PAD( 61 )
#undef BFME_WM_PAD
	virtual void winFillRect( Color color, Real width,
							  Int startX, Int startY, Int endX, Int endY );	///< vtable +0xF8
	virtual void winOpenRect( Color color, Real width,
							  Int startX, Int startY, Int endX, Int endY );	///< vtable +0xFC
};

extern GameWindowManager *TheWindowManager;				///< retail [0x012F1B40]

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void unused00();								///< +0x00
	virtual void setText( UnicodeString text );				///< +0x04
	virtual void unused02();								///< +0x08
	virtual Int getTextLength( void );						///< +0x0C
	virtual void unused04();								///< +0x10
	virtual void unused05();								///< +0x14
	virtual void setFont( GameFont *font );					///< +0x18
	virtual GameFont *getFont( void );						///< +0x1C
	virtual void setWordWrap( Int wordWrap );				///< +0x20
	virtual void setWordWrapCentered( Bool centered );		///< +0x24
	virtual void setTextColor( Color color, Color drop );	///< +0x28
	virtual void unused11();								///< +0x2C
	virtual void unused12();								///< +0x30
	virtual void unused13();								///< +0x34
	virtual void draw( Int x, Int y, Int xDrop, Int yDrop );	///< +0x38
	virtual void getSize( Int *width, Int *height );		///< +0x3C
	virtual Int getWidth( Int charPos = -1 );				///< +0x40
	virtual void unused17();								///< +0x44
	virtual void unused18();								///< +0x48
	virtual void setUseHotkey( Bool use, Color color );		///< +0x4C
	virtual void setClipRegion( IRegion2D *region );		///< +0x50
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual Bool loadIniFilesFromLegend();
	virtual void slot03();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual Bool slot06( Int arg );
	virtual void slot07();
	virtual void slot08( Int arg );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/IMEManager.h
class IMEManagerInterface : public SubsystemInterface
{
public:
	virtual ~IMEManagerInterface() {}
	virtual void attach( GameWindow *window ) = 0;
	virtual void detatch() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual Bool isEnabled() = 0;
	virtual Bool isAttachedTo( GameWindow *window ) = 0;
	virtual GameWindow *getWindow() = 0;
	virtual Bool isComposing() = 0;
	virtual void getCompositionString( UnicodeString &string ) = 0;
	virtual Int getCompositionCursorPosition() = 0;
	virtual Int getIndexBase() = 0;							///< +0x4C
	virtual Int getCandidateCount() = 0;					///< +0x50
	virtual UnicodeString *getCandidate( Int index ) = 0;	///< +0x54
	virtual Int getSelectedCandidateIndex() = 0;			///< +0x58
	virtual Int getCandidatePageSize() = 0;					///< +0x5C
	virtual Int getCandidatePageStart() = 0;				///< +0x60
};

inline Int BitTest( UnsignedInt bits, UnsignedInt mask ) { return (bits & mask) != 0; }

extern Int IMECandidateWindowLineSpacing;				///< retail [0x012B68F8]
static DisplayString *Dstring = 0;						///< retail [0x012F38F8]

// ?IMECandidateTextAreaDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void IMECandidateTextAreaDraw( GameWindow *window, WinInstanceData *instData )
{
	// set up for rendering
	ICoord2D origin, size, start, end;
	Color		textColor,
					textBorder,
					textSelectColor,
					textSelectBorder;
	IRegion2D textRegion;
	Color black = GameMakeColor( 0, 0, 0, 255 );

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get a nice region from the positions
	textRegion.lo.x = origin.x;
	textRegion.lo.y = origin.y;
	textRegion.hi.x = origin.x + size.x;
	textRegion.hi.y = origin.y + size.y;

	// get the right colors for drawing
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == 0 )
	{

		textSelectColor		= window->winGetDisabledTextColor();
		textSelectBorder	= window->winGetDisabledTextBorderColor();
		textColor		= window->winGetDisabledTextColor();
		textBorder	= window->winGetDisabledTextBorderColor();

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();
		textSelectColor		= window->winGetHiliteTextColor();
		textSelectBorder	= window->winGetHiliteTextBorderColor();

	}  // end else if, hilited
	else
	{

		textSelectColor		= window->winGetHiliteTextColor();
		textSelectBorder	= window->winGetHiliteTextBorderColor();
		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();

	}  // end else, just enabled

	{
		Real borderWidth = 1.0f;

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( GameMakeColor( 0xDA, 0x96, 0x50, 0xFF ), borderWidth,
									   start.x, start.y, end.x, end.y );
		TheWindowManager->winFillRect( black, 0,
									   start.x + 1, start.y + 1, end.x - 1, end.y - 1 );
	}

	if ( Dstring == 0 )
	{
		return;
	}

	IMEManagerInterface *ime = (IMEManagerInterface*)window->winGetUserData();

	if ( ime == 0 )
	{
		return;
	}

	GameFont *font = window->winGetFont();
	Int height;

	// set the font
	Dstring->setFont( font );

	// cacl line height
	height = font->height + IMECandidateWindowLineSpacing;

	// set the clip region
	Dstring->setClipRegion( &textRegion );

	Int first = ime->getCandidatePageStart();
	Int total = ime->getCandidateCount();
	Int pageSize = ime->getCandidatePageSize();
	Int selected = ime->getSelectedCandidateIndex();

	Int count = pageSize;

	if ( count + first > total )
	{
		count = total - first;
	}

	selected = selected - first;
	UnicodeString number;

	// calulate the widest number text
	Int width;
	Dstring->setText( UnicodeString( L"00:" ) );
	width = Dstring->getWidth();

	// calc y start pos
	Int y = origin.y;
	Int leftEdge = origin.x + 10 + width;

	for ( Int i = 0; i < count; i++, y += height )
	{
		UnicodeString *candidate = ime->getCandidate( first + i );
		Int tcolor;

		if ( i == selected )
		{
			tcolor = textSelectColor;
		}
		else
		{
			tcolor = textColor;
		}

		// draw number tab first
		number.format( UnicodeString( L"%d:" ), i + ime->getIndexBase() );
		Dstring->setText( number );
		width = Dstring->getWidth();
		Dstring->setTextColor( tcolor, black );
		Dstring->draw( leftEdge - width, y, 1, 1 );

		// draw candidate
		Dstring->setText( *candidate );
		Dstring->draw( leftEdge, y, 1, 1 );
	}
}

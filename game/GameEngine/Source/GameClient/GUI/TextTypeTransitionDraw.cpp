// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: TextTypeTransition::draw (retail 0x005A0A00, 57 bytes) and the
// file-static drawTypeText it calls (retail 0x005A0450, 363 bytes), from Zero
// Hour's GameWindowTransitionsStyles.cpp. They share this TU because retail
// passes drawTypeText's window in EAX and its display string in EDI, MSVC
// 7.1's private convention for a static whose only caller it can see.
//
// BFME's DisplayString draws with a separate two-colour setter (vtable +0x28)
// and draw(x, y, 1, 1) at +0x38, and its getSize/setClipRegion slots sit
// where the Zero Hour header has other members, so this file carries a local
// ABI slice of the classes instead of the reference headers.
//
// Shape note measured against retail: ICoord2D has an empty user-declared
// constructor. Without it MSVC encodes clipRegion.hi.x's lea as [ecx+ebx]
// where retail has [ebx+ecx] (the one-byte residue the banked attempts
// carried); the same lever is what landed the W3D gadget draw siblings.
#include <stddef.h>
#include "Common/UnicodeString.h"

#include "../../../Include/Common/ScalarTypes/Int.h"
#include "../../../Include/Common/ScalarTypes/UnsignedInt.h"
typedef unsigned char Bool;
typedef int Color;

class GameFont;

struct ICoord2D
{
	ICoord2D() {}
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText( UnicodeString text );
	virtual void slot08();
	virtual Int getTextLength();
	virtual void slot10();
	virtual void slot14();
	virtual void setFont( GameFont *font );
	virtual GameFont *getFont();
	virtual void setWordWrap( Int wordWrap );
	virtual void setWordWrapCentered( Bool isCentered );
	virtual void setTextColor( Color color, Color dropColor );
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void draw( Int x, Int y, Int a, Int b );
	virtual void getSize( Int *width, Int *height );
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void setUseHotkey( Bool useHotkey, Color color );
	virtual void setClipRegion( IRegion2D *region );
};

struct TextData
{
	DisplayString *text;
	Bool centered;
};

enum { WIN_STATUS_WRAP_CENTERED = 0x00040000 };

class GameWindow
{
public:
	void *winGetUserData();
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	UnsignedInt winGetStatus();
	Int winGetEnabledTextColor();
	Int winGetEnabledTextBorderColor();
};

class TextTypeTransition
{
public:
	virtual void draw();

private:
	Int m_frameLength;					// +0x04
	char m_unmodelled08[ 4 ];
	GameWindow *m_win;					// +0x0C
	Int m_startFrame;					// +0x10
	char m_unmodelled14[ 0x28 - 0x14 ];
	Int m_drawState;					// +0x28
	char m_unmodelled2C[ 4 ];
	UnicodeString m_partialText;		// +0x30
	DisplayString *m_dStr;				// +0x34
};

static void drawTypeText( GameWindow *window, DisplayString *str )
{
	TextData *tData = (TextData *)window->winGetUserData();
	Int textColor = window->winGetEnabledTextColor();
	Int textDropColor = window->winGetEnabledTextBorderColor();
	Int textWidth, textHeight, wordWrap;
	DisplayString *text = tData->text;
	ICoord2D origin, size, textPos;
	IRegion2D clipRegion;

	// sanity
	if( text == 0 || text->getTextLength() == 0 )
		return;

	GameFont *font = text->getFont();
	str->setFont( font );

	// get window position and size
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// Set the text Wrap width
	wordWrap = size.x - 10;
	text->setWordWrap( wordWrap );
	str->setWordWrap( wordWrap );
	if( ( window->winGetStatus() & WIN_STATUS_WRAP_CENTERED ) != 0 )
	{
		str->setWordWrapCentered( 1 );
		text->setWordWrapCentered( 1 );
	}
	else
	{
		text->setWordWrapCentered( 0 );
		str->setWordWrapCentered( 0 );
	}

	// how much space will this text take up
	text->getSize( &textWidth, &textHeight );

	// Init the clip region
	clipRegion.lo.x = origin.x;
	clipRegion.lo.y = origin.y;
	clipRegion.hi.x = origin.x + size.x;
	clipRegion.hi.y = origin.y + size.y;

	if( tData->centered )
	{
		textPos.x = origin.x + ( size.x / 2 ) - ( textWidth / 2 );
		textPos.y = origin.y + ( size.y / 2 ) - ( textHeight / 2 );
	}
	else
	{
		textPos.x = origin.x + 7;
		textPos.y = origin.y + ( size.y / 2 ) - ( textHeight / 2 );
	}

	str->setClipRegion( &clipRegion );
	str->setTextColor( textColor, textDropColor );
	str->draw( textPos.x, textPos.y, 1, 1 );
}

void TextTypeTransition::draw( void )
{
	if( m_drawState > m_startFrame && m_drawState < m_frameLength )
	{
		m_dStr->setText( m_partialText );
		drawTypeText( m_win, m_dStr );
	}
}

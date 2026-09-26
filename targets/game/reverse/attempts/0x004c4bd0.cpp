// ?IMECandidateTextAreaDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.466 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DTRIAL_NO_BCOLOR /Iinputs/reference/shims/displaystring /Iinputs/reference/shims/displaystringmanager /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#define UNICODESTRING_H
#include "string_base.h"
typedef unsigned short wchar_t;

class UnicodeString
{
public:
	UnicodeString() { m_text = 0; }
	UnicodeString( const wchar_t *str )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase( str );
	}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that );
	}
	~UnicodeString()
	{
		((StringBase<wchar_t> *)this)->releaseBuffer();
	}
	void __cdecl format( UnicodeString fmt, ... );
	int getLength() const
	{
		return ((const StringBase<wchar_t> *)this)->getLength();
	}
	int compareNoCase( const UnicodeString &that ) const
	{
		return ((const StringBase<wchar_t> *)this)->compareNoCase(
			*(const StringBase<wchar_t> *)&that );
	}
	static UnicodeString TheEmptyString;

private:
	wchar_t *m_text;
};

#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"

class BfmeImeManagerInterface
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot0C( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot1C( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual void slot2C( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot3C( void ) = 0;
	virtual void slot40( void ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot48( void ) = 0;
	virtual Int getIndexBase( void ) = 0;
	virtual Int getCandidateCount( void ) = 0;
	virtual UnicodeString *getCandidate( Int index ) = 0;
	virtual Int getSelectedCandidateIndex( void ) = 0;
	virtual Int getCandidatePageSize( void ) = 0;
	virtual Int getCandidatePageStart( void ) = 0;
};

class BfmeImeDisplayString
{
public:
	virtual void slot00( void ) = 0;
	virtual void setText( UnicodeString text ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot0C( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void setFont( GameFont *font ) = 0;
	virtual void slot1C( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void setColors( Color color, Color dropColor ) = 0;
	virtual void slot2C( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void drawAtOffsets( Int x, Int y, Int xDrop, Int yDrop ) = 0;
	virtual void slot3C( void ) = 0;
	virtual Int getWidth( Int charPos = -1 ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot48( void ) = 0;
	virtual void slot4C( void ) = 0;
	virtual void setClipRegion( IRegion2D *region ) = 0;
};

Int IMECandidateWindowLineSpacing = 2;
static BfmeImeDisplayString *Dstring = NULL;

void IMECandidateTextAreaDraw( GameWindow *window, WinInstanceData *instData )
{
	ICoord2D origin, size, start, end;
	Color textColor, textBorder, textSelectColor, textSelectBorder;
	IRegion2D textRegion;
	Color black = GameMakeColor( 0, 0, 0, 255 );

	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	textRegion.lo.x = origin.x;
	textRegion.lo.y = origin.y;
	textRegion.hi.x = origin.x + size.x;
	textRegion.hi.y = origin.y + size.y;

	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{
		textSelectColor = window->winGetDisabledTextColor();
		textSelectBorder = window->winGetDisabledTextBorderColor();
		textColor = window->winGetDisabledTextColor();
		textBorder = window->winGetDisabledTextBorderColor();
	}
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{
		textColor = window->winGetEnabledTextColor();
		textBorder = window->winGetEnabledTextBorderColor();
		textSelectColor = window->winGetHiliteTextColor();
		textSelectBorder = window->winGetHiliteTextBorderColor();
	}
	else
	{
		textSelectColor = window->winGetHiliteTextColor();
		textSelectBorder = window->winGetHiliteTextBorderColor();
		textColor = window->winGetEnabledTextColor();
		textBorder = window->winGetEnabledTextBorderColor();
	}

	{
		Real borderWidth = 1.0f;
		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( 0xFFDA9650, borderWidth,
			start.x, start.y, end.x, end.y );
		start.x++;
		start.y++;
		end.x--;
		end.y--;
		TheWindowManager->winFillRect( black, 0,
			start.x, start.y, end.x, end.y );
	}

	if( Dstring == NULL )
	{
		return;
	}

	BfmeImeManagerInterface *ime = (BfmeImeManagerInterface*)window->winGetUserData();
	if( ime == NULL )
	{
		return;
	}

	GameFont *font = window->winGetFont();
	Int height;
	Dstring->setFont( font );
	height = font->height + IMECandidateWindowLineSpacing;
	Dstring->setClipRegion( &textRegion );

	Int first = ime->getCandidatePageStart();
	Int total = ime->getCandidateCount();
	Int pageSize = ime->getCandidatePageSize();
	Int selected = ime->getSelectedCandidateIndex();
	Int count = pageSize;

	if( count + first > total )
	{
		count = total - first;
	}

	selected = selected - first;
	UnicodeString number;
	Int width;
	Dstring->setText( UnicodeString( L"00:" ) );
	width = Dstring->getWidth();

	Int y = origin.y;
	Int leftEdge = origin.x + 10 + width;

	for( Int i = 0; i < count; i++, y += height )
	{
		UnicodeString *candidate = ime->getCandidate( first + i );
		Int tcolor;
#if !defined( TRIAL_NO_BCOLOR )
		Int bcolor;
#endif

		if( i == selected )
		{
			tcolor = textSelectColor;
	#if !defined( TRIAL_NO_BCOLOR )
			bcolor = textSelectBorder;
	#endif
		}
		else
		{
			tcolor = textColor;
	#if !defined( TRIAL_NO_BCOLOR )
			bcolor = textBorder;
	#endif
		}

		number.format( UnicodeString( L"%d:" ), i + ime->getIndexBase() );
		Dstring->setText( number );
		width = Dstring->getWidth();
		Dstring->setColors( tcolor, black );
		Dstring->drawAtOffsets( leftEdge - width, y, 1, 1 );

		Dstring->setText( *candidate );
		Dstring->setColors( tcolor, black );
		Dstring->drawAtOffsets( leftEdge, y, 1, 1 );
	}
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// W3DGadgetTextEntryDraw (retail 0x00798F30, 495 bytes) and the file-static
// text renderer it calls directly, retail 0x007986C0 (1720 bytes), in one TU
// as retail has them: 0x00798F30 reaches 0x007986C0 with a direct call, not
// through the ILT, so the helper is internal to this file.
//
// The renderer only matches as that static: compiled with external linkage
// MSVC 7.1 loads x late and gives EBX to the window in the IME/font region,
// where retail keeps x in EBP from entry and the window in memory.
//
// ?Rva007986C0@@YAXPAVGameWindow@@HHHHHH@Z
//
// Retail 0x007986C0 (1720 bytes through the RET at +0x6B7, then INT3) is the
// BFME text-entry text renderer that W3DGadgetTextEntryDraw (0x00798F30) and
// the image-draw callback (0x007991A0) call with seven cdecl words.  It is the
// descendant of Zero Hour's file-static drawTextEntryText, but BFME rewrote it
// around a selection range: the text left of the selection, the highlighted
// selection (inverted drop colour on black), and the text right of it are
// drawn as three clipped runs, and the cursor blinks off timeGetTime.
//
// Identity: the owner name stays address-derived; the Zero Hour helper spelling has a
// different arity, so it is not claimed here.
//
// ABI slice: the BFME DisplayString, IMEManagerInterface and
// GameWindowManager vtables differ from the Zero Hour headers, so this TU
// declares only the slots the body calls, at their retail offsets, as
// TextTypeTransitionDraw.cpp does for the same DisplayString table.
//
// Both bodies are written against BFME ABI slices (DisplayString,
// IMEManagerInterface and GameWindowManager vtables, the EntryData and
// GameWindow layouts) instead of the Zero Hour headers, whose vtables and
// layouts differ; the caller's getSize is DisplayString slot +0x3C.

/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: W3DGadgetTextEntryDraw.cpp //////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: W3DGadgetTextEntryDraw.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      W3D implementation for the text entry gadget
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
// This unit's GameWindow view defines the winGet*Color accessors inline 4 bytes
// past retail's slots (0x0047A260/0x0047A2A0/0x0047A2E0, 0x00484260, 0x0059E4A0,
// 0x0078CF80) and emits those COMDAT copies; rename them so only retail-equal
// copies carry the names. Inlined calls are unchanged.
#define winGetEnabledColor winGetEnabledColor_LocalView
#define winGetEnabledBorderColor winGetEnabledBorderColor_LocalView
#define winGetDisabledColor winGetDisabledColor_LocalView
#define winGetDisabledBorderColor winGetDisabledBorderColor_LocalView
#define winGetHiliteColor winGetHiliteColor_LocalView
#define winGetHiliteBorderColor winGetHiliteBorderColor_LocalView
#include <stddef.h>
#include "Common/UnicodeString.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef int Color;
typedef float Real;
typedef unsigned short WideChar;

enum { WIN_COLOR_UNDEFINED = 0x00FFFFFF };
enum { WIN_STATUS_ENABLED = 0x00000008 };
enum { WIN_STATUS_ONE_LINE = 0x00004000 };
enum { WIN_STATE_HILITED = 0x00000002 };
enum { GWS_COMBO_BOX = 0x00008000 };

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

template <class T> inline const T &min007986C0( const T &a, const T &b ) { return a < b ? a : b; }
template <class T> inline const T &max007986C0( const T &a, const T &b ) { return a > b ? a : b; }

class GameFont
{
public:
	char m_unmodelled00[ 0x10 ];
	Int m_height;						// +0x10
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
	virtual void draw34( Int x, Int y );
	virtual void draw( Int x, Int y, Int a, Int b );
	virtual void getSize( Int *width, Int *height );
	virtual Int getWidth( Int charPos );
	virtual void slot44();
	virtual void slot48();
	virtual void setUseHotkey( Bool useHotkey, Color color );
	virtual void setClipRegion( IRegion2D *region );
	virtual void slot54();
	virtual void appendChar( WideChar c );
};

struct EntryData
{
	DisplayString *text;				// +0x00
	DisplayString *sText;				// +0x04
	DisplayString *constructText;		// +0x08
	char m_unmodelled0C[ 0x12 - 0x0C ];
	Bool secretText;					// +0x12
	char m_unmodelled13[ 0x1C - 0x13 ];
	unsigned short charPos;				// +0x1C
	unsigned short selectPos;			// +0x1E
	char m_unmodelled20[ 0x24 - 0x20 ];
	Int scrollPos;						// +0x24
};

class Image;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
struct WinDrawData
{
	const Image *image;
	Color color;
	Color borderColor;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	UnsignedInt getState( void ) { return m_state; }

private:
	unsigned char m_unmodelled00[ 8 ];
	UnsignedInt m_state;				// +0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
// The three draw-data arrays sit where W3DStaticTextDraw_Thunk.cpp places
// them: enabled +0x48, disabled +0xB4, hilite +0x120.
class GameWindow
{
public:
	void *winGetUserData();
	Int winGetScreenPosition( Int *x, Int *y );
	Int winGetSize( Int *width, Int *height );
	GameFont *winGetFont();
	GameWindow *winGetParent();
	UnsignedInt winGetStyle();
	UnsignedInt winGetStatus();
	Color winGetEnabledTextColor();
	Color winGetEnabledTextBorderColor();
	Color winGetDisabledTextColor();
	Color winGetDisabledTextBorderColor();
	Color winGetHiliteTextColor();
	Color winGetHiliteTextBorderColor();
	Color winGetIMECompositeTextColor();
	Color winGetIMECompositeBorderColor();

	Color winGetEnabledColor( Int index ) { return m_enabledDrawData[ index ].color; }
	Color winGetEnabledBorderColor( Int index ) { return m_enabledDrawData[ index ].borderColor; }
	Color winGetDisabledColor( Int index ) { return m_disabledDrawData[ index ].color; }
	Color winGetDisabledBorderColor( Int index ) { return m_disabledDrawData[ index ].borderColor; }
	Color winGetHiliteColor( Int index ) { return m_hiliteDrawData[ index ].color; }
	Color winGetHiliteBorderColor( Int index ) { return m_hiliteDrawData[ index ].borderColor; }

private:
	unsigned char m_unmodelled00[ 0x48 ];
	WinDrawData m_enabledDrawData[ 9 ];		// +0x48
	WinDrawData m_disabledDrawData[ 9 ];	// +0xB4
	WinDrawData m_hiliteDrawData[ 9 ];		// +0x120
};

// GadgetTextEntry.h header inlines over draw-data index 0.
inline Color GadgetTextEntryGetEnabledColor( GameWindow *g ) { return g->winGetEnabledColor( 0 ); }
inline Color GadgetTextEntryGetEnabledBorderColor( GameWindow *g ) { return g->winGetEnabledBorderColor( 0 ); }
inline Color GadgetTextEntryGetDisabledColor( GameWindow *g ) { return g->winGetDisabledColor( 0 ); }
inline Color GadgetTextEntryGetDisabledBorderColor( GameWindow *g ) { return g->winGetDisabledBorderColor( 0 ); }
inline Color GadgetTextEntryGetHiliteColor( GameWindow *g ) { return g->winGetHiliteColor( 0 ); }
inline Color GadgetTextEntryGetHiliteBorderColor( GameWindow *g ) { return g->winGetHiliteBorderColor( 0 ); }

inline Int BitTest( UnsignedInt bits, UnsignedInt mask ) { return ( bits & mask ) != 0; }
#define FALSE 0
#define WIN_DRAW_LINE_WIDTH 1.0f

class Rva00478180
{
public:
	Int set( Int a, Int b );
};

class IMEManagerInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Bool isAttachedTo( GameWindow *window );
	virtual void slot3C();
	virtual Bool isComposing();
	virtual void getCompositionString( UnicodeString &string );
	virtual Int getCompositionCursorPosition();
};

class GameWindowManager
{
public:
	virtual void slot000(); virtual void slot004(); virtual void slot008(); virtual void slot00C();
	virtual void slot010(); virtual void slot014(); virtual void slot018(); virtual void slot01C();
	virtual void slot020(); virtual void slot024(); virtual void slot028(); virtual void slot02C();
	virtual void slot030(); virtual void slot034(); virtual void slot038(); virtual void slot03C();
	virtual void slot040(); virtual void slot044(); virtual void slot048(); virtual void slot04C();
	virtual void slot050(); virtual void slot054(); virtual void slot058(); virtual void slot05C();
	virtual void slot060(); virtual void slot064(); virtual void slot068(); virtual void slot06C();
	virtual void slot070(); virtual void slot074(); virtual void slot078(); virtual void slot07C();
	virtual void slot080(); virtual void slot084(); virtual void slot088(); virtual void slot08C();
	virtual void slot090(); virtual void slot094(); virtual void slot098(); virtual void slot09C();
	virtual void slot0A0(); virtual void slot0A4(); virtual void slot0A8();
	virtual GameWindow *winGetFocus();
	virtual void slot0B0(); virtual void slot0B4(); virtual void slot0B8(); virtual void slot0BC();
	virtual void slot0C0(); virtual void slot0C4(); virtual void slot0C8(); virtual void slot0CC();
	virtual void slot0D0(); virtual void slot0D4(); virtual void slot0D8(); virtual void slot0DC();
	virtual void slot0E0(); virtual void slot0E4(); virtual void slot0E8(); virtual void slot0EC();
	virtual void slot0F0(); virtual void slot0F4();
	virtual void winFillRect( Color color, Real width, Int startX, Int startY, Int endX, Int endY );	// +0xF8
	virtual void winOpenRect( Color color, Real width, Int startX, Int startY, Int endX, Int endY );	// +0xFC
};

extern IMEManagerInterface *TheIMEManager;
extern GameWindowManager *TheWindowManager;
extern Int Rva007985E0( Int color );
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );

static void Rva007986C0( GameWindow *window, Color textColor, Color textDropColor,
									Color compositeColor, Color compositeDropColor, Int x, Int y )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	DisplayString *text = e->text;
	Int compositeCursorPos = 0;

	// Check to see if the IME manager is composing text
	e->constructText->setText( UnicodeString::TheEmptyString );
	if( TheIMEManager && TheIMEManager->isAttachedTo( window ) && TheIMEManager->isComposing() )
	{
		UnicodeString composition;

		TheIMEManager->getCompositionString( composition );

		if( e->secretText )
		{
			e->sText->setText( UnicodeString::TheEmptyString );
			Int len = composition.getLength() + e->text->getTextLength();
			for( Int i = 0; i < len; i++ )
				e->sText->appendChar( '*' );
		}
		else
		{
			e->constructText->setText( composition );
			compositeCursorPos = TheIMEManager->getCompositionCursorPosition();
		}
	}

	// get out of here if no text color to show up
	if( textColor == WIN_COLOR_UNDEFINED )
		return;

	// if our text is "secret" we will print only '*' characters
	if( e->secretText )
		text = e->sText;

	// make sure our font is the same as our parents
	if( text->getFont() != window->winGetFont() )
		text->setFont( window->winGetFont() );
	if( e->constructText->getFont() != window->winGetFont() )
		e->constructText->setFont( window->winGetFont() );

	ICoord2D origin, size;
	IRegion2D clipRegion, region;

	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );
	clipRegion.lo.x = origin.x;
	clipRegion.hi.x = origin.x + size.x;
	clipRegion.lo.y = origin.y;
	clipRegion.hi.y = origin.y + size.y;
	text->setClipRegion( &clipRegion );
	e->constructText->setClipRegion( &clipRegion );
	region = clipRegion;

	text->getWidth( e->charPos );
	x += 2 - text->getWidth( e->scrollPos );
	Int cursorPos = x;

	UnsignedInt selectPos = e->selectPos;
	UnsignedInt charPos = e->charPos;
	UnsignedInt selStart = min007986C0( selectPos, charPos );
	UnsignedInt selEnd = max007986C0( selectPos, charPos );
	Int lineHeight = max007986C0( size.y - 4, window->winGetFont()->m_height );

	// the text in front of the selection
	if( selStart > 0 )
	{
		Int textWidth = text->getWidth( selStart );
		region.hi.x = min007986C0( clipRegion.hi.x, x + textWidth );
		text->setClipRegion( &region );
		text->setTextColor( textColor, textDropColor );
		text->draw( x, y, 1, 1 );
		x += textWidth;
		cursorPos += textWidth;
	}

	if( e->constructText->getTextLength() > 0 && charPos == selStart )
	{
		e->constructText->setTextColor( compositeColor, compositeDropColor );
		e->constructText->draw( x, y, 1, 1 );
		cursorPos += e->constructText->getWidth( compositeCursorPos );
		x += e->constructText->getWidth( -1 );
	}

	// the selection
	if( selEnd > selStart )
	{
		Int selWidth = text->getWidth( selEnd ) - text->getWidth( selStart );
		GameWindow *parent = window->winGetParent();
		if( parent && !(parent->winGetStyle() & GWS_COMBO_BOX) )
			parent = NULL;

		if( window == TheWindowManager->winGetFocus() || (parent && parent == TheWindowManager->winGetFocus()) )
		{
			IRegion2D selRegion;
			selRegion.lo.x = max007986C0( x, origin.x );
			selRegion.lo.y = origin.y + 2;
			selRegion.hi.x = min007986C0( x + selWidth, origin.x + size.x );
			selRegion.hi.y = origin.y + lineHeight + 2;
			if( selRegion.lo.x < selRegion.hi.x )
				TheWindowManager->winFillRect( textColor, 1.0f, selRegion.lo.x, selRegion.lo.y, selRegion.hi.x, selRegion.hi.y );
		}

		region.lo.x = max007986C0( clipRegion.lo.x, x );
		region.hi.x = min007986C0( clipRegion.hi.x, x + selWidth );
		text->setClipRegion( &region );
		text->setTextColor( 0xFF000000, Rva007985E0( textDropColor ) );
		text->draw34( x - text->getWidth( selStart ), y );
		x += selWidth;

		if( selEnd == charPos )
		{
			cursorPos += selWidth;
			if( e->constructText->getTextLength() > 0 )
			{
				e->constructText->getWidth( compositeCursorPos );
				e->constructText->setTextColor( compositeColor, compositeDropColor );
				e->constructText->draw( x, y, 1, 1 );
				cursorPos += e->constructText->getWidth( compositeCursorPos );
				x += e->constructText->getWidth( -1 );
			}
		}
	}

	// draw blinking cursor
	GameWindow *parent = window->winGetParent();
	if( parent && !(parent->winGetStyle() & GWS_COMBO_BOX) )
		parent = NULL;

	if( (window == TheWindowManager->winGetFocus() || (parent && parent == TheWindowManager->winGetFocus())) && (timeGetTime() & 0x200) )
		TheWindowManager->winFillRect( textColor, 1.0f, cursorPos, origin.y + 2, cursorPos + 3, origin.y + lineHeight + 2 );
	((Rva00478180 *)window)->set( cursorPos - origin.x + 2, 0 );

	// the text behind the selection
	if( selEnd < (UnsignedInt)text->getTextLength() )
	{
		region.lo.x = max007986C0( clipRegion.lo.x, x );
		region.hi.x = clipRegion.hi.x;
		text->setClipRegion( &region );
		Int w = text->getWidth( selEnd );
		text->setClipRegion( &region );
		text->setTextColor( textColor, textDropColor );
		text->draw( x - w, y, 1, 1 );
	}
}

// A local, address-qualified construction-only view of ICoord2D: no field,
// store, destructor or escaping object, and ICoord2D itself stays in use.
template <class Coord>
struct DefaultConstructed00798f30 : Coord
{
    DefaultConstructed00798f30() {}
};

void W3DGadgetTextEntryDraw( GameWindow *window, WinInstanceData *instData )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	DefaultConstructed00798f30<ICoord2D> origin, size, start, end;
	Color backBorder, backColor, textColor, textBorder, 
			compositeColor, compositeBorder;

	// cancel unichar flag
	*((unsigned char*)e + 0x15) = 0;

	// get size and position of window
	window->winGetScreenPosition( &origin.x, &origin.y );
	window->winGetSize( &size.x, &size.y );

	// get the right colors
	if( BitTest( window->winGetStatus(), WIN_STATUS_ENABLED ) == FALSE )
	{

		compositeColor	= window->winGetDisabledTextColor();
		compositeBorder	= window->winGetDisabledTextBorderColor();
		textColor		= window->winGetDisabledTextColor();
		textBorder	= window->winGetDisabledTextBorderColor();
		backColor		= GadgetTextEntryGetDisabledColor( window );
		backBorder	= GadgetTextEntryGetDisabledBorderColor( window );

	}  // end if, disabled
	else if( BitTest( instData->getState(), WIN_STATE_HILITED ) )
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetHiliteTextColor();
		textBorder	= window->winGetHiliteTextBorderColor();
		backColor		= GadgetTextEntryGetHiliteColor( window );
		backBorder	= GadgetTextEntryGetHiliteBorderColor( window );

	}  // end else if, hilited
	else
	{

		compositeColor	= window->winGetIMECompositeTextColor();
		compositeBorder	= window->winGetIMECompositeBorderColor();
		textColor		= window->winGetEnabledTextColor();
		textBorder	= window->winGetEnabledTextBorderColor();
		backColor		= GadgetTextEntryGetEnabledColor( window );
		backBorder	= GadgetTextEntryGetEnabledBorderColor( window );

	}  // end else, just enabled

	// draw the back border
	if( backBorder != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x;
		start.y = origin.y;
		end.x = start.x + size.x;
		end.y = start.y + size.y;
		TheWindowManager->winOpenRect( backBorder, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the filled back
	if( backColor != WIN_COLOR_UNDEFINED )
	{

		start.x = origin.x + 1;
		start.y = origin.y + 1;
		end.x = start.x + size.x - 2;
		end.y = start.y + size.y - 2;
		TheWindowManager->winFillRect( backColor, WIN_DRAW_LINE_WIDTH,
																	 start.x, start.y, end.x, end.y );

	}  // end if

	// draw the text
	Int textWidth, fontHeight;
	e->text->getSize( &textWidth, &fontHeight );
	Int startOffset = 5;
	volatile Int width;

	width = size.x - (2 * startOffset);
	start.x = origin.x + startOffset;  // offset a little bit into the entry
	if( BitTest( window->winGetStatus(), WIN_STATUS_ONE_LINE ) )
		start.y = size.y / 2 - (fontHeight + 1) / 2;
	else
		start.y = origin.y + startOffset;  // offset a little bit into the entry

	// draw the edit text
	Rva007986C0( window, textColor, textBorder, compositeColor, compositeBorder,
										 start.x, start.y );

}  // end W3DGadgetTextEntryDraw



// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// FILE: TextEntry.cpp ////////////////////////////////////////////////////////
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
// File name: TextEntry.cpp
//
// Created:   Colin Day, June 2001
//
// Desc:      Text entry GUI gadget
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/IMEManager.h"
#include "GameClient/LookAtXlat.h"

// Retail's UnicodeString derives from StringBase<unsigned short> and holds
// nothing of its own, so its copy ctor is a forwarder retail inlines at every
// by-value-return and member-copy site: the bytes encode the base body at
// 0x00888400 (??0?$StringBase@G@@AAE@ABV0@@Z) directly. The vendored
// UnicodeString.h leaves the copy ctor declared and undefined, so without this
// cl emits an out-of-line call to ??0UnicodeString@@QAE@ABV0@@Z instead.
#include "string_base.h"

inline UnicodeString::UnicodeString(const UnicodeString &stringSrc)
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		*(const StringBase<unsigned short> *)&stringSrc);
}


// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////
struct BfmeTextEntrySystemData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	UnsignedInt flags;
	Short maxTextLen;
	UnsignedByte receivedUnichar;
	UnsignedByte drawTextFromStart;
	UnsignedByte systemFlag;
	UnsignedByte padding15[3];
	GameWindow *constructList;
	UnsignedShort charPos;
	UnsignedShort conCharPos;
	UnsignedShort unknown20;
};

struct BfmeUnicodeStringData
{
	UnsignedShort *data;
};

class BfmeTextEntryDisplayString
{
public:
	virtual void slot0( void );
	virtual void setText( UnicodeString text );
	virtual UnicodeString getText( void );
	virtual Int getTextLength( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
	virtual void slot9( void );
	virtual void slot10( void );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual void slot13( void );
	virtual void slot14( void );
	virtual void slot15( void );
	virtual void slot16( void );
	virtual void slot17( void );
	virtual void slot18( void );
	virtual void slot19( void );
	virtual void slot20( void );
	virtual void slot21( void );
	virtual void appendChar( WideChar character );
};

class BfmeDisplayStringManager
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
	virtual void slot9( void );
	virtual void freeDisplayString( DisplayString *string );
};

class BfmeImeManagerInterface
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void slot3( void );
	virtual void slot4( void );
	virtual void slot5( void );
	virtual void slot6( void );
	virtual void slot7( void );
	virtual void slot8( void );
	virtual void attach( GameWindow *window );
	virtual void slot10( void );
	virtual void slot11( void );
	virtual void slot12( void );
	virtual Bool slot13( void );
	virtual Bool isAttachedTo( GameWindow *window );
};

struct Rva005A6790Object
{
	char padding[0x1ec];
	Int value;
	Int setValue( Int value );
};

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif
///////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
static Byte drawCnt = 0;
// static TbIME *ourIME = NULL;  ///< @todo need this for IME kanji support
static GameWindow *curWindow = NULL;  /**< so we can keep track of the input
																					 window when using IME */

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////
extern void GadgetTextEntrySetCursorPosition( GameWindow *window, UnsignedInt pos );

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// GadgetTextEntryInput =======================================================
/** Handle input for text entry field */
//=============================================================================
WindowMsgHandledType GadgetTextEntryInput( GameWindow *window, UnsignedInt msg,
													 WindowMsgData mData1, WindowMsgData mData2 )
{
	EntryData *e = (EntryData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	if ( TheIMEManager && TheIMEManager->isAttachedTo( window) && TheIMEManager->isComposing())
	{
		// ignore input while IME has focus
		return MSG_HANDLED;
	}

	switch( msg ) 
	{
		// ------------------------------------------------------------------------
		case GWM_IME_CHAR:
		{
			WideChar ch = (WideChar) mData1;

			// --------------------------------------------------------------------
			if ( ch == VK_RETURN )
			{
				// Done with this edit
			 		TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
			 																				GEM_EDIT_DONE,
			 																				(WindowMsgData)window, 
			 																				0 );
				return MSG_HANDLED;
			};

			if( ch )
			{
				// Constrain keys based on rules for entry box.
				if( e->numericalOnly )
				{
					if( TheWindowManager->winIsDigit( ch ) == 0 )
						return MSG_HANDLED;
				}
				if( e->alphaNumericalOnly )
				{
					if( TheWindowManager->winIsAlNum( ch ) == 0 )
						return MSG_HANDLED;
				}
				if ( e->aSCIIOnly )
				{
					if ( TheWindowManager->winIsAscii( ch ) == 0 )
					{
						return MSG_HANDLED;
					}
				}

				if( e->charPos < e->maxTextLen-1 )
				{
						e->text->appendChar( ch );
						e->sText->appendChar( L'*' );
						e->charPos++;
						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GEM_UPDATE_TEXT,
																						(WindowMsgData)window, 
																						0 );
				}
			}
			break;
		}
		// ------------------------------------------------------------------------
		case GWM_CHAR:
			if ( BitTest( mData2, KEY_STATE_DOWN ) && BitTest( mData2, KEY_STATE_ALT | KEY_STATE_CONTROL ) )
			{
				return MSG_IGNORED; // text extries shouldn't care about CTRL+* or ALT+*
			}

			switch( mData1 )
			{
				/*
				// --------------------------------------------------------------------
				case KEY_KPENTER:
				case KEY_ENTER:
					// Done with this edit
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						if( e->receivedUnichar == FALSE )
						{
							TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																									GEM_EDIT_DONE,
																									(WindowMsgData)window, 
																									0 );
						}
					}

					break;
				 */
				// --------------------------------------------------------------------
				// Don't process these keys
				case KEY_ESC:
				case KEY_PGUP:
				case KEY_PGDN:
				case KEY_HOME:
				case KEY_END:
				case KEY_F1:
				case KEY_F2:
				case KEY_F3:
				case KEY_F4:
				case KEY_F5:
				case KEY_F6:
				case KEY_F7:
				case KEY_F8:
				case KEY_F9:
				case KEY_F10:
				case KEY_F11:
				case KEY_F12:
				case KEY_CAPS:
				case KEY_DEL:
					return MSG_IGNORED;

				// --------------------------------------------------------------------
				case KEY_DOWN:
				case KEY_RIGHT:
				case KEY_TAB:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						GameWindow *parent;
						parent = window->winGetParent();
						if(parent && !BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
							parent = NULL;
						if(parent)
							TheWindowManager->winNextTab(parent);
						else
							TheWindowManager->winNextTab(window);
					}
					
					break;

				// --------------------------------------------------------------------
				case KEY_UP:
				case KEY_LEFT:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						GameWindow *parent;
						parent = window->winGetParent();
						if(parent && !BitTest(parent->winGetStyle(), GWS_COMBO_BOX))
							parent = NULL;
						if(parent)
							TheWindowManager->winPrevTab(parent);
						else
							TheWindowManager->winPrevTab(window);
					}
					break;

				// --------------------------------------------------------------------
				case KEY_BACKSPACE:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						// if conCharPos != 0 this will fall through to next case.
						// it should be noted that conCharPos can only != 0 in Jap & Kor
						if( e->conCharPos == 0 )
						{
							if( e->charPos > 0 )
							{

								e->text->removeLastChar();
								e->sText->removeLastChar();
								e->charPos--;
								TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																								GEM_UPDATE_TEXT,
																								(WindowMsgData)window, 
																								0 );
							}  // end if
						}
					}
					break;

			}  // end switch( mData1 )

			break;

		// ------------------------------------------------------------------------
		case GWM_LEFT_DOWN:
			BitSet( instData->m_state, WIN_STATE_HILITED );
			TheWindowManager->winSetFocus( window );
			break;

		// ------------------------------------------------------------------------
		case GWM_MOUSE_ENTERING:

			if (BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{

				BitSet( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window, 0 );
				//TheWindowManager->winSetFocus( window );
			}

			break;

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window, 0 );
			}
			break;

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GGM_LEFT_DRAG,
																						(WindowMsgData)window, 0 );
			break;

		// ------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetTextEntryInput

// GadgetTextEntrySystem ======================================================
/** Handle system messages for entry field */
//=============================================================================
WindowMsgHandledType GadgetTextEntrySystem( GameWindow *window, UnsignedInt msg,
																WindowMsgData mData1, WindowMsgData mData2 )
{
	BfmeTextEntrySystemData *e = (BfmeTextEntrySystemData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg )
	{

		// ------------------------------------------------------------------------
		case GEM_GET_TEXT:
			((StringBase<unsigned short> *)mData2)->set(
				*(const StringBase<unsigned short> *)&((BfmeTextEntryDisplayString *)e->text)->getText());
			break;

		// ------------------------------------------------------------------------
		case GEM_SET_TEXT:
		{

			const UnicodeString* ustr = (const UnicodeString*)mData1;
			((BfmeTextEntryDisplayString *)e->text)->setText( *ustr );
			if( TheWindowManager->winGetFocus() == window )
				GadgetTextEntrySetCursorPosition( window, ((BfmeUnicodeStringData *)ustr)->data ? ((BfmeUnicodeStringData *)ustr)->data[2] : 0 );
			else
				GadgetTextEntrySetCursorPosition( window, 0 );
			((BfmeTextEntryDisplayString *)e->constructText)->setText( UnicodeString::TheEmptyString );
			e->conCharPos = e->charPos;
			e->unknown20 = 0;

			// set our secret text string to be filled with '*' the same length
			((BfmeTextEntryDisplayString *)e->sText)->setText( UnicodeString::TheEmptyString );
			Int len = ((BfmeUnicodeStringData *)ustr)->data ? ((BfmeUnicodeStringData *)ustr)->data[2] : 0;
			for( Int i = 0; i < len; i++ )
				((BfmeTextEntryDisplayString *)e->sText)->appendChar( L'*' );

			break;

		}  // end set text

		// ------------------------------------------------------------------------
		case GWM_CREATE:

			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
			if( e && e->systemFlag )
				((Rva005A6790Object *)TheLookAtTranslator)->setValue( 2 );

			// delete the edit display string
			((BfmeDisplayStringManager *)TheDisplayStringManager)->freeDisplayString( e->text );
			((BfmeDisplayStringManager *)TheDisplayStringManager)->freeDisplayString( e->sText );
			((BfmeDisplayStringManager *)TheDisplayStringManager)->freeDisplayString( e->constructText );

			// delete construct list
			if( e->constructList && TheWindowManager )
				TheWindowManager->winDestroy( e->constructList );

			// free all edit data
			delete( (EntryData *)window->winGetUserData() );
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
			if( mData1 == FALSE )
			{
				// If we're losing focus
				/// @todo need to enable this for IME support
				// ourIME->UnActivate();
				if( e->drawTextFromStart )
				{
					e->drawTextFromStart = 0;
					TheWindowManager->winSendSystemMsg( window->winGetOwner(),
																			GEM_EDIT_DONE,
																			(WindowMsgData)window, 1 );
				}
				GadgetTextEntrySetCursorPosition( window, ((BfmeTextEntryDisplayString *)e->text)->getTextLength() );
				e->conCharPos = e->charPos;
				BitClear( instData->m_state, WIN_STATE_SELECTED );
				BitClear( instData->m_state, WIN_STATE_HILITED );
				curWindow = NULL;

				if( e->constructList )
					e->constructList->winHide( TRUE );
				((BfmeTextEntryDisplayString *)e->constructText)->setText( UnicodeString::TheEmptyString );
				e->unknown20 = 0;
				if(TheIMEManager && ((BfmeImeManagerInterface *)TheIMEManager)->isAttachedTo(window))
					((BfmeImeManagerInterface *)TheIMEManager)->attach(NULL);
				//TheIMEManager->detatch();
			}
			else
			{
				GadgetTextEntrySetCursorPosition( window, ((BfmeTextEntryDisplayString *)e->text)->getTextLength() );
				e->conCharPos = 0;
				curWindow = window;
				/// @todo need to enable this for IME support
				if (TheIMEManager)
					((BfmeImeManagerInterface *)TheIMEManager)->attach( window );
				// ourIME->Activate( (void *)ApplicationHWnd );
				BitSet( instData->m_state, WIN_STATE_SELECTED );
				BitSet( instData->m_state, WIN_STATE_HILITED );
				e->drawTextFromStart = 0;
			}

			TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					GGM_FOCUS_CHANGE,
																					mData1, 
																					window->winGetWindowId() );

			*(Bool*)mData2 = TRUE;
			break;

		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetTextEntrySystem

/** @todo we might want to do something like this if we use IME for language
	* support in this product */
/*
// used to create interface to IME
BoolCode InitializeEntryGadget( void )
{
	ourIME = NEW TbIME;

	ourIME->Composition_SetMaxLength( 11 );

	return TRUE;
}

// used to destroy interface to IME
BoolCode ShutdownEntryGadget( void )
{
	delete ourIME;
	ourIME = NULL;

	return TRUE;
}

void InformEntry( WideChar c )
{
	Int i, listCount = 0;
	EntryData *e;

	if( ourIME == NULL || curWindow == NULL )
		return;

	e = (EntryData *)curWindow->winGetUserData();

	if( (	(OurLanguage == LANGUAGE_ID_JAPANESE)			||
				(OurLanguage == LANGUAGE_ID_KOREAN)	)			&&
			(	(e->aSCIIOnly == FALSE )					&&
				(e->alphaNumericalOnly == FALSE )	&&
				(e->numericalOnly == FALSE ) ) )
	{
		e->receivedUnichar = TRUE;

		// we must eat the following keys
		switch( c )
		{
			case L'\a':
			case L'\b':
			case L'\f':
			case L'\t':
			case L'\v':
				return;

			// we must completely ignore the return key
			case L'\r':
			case L'\n':
				e->receivedUnichar = FALSE;
				return;
		}

		if( e->charPos < e->maxTextLen-1 )
		{
			e->text[ e->charPos++ ] = c;
			e->text[ e->charPos ] = 0;
		}

		// always update the construction buffer after a key has come through here.
		TheWindowManager->winStrcpy( e->constructText, (WideChar *)ourIME->Composition_Get() );
		e->conCharPos = NoxStrlen( e->constructText );

		// we might need to update our listbox
		listCount = ourIME->CandidateList_GetSize();

		if( TRUE )	//listCount == 0)
		{
			// if no entries just hide it and leave
			if( e->constructList )
				e->constructList->winHide( TRUE );
		}
		else
		{
			Int maxWidth = 0;
			ListboxData list = NULL;
			ICoord2D constructSize, sliderSize;

			WinHide( e->constructList, FALSE );
			list = (ListBoxData)e->constructList->winGetUserData();

			e->constructList->winGetSize( &constructSize.x, &constructSize.y );
			list->slider->winGetSize( &sliderSize.x, &sliderSize.y );

			TheWindowManager->winSendSystemMsg( e->constructList, GLM_DEL_ALL, 0, 0 );

			for( i=0; i<listCount; i++ )
			{
				Int tempWidth;

				WideChar *text = (WideChar *)ourIME->CandidateList_GetItem( i );

				TheWindowManager->winGetTextSize( e->constructList->instData.font,
																					text, NULL, &tempWidth, 0 );

				if( tempWidth > maxWidth )
					maxWidth = tempWidth;

				UnicodeString tmp(text);
				TheWindowManager->winSendSystemMsg( e->constructList, GLM_ADD_ENTRY,
																						(WindowMsgData)&tmp, -1 );
			}

			e->constructList->winSetSize( maxWidth + sliderSize.y,
																		constructSize.y );
		}
	}
}
*/

// GadgetTextEntrySetFont =====================================================
/** Set the font for a text entry control, we need to set the window
	* text font, the tooltip font, and the edit text display strings for
	* the text data itself and the secret text */
//=============================================================================
void GadgetTextEntrySetFont( GameWindow *g, GameFont *font )
{
	EntryData *entryData = (EntryData *)g->winGetUserData();
	DisplayString *dString;
	typedef void (DisplayString::*BFMESetFontFn)( GameFont * );

	// set the font for the display strings all windows have
	dString = g->winGetInstanceData()->getTextDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
	dString = g->winGetInstanceData()->getTooltipDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );

	// text entry specific
	if( entryData )
	{

		dString = entryData->text;
		if( dString )
			(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
		dString = entryData->sText;
		if( dString )
			(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );

	}  // end if

}  // end GadgetTextEntrySetFont

// GadgetTextEntryGetText =======================================================
/** Get the text for a Text entry */
//=============================================================================
UnicodeString GadgetTextEntryGetText( GameWindow *textentry )
{

	// sanity
	if( textentry == NULL )
		return UnicodeString::TheEmptyString;

	// verify that this is a list box
	if( BitTest( textentry->winGetStyle(), GWS_ENTRY_FIELD ) == FALSE )
		return UnicodeString::TheEmptyString;

	UnicodeString result;
	TheWindowManager->winSendSystemMsg( textentry, GEM_GET_TEXT, 0, (WindowMsgData)&result );
	return result;

}  // end GadgetListBoxGetText

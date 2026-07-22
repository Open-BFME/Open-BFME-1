// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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

// FILE: GadgetComboBox.cpp ///////////////////////////////////////////////////
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
// File name: ListBox.cpp
//
// Created:   Dean Iverson, March 1998
//						Colin Day, June 2001
//
// Desc:      ListBox GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "Common/AudioEventRTS.h"
#include "Common/GameAudio.h"
#include "Common/Debug.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameWindowGlobal.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void HideListBox(GameWindow * window);

// GadgetComboBoxInput =========================================================
/** Handle input for Combo box */
//=============================================================================
WindowMsgHandledType GadgetComboBoxInput( GameWindow *window, UnsignedInt msg,
												 WindowMsgData mData1, WindowMsgData mData2 )
{
//	ComboBoxData *combo = (ComboBoxData *)window->winGetUserData();
	WinInstanceData *instData = window->winGetInstanceData();
	GameWindow *editBox = GadgetComboBoxGetEditBox(window);
	switch (msg)
	{

		// ------------------------------------------------------------------------
		case GWM_CHAR:
		{

			switch (mData1)
			{
				
				// --------------------------------------------------------------------
				case KEY_DOWN:
				case KEY_RIGHT:
				case KEY_TAB:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
						TheWindowManager->winNextTab(window);
					break;

				// --------------------------------------------------------------------
				case KEY_UP:
				case KEY_LEFT:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
						TheWindowManager->winPrevTab(window);
					break;

				// --------------------------------------------------------------------
				default:
					return TheWindowManager->winSendInputMsg( editBox, GWM_CHAR, mData1, mData2 );

			}  // end switch( mData1 )

			break;

		}  // end case char

		// ------------------------------------------------------------------------
		case GWM_WHEEL_DOWN:
		{

			break;

		}  // end wheel down

		// ------------------------------------------------------------------------
		case GWM_WHEEL_UP:
		{
			break;

		}  // end wheel up

		// ------------------------------------------------------------------------
		case GWM_LEFT_UP:
		{
			ComboBoxData *comboData = (ComboBoxData *)window->winGetUserData();
				ICoord2D winSize;
				//ICoord2D winPosition;
				ICoord2D newSize;
				Int listX =0;
				Int multiplier;
				comboData->dontHide = FALSE;
				AudioEventRTS buttonClick("GUIClick");

				if( TheAudio )
				{
					TheAudio->addAudioEvent( &buttonClick );
				}  // end if

				GameWindow *listBox = GadgetComboBoxGetListBox(window);
				if (listBox)
				{
					TheWindowManager->winSetLoneWindow(window);
					// If the Listbox isn't showing, Show it.
					if(listBox->winIsHidden())
					{
						listBox->winHide(FALSE);
						window->winGetSize(&winSize.x, &winSize.y);
						WinInstanceData *listInstData = listBox->winGetInstanceData();
						ListboxData *listData = (ListboxData *)listBox->winGetUserData();
						// If we have less entries then our max display is set to, only show
						// those entries and not additional blank lines.  Also, just so it looks
						// pretty, hide the list box's sliders if we don't need to scroll.
						if(comboData->entryCount <= comboData->maxDisplay)
						{
							multiplier = comboData->entryCount;
							listX = winSize.x;// + 16;
							
							if(listData->upButton)
								listData->upButton->winHide(TRUE);
							if(listData->downButton)
								listData->downButton->winHide(TRUE);
							if(listData->slider)
								listData->slider->winHide(TRUE);
						}
						else
						{
							multiplier = comboData->maxDisplay;
							listX = winSize.x;
							if(listData->upButton)
								listData->upButton->winHide(FALSE);
							if(listData->downButton)
								listData->downButton->winHide(FALSE);
							if(listData->slider)
								listData->slider->winHide(FALSE);
							
						}
						
						newSize.y = ((TheWindowManager->winFontHeight( listInstData->getFont() ) ) * multiplier) + multiplier * 2 + 4;
						window->winSetSize(winSize.x , winSize.y + newSize.y );
						listBox->winSetPosition(0, winSize.y);

						listBox->winSetSize(listX , newSize.y);
					}
					// if the Listbox was showing, hide it.
					else
					{
						HideListBox(window);
					}
				}			break;

		}  // end left click, left up

		// ------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{
			break;

		}  // end right up, right click

/*
		// ------------------------------------------------------------------------
		case GWM_MOUSE_ENTERING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) ) 
			{

				BitSet( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_ENTERING,
																						(WindowMsgData)window, 
																						0 );
				TheWindowManager->winSetFocus( window );

			}  // end if

			break;

		}  //  end mouse entering

		// ------------------------------------------------------------------------
		case GWM_MOUSE_LEAVING:
		{

			if( BitTest( instData->getStyle(), GWS_MOUSE_TRACK )) 
			{

				BitClear( instData->m_state, WIN_STATE_HILITED );
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GBM_MOUSE_LEAVING,
																						(WindowMsgData)window, 
																						0 );
			}  // end if

			break;

		}  // end mouse leaving
*/

		// ------------------------------------------------------------------------
		case GWM_LEFT_DRAG:

			if (BitTest( instData->getStyle(), GWS_MOUSE_TRACK ) )
				TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						GGM_LEFT_DRAG,
																						(WindowMsgData)window, 
																						0 );
			break;

		// ------------------------------------------------------------------------
//		case GWM_LEFT_DOWN:

			// we want to eat the down... so we may receive the up.
//			return MSG_HANDLED;

		//-------------------------------------------------------------------------
		default:
			return MSG_IGNORED;

	}  // end switch msg

	return MSG_HANDLED;

}  // end GadgetComboBoxInput

// HideListBox ================================================================
/** Called to close the listbox if it is opened */
//=============================================================================
void HideListBox(GameWindow * window)
{
	ICoord2D winSize;
	ICoord2D newSize;
	GameWindow *listBox = GadgetComboBoxGetListBox(window);
	if (!listBox)
		return;

	if(!listBox->winIsHidden())
	{
		listBox->winHide(TRUE);
		GameWindow *editBox = GadgetComboBoxGetEditBox(window);
		editBox->winGetSize(&winSize.x, &winSize.y);
		window->winGetSize(&newSize.x, &newSize.y);
		window->winSetSize(newSize.x, winSize.y );
	}
}

// GadgetComboBoxSystem =======================================================
// ?GadgetComboBoxSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// Body in GadgetComboBoxSystem.asm (exact 2153B retail @ 0x004B42F0).
// ZH C++ diverges at prologue stack frame (retail sub esp,0xA4 vs ZH 0x2C)
// and compiled size 2352; identity proved via Ghidra ENTRY + thunk 0x43A887.

// GadgetComboBoxSetColors ====================================================
/** Set the colors for a Combo box, note that this will also automatically
	* change the colors of any attached slider, slider thumb, and slider 
	* buttons */
//=============================================================================
void GadgetComboBoxSetColors( GameWindow *comboBox,
														 Color enabledColor, 
														 Color enabledBorderColor,
														 Color enabledSelectedItemColor, 
														 Color enabledSelectedItemBorderColor,
														 Color disabledColor, 
														 Color disabledBorderColor,
														 Color disabledSelectedItemColor, 
														 Color disabledSelectedItemBorderColor,
														 Color hiliteColor, 
														 Color hiliteBorderColor,
														 Color hiliteSelectedItemColor, 
														 Color hiliteSelectedItemBorderColor )
{
//	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	// enabled

// enabled
		GadgetComboBoxSetEnabledColor( comboBox, enabledColor);
		GadgetComboBoxSetEnabledBorderColor( comboBox, enabledBorderColor );
		GadgetComboBoxSetEnabledSelectedItemColor( comboBox, enabledSelectedItemColor );
		GadgetComboBoxSetEnabledSelectedItemBorderColor( comboBox, enabledSelectedItemBorderColor );
		// disabled
		GadgetComboBoxSetDisabledColor( comboBox, disabledColor );
		GadgetComboBoxSetDisabledBorderColor( comboBox, disabledBorderColor );
		GadgetComboBoxSetDisabledSelectedItemColor( comboBox, disabledSelectedItemColor );
		GadgetComboBoxSetDisabledSelectedItemBorderColor( comboBox, disabledSelectedItemBorderColor );
		// hilite
		GadgetComboBoxSetHiliteColor( comboBox, hiliteColor );
		GadgetComboBoxSetHiliteBorderColor( comboBox,hiliteBorderColor );
		GadgetComboBoxSetHiliteSelectedItemColor( comboBox, hiliteSelectedItemColor );
		GadgetComboBoxSetHiliteSelectedItemBorderColor( comboBox, hiliteSelectedItemBorderColor );
	
	// BFME ComboBoxData child window offsets (see retail SetColors @ 0x4B3590):
	// dropDownButton@+0x24, editBox@+0x28, listBox@+0x2c. Inline ZH getters
	// use 0x20/0x24/0x28 — load fields by offset so this body matches retail.
	// Access order matches source: editBox, dropDownButton, listBox.
	{
		ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
		GameWindow *editBox = NULL;
		if( comboBoxData )
			editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
		if (editBox)
		{
			// enabled
			GadgetButtonSetEnabledColor( editBox, enabledColor );
			GadgetButtonSetEnabledBorderColor( editBox, enabledBorderColor );
			GadgetButtonSetEnabledSelectedColor( editBox, enabledSelectedItemColor );
			GadgetButtonSetEnabledSelectedBorderColor( editBox, enabledSelectedItemBorderColor );
			// disabled
			GadgetButtonSetDisabledColor( editBox, disabledColor );
			GadgetButtonSetDisabledBorderColor( editBox, disabledBorderColor );
			GadgetButtonSetDisabledSelectedColor( editBox, disabledSelectedItemColor );
			GadgetButtonSetDisabledSelectedBorderColor( editBox, disabledSelectedItemBorderColor );
			// hilite
			GadgetButtonSetHiliteColor( editBox,hiliteColor );
			GadgetButtonSetHiliteBorderColor( editBox, hiliteBorderColor );
			GadgetButtonSetHiliteSelectedColor( editBox, hiliteSelectedItemColor );
			GadgetButtonSetHiliteSelectedBorderColor( editBox, hiliteSelectedItemBorderColor );
		}
	}

	{
		ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
		GameWindow *dropDownButton = NULL;
		if( comboBoxData )
			dropDownButton = *(GameWindow **)((char *)comboBoxData + 0x24);
		if (dropDownButton)
		{
			// enabled
			GadgetButtonSetEnabledColor( dropDownButton, enabledColor );
			GadgetButtonSetEnabledBorderColor( dropDownButton, enabledBorderColor );
			GadgetButtonSetEnabledSelectedColor( dropDownButton, enabledSelectedItemColor );
			GadgetButtonSetEnabledSelectedBorderColor( dropDownButton, enabledSelectedItemBorderColor );
			// disabled
			GadgetButtonSetDisabledColor( dropDownButton, disabledColor );
			GadgetButtonSetDisabledBorderColor( dropDownButton, disabledBorderColor );
			GadgetButtonSetDisabledSelectedColor( dropDownButton, disabledSelectedItemColor );
			GadgetButtonSetDisabledSelectedBorderColor( dropDownButton, disabledSelectedItemBorderColor );
			// hilite
			GadgetButtonSetHiliteColor( dropDownButton,hiliteColor );
			GadgetButtonSetHiliteBorderColor( dropDownButton, hiliteBorderColor );
			GadgetButtonSetHiliteSelectedColor( dropDownButton, hiliteSelectedItemColor );
			GadgetButtonSetHiliteSelectedBorderColor( dropDownButton, hiliteSelectedItemBorderColor );
		}
	}

	{
		ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
		GameWindow * listBox = NULL;
		if( comboBoxData )
			listBox = *(GameWindow **)((char *)comboBoxData + 0x2c);
		if ( listBox )
		{
			GadgetListBoxSetColors(listBox,
														enabledColor,
														enabledBorderColor,
														enabledSelectedItemColor,
														enabledSelectedItemBorderColor,
														disabledColor,
														disabledBorderColor,
														disabledSelectedItemColor,
														disabledSelectedItemBorderColor,
														hiliteColor,
														hiliteBorderColor,
														hiliteSelectedItemColor,
														hiliteSelectedItemBorderColor );
		}
	}
}  // end GadgetComboBoxSetColors

// GadgetComboBoxSetIsEditable ================================================
/** Sets up the Text Entry gadget as editable or not */
//=============================================================================
void GadgetComboBoxSetIsEditable(GameWindow *comboBox, Bool isEditable  )
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();	
	GameWindow *editBox = GadgetComboBoxGetEditBox(comboBox);
	UnsignedInt status ;
	if(!editBox)
	 return;

	comboData->isEditable = isEditable;
	if (isEditable)
	{
		status = editBox->winGetStatus();
		
		BitClear(status, WIN_STATUS_NO_INPUT);
//		BitClear(status, WIN_STATUS_NO_FOCUS);
		editBox->winSetStatus(status);
	}
	else
	{
		status = editBox->winGetStatus();
		
		BitSet(status, WIN_STATUS_NO_INPUT);
//		BitSet(status, WIN_STATUS_NO_FOCUS);
		editBox->winSetStatus(status);
	}
}//void GadgetComboBoxSetIsEditable(GameWindow *comboBox, Int maxChars )

// GadgetComboBoxSetIsAsciiOnly ==================================================
/** Get the text the Combo Box */
//=============================================================================
void GadgetComboBoxSetLettersAndNumbersOnly(GameWindow *comboBox, Bool isLettersAndNumbersOnly)
{	
	//sanity
	if(comboBox == NULL)
		return;
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();

	comboData->lettersAndNumbersOnly = isLettersAndNumbersOnly;
	if(comboData->entryData)
		comboData->entryData->alphaNumericalOnly = isLettersAndNumbersOnly;

}

// GadgetComboBoxSetAsciiOnly ==================================================
/** Get the text the Combo Box */
//=============================================================================
void GadgetComboBoxSetAsciiOnly(GameWindow *comboBox, Bool isAsciiOnly  )
{
	//sanity
	if(comboBox == NULL)
		return;
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();

	comboData->asciiOnly = isAsciiOnly;
	if(comboData->entryData)
		comboData->entryData->aSCIIOnly = isAsciiOnly;

}

// GadgetComboBoxSetMaxChars ==================================================
/** Get the text the Combo Box */
//=============================================================================
void GadgetComboBoxSetMaxChars( GameWindow *comboBox, Int maxChars )
{
	//sanity
	if(comboBox == NULL)
		return;

	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	comboData->maxChars = maxChars;
	comboData->entryData->maxTextLen = maxChars;

}//void GadgetComboBoxSetMaxChars( GameWindow *comboBox, Int maxChars )

// GadgetComboBoxSetMaxDisplay ================================================
/** Sets the MaxDisplay variable to the new Max Display */
//=============================================================================
void GadgetComboBoxSetMaxDisplay( GameWindow *comboBox, Int maxDisplay )
{
	ComboBoxData *comboData = (ComboBoxData *)comboBox->winGetUserData();
	comboData->maxDisplay = maxDisplay;

}//void GadgetComboBoxSetMaxDisplay( GameWindow *comboBox, Int maxDisplay );

// GadgetComboBoxGetText =======================================================
/** Get the text the Combo Box */
//=============================================================================
UnicodeString GadgetComboBoxGetText( GameWindow *comboBox )
{

	// sanity
	if( comboBox == NULL )
		return UnicodeString::TheEmptyString;

	// verify that this is a combo box
	if( BitTest( comboBox->winGetStyle(), GWS_COMBO_BOX ) == FALSE )
		return UnicodeString::TheEmptyString;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	return GadgetTextEntryGetText(
		comboBoxData && *(GameWindow **)((char *)comboBoxData + 0x28)
			? *(GameWindow **)((char *)comboBoxData + 0x28)
			: NULL );
}

// GadgetComboBoxSetText =======================================================
/** Set the text the Combo Box */
//=============================================================================
void GadgetComboBoxSetText( GameWindow *comboBox, UnicodeString text )
{
	if( comboBox == NULL )
		return;

	GadgetTextEntrySetText(GadgetComboBoxGetEditBox(comboBox), text);
}

// GadgetComboBoxAddEntry =======================================================
/** Convenience wrapper function for adding an entry */
//=============================================================================
Int GadgetComboBoxAddEntry( GameWindow *comboBox, UnicodeString text, Color color )
{
	// sanity
	if( comboBox == NULL )
		return -1;
	return (Int)TheWindowManager->winSendSystemMsg( comboBox, GCM_ADD_ENTRY, (WindowMsgData)&text, color );
}
// GadgetComboBoxReset =======================================================
/** Convenience wrapper function for resetting the Combo Box entries */
//=============================================================================
void GadgetComboBoxReset( GameWindow *comboBox )
{
	// sanity
	if( comboBox == NULL )
		return;
	// reset via system message
	TheWindowManager->winSendSystemMsg( comboBox, GCM_DEL_ALL, 0, 0 );
}
// GadgetComboBoxHideList =======================================================
/** Convenience wrapper function hiding the list */
//=============================================================================
void GadgetComboBoxHideList( GameWindow *comboBox )
{
	// sanity
	if( comboBox == NULL )
		return;
	// reset via system message
	TheWindowManager->winSendSystemMsg( comboBox, GGM_CLOSE, 0, 0 );
}
// GadgetComboBoxSetFont =======================================================
/** Function used to set the Font of the combo box and all sub gadgets */
//=============================================================================
void GadgetComboBoxSetFont( GameWindow *comboBox, GameFont *font )
{
	// sanity
	if( comboBox == NULL )
		return;

	typedef void (DisplayString::*BFMESetFontFn)( GameFont * );

	// set the ListBox gadget's font (BFME ComboBoxData listBox @ +0x2c)
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	if( comboBoxData )
	{
		GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2c);
		if( listBox )
			listBox->GameWindow::winSetFont( font );
	}

	// set the Text Entry gadget's font (BFME ComboBoxData editBox @ +0x28)
	comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	if( comboBoxData )
	{
		GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
		if( editBox )
			editBox->GameWindow::winSetFont( font );
	}

	// set the font for the display strings all windows have
	// BFME DisplayString::setFont is vtable slot 6 (0x18), same as ListBox/TextEntry
	DisplayString *dString;
	dString = comboBox->winGetInstanceData()->getTextDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
	dString = comboBox->winGetInstanceData()->getTooltipDisplayString();
	if( dString )
		(dString->*(*(BFMESetFontFn *)&(*(void ***)dString)[6]))( font );
}

// GadgetComboBoxSetEnabledTextColors =========================================
/** Set the Enabled Text Colors for the Sub Gadgets*/
//=============================================================================
void GadgetComboBoxSetEnabledTextColors(GameWindow *comboBox, Color color, Color borderColor )
{
	// sanity
	if( comboBox == NULL )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2c);
	if(listBox)
		listBox->winSetEnabledTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetEnabledTextColors(color,borderColor);
}
// GadgetComboBoxSetDisabledTextColors ========================================
/** Set the Disabled Text Colors for the Sub Gadgets */
//=============================================================================
void GadgetComboBoxSetDisabledTextColors(GameWindow *comboBox, Color color, Color borderColor )
{
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	// sanity
	if( comboBox == NULL )
		return;

	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetDisabledTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetDisabledTextColors(color,borderColor);
}
// GadgetComboBoxSetHiliteTextColors ==========================================
/** Set the Hilite Text Colors for the Sub Gadgets */
//=============================================================================
void GadgetComboBoxSetHiliteTextColors( GameWindow *comboBox,Color color, Color borderColor )
{
	// sanity
	if( comboBox == NULL )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();
	
	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetHiliteTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetHiliteTextColors(color,borderColor);
}
// GadgetComboBoxSetIMECompositeTextColors ====================================
/** Set the IME Composite Text Colors Text Colors for the Sub Gadgets */
//=============================================================================
void GadgetComboBoxSetIMECompositeTextColors(GameWindow *comboBox, Color color, Color borderColor )
{
	// sanity
	if( comboBox == NULL )
		return;
	
	ComboBoxData *comboBoxData = (ComboBoxData *)comboBox->winGetUserData();

	GameWindow *listBox = *(GameWindow **)((char *)comboBoxData + 0x2C);
	if(listBox)
		listBox->winSetIMECompositeTextColors( color,borderColor);
	GameWindow *editBox = *(GameWindow **)((char *)comboBoxData + 0x28);
	if(editBox)
		editBox->winSetIMECompositeTextColors(color,borderColor);
}

// GadgetComboBoxGetSelectedPos ===============================================
/** Convenience wrapper function for getting the selected Position */
//=============================================================================
void GadgetComboBoxGetSelectedPos( GameWindow *comboBox, Int *selectedIndex )
{
	// sanity
	if( comboBox == NULL )
		return;

	// get selected indeces via system message
	TheWindowManager->winSendSystemMsg( comboBox, GCM_GET_SELECTION, 0, (WindowMsgData)selectedIndex );
}

// GadgetComboBoxSetSelectedPos ===============================================
/** Convenience wrapper function for setting the selected Position, if don't hide
		is set to true, the listbox won't be forced to hide when the Selected call is
		passed back */
//=============================================================================
void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, Int selectedIndex, Bool dontHide )
{
	// sanity
	if( comboBox == NULL )
		return;

	// get selected indeces via system message
	TheWindowManager->winSendSystemMsg( comboBox, GCM_SET_SELECTION, selectedIndex, dontHide );
}
// GadgetComboBoxSetItemData ==================================================
/** Convenience wrapper function for setting the Item data for the listbox under the combo box */
//=============================================================================
void GadgetComboBoxSetItemData( GameWindow *comboBox, Int index, void *data )
{
	if (comboBox)
		TheWindowManager->winSendSystemMsg( comboBox, GCM_SET_ITEM_DATA, index, (WindowMsgData)data);
}
// GadgetComboBoxGetItemData ==================================================
/** Convenience wrapper function for getting the Item data from the listbox under the combo Box */
//=============================================================================
void *GadgetComboBoxGetItemData( GameWindow *comboBox, Int index )
{
	void *data = NULL;
	
	if (comboBox)
	{
		TheWindowManager->winSendSystemMsg( comboBox, GCM_GET_ITEM_DATA, index, (WindowMsgData)&data);
	}
	return (data);
}

// GadgetComboBoxGetLength =================================================
/** Get the list length data contained in the listboxData
	* parameter. */
//=============================================================================
Int GadgetComboBoxGetLength( GameWindow *combobox )
{
	ComboBoxData *comboboxData = (ComboBoxData *)combobox->winGetUserData();
	if (comboboxData)
		return *(Int *)((char *)comboboxData + 0x20);

	return 0;
}  // end GadgetListBoxGetListLength

// Keep GadgetComboBoxGetDropDownButton COMDAT in this TU (was only referenced by
// SetColors before the BFME field-offset hardcode; 23B matched at 0x0047A560).
GameWindow *GadgetComboBox_force_GetDropDownButton(GameWindow *g)
{
	return GadgetComboBoxGetDropDownButton(g);
}

// Keep GadgetTextEntrySetTextColor COMDAT in this TU (was only referenced by the
// old C++ GadgetComboBoxSystem body; 53B matched at 0x004B3530). Header declares
// it inline — taking its address forces an out-of-line COMDAT emission.
void (*GadgetComboBox_force_TextEntrySetTextColor)(GameWindow *, Color) =
	&GadgetTextEntrySetTextColor;

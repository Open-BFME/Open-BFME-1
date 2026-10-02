// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
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

// FILE: RadioButton.cpp //////////////////////////////////////////////////////
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
// File name: \projects\RTS\code\gameengine\Source\GameClient\GUI\Gadget\GadgetTabControl.cpp
//
// Created:   Graham Smallwood, November 2001
//
// Desc:      Tab Set GUI control
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Common/Language.h"
#include "Gameclient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetTabControl.h"

// DEFINES ////////////////////////////////////////////////////////////////////

// PRIVATE TYPES //////////////////////////////////////////////////////////////

// PRIVATE DATA ///////////////////////////////////////////////////////////////

// PUBLIC DATA ////////////////////////////////////////////////////////////////

// PRIVATE PROTOTYPES /////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////

// GadgetTabControlInput =====================================================
/** Handle input for TabControl */
//=============================================================================
WindowMsgHandledType GadgetTabControlInput( GameWindow *tabControl, UnsignedInt msg,
														 WindowMsgData mData1, WindowMsgData mData2 )
{
//	WinInstanceData *instData = tabControl->winGetInstanceData();
	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	Int tabX, tabY;
	tabControl->winGetScreenPosition( &tabX, &tabY );
	Int mouseX = LOLONGTOSHORT(mData1) - tabX;//mData1 is packedMouseCoords in screen space
	Int mouseY = HILONGTOSHORT(mData1) - tabY;
	Int tabsLeft = tabData->tabsLeftLimit;
	Int tabsRight = tabData->tabsRightLimit;
	Int tabsBottom = tabData->tabsBottomLimit;
	Int tabsTop = tabData->tabsTopLimit;

	switch( msg ) 
	{
		case GWM_LEFT_DOWN:
		{
			if(		(mouseX < tabsLeft)
					|| (mouseX > tabsRight)
					|| (mouseY < tabsTop)
					|| (mouseY > tabsBottom)
					)
			{//I eat input on myself that isn't a tab (a button click would mean I don't see the input ever.)
				return MSG_HANDLED;
			}

			Int distanceIn;
			Int tabSize;
			if( (tabData->tabEdge == TP_RIGHT_SIDE) || (tabData->tabEdge == TP_LEFT_SIDE) )
			{//scan down to find which button
				distanceIn = mouseY - tabsTop;
				tabSize = tabData->tabHeight;
			}
			else
			{//scan right to find which button
				distanceIn = mouseX - tabsLeft;
				tabSize = tabData->tabWidth;
			}
			Int tabPressed = distanceIn / tabSize;
			if( ! tabData->subPaneDisabled[tabPressed]  &&  (tabPressed != tabData->activeTab) )
				GadgetTabControlShowSubPane( tabControl, tabPressed );
		}

		default:
		{
			return MSG_IGNORED;
		}
	}

	return MSG_HANDLED;

}  // end GadgetTabControlInput

// GadgetTabControlSystem ====================================================
/** Handle system messages for TabControl */
//=============================================================================
WindowMsgHandledType GadgetTabControlSystem( GameWindow *tabControl, UnsignedInt msg,
															WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg ) 
	{
		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
		{
			TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

			// free tab control user data
			delete tabData;

			break;
		
		}  // end destroy

		case GGM_RESIZED:
		{//On resize, we need to upkeep the pane sizes and tabs since they are bound to us
			GadgetTabControlResizeSubPanes( tabControl );
			GadgetTabControlComputeTabRegion( tabControl );

			break;
		}

		case GBM_SELECTED:
		{//Pass buttons messages up
			GameWindow *parent = tabControl->winGetParent();

			if( parent )
				return TheWindowManager->winSendSystemMsg( parent, msg, mData1, mData2 );
		}

		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetTabControlSystem

void GadgetTabControlComputeTabRegion( GameWindow *tabControl )///< Recalc the tab positions based on userData
{
	Int winWidth, winHeight;
	tabControl->winGetSize( &winWidth, &winHeight );

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	Int horzOffset = 0, vertOffset = 0;
	if( (tabData->tabEdge == TP_TOP_SIDE)  ||  (tabData->tabEdge == TP_BOTTOM_SIDE) )
	{
		if( tabData->tabOrientation == TP_CENTER )
		{
			horzOffset = winWidth - ( 2 * tabData->paneBorder ) - ( tabData->tabCount * tabData->tabWidth );
			horzOffset /= 2;
		}
		else if( tabData->tabOrientation == TP_BOTTOMRIGHT )
		{
			horzOffset = winWidth - ( 2 * tabData->paneBorder ) - ( tabData->tabCount * tabData->tabWidth );
		}
		else if( tabData->tabOrientation == TP_TOPLEFT )
		{
			horzOffset = 0;
		}
	}
	else
	{
		if( tabData->tabOrientation == TP_CENTER )
		{
			vertOffset = winHeight - ( 2 * tabData->paneBorder ) - ( tabData->tabCount * tabData->tabHeight );
			vertOffset /= 2;
		}
		else if( tabData->tabOrientation == TP_BOTTOMRIGHT )
		{
			vertOffset = winHeight - ( 2 * tabData->paneBorder ) - ( tabData->tabCount * tabData->tabHeight );
		}
		else if( tabData->tabOrientation == TP_TOPLEFT )
		{
			vertOffset = 0;
		}
	}

	if( tabData->tabEdge == TP_TOP_SIDE )
	{
		tabData->tabsTopLimit = tabData->paneBorder;
		tabData->tabsBottomLimit = tabData->paneBorder + tabData->tabHeight;
		tabData->tabsLeftLimit = tabData->paneBorder + horzOffset;
		tabData->tabsRightLimit = tabData->paneBorder + horzOffset + ( tabData->tabWidth * tabData->tabCount );
	}
	else if( tabData->tabEdge == TP_BOTTOM_SIDE )
	{
		tabData->tabsTopLimit = winHeight - tabData->paneBorder - tabData->tabHeight;
		tabData->tabsBottomLimit = winHeight - tabData->paneBorder;
		tabData->tabsLeftLimit = tabData->paneBorder + horzOffset;
		tabData->tabsRightLimit = tabData->paneBorder + horzOffset + ( tabData->tabWidth * tabData->tabCount );
	}
	else if( tabData->tabEdge == TP_RIGHT_SIDE )
	{
		tabData->tabsLeftLimit = winWidth - tabData->paneBorder - tabData->tabWidth;
		tabData->tabsRightLimit = winWidth - tabData->paneBorder;
		tabData->tabsTopLimit = tabData->paneBorder + vertOffset;
		tabData->tabsBottomLimit = tabData->paneBorder + vertOffset + ( tabData->tabHeight * tabData->tabCount );
	}
	else if( tabData->tabEdge == TP_LEFT_SIDE )
	{
		tabData->tabsLeftLimit = tabData->paneBorder;
		tabData->tabsRightLimit = tabData->paneBorder + tabData->tabWidth;
		tabData->tabsTopLimit = tabData->paneBorder + vertOffset;
		tabData->tabsBottomLimit = tabData->paneBorder + vertOffset + ( tabData->tabHeight * tabData->tabCount );
	}

}

void GadgetTabControlComputeSubPaneSize( GameWindow *tabControl, Int *width, Int *height, Int *x, Int *y )
{
	Int winWidth, winHeight;
	tabControl->winGetSize( &winWidth, &winHeight );

	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	if( (tabData->tabEdge == TP_TOP_SIDE)  ||  (tabData->tabEdge == TP_BOTTOM_SIDE) )
		*height = winHeight - (2 * tabData->paneBorder) - tabData->tabHeight;
	else
		*height = winHeight - (2 * tabData->paneBorder);

	if( (tabData->tabEdge == TP_LEFT_SIDE)  ||  (tabData->tabEdge == TP_RIGHT_SIDE) )
		*width = winWidth - (2 * tabData->paneBorder) - tabData->tabWidth;
	else
		*width = winWidth - (2 * tabData->paneBorder);

	if( tabData->tabEdge == TP_LEFT_SIDE )
		*x = tabData->paneBorder + tabData->tabWidth;
	else
		*x = tabData->paneBorder;

	if( tabData->tabEdge == TP_TOP_SIDE )
		*y = tabData->paneBorder + tabData->tabHeight;
	else
		*y = tabData->paneBorder;
}

void GadgetTabControlShowSubPane( GameWindow *tabControl, Int whichPane)
{
	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();

	for( Int paneIndex = 0; paneIndex < NUM_TAB_PANES; paneIndex++ )
	{
		if( tabData->subPanes[paneIndex] != NULL )
			tabData->subPanes[paneIndex]->winHide( true );
	}
	if( tabData->subPanes[whichPane] )
		tabData->activeTab = whichPane;
	else
		tabData->activeTab = 0;

	Int tabCountMinusOne = tabData->tabCount - 1;
	Int *activeTabSrc = (tabData->activeTab < tabCountMinusOne) ? &tabData->activeTab : &tabCountMinusOne;
	tabData->activeTab = *activeTabSrc;

	tabData->subPanes[tabData->activeTab]->winHide( false );
}

void GadgetTabControlResizeSubPanes( GameWindow *tabControl )
{
	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();
	Int width, height, x, y;
	GadgetTabControlComputeSubPaneSize(tabControl, &width, &height, &x, &y);
	for( Int paneIndex = 0; paneIndex < NUM_TAB_PANES; paneIndex++ )
	{
		if( tabData->subPanes[paneIndex] )
		{
			tabData->subPanes[paneIndex]->winSetSize( width, height );
			tabData->subPanes[paneIndex]->winSetPosition( x, y );
		}
	}
}

///<In game creation finished, hook up Children to SubPane array
void GadgetTabControlFixupSubPaneList( GameWindow *tabControl )
{
	Int childIndex =0;
	TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();
	GameWindow *child = tabControl->winGetChild();
	if( child )
	{//need to write down children, and they are reversed from our array
		while( child->winGetNext() != NULL )
		{
			child = child->winGetNext();
		}

		while( child )
		{
			tabData->subPanes[childIndex] = child;
			childIndex++;
			child = child->winGetPrev();
		}
	}
}

// BFME's factory consumes a 52-byte record, not the ZH scalar argument list.
// Slots not assigned by this caller retain their constructor's zero values.
#include "string_base.h"
struct Rva004BDE80CreateData {
    GameWindow *slot_00;
    unsigned slot_04;
    int slot_08, slot_0c, slot_10, slot_14, slot_18;
    GameWinSystemFunc slot_1c;
    unsigned slot_20, slot_24, slot_28, slot_2c;
    WinInstanceData *slot_30;
    Rva004BDE80CreateData() : slot_00(0), slot_04(0), slot_08(0),
        slot_0c(0), slot_10(0), slot_14(0), slot_18(0), slot_1c(0),
        slot_20(0), slot_24(0), slot_28(0), slot_2c(0), slot_30(0) {}
};
class Rva004BDE80ManagerView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
    virtual void slot_54();
    virtual void slot_58();
    virtual void slot_5c();
    virtual void slot_60();
    virtual void slot_64();
    virtual void slot_68();
    virtual void slot_6c();
    virtual void slot_70();
    virtual GameWindow *slot_74(Rva004BDE80CreateData *record);
};
void GadgetTabControlCreateSubPanes(GameWindow *tabControl)
{
    TabControlData *tabData = (TabControlData *)tabControl->winGetUserData();
    Int width, height, x, y;
    GadgetTabControlComputeSubPaneSize(tabControl, &width, &height, &x, &y);
    for (Int paneIndex = 0; paneIndex < NUM_TAB_PANES; paneIndex++) {
        if (tabData->subPanes[paneIndex] == NULL) {
            Rva004BDE80CreateData record;
            record.slot_00 = tabControl;
            record.slot_04 = WIN_STATUS_NONE;
            record.slot_08 = x;
            record.slot_0c = y;
            record.slot_1c = PassSelectedButtonsToParentSystem;
            tabData->subPanes[paneIndex] =
                ((Rva004BDE80ManagerView *)TheWindowManager)->slot_74(&record);
            WinInstanceData *instData = tabData->subPanes[paneIndex]->winGetInstanceData();
            BitSet(instData->m_style, GWS_TAB_PANE);
            char buffer[20];
            sprintf(buffer, "Pane %d", paneIndex);
            ((StringBase<char> *)&instData->m_decoratedNameString)->set(buffer, strlen(buffer));
            tabData->subPanes[paneIndex]->winEnable(BitTest(tabControl->winGetStatus(), WIN_STATUS_ENABLED));
        } else {
            tabData->subPanes[paneIndex]->winSetSize(width, height);
            tabData->subPanes[paneIndex]->winSetPosition(x, y);
        }
    }
    GadgetTabControlShowSubPane(tabControl, tabData->activeTab);
}

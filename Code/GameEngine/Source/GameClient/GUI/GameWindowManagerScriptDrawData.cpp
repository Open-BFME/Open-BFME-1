// cl: -Ireference/shims/stringbaseascii -Ireference/shims/stringbaseunicode -D__PLACEMENT_VEC_NEW_INLINE -D_STLP_USE_STATIC_LIB -DBFME_STLP_NODE_ALLOC -Ireference/shims/stlp_nodealloc -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/shims/sweep -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -ICode/Libraries/Source/WWVegas/WWLib
// stlport
// BFME window draw-data parser, RVA 0x00485EE0, 1221 bytes.
// Upstream: GeneralsMD GameWindowManagerScript.cpp; string-base ABI shims
// preserve the retail AsciiString temporary construction and destruction.
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

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// USER INCLUDES //////////////////////////////////////////////////////////////
#include "Lib/BaseType.h"
#include "Common/Debug.h"
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameMemory.h"
#include "Common/NameKeyGenerator.h"
#include "Common/FunctionLexicon.h"
#include "GameClient/Display.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Gadget.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindowGlobal.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTabControl.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetRadioButton.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetSlider.h"
#include "GameClient/GameText.h"
#include "GameClient/HeaderTemplate.h"

extern WinDrawData enabledDropDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledDropDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteDropDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledEditBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledEditBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteEditBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledListBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledListBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteListBoxDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledUpButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledUpButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteUpButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteDownButtonDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledSliderDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledSliderDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteSliderDrawData[ MAX_DRAW_DATA ];
extern WinDrawData enabledSliderThumbDrawData[ MAX_DRAW_DATA ];
extern WinDrawData disabledSliderThumbDrawData[ MAX_DRAW_DATA ];
extern WinDrawData hiliteSliderThumbDrawData[ MAX_DRAW_DATA ];

static Int scanUnsignedInt( const char *source, UnsignedInt& val )
{
	Int ret = sscanf( source, "%d", &val ); // not strictly necessary to wrap this, but it's more consistent

	return ret;
}  // end scanUnsignedInt

Bool parseDrawData( char *token, WinInstanceData *instData,
													 char *buffer, void *data )
{
	Int i;
	UnsignedInt r, g, b, a;
	WinDrawData *drawData;
	Bool first = TRUE;
	char *c;
	char *seps       = " :,\n\r\t";

	for( i = 0; i < MAX_DRAW_DATA; i++ )
	{

		// get the right draw data
		if( strcmp( token, "ENABLEDDRAWDATA" ) == 0 )	
			drawData = &instData->m_enabledDrawData[ i ];
		else if( strcmp( token, "DISABLEDDRAWDATA" ) == 0 )	
			drawData = &instData->m_disabledDrawData[ i ];
		else if( strcmp( token, "HILITEDRAWDATA" ) == 0 )	
			drawData = &instData->m_hiliteDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDUPBUTTONDRAWDATA" ) == 0 )
			drawData = &enabledUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDUPBUTTONDRAWDATA" ) == 0 )
			drawData = &disabledUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITEUPBUTTONDRAWDATA" ) == 0 )
			drawData = &hiliteUpButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &enabledDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &disabledDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITEDOWNBUTTONDRAWDATA" ) == 0 )
			drawData = &hiliteDownButtonDrawData[ i ];
		else if( strcmp( token, "LISTBOXENABLEDSLIDERDRAWDATA" ) == 0 )
			drawData = &enabledSliderDrawData[ i ];
		else if( strcmp( token, "LISTBOXDISABLEDSLIDERDRAWDATA" ) == 0 )
			drawData = &disabledSliderDrawData[ i ];
		else if( strcmp( token, "LISTBOXHILITESLIDERDRAWDATA" ) == 0 )
			drawData = &hiliteSliderDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledSliderThumbDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledSliderThumbDrawData[ i ];
		else if( strcmp( token, "SLIDERTHUMBHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteSliderThumbDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXDROPDOWNBUTTONHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteDropDownButtonDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXEDITBOXHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteEditBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXENABLEDDRAWDATA" ) == 0 )
			drawData = &enabledListBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXDISABLEDDRAWDATA" ) == 0 )
			drawData = &disabledListBoxDrawData[ i ];
		else if( strcmp( token, "COMBOBOXLISTBOXHILITEDRAWDATA" ) == 0 )
			drawData = &hiliteListBoxDrawData[ i ];
		else
		{

			DEBUG_LOG(( "ParseDrawData, undefined token '%s'\n", token ));
			assert( 0 );
			return FALSE;

		}  // end else

		// IMAGE: X
		if( first == TRUE )
			c = strtok( buffer, seps );  // label
		else
			c = strtok( NULL, seps );  // label
		first = FALSE;
	
		c = strtok( NULL, seps );  // value
		if( strcmp( c, "NoImage" ) )
			drawData->image = TheMappedImageCollection->findImageByName( AsciiString( c ) );
		else
			drawData->image = NULL;
		// COLOR: R G B A
		c = strtok( NULL, seps );  // label
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		drawData->color = GameMakeColor( r, g, b, a );

		// BORDERCOLOR: R G B A
		c = strtok( NULL, seps );  // label
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, r );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, g );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, b );
		c = strtok( NULL, seps );  // value
		scanUnsignedInt( c, a );
		drawData->borderColor = GameMakeColor( r, g, b, a );

	}  // end for i

	return TRUE;

}  // end parseDrawData

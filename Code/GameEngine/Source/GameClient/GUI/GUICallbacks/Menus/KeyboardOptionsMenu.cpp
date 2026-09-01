// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// FILE: KeyboardOptionsMenu.cpp //////////////////////////////////////////////
//
// No port of Zero Hour's KeyboardOptionsMenu.cpp existed under Code/. This is a
// partial one: the Input callback the .data callback table names at 0x004C9290.
// The body is Zero Hour's unchanged - it is the same escape-key handler five
// other menus in this directory carry - and the shims are the standard menu set.
//
///////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"

#include "Common/NameKeyGenerator.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/WindowLayout.h"

static GameWindow *listBoxCommandList = NULL;

struct BfmeMetaMapRec
{
	BfmeMetaMapRec *next;
	unsigned char padding[0x14];
	MappableKeyCategories category;
	unsigned int key;
	UnicodeString displayName;
};

struct BfmeMetaMap
{
	unsigned char padding[8];
	BfmeMetaMapRec *first;
};

void fillCommandListBox( MappableKeyCategories cat )
{
	if (!listBoxCommandList)
		return;

	GadgetListBoxReset(listBoxCommandList);
	Color color = GameMakeColor(255, 255, 255, 255);

	BfmeMetaMap *metaMap = (BfmeMetaMap *)TheMetaMap;
	for (const BfmeMetaMapRec *rec = metaMap->first; rec; rec = rec->next)
	{
		if (rec->category == cat)
			GadgetListBoxAddEntryText(listBoxCommandList, rec->displayName, color, -1, -1);
	}
}

//-------------------------------------------------------------------------------------------------
/** keyboard options menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType KeyboardOptionsMenuInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{

	switch( msg )
	{

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;

			switch( key )
			{

				// ----------------------------------------------------------------------------------------
				case KEY_ESC:
				{

					//
					// send a simulated selected event to the parent window of the
					// back/exit button
					//
					if( BitTest( state, KEY_STATE_UP ) )
					{
						AsciiString buttonName( "KeyboardOptionsMenu.wnd:ButtonBack" );
						NameKeyType buttonID = TheNameKeyGenerator->nameToKey( buttonName );
						GameWindow *button = TheWindowManager->winGetWindowFromId( window, buttonID );

						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED,
																								(WindowMsgData)button, buttonID );

					}  // end if

					// don't let key fall through anywhere else
					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;

}  // end KeyboardOptionsMenuInput

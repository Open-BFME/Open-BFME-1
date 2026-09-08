// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// FILE: KeyboardOptionsMenu.cpp //////////////////////////////////////////////
//
// Port of the Zero Hour KeyboardOptionsMenu.cpp initializer and input callback.
// The initializer is the retail KeyboardOptionsMenu.wnd control setup; the
// input body is the unchanged escape-key handler shared by the sibling menus.
//
///////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"

#include "../../../../../../reference/shims/displaystring/GameClient/DisplayString.h"

#include "Common/NameKeyGenerator.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GameText.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/MetaEvent.h"
#include "GameClient/WindowLayout.h"

static NameKeyType buttonBackID = NAMEKEY_INVALID;
static GameWindow *buttonBack = NULL;

static NameKeyType parentKeyboardOptionsMenuID = NAMEKEY_INVALID;
static GameWindow *parentKeyboardOptionsMenu = NULL;

static NameKeyType comboBoxCategoryListID = NAMEKEY_INVALID;
static GameWindow *comboBoxCategoryList = NULL;

static NameKeyType listBoxCommandListID = NAMEKEY_INVALID;
static GameWindow *listBoxCommandList = NULL;

static NameKeyType staticTextDescriptionID = NAMEKEY_INVALID;
static GameWindow *staticTextDescription = NULL;

static NameKeyType staticTextCurrentHotkeyID = NAMEKEY_INVALID;
static GameWindow *staticTextCurrentHotkey = NULL;

static NameKeyType buttonResetAllID = NAMEKEY_INVALID;
static GameWindow *buttonResetAll = NULL;

static NameKeyType textEntryAssignHotkeyID = NAMEKEY_INVALID;
static GameWindow *textEntryAssignHotkey = NULL;

static NameKeyType buttonAssignID = NAMEKEY_INVALID;
static GameWindow *buttonAssign = NULL;

UnicodeString alt;
UnicodeString ctrl;
UnicodeString shift;

// The retail initializer calls these already-published ILT entry points.  The
// callback is installed through the ILT as a GameWinInputFunc, so its machine
// ABI is taken from GameWindow rather than guessed from the thunk's neutral
// generated declaration.
extern void j_00004f7a();
extern void j_000189c6();

void fillCommandListBox( MappableKeyCategories cat );

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

struct BfmeKeyboardEntryData
{
	DisplayString *text;
	DisplayString *sText;
	DisplayString *constructText;
	Bool secretText;
	Bool numericalOnly;
	Bool alphaNumericalOnly;
	Bool aSCIIOnly;
	Short maxTextLen;
	Bool receivedUnichar;
	Bool drawTextFromStart;
	GameWindow *constructList;
	void *bfmeEntryPad;
	UnsignedShort charPos;
	UnsignedShort conCharPos;
};

class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

void KeyboardOptionsMenuInit( WindowLayout *layout, void *userData )
{
	parentKeyboardOptionsMenuID = TheNameKeyGenerator->nameToKey("KeyboardOptionsMenu.wnd:ParentKeyboardOptionsMenu");
	parentKeyboardOptionsMenu = TheWindowManager->winGetWindowFromId( NULL, parentKeyboardOptionsMenuID );

	buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString("KeyboardOptionsMenu.wnd:ButtonBack") );
	buttonBack = TheWindowManager->winGetWindowFromId( parentKeyboardOptionsMenu, buttonBackID );

	comboBoxCategoryListID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:ComboBoxCategoryList" );
	comboBoxCategoryList = TheWindowManager->winGetWindowFromId( NULL, comboBoxCategoryListID );

	listBoxCommandListID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:ListBoxCommandList" );
	listBoxCommandList = TheWindowManager->winGetWindowFromId( NULL, listBoxCommandListID );

	staticTextDescriptionID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:StaticTextDescription" );
	staticTextDescription = TheWindowManager->winGetWindowFromId( NULL, staticTextDescriptionID );

	staticTextCurrentHotkeyID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:StaticTextCurrentHotkey" );
	staticTextCurrentHotkey = TheWindowManager->winGetWindowFromId( NULL, staticTextCurrentHotkeyID );

	buttonResetAllID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:ButtonResetAll" );
	buttonResetAll = TheWindowManager->winGetWindowFromId( NULL, buttonResetAllID );

	textEntryAssignHotkeyID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:TextEntryAssignHotkey" );
	textEntryAssignHotkey = TheWindowManager->winGetWindowFromId( NULL, textEntryAssignHotkeyID );

	buttonAssignID = TheNameKeyGenerator->nameToKey( "KeyboardOptionsMenu.wnd:ButtonAssign" );
	buttonAssign = TheWindowManager->winGetWindowFromId( NULL, buttonAssignID );

	textEntryAssignHotkey->winSetInputFunc( (GameWinInputFunc)j_000189c6 );
	j_00004f7a();
	fillCommandListBox( CATEGORY_CONTROL );
	textEntryAssignHotkey->winEnable( false );

	BfmeKeyboardEntryData *e = (BfmeKeyboardEntryData *)textEntryAssignHotkey->winGetUserData();
	e->text->setText( UnicodeString::TheEmptyString );
	e->charPos = e->text->getTextLength();

	alt = TheGameText->fetch( "KEYBOARD:Alt+" );
	ctrl = TheGameText->fetch( "KEYBOARD:Ctrl+" );
	shift = TheGameText->fetch( "KEYBOARD:Shift+" );

	((BfmeVirtualHideLayout *)layout)->hide( FALSE );
	TheWindowManager->winSetFocus( parentKeyboardOptionsMenu );
}

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

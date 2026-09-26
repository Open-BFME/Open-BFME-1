// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
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

#include "../../../../../../inputs/reference/shims/displaystring/GameClient/DisplayString.h"

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

// KeyboardTextEntryInput identity: the byte-matched initializer above installs
// ILT 0x000189C6, which jumps to 0x004CA140. The ZH callback has the same
// ordered modifier, text-entry, and mouse branches. Native instruction witnesses
// and boundary/table verification are recorded in build/unclaimed_map/astra_N/.
// BFME text-entry and IME access views. Unread fields stay opaque.
class Rva004CA140DisplayString {
public:
 virtual ~Rva004CA140DisplayString();
 virtual void setText(UnicodeString);
 virtual UnicodeString getText();
 virtual int getTextLength();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual void slot0e();
 virtual void slot0f();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void removeLastChar();
 virtual void appendChar(WideChar);
};
struct Rva004CA140EntryData {
 Rva004CA140DisplayString *text, *sText;
 void *opaque08;
 unsigned int flags;
 unsigned char opaque10[0xc];
 unsigned short charPos;
 unsigned short opaque1e;
 unsigned short conCharPos;
};
extern Bool shiftDown, ctrlDown, altDown, absolute;
void doKeyDown(EntryData *, UnicodeString);
void doKeyUp(EntryData *, UnicodeString);
void setKeyDown(UnicodeString, Bool);
// ILT 0x000275C0 routes to the matched character-policy body 0x000861E0.
// This caller pushes the complete 32-bit flags value at 0x004CA1D7..1DC.
// The callee uses its low-byte bits. Preserve that witnessed stack contract
// through the existing address-owned thunk; no speculative typed pin.
extern void j_000275c0();
class Rva004CA140IMEManager {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot0a();
 virtual void slot0b();
 virtual void slot0c();
 virtual void slot0d();
 virtual Bool isAttachedTo(GameWindow *);
 virtual void slot3c();
 virtual Bool isComposing();
};
#include "GameClient/IMEManager.h"
WindowMsgHandledType KeyboardTextEntryInput( GameWindow *window, UnsignedInt msg,
													 WindowMsgData mData1, WindowMsgData mData2 )
{
	Rva004CA140EntryData *e = (Rva004CA140EntryData *)window->winGetUserData();

	WinInstanceData *instData = window->winGetInstanceData();

	if ( TheIMEManager && ((Rva004CA140IMEManager *)TheIMEManager)->isAttachedTo( window) && ((Rva004CA140IMEManager *)TheIMEManager)->isComposing())
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
			 																				0x4030,
			 																				(WindowMsgData)window, 
			 																				0 );
				return MSG_HANDLED;
			};

			if( ch )
			{
                if (!((bool (__cdecl *)(WideChar, unsigned int))j_000275c0)(ch, e->flags))
                    return MSG_HANDLED;

				if( e->text->getTextLength() <= 1 )
				{
					e->text->setText( UnicodeString::TheEmptyString );
					e->text->appendChar( ch );
					e->charPos = e->text->getTextLength();
					TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					0x4031,
																					(WindowMsgData)window, 
																					0 );
					return MSG_HANDLED;
				}
				//else check is modifiers are persent
				else
				{
					char c = e->text->getText().getCharAt(e->text->getTextLength() - 1 );
					if(c == '+' )
					{
						e->text->appendChar( ch );
						e->charPos++;
						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						0x4031,
																						(WindowMsgData)window, 
																						0 );
						return MSG_HANDLED;
					}
					// if not, reset textEntry
					else
					{
						//if any of the modifiers are down, just replace letter
						if( ( shiftDown | ctrlDown | altDown ) && ( !absolute ) )
						{
							char test = e->text->getText().getCharAt(e->text->getTextLength() - 1);
							// only replace letter if not the same as last char of string (removes flickering)
							if( test != ch )
							{
								e->text->removeLastChar();
								e->text->appendChar( ch );
								TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																								0x4031,
																								(WindowMsgData)window, 
																								0 );
							}
						}
						//else reset textEntry
						else
						{
							e->text->setText( UnicodeString::TheEmptyString );
							e->text->appendChar( ch );
							e->charPos = 1;
							TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																							0x4031,
																							(WindowMsgData)window, 
																							0 );
						}
						return MSG_HANDLED;
					}
				}
				

			}
			break;
		}
		// ------------------------------------------------------------------------
		case GWM_CHAR:

			switch( mData1 )
			{
				

				// -------------------------------------------------------------------------------------------
				// modifier cases

				case KEY_LCTRL:
				{
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						UnicodeString mod = ctrl;
						doKeyDown( (EntryData *)e, mod );
						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																0x4031,
																(WindowMsgData)window, 
																0 );

						return MSG_HANDLED;
					}
					if( BitTest(mData2, KEY_STATE_UP ) )
					{
							UnicodeString mod = ctrl;
							doKeyUp( (EntryData *)e, mod );
							TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						0x4031,
																						(WindowMsgData)window, 
																						0 );

							return MSG_HANDLED;
					}
					break;
				}

				case KEY_RSHIFT:
				case KEY_LSHIFT:
				{
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						UnicodeString mod = shift;
						doKeyDown( (EntryData *)e, mod );
						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																0x4031,
																(WindowMsgData)window, 
																0 );

						return MSG_HANDLED;

					}
					if( BitTest( mData2, KEY_STATE_UP ) )
					{
						UnicodeString mod = shift;
						doKeyUp((EntryData *)e, mod );

						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																						0x4031,
																						(WindowMsgData)window, 
																						0 );


						return MSG_HANDLED;
					}
					break;
				}

				case KEY_LALT:
				{
					if( BitTest( mData2, KEY_STATE_DOWN ) )
					{
						UnicodeString mod = alt;
						doKeyDown( (EntryData *)e, mod );

						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																0x4031,
																(WindowMsgData)window, 
																0 );

						return MSG_HANDLED;

					}
					if( BitTest(mData2, KEY_STATE_UP ) )
					{
						UnicodeString mod = alt;
						doKeyUp( (EntryData *)e, mod );
						TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																0x4031,
																(WindowMsgData)window, 
																0 );

						return MSG_HANDLED;
					}
					break;
				}

				// -------------------------------------------------------------------------------------------


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
					return MSG_IGNORED;

				// --------------------------------------------------------------------
				case KEY_DOWN:
				case KEY_RIGHT:
				case KEY_TAB:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
						window->winNextTab();
					break;

				// --------------------------------------------------------------------
				case KEY_UP:
				case KEY_LEFT:

					if( BitTest( mData2, KEY_STATE_DOWN ) )
						window->winPrevTab();
					break;

				// --------------------------------------------------------------------
				case KEY_BACKSPACE:
				{
					e->text->setText( UnicodeString::TheEmptyString );
					e->charPos = e->text->getTextLength();
					TheWindowManager->winSendSystemMsg( window->winGetOwner(), 
																					0x4031,
																					(WindowMsgData)window, 
																					0 );
					setKeyDown(shift, false );
					setKeyDown(ctrl, false );
					setKeyDown(alt, false );
					return MSG_HANDLED;
					
					break;
				}
				case KEY_DEL:
				{

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
																								0x4031,
																								(WindowMsgData)window, 
																								0 );
							}  // end if
						}
					}
					break;
				}

				// ----------------------------------------------------------------------------------------
				// doing research to see if this will fix the keyboard stuff
				


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
				TheWindowManager->winSetFocus( window );
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



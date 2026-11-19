// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Both GameWindowManager::gogoMessageBox overloads:
//
//   gogoMessageBox (11 args)  0x0047DB60   183 B  UAE, vtable slot 13
//   gogoMessageBox (12 args)  0x0047EF70  1518 B  UAE, vtable slot 12
//
// The short one exists only to call the long one with useLogo=FALSE, and they
// were in two files that disagreed about where the long one sits: the
// forwarder's copy had to put it at slot 12 because that is the `call
// [edx+0x30]` it compiles, and the long one's copy parked it at the end of the
// table past winSetModal, which its own body could not contradict because no
// body calls it through the table. Slot 12 is the pinned reading and the
// merged table uses it -- the placeholder slots the long body needs
// (winCreateFromScript 26, winSetFocus 44, winGetWindowFromId 55, winSetModal
// 59) all land unchanged around it.
//
// The 12-argument overload (`ret 0x30` is x/y/w/h + flags + two by-value
// UnicodeStrings + four callbacks + useLogo).
//
// Lifted out of GameWindowManager.cpp rather than converted in place. That
// translation unit builds against Zero Hour's AsciiString, whose methods do not
// exist in retail: the body there compiles `tempName = menuName;
// tempName.concat("ButtonOk"); nameToKey(tempName)` into a UnicodeString
// format_va call, where retail emits StringBase<char>::set(const StringBase &),
// concat(const char *, int) and nameToKey(const char *). Switching that file to
// retail's string model would put its 114 matched rows at risk, so the function
// gets its own TU with the shims it actually needs.
//
// GameWindowManager's vtable slots are pinned by the indirect calls in the
// body: winCreateFromScript at +0x68 (twice, the useLogo branches),
// winSetFocus at +0xb0 (twice), winGetWindowFromId at +0xdc (seven times, one
// per named child) and winSetModal at +0xec.

#include <stddef.h>
#include <string.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Include/Common/ScalarTypes.h"



#include "../../../Include/Common/NameKeyType.h"

#define FALSE false

// The message-box button bits, read straight off the tests in the body:
// `test bl,8` guards the OK branch, `test bl,1` the Yes branch, and the
// combined No/Cancel test is `and al,6 / cmp al,6`.
enum {
	MSG_BOX_YES    = 0x01,
	MSG_BOX_NO     = 0x02,
	MSG_BOX_CANCEL = 0x04,
	MSG_BOX_OK     = 0x08
};

// Canonical UnicodeString lifetime delegates to the retail wide StringBase.
inline UnicodeString::UnicodeString(const UnicodeString &that)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
        *(const StringBase<unsigned short> *)&that);
}

inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

typedef void (*GameWinMsgBoxFunc)( void );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
struct WindowMessageBoxData
{
	GameWinMsgBoxFunc yesCallback;
	GameWinMsgBoxFunc noCallback;
	GameWinMsgBoxFunc okCallback;
	GameWinMsgBoxFunc cancelCallback;
};

class WindowLayoutInfo;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winSetPosition( Int x, Int y );
	Int winGetPosition( Int *x, Int *y );
	Int winGetSize( Int *w, Int *h );
	Int winSetSize( Int w, Int h );
	Int winHide( Bool hide );
	Int winBringToTop( void );
	void winSetUserData( void *data );
	GameWindow *winGetChild( void );
	GameWindow *winGetNext( void );

	// BFME clears this immediately after winCreateFromScript returns; Zero
	// Hour's source has no such statement.
	char  m_pre[0x1F4];
	void *m_clearedOnCreate;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

// Padded to retail's slot numbers; only the four the body calls are named.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	// The two overloads share a name, so MSVC lays them out in REVERSE
	// declaration order: the 12-argument form, declared second, lands at slot
	// 12 -- exactly where the forwarder's `call [edx+0x30]` puts it -- and the
	// forwarder itself at slot 13. Declared the intuitive way round, the
	// forwarding call compiles to +0x34 and misses.
	virtual GameWindow *gogoMessageBox( Int x, Int y, Int width, Int height,
			UnsignedShort buttonFlags, UnicodeString titleString,
			UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
			GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
			GameWinMsgBoxFunc cancelCallback );
	virtual GameWindow *gogoMessageBox( Int x, Int y, Int width, Int height,
			UnsignedShort buttonFlags, UnicodeString titleString,
			UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
			GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
			GameWinMsgBoxFunc cancelCallback, Bool useLogo );
	virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	// Retail reserves three argument slots at the call, so this takes two
	// pointers after the by-value name, not one.
	virtual GameWindow *winCreateFromScript( AsciiString file, WindowLayoutInfo *info = 0, void *extra = 0 );	// +0x68
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43();
	virtual Int winSetFocus( GameWindow *win );					// +0xb0
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54();
	virtual GameWindow *winGetWindowFromId( GameWindow *win, Int id );	// +0xdc
	virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual void winSetModal( GameWindow *win );					// +0xec
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

void GadgetStaticTextSetText( GameWindow *win, UnicodeString text );

// ?gogoMessageBox@GameWindowManager@@UAEPAVGameWindow@@HHHHGVUnicodeString@@0P6AXXZ111_N@Z
GameWindow *GameWindowManager::gogoMessageBox( Int x, Int y, Int width, Int height,
		UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString,
		GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback,
		GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback, Bool useLogo )
{
	if (buttonFlags == 0) {
		return NULL;
	}

	GameWindow *trueParent = NULL;
	if (useLogo)
		trueParent = winCreateFromScript( AsciiString("Menus/QuitMessageBox.wnd") );
	else
		trueParent = winCreateFromScript( AsciiString("Menus/MessageBox.wnd") );

	trueParent->m_clearedOnCreate = NULL;

	AsciiString menuName;
	if (useLogo)
		menuName.StringBase<char>::set( "QuitMessageBox.wnd:", 19 );
	else
		menuName.StringBase<char>::set( "MessageBox.wnd:", 15 );

	AsciiString tempName;
	GameWindow *parent = NULL;

	tempName = menuName;
	tempName.StringBase<char>::concat( "MessageBoxParent", 16 );
	// Nested here (unlike the button lookups below): retail loads
	// TheWindowManager's vtable into edi before evaluating nameToKey and calls
	// through the cached copy.
	parent = TheWindowManager->winGetWindowFromId( trueParent,
			TheNameKeyGenerator->nameToKey( tempName.str() ) );
	if (parent != NULL) {
		parent->m_clearedOnCreate = NULL;
	}
	TheWindowManager->winSetModal( trueParent );
	TheWindowManager->winSetFocus( NULL );
	TheWindowManager->winSetFocus( parent );

	float ratioX, ratioY = 1;

	if (width > 0 && height > 0) {
		ICoord2D temp;
		parent->winGetSize( &temp.x, &temp.y );
		ratioX = (float)width / (float)temp.x;
		ratioY = (float)height / (float)temp.y;
		parent->winSetSize( width, height );

		GameWindow *child;
		for (child = parent->winGetChild(); child; child = child->winGetNext()) {
			child->winGetSize( &temp.x, &temp.y );
			temp.x = Int(temp.x * ratioX);
			temp.y = Int(temp.y * ratioY);
			child->winSetSize( temp.x, temp.y );

			child->winGetPosition( &temp.x, &temp.y );
			temp.x = Int(temp.x * ratioX);
			temp.y = Int(temp.y * ratioY);
			child->winSetPosition( temp.x, temp.y );
		}
	}

	if (x >= 0 && y >= 0)
		parent->winSetPosition( x, y );

	Int buttonX[3], buttonY[3];

	NameKeyType buttonOkID = NAMEKEY_INVALID;

	tempName = menuName;
	tempName.StringBase<char>::concat( "ButtonOk", 8 );
	buttonOkID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonOk = TheWindowManager->winGetWindowFromId( parent, buttonOkID );
	buttonOk->winGetPosition( &buttonX[0], &buttonY[0] );

	tempName = menuName;
	tempName.StringBase<char>::concat( "ButtonYes", 9 );
	NameKeyType buttonYesID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonYes = TheWindowManager->winGetWindowFromId( parent, buttonYesID );

	tempName = menuName;
	tempName.StringBase<char>::concat( "ButtonNo", 8 );
	NameKeyType buttonNoID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonNo = TheWindowManager->winGetWindowFromId( parent, buttonNoID );
	buttonNo->winGetPosition( &buttonX[1], &buttonY[1] );

	tempName = menuName;
	tempName.StringBase<char>::concat( "ButtonCancel", 12 );
	NameKeyType buttonCancelID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonCancel = TheWindowManager->winGetWindowFromId( parent, buttonCancelID );
	buttonCancel->winGetPosition( &buttonX[2], &buttonY[2] );

	if ((buttonFlags & MSG_BOX_OK) == MSG_BOX_OK) {
		buttonOk->winSetPosition( buttonX[0], buttonY[0] );
		buttonOk->winHide( FALSE );
	} else if ((buttonFlags & MSG_BOX_YES) == MSG_BOX_YES) {
		buttonYes->winSetPosition( buttonX[0], buttonY[0] );
		buttonYes->winHide( FALSE );
	}

	if ((buttonFlags & (MSG_BOX_NO | MSG_BOX_CANCEL)) == (MSG_BOX_NO | MSG_BOX_CANCEL)) {
		buttonNo->winSetPosition( buttonX[1], buttonY[1] );
		buttonCancel->winSetPosition( buttonX[2], buttonY[2] );
		buttonNo->winHide( FALSE );
		buttonCancel->winHide( FALSE );
	} else if ((buttonFlags & MSG_BOX_NO) == MSG_BOX_NO) {
		buttonNo->winSetPosition( buttonX[2], buttonY[2] );
		buttonNo->winHide( FALSE );
	} else if ((buttonFlags & MSG_BOX_CANCEL) == MSG_BOX_CANCEL) {
		buttonCancel->winSetPosition( buttonX[2], buttonY[2] );
		buttonCancel->winHide( FALSE );
	}

	tempName = menuName;
	tempName.StringBase<char>::concat( "StaticTextTitle", 15 );
	NameKeyType staticTextTitleID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *staticTextTitle = TheWindowManager->winGetWindowFromId( parent, staticTextTitleID );
	GadgetStaticTextSetText( staticTextTitle, titleString );

	tempName = menuName;
	tempName.StringBase<char>::concat( "StaticTextMessage", 17 );
	NameKeyType staticTextMessageID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *staticTextMessage = TheWindowManager->winGetWindowFromId( parent, staticTextMessageID );
	GadgetStaticTextSetText( staticTextMessage, bodyString );

	WindowMessageBoxData *MsgBoxCallbacks = new WindowMessageBoxData;
	MsgBoxCallbacks->cancelCallback = cancelCallback;
	MsgBoxCallbacks->noCallback = noCallback;
	MsgBoxCallbacks->okCallback = okCallback;
	MsgBoxCallbacks->yesCallback = yesCallback;

	trueParent->winSetUserData( MsgBoxCallbacks );

	parent->winHide( FALSE );
	parent->winBringToTop();

	return trueParent;
}

// ?gogoMessageBox@GameWindowManager@@UAEPAVGameWindow@@HHHHGVUnicodeString@@0P6AXXZ111@Z
GameWindow *GameWindowManager::gogoMessageBox( Int x, Int y, Int width, Int height,
		UnsignedShort buttonFlags, UnicodeString titleString, UnicodeString bodyString,
		GameWinMsgBoxFunc yesCallback, GameWinMsgBoxFunc noCallback,
		GameWinMsgBoxFunc okCallback, GameWinMsgBoxFunc cancelCallback )
{
	return gogoMessageBox(x, y, width, height, buttonFlags, titleString, bodyString,
			yesCallback, noCallback, okCallback, cancelCallback, FALSE);
}

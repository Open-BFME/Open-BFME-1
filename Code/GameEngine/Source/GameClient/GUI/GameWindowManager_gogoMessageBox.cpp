// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// GameWindowManager::gogoMessageBox, retail 0x0047EF70, 1518 bytes -- the
// 13-argument overload (`ret 0x30` is x/y/w/h + flags + two by-value
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
#include "string_base.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
enum NameKeyType { NAMEKEY_INVALID = 0 };

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

// Retail's AsciiString is the StringBase<char> shim: the assignment lands on
// set(const StringBase<char> &) at 0x00887C90 and concat on the (str, len)
// overload at 0x00887D60, with the const char * constructor at 0x00888BC0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_data = 0; }

	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}

	// Declared, not implicit: without it the class is trivially copyable and
	// MSVC passes the 4-byte member by value and destroys the temporary in the
	// caller. Retail constructs the temporary straight into the outgoing
	// argument slot and leaves the destruction to the callee.
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}

	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	AsciiString &operator=( const AsciiString &that )
	{
		((StringBase<char> *)this)->set( *(const StringBase<char> *)&that );
		return *this;
	}

	void set( const char *s, int len )
	{
		((StringBase<char> *)this)->set( s, len );
	}

	// Both inline: retail folds the literal's length into the (str, len)
	// overload at 0x00887D60, and reads the text straight out of the buffer
	// eight bytes past the header rather than calling str().
	void concat( const char *s )
	{
		((StringBase<char> *)this)->concat( s, (int)strlen( s ) );
	}

	const char *str() const
	{
		return m_data ? (const char *)(m_data + 8) : "";
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that );
	}

	~UnicodeString() { ((StringBase<wchar_t> *)this)->releaseBuffer(); }

private:
	wchar_t *m_data;
};

struct ICoord2D { Int x, y; };

typedef void (*GameWinMsgBoxFunc)( void );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
struct WindowMessageBoxData
{
	GameWinMsgBoxFunc yesCallback;
	GameWinMsgBoxFunc noCallback;
	GameWinMsgBoxFunc okCallback;
	GameWinMsgBoxFunc cancelCallback;
};

class WindowLayoutInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

// Padded to retail's slot numbers; only the four the body calls are named.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
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
	virtual GameWindow *gogoMessageBox( Int x, Int y, Int width, Int height,
			UnsignedShort buttonFlags, UnicodeString titleString,
			UnicodeString bodyString, GameWinMsgBoxFunc yesCallback,
			GameWinMsgBoxFunc noCallback, GameWinMsgBoxFunc okCallback,
			GameWinMsgBoxFunc cancelCallback, Bool useLogo );
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
		menuName.set( "QuitMessageBox.wnd:", 19 );
	else
		menuName.set( "MessageBox.wnd:", 15 );

	AsciiString tempName;
	GameWindow *parent = NULL;

	tempName = menuName;
	tempName.concat( "MessageBoxParent" );
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
	tempName.concat( "ButtonOk" );
	buttonOkID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonOk = TheWindowManager->winGetWindowFromId( parent, buttonOkID );
	buttonOk->winGetPosition( &buttonX[0], &buttonY[0] );

	tempName = menuName;
	tempName.concat( "ButtonYes" );
	NameKeyType buttonYesID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonYes = TheWindowManager->winGetWindowFromId( parent, buttonYesID );

	tempName = menuName;
	tempName.concat( "ButtonNo" );
	NameKeyType buttonNoID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *buttonNo = TheWindowManager->winGetWindowFromId( parent, buttonNoID );
	buttonNo->winGetPosition( &buttonX[1], &buttonY[1] );

	tempName = menuName;
	tempName.concat( "ButtonCancel" );
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
	tempName.concat( "StaticTextTitle" );
	NameKeyType staticTextTitleID = TheNameKeyGenerator->nameToKey( tempName.str() );
	GameWindow *staticTextTitle = TheWindowManager->winGetWindowFromId( parent, staticTextTitleID );
	GadgetStaticTextSetText( staticTextTitle, titleString );

	tempName = menuName;
	tempName.concat( "StaticTextMessage" );
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

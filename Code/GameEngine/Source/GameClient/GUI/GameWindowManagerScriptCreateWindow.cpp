// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// createWindow (retail 0x004874A0, 320 bytes): the GameWindowManagerScript.cpp
// file-static that parseWindow (0x00487F80, call sites +0x3F9 and +0x51F) uses
// to build a user window, a tab pane or a gadget from a parsed window block.
//
// Identity is the Zero Hour twin in GameWindowManagerScript.cpp: peekWindow()
// for the parent, strcmp against "USER" (0x010F9204) and "TABPANE"
// (0x010F91D8) that OR GWS_USER_WINDOW 0x200 / GWS_TAB_PANE 0x4000 into the
// instance style, createGadget (0x00486B10) otherwise, the four edit-data
// callback strings, setWindowText (0x004864E0) with the text label, and
// winSendInputMsg(parent, GWM_SCRIPT_CREATE, id, 0) when there is a parent.
// BFME moved status/position/size/callbacks into the window record that
// parseWindow fills at 0x012F253C and winCreate (slot +0x74) takes whole; the
// record's +0x30 is the instance data (parseWindow stores &instData there and
// this body hands it to winSetInstanceData).
//
// Retail gives createWindow MSVC 7.1's private internal-linkage register
// convention (type in EDX, record in EBX, id and data on the stack, caller
// cleans) and calls setWindowText with the window in ESI. Neither has a C++
// spelling; the compiler reproduces both on its own once createWindow has a
// visible caller and setWindowText a visible body in the same TU, which is
// why both companions below live here (same lever as
// W3DStaticTextDraw_Thunk.cpp). The byte-proven stack order is id before
// data; where the two register parameters sit in the list is not
// byte-provable (both orders compile identically) and follows the Zero Hour
// order, where the instance data this record carries came before data.

#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>

typedef int Int;
typedef unsigned int UnsignedInt;

class WinInstanceData
{
public:
	char m_pad0[ 0x0C ];
	UnsignedInt m_style;							// +0x0C (layout witness)
	char m_pad10[ 0x188 - 0x10 ];
	AsciiString m_textLabelString;		// +0x188 (ZH twin passes it to setWindowText)
};

class GameWindow
{
public:
	Int winSetInstanceData( WinInstanceData *data );
	UnsignedInt winGetStyle( void );
	Int winSetText( UnicodeString newText );
};

// Ledger names for the two GameWindow calls retail makes on every path
// (ZH winSetWindowId / winGetEditData positions; identities not yet proven).
class Rva00478C90Object { public: Int store( UnsignedInt value ); };
class Gen_004791e0 { public: Int m( void ); };

struct GameWindowEditData
{
	AsciiString systemCallbackString;
	AsciiString inputCallbackString;
	AsciiString tooltipCallbackString;
	AsciiString drawCallbackString;
};

class Open2479440Record
{
public:
	char m_pad0[ 0x30 ];
	WinInstanceData *dword_30;
};

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva004874A0ManagerView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3C();
	virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4C();
	virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5C();
	virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6C();
	virtual void s70();
	virtual GameWindow *s74( Open2479440Record *record );		// ZH winCreate position
	virtual void s78(); virtual void s7C();
	virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8C();
	virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9C();
	virtual void sA0(); virtual void sA4(); virtual void sA8(); virtual void sAC();
	virtual void sB0(); virtual void sB4(); virtual void sB8(); virtual void sBC();
	virtual void sC0(); virtual void sC4(); virtual void sC8(); virtual void sCC();
	virtual void sD0(); virtual void sD4();
	virtual Int sD8( GameWindow *window, UnsignedInt msg,
		UnsignedInt data1, UnsignedInt data2 );	// ZH winSendInputMsg position
};

class GameTextInterface;
extern GameTextInterface *TheGameText;

class Rva004864E0GameTextView
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24();
	virtual UnicodeString s28( const char *label, bool *exists );	// ZH fetch position
};

GameWindow *createGadget( char *type, void *data, Open2479440Record *record, GameWindow *source );

void GadgetButtonSetText( GameWindow *g, UnicodeString text );
void GadgetRadioSetText( GameWindow *g, UnicodeString text );
void GadgetCheckBoxSetText( GameWindow *g, UnicodeString text );
void GadgetStaticTextSetText( GameWindow *g, UnicodeString text );
void GadgetTextEntrySetText( GameWindow *g, UnicodeString text );

static AsciiString theSystemString;
static AsciiString theInputString;
static AsciiString theTooltipString;
static AsciiString theDrawString;

static GameWindow **stackPtr;
static GameWindow *windowStack[ 10 ];

static GameWindow *peekWindow( void )
{
	if( stackPtr == windowStack )
		return 0;
	return *( stackPtr - 1 );
}

// Convention companion only: its row stays with setWindowText_Thunk.cpp.
// ?setWindowText@@YAXPAVGameWindow@@VAsciiString@@@Z present-unmatched
static void setWindowText( GameWindow *window, AsciiString textLabel )
{
	if( textLabel.isEmpty() )
		return;

	UnicodeString theText, entryText;
	theText = ( (Rva004864E0GameTextView *)TheGameText )->s28( textLabel.str(), 0 );
	if( window->winGetStyle() & 0x00000001 )
		GadgetButtonSetText( window, theText );
	else if( window->winGetStyle() & 0x00000002 )
		GadgetRadioSetText( window, theText );
	else if( window->winGetStyle() & 0x00000004 )
		GadgetCheckBoxSetText( window, theText );
	else if( window->winGetStyle() & 0x00000080 )
		GadgetStaticTextSetText( window, theText );
	else if( window->winGetStyle() & 0x00000040 )
	{
		entryText.translate( textLabel );
		GadgetTextEntrySetText( window, entryText );
	}
	else
		window->winSetText( theText );
}

static GameWindow *createWindow( char *type, Int id, Open2479440Record *record, void *data )
{
	GameWindow *window, *parent;

	parent = peekWindow();

	if( !strcmp( type, "USER" ) )
	{
		window = ( (Rva004874A0ManagerView *)TheWindowManager )->s74( record );
		if( window )
		{
			record->dword_30->m_style |= 0x00000200;
			( (Rva00478C90Object *)window )->store( id );
		}
	}
	else if( !strcmp( type, "TABPANE" ) )
	{
		window = ( (Rva004874A0ManagerView *)TheWindowManager )->s74( record );
		if( window )
		{
			record->dword_30->m_style |= 0x00004000;
			window->winSetInstanceData( record->dword_30 );
			( (Rva00478C90Object *)window )->store( id );
		}
	}
	else
	{
		window = createGadget( type, data, record, 0 );
		if( window )
			( (Rva00478C90Object *)window )->store( id );
	}

	if( window )
	{
		GameWindowEditData *editData = (GameWindowEditData *)( (Gen_004791e0 *)window )->m();
		if( editData )
		{
			editData->systemCallbackString = theSystemString;
			editData->inputCallbackString = theInputString;
			editData->tooltipCallbackString = theTooltipString;
			editData->drawCallbackString = theDrawString;
		}
	}

	if( window )
		setWindowText( window, record->dword_30->m_textLabelString );

	if( window && parent )
		( (Rva004874A0ManagerView *)TheWindowManager )->sD8( parent, 0x16, id, 0 );

	return window;
}

// Keeps the file-static createWindow emitted: retail's two callers are in
// parseWindow, which is still a byte-accurate emitted body in
// GameWindowManagerScript.cpp (same keeper as retainParseChildWindows there).
// ?retainCreateWindow@@YAPAVGameWindow@@PADHPAVOpen2479440Record@@PAX@Z absent-from-retail
GameWindow *retainCreateWindow( char *type, Int id, Open2479440Record *record, void *data )
{
	return createWindow( type, id, record, data );
}

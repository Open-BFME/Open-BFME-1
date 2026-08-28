// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib

// FILE: GadgetPushButtonSystem.cpp ////////////////////////////////////////////
//
// GadgetPushButtonSystem, retail 0x004BCBB0. The .data callback table names it.
//
// Kept out of GadgetPushButton.cpp so that file keeps serving its fifteen
// matched rows: this body needs the StringBase-backed AsciiString/UnicodeString
// pair, and swapping the string classes under a TU that size moves codegen
// everywhere.
//
// Zero Hour's body with three BFME drifts:
//
//  1. PushButtonData is not a POD here. Before operator delete retail hands the
//     DisplayString at +0x30 back to TheDisplayStringManager (vtable +0x28) and
//     releases an AsciiString at +0x1C. The release is written at the call site
//     and the AsciiString left to the implicit destructor, because that is the
//     only spelling MSVC inlines: a user-declared destructor holding both, in
//     class or out of it, is emitted as a call here instead.
//
//     GadgetPushButton.cpp's RetailPushButtonData describes the same storage as
//     plain fields, since getNewPushButtonData initialises it field by field;
//     that is why this file spells its own type rather than reusing it.
//
//  2. GameWindow::winSetText is virtual in BFME (?winSetText@GameWindow@@UAEH...)
//     but this call site reaches it directly, so it is called by qualified name.
//     Its UnicodeString argument is passed by value, which is the `mov [esp+N],esp`
//     / `mov ecx,esp` pair at 0x004BCC80 - and what the string shims are for.
//
//  3. GameWindowManager::winSendSystemMsg is vtable +0xD4.
//
// The switch is a compare chain, not a table: 0x17 first, then 1 and 2 by
// successive dec, then 0x4001 off the above-branch. That is four cases, which
// is what Zero Hour has, so BFME dropped none of them.
//
///////////////////////////////////////////////////////////////////////////////

#include <stddef.h>
#include <wchar.h>

#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

enum
{
	GWM_CREATE			= 1,
	GWM_DESTROY			= 2,
	GWM_INPUT_FOCUS		= 23,

	GGM_SET_LABEL		= 16385,
	GGM_FOCUS_CHANGE	= 16387
};

enum { WIN_STATE_HILITED = 0x00000002 };

class DisplayString;

// Only the slot the destructor reaches is claimed, and only its offset.
class BfmeDisplayStringManager
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;	// +0x28
};

extern BfmeDisplayStringManager *TheDisplayStringManager;			// 0x012F12CC

// The layout GWM_DESTROY unwinds. Everything below +0x1C is untouched here.
struct PushButtonData
{
	unsigned char m_unmodelled_00[ 0x1C ];
	AsciiString m_label;						// +0x1C
	unsigned char m_unmodelled_20[ 0x10 ];
	DisplayString *m_displayString;				// +0x30
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	class GameWindow *getOwner() { return m_owner; }

	unsigned char m_unmodelled_00[ 8 ];
	UnsignedInt m_state;						// +0x08
	unsigned char m_unmodelled_0C[ 8 ];
	class GameWindow *m_owner;					// +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void *winGetUserData();
	void winSetUserData( void *data );
	Int winGetWindowId();

	virtual Int winSetText( UnicodeString text );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_0C() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_1C() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_2C() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_38() = 0;
	virtual void _bfme_pad_3C() = 0;
	virtual void _bfme_pad_40() = 0;
	virtual void _bfme_pad_44() = 0;
	virtual void _bfme_pad_48() = 0;
	virtual void _bfme_pad_4C() = 0;
	virtual void _bfme_pad_50() = 0;
	virtual void _bfme_pad_54() = 0;
	virtual void _bfme_pad_58() = 0;
	virtual void _bfme_pad_5C() = 0;
	virtual void _bfme_pad_60() = 0;
	virtual void _bfme_pad_64() = 0;
	virtual void _bfme_pad_68() = 0;
	virtual void _bfme_pad_6C() = 0;
	virtual void _bfme_pad_70() = 0;
	virtual void _bfme_pad_74() = 0;
	virtual void _bfme_pad_78() = 0;
	virtual void _bfme_pad_7C() = 0;
	virtual void _bfme_pad_80() = 0;
	virtual void _bfme_pad_84() = 0;
	virtual void _bfme_pad_88() = 0;
	virtual void _bfme_pad_8C() = 0;
	virtual void _bfme_pad_90() = 0;
	virtual void _bfme_pad_94() = 0;
	virtual void _bfme_pad_98() = 0;
	virtual void _bfme_pad_9C() = 0;
	virtual void _bfme_pad_A0() = 0;
	virtual void _bfme_pad_A4() = 0;
	virtual void _bfme_pad_A8() = 0;
	virtual void _bfme_pad_AC() = 0;
	virtual void _bfme_pad_B0() = 0;
	virtual void _bfme_pad_B4() = 0;
	virtual void _bfme_pad_B8() = 0;
	virtual void _bfme_pad_BC() = 0;
	virtual void _bfme_pad_C0() = 0;
	virtual void _bfme_pad_C4() = 0;
	virtual void _bfme_pad_C8() = 0;
	virtual void _bfme_pad_CC() = 0;
	virtual void _bfme_pad_D0() = 0;
	virtual void winSendSystemMsg( GameWindow *window, UnsignedInt msg,
								   WindowMsgData mData1, WindowMsgData mData2 ) = 0;	// +0xD4
};

extern GameWindowManager *TheWindowManager;							// 0x012F1B40

// ?GadgetPushButtonSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType GadgetPushButtonSystem( GameWindow *window, UnsignedInt msg,
											 WindowMsgData mData1, WindowMsgData mData2 )
{
	WinInstanceData *instData = window->winGetInstanceData();

	switch( msg )
	{

		// ------------------------------------------------------------------------
		case GGM_SET_LABEL:
		{
			// set text into the win instance text data field
			window->GameWindow::winSetText( *(UnicodeString *)mData1 );
			break;
		}

		// ------------------------------------------------------------------------
		case GWM_CREATE:
			break;

		// ------------------------------------------------------------------------
		case GWM_DESTROY:
		{
			PushButtonData *pData = (PushButtonData *)window->winGetUserData();
			if( pData )
			{
				TheDisplayStringManager->freeDisplayString( pData->m_displayString );
				delete pData;
			}
			window->winSetUserData( NULL );
		}
			break;

		// ------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:

			if( mData1 == 0 )
				instData->m_state &= ~WIN_STATE_HILITED;
			else
				instData->m_state |= WIN_STATE_HILITED;

			TheWindowManager->winSendSystemMsg( instData->getOwner(),
												GGM_FOCUS_CHANGE,
												(WindowMsgData)mData1,
												window->winGetWindowId() );
			if( mData1 == 0 )
				*(Bool *)mData2 = false;
			else
				*(Bool *)mData2 = true;
			break;

		default:
			return MSG_IGNORED;

	}  // end switch( msg )

	return MSG_HANDLED;

}  // end GadgetPushButtonSystem

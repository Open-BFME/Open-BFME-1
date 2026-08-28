// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

// FILE: ControlBarBeacon.cpp /////////////////////////////////////////////////
//
// BeaconWindowInput, retail 0x004A37E0. No port of Zero Hour's
// ControlBarBeacon.cpp existed under Code/; the .data callback table names this
// address, and the body is one escape-key branch.
//
// BFME does more here than Zero Hour, which only deselects: it first posts a
// message of type 0x3EB with a single TRUE boolean argument, and only then
// deselects. The deselect also takes no argument in BFME - retail pushes
// nothing before the virtual at slot 0xE8 - where the vendored header declares
// deselectAllDrawables( Bool ).
//
// The three interfaces are spelled TU-locally: their headers reach most of
// GameClient, and only the two slots and the argument list are recoverable from
// this call site.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

enum WindowMsgHandledType { MSG_IGNORED = 0, MSG_HANDLED = 1 };

class GameWindow;

// GWM_CHAR, and KEY_ESC as the vendored headers spell them.
enum { GWM_CHAR = 0x15, KEY_ESC = 1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	void appendBooleanArgument( Bool arg );
};

// appendMessage is vtable slot 0x34 of MessageStream.
class BfmeMessageStream
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0;
	virtual void slot0C() = 0; virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0; virtual void slot20() = 0;
	virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual GameMessage *appendMessage( UnsignedInt type ) = 0;
};

// deselectAllDrawables is vtable slot 0xE8 of InGameUI, and takes no argument.
class BfmeInGameUI
{
public:
	virtual void slot000() = 0; virtual void slot004() = 0; virtual void slot008() = 0;
	virtual void slot00C() = 0; virtual void slot010() = 0; virtual void slot014() = 0;
	virtual void slot018() = 0; virtual void slot01C() = 0; virtual void slot020() = 0;
	virtual void slot024() = 0; virtual void slot028() = 0; virtual void slot02C() = 0;
	virtual void slot030() = 0; virtual void slot034() = 0; virtual void slot038() = 0;
	virtual void slot03C() = 0; virtual void slot040() = 0; virtual void slot044() = 0;
	virtual void slot048() = 0; virtual void slot04C() = 0; virtual void slot050() = 0;
	virtual void slot054() = 0; virtual void slot058() = 0; virtual void slot05C() = 0;
	virtual void slot060() = 0; virtual void slot064() = 0; virtual void slot068() = 0;
	virtual void slot06C() = 0; virtual void slot070() = 0; virtual void slot074() = 0;
	virtual void slot078() = 0; virtual void slot07C() = 0; virtual void slot080() = 0;
	virtual void slot084() = 0; virtual void slot088() = 0; virtual void slot08C() = 0;
	virtual void slot090() = 0; virtual void slot094() = 0; virtual void slot098() = 0;
	virtual void slot09C() = 0; virtual void slot0A0() = 0; virtual void slot0A4() = 0;
	virtual void slot0A8() = 0; virtual void slot0AC() = 0; virtual void slot0B0() = 0;
	virtual void slot0B4() = 0; virtual void slot0B8() = 0; virtual void slot0BC() = 0;
	virtual void slot0C0() = 0; virtual void slot0C4() = 0; virtual void slot0C8() = 0;
	virtual void slot0CC() = 0; virtual void slot0D0() = 0; virtual void slot0D4() = 0;
	virtual void slot0D8() = 0; virtual void slot0DC() = 0; virtual void slot0E0() = 0;
	virtual void slot0E4() = 0;
	virtual void deselectAllDrawables() = 0;
};

extern BfmeMessageStream *TheMessageStream;
extern BfmeInGameUI *TheInGameUI;

// ?BeaconWindowInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType BeaconWindowInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{
	if (msg == GWM_CHAR && mData1 == KEY_ESC)
	{
		GameMessage *message = TheMessageStream->appendMessage( 0x3EB );
		message->appendBooleanArgument( true );

		TheInGameUI->deselectAllDrawables(); // there should only be one beacon and nothing else selected
		return MSG_HANDLED;
	}

	return MSG_IGNORED;

}  // end BeaconWindowInput

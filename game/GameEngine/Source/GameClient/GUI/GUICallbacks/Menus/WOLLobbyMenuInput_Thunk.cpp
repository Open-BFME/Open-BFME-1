// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// WOLLobbyMenuInput, retail 0x004F9680 (78 bytes).
//
// The FunctionLexicon input table at 0x012A96E4 stores the string
// WOLLobbyMenuInput in its row at 0x012A9804 next to the ILT thunk 0x004085E9,
// and that thunk jumps to 0x004F9680.  The ledger had this name on 0x0050B080,
// which the same table gives to WOLWelcomeMenuInput through the thunk
// 0x00428A9C.  The two bodies are byte-identical once their three global
// operands are masked, which is how the swap went unnoticed.
//
// The body lives here rather than in WOLLobbyMenu.cpp because the exception
// funclet _$E25 in that translation unit already fails its byte check: retail
// calls the PeerResponse list constructor through the thunk 0x00048667 and no
// pin in targets/game/reverse/symbols.csv offers that address.  That failure predates this
// commit and blocks any claim scoped to the file.
//
// Local ABI-slice replica so no shared header moves.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
typedef unsigned int NameKeyType;
typedef unsigned char UnsignedByte;
typedef unsigned char Bool;

class GameWindow;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

// upstream values: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
enum { GWM_CHAR = 0x15 };
enum { GBM_SELECTED = 0x4008 };
enum { KEY_ESC = 1 };
enum { KEY_STATE_UP = 1 };

// Only winSendSystemMsg is reconstructed; the slots ahead of it place it at
// retail's call through [vtable+0xD4].
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual WindowMsgHandledType winSendSystemMsg( GameWindow *window, UnsignedInt msg,
												   WindowMsgData mData1, WindowMsgData mData2 );
};

extern GameWindowManager *TheWindowManager;			///< retail 0x012F1B40

static Bool buttonPushed;							///< retail 0x012F45C1
static GameWindow *buttonBack;						///< retail 0x012F4608
static NameKeyType buttonBackID;					///< retail 0x012F45DC

WindowMsgHandledType WOLLobbyMenuInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{
	switch( msg )
	{

		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;
			if (buttonPushed)
				break;

			switch( key )
			{

				case KEY_ESC:
				{

					if( state & KEY_STATE_UP )
					{
						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED,
																							(WindowMsgData)buttonBack, buttonBackID );

					}  // end if

					return MSG_HANDLED;

				}  // end escape

			}  // end switch( key )

		}  // end char

	}  // end switch( msg )

	return MSG_IGNORED;
}// WOLLobbyMenuInput

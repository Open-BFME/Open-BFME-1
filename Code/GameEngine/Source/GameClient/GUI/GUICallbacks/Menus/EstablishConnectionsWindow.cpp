// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: EstablishConnectionsControlSystem, retail 0x004C8570.
//
// The Zero Hour body unchanged: a switch with one arm, which compiles to the
// leading cmp/jne. Everything it touches is spelled locally.
//
// abortGame is called through vtable slot 3, not directly. That agrees with
// what nat.cpp already recorded about this class -- "BFME EstablishConnections-
// Menu declares its five public methods virtual so setPlayerStatus is slot 5"
// -- and fixes another of the five: slot 3 is abortGame.
//
// Two globals are read: TheEstablishConnectionsMenu at 0x012F363C and the
// button's control id at 0x012F39C0. The second is the file-scope buttonQuitID
// the Zero Hour source initialises in the window's init callback.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winGetWindowId( void );					///< ILT 0x000188A4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/EstablishConnectionsMenu.h
class EstablishConnectionsMenu
{
public:
	// Only the one slot is named. The three before it exist to place it: retail
	// calls [eax+0x0c].
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void abortGame( void ) = 0;			///< slot 3
};

extern EstablishConnectionsMenu *TheEstablishConnectionsMenu;	///< retail 0x012F363C
extern int buttonQuitID;										///< retail 0x012F39C0

enum WindowMsgHandledType
{
	MSG_IGNORED = 0,
	MSG_HANDLED = 1
};

typedef unsigned int WindowMsgData;

// Retail compares the message against 0x4008 directly.
enum { GBM_SELECTED = 0x4008 };

// ?EstablishConnectionsControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType EstablishConnectionsControlSystem(GameWindow *window, unsigned int msg,
																											 WindowMsgData mData1, WindowMsgData mData2) {

	switch (msg) {
		case GBM_SELECTED:
			{
				GameWindow *control = (GameWindow *)mData1;
				int controlID = control->winGetWindowId();

				if (controlID == buttonQuitID) {
					TheEstablishConnectionsMenu->abortGame();
				}
				break;
			}
	} // end switch
	return MSG_HANDLED;
}

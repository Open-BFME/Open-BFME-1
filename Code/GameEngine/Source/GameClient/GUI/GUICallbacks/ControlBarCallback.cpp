// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// ControlBarInput, retail 0x004BFFD0 (3 bytes).
//
// The FunctionLexicon input table at 0x012A96E4 stores the string
// ControlBarInput next to the ILT thunk 0x0040F033, and that thunk jumps to
// 0x004BFFD0.  Retail parks xor eax eax then ret there, which is what
// return MSG_IGNORED compiles to once the four arguments go unread.
//
// Zero Hour keeps this callback in ControlBarCallback.cpp beside LeftHUDInput,
// so this file takes the same name and waits for its neighbours.
//
// Local ABI-slice replica so no shared header moves.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

class GameWindow;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

WindowMsgHandledType ControlBarInput( GameWindow *window, UnsignedInt msg,
																			WindowMsgData mData1, WindowMsgData mData2 )
{
	return MSG_IGNORED;
}

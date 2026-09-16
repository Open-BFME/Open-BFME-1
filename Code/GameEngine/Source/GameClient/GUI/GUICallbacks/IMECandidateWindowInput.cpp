// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// IMECandidateWindowInput, retail 0x004C4A30 (6 bytes).
//
// The FunctionLexicon input table at 0x012A96E4 stores the string
// IMECandidateWindowInput in its row at 0x012A9948 next to the ILT thunk
// 0x0040A4B1, and that thunk jumps to 0x004C4A30.  Retail parks mov eax 1 then
// ret there, which is return MSG_HANDLED with all four arguments unread.  The
// candidate window swallows every message so that nothing reaches the windows
// underneath it.
//
// Local ABI-slice replica so no shared header moves.

typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;

class GameWindow;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

WindowMsgHandledType IMECandidateWindowInput( GameWindow *window, UnsignedInt msg,
																							WindowMsgData mData1, WindowMsgData mData2 )
{
	return MSG_HANDLED;
}

// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: retail 0x0064C6C0 (29 bytes) is the twin of BfmeConv506.cpp bfmeGoBPB with the
// guarded object as the SIXTH argument (the two arguments before it are not read): the
// three leading arguments are forwarded to its thiscall member.
//
// That member is reached through the ILT thunk 0x00018A9D, five bytes of
// `jmp 0x00649AE0`, with the receiver in ECX and three stack slots pushed right to
// left. The body the thunk reaches is the ledger's matched
// PeerThreadClass::nickErrorCallback, but that name is already defined twice in
// this tree -- game/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp
// carries an unmatched copy of the upstream body and
// PeerThreadNickErrorCallback.cpp the retail-truth one -- so naming it here would
// land this file in that existing duplicate instead of clearing its blocker. The
// only symbol defined at 0x00018A9D itself is the generated zero-argument thunk
// ?j_00018a9d@@YAXXZ (game/gen_small/gthunks_026.cpp), which the link keeps
// because it is retail's five bytes, so the reference carries that name and the
// three-argument thiscall shape is recovered through the union pun the tree
// already uses for thunks reached with arguments (BfmeConv1850.cpp,
// game/GameEngine/Source/Common/INI/INIWindowTransition.cpp). The enclosing
// forwarder keeps its own sixth parameter type, so this file's
// ?bfmeGoBPB0064C6C0 mangling is untouched.
extern void j_00018a9d();

class BfmeSubBPB0064C6C0
{
public:
	typedef void (BfmeSubBPB0064C6C0::*Dispatch)(void *, int, const char *);
};

void bfmeGoBPB0064C6C0(void *one, void *two, void *three, int unusedFour, int unusedFive, BfmeSubBPB0064C6C0 *sub)
{
	if (sub != 0)
	{
		union { void (*thunk)(); BfmeSubBPB0064C6C0::Dispatch dispatch; } pun;
		pun.thunk = j_00018a9d;

		(sub->*pun.dispatch)(one, reinterpret_cast<int>(two), reinterpret_cast<const char *>(three));
	}
}
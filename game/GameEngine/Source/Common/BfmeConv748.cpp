// Retail's call at 0x0033B855 goes to the incremental-link thunk
// ?j_0001ab86@@YAXXZ (game/gen_small/thunks_012.cpp), whose own jump targets
// 0x00193760.  The thunk is declared with no parameters, so the argument retail
// pushes is threaded through a punned union: MSVC 7.1 folds the pun back into a
// DIRECT call to the thunk, which keeps the bytes identical and makes the
// reference resolvable by a real object.  This is the pattern BfmeConv1601.cpp
// already uses for this same thunk.  The thunk's target pops the argument, so
// the stack stays balanced.
void __cdecl j_0001ab86(void);

class BfmeOtherDPA
{
public:
	unsigned char m_bfmeHead[8];
	char m_bfmeVal;
};

BfmeOtherDPA *bfmeGoDPA(BfmeOtherDPA *other, void *value, char *src)
{
	volatile int tmp = 0;
	union CopyCall
	{
		void (__cdecl *freeCall)(void);
		void (BfmeOtherDPA::*memberCall)(void *);
	} copyCall;
	copyCall.freeCall = &j_0001ab86;
	(other->*copyCall.memberCall)(value);
	other->m_bfmeVal = *src;
	return other;
}

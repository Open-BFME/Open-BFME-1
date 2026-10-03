// Open-BFME5 conversions.

// Retail's call at 0x003C5C26 goes to the incremental-link thunk
// ?j_0000ad85@@YAXXZ (game/gen_small/thunks_004.cpp), whose own jump targets
// 0x0003C5AF0: _STL::vector<Gen_t_003c5af0_p4cd>::insert.  The thunk is
// declared with no parameters, so the two arguments retail pushes are threaded
// through a punned union: MSVC 7.1 folds the pun back into a DIRECT call to the
// thunk, which keeps the bytes identical and makes the reference resolvable by
// a real object.  This is the pattern BfmeConv1601.cpp already uses for
// ?j_0001ab86@@YAXXZ.  The thunk's target pops the arguments, so the stack
// stays balanced.
void __cdecl j_0000ad85(void);

struct BfmeNodeIC;

class BfmeThingIC
{
public:
	void *m_bfmeVal;
};

struct BfmeNodeIC
{
	char m_bfmePad[0x28];
	BfmeNodeIC *m_bfmeNext;
};

void __stdcall bfmeGoIC(BfmeNodeIC *n, BfmeThingIC *t)
{
	while (n) {
		union CopyCall
		{
			void (__cdecl *freeCall)(void);
			void (BfmeThingIC::*memberCall)(void *, BfmeNodeIC *);
		} copyCall;
		copyCall.freeCall = &j_0000ad85;
		(t->*copyCall.memberCall)(t->m_bfmeVal, n);
		n = n->m_bfmeNext;
	}
}

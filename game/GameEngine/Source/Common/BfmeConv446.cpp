// Retail's call at 0x003CA6C0 pushes m_bfmeWhat twice and lets the callee clean
// the stack.  The only definition of RVA 0x00041164 is the 5-byte ILT thunk
// ?j_00041164@@YAXXZ (game/gen_small/thunks_031.cpp), whose name spells a
// void(void) __cdecl symbol, so the two-argument signature cannot be written as
// a declaration of that symbol.  Calling the thunk through an alias carrying
// retail's entry ABI folds back to the same `call ?j_00041164@@YAXXZ` while the
// relocation stays on the one symbol defined at 0x00041164.
extern void j_00041164();
typedef void (*Rva003CA6C0Callee)(void *one, void *two);

class BfmeThingBDF
{
public:
	void bfmeGoBDF();
	unsigned char m_bfmeHead[0xb4];
	void *m_bfmeWhat;
};

void BfmeThingBDF::bfmeGoBDF()
{
	((Rva003CA6C0Callee)&j_00041164)(m_bfmeWhat, m_bfmeWhat);
}

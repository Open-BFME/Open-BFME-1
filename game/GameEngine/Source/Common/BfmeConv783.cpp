// Retail's global at 0x012F0898 is `GameLogic *TheGameLogic`, defined once in
// GameLogic/System/GameLogic.cpp.  This TU reads through its own file-local
// view of the object.
class GameLogic;

extern GameLogic *TheGameLogic;

struct BfmeOtherDUI
{
	unsigned char m_bfmeHead[0x3c];
	void *m_bfmeField;
};

struct BfmeSubDUI
{
	unsigned char m_bfmeHead[0xa0];
	void *m_bfmeSlot;
};

struct BfmeThingDUI
{
	void bfmeGoDUI();
	unsigned char m_bfmeHead[0x44];
	BfmeSubDUI *m_bfmeSub;
};

// Retail's callee for this body is the five-byte ILT thunk at 0x0001E47F. The
// ledger owns that address as ?j_0001e47f@@YAXXZ (game/gen_small/thunks_014.cpp,
// a `void __cdecl(void)` body), so the call is spelled with the ledger's name and
// cast to the one-argument register convention this site uses -- the same shape
// AIStateMachineDestructor.cpp uses for j_00027566 and j_0001e47f.  A second
// identity for the address would leave the symbol unresolved at link time.
extern void j_0001e47f();
typedef void (__fastcall *OneDUICall)(BfmeThingDUI *);

void BfmeThingDUI::bfmeGoDUI()
{
	((OneDUICall)j_0001e47f)(this);

	BfmeSubDUI *sub = m_bfmeSub;
	if (sub)
		sub->m_bfmeSlot = ((BfmeOtherDUI *)TheGameLogic)->m_bfmeField;
}

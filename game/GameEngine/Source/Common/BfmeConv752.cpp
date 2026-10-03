// Retail's callee for this body is the five-byte ILT thunk at 0x00003C56. The
// ledger owns that address as ?j_00003c56@@YAXXZ (game/gen_small/thunks_001.cpp,
// a `void __cdecl(void)` body), so the call is spelled with the ledger's name and
// reached through a member-pointer union -- the calling convention this site
// actually uses (this in ecx, one stack argument) is not expressible on a
// `void __cdecl(void)` declaration, and a second identity for the address would
// leave the symbol unresolved at link time.
extern void j_00003c56();

class BfmeSubDPE
{
	unsigned char m_bfmeHead[4];
};

class BfmeFirstDPE
{
public:
	BfmeSubDPE m_bfmeSub;
};

class BfmeOtherDPE
{
public:
	typedef void (BfmeOtherDPE::*CallMember)(BfmeSubDPE *);
};

class BfmeThingDPE
{
public:
	BfmeOtherDPE *bfmeGoDPE(BfmeOtherDPE *other);
	BfmeFirstDPE *m_bfmeFirst;
};

BfmeOtherDPE *BfmeThingDPE::bfmeGoDPE(BfmeOtherDPE *other)
{
	union { void (__cdecl *raw)(); BfmeOtherDPE::CallMember member; } call;
	call.raw = j_00003c56;

	volatile int tmp = 0;
	(other->*call.member)(&m_bfmeFirst->m_bfmeSub);
	return other;
}

// Retail's callee for this body is the five-byte ILT thunk at 0x0002AFEF. The
// ledger owns that address as ?j_0002afef@@YAXXZ (game/gen_small/thunks_020.cpp,
// a `void __cdecl(void)` body), so the call is spelled with the ledger's name and
// reached through a member-pointer union -- the calling convention this site
// actually uses (this in ecx, one stack argument) is not expressible on a
// `void __cdecl(void)` declaration, and a second identity for the address would
// leave the symbol unresolved at link time.
extern void j_0002afef();

struct BfmeSubBRE
{
	typedef void (BfmeSubBRE::*DoMember)(void *);

	unsigned char m_bfmeHead[0x24];
	unsigned int m_bfmeFlags;
};

class BfmeThingBRE
{
public:
	void bfmeGoBRE(void *what);
	BfmeSubBRE *m_bfmeSub;
};

void BfmeThingBRE::bfmeGoBRE(void *what)
{
	union { void (__cdecl *raw)(); BfmeSubBRE::DoMember member; } call;
	call.raw = j_0002afef;

	(m_bfmeSub->*call.member)(what);
	m_bfmeSub->m_bfmeFlags |= 8;
	m_bfmeSub->m_bfmeFlags &= 0xffffffef;
}

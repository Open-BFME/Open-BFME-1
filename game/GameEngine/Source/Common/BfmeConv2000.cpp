// Both base calls go through five-byte incremental-link thunks, so retail calls
// the thunks and the ledger owns those addresses as ?j_<rva>@@YAXXZ; the calls
// below spell those names. The union of a cdecl entry with a member-function
// pointer is the tree's way to call such a thunk with `this` in ecx
// (GameNetwork/GameSpy/GameSpyInfoHost.cpp).
extern void j_0003f6d9();	// ?j_0003f6d9@@YAXXZ
extern void j_000388e8();	// ?j_000388e8@@YAXXZ

// The three vftables this constructor stores are pinned in
// targets/game/reverse/symbols.csv (_bfmeVftAEVJ/_bfmeVftBEVJ/_bfmeVftCEVJ)
// but no object defines them yet, so they still need a data row.
extern "C" void *bfmeVftAEVJ[];
extern "C" void *bfmeVftBEVJ[];
extern "C" void *bfmeVftCEVJ[];

class BfmeHostEVJ;

class BfmeSubEVJ
{
public:
	void *volatile m_bfmeVftCEVJ;
	unsigned char m_bfmePadCEVJ[8];
};

class BfmeHostEVJ
{
public:
	BfmeHostEVJ(BfmeHostEVJ *other);

	void *volatile m_bfmeVftAEVJ;
	int m_bfmePadAEVJ;
	void *volatile m_bfmeVftBEVJ;
	int m_bfmePadBEVJ;
	BfmeSubEVJ m_bfmeSubEVJ;
	char m_bfmeFlagEVJ;
};

BfmeHostEVJ::BfmeHostEVJ(BfmeHostEVJ *other)
{
	{
		typedef void (BfmeHostEVJ::*F)(BfmeHostEVJ *);
		union { void (*entry)(); F method; } call;
		call.entry = j_0003f6d9;
		(this->*call.method)(other);
	}
	{
		typedef void (BfmeSubEVJ::*F)(BfmeSubEVJ *);
		union { void (*entry)(); F method; } call;
		call.entry = j_000388e8;
		(&m_bfmeSubEVJ->*call.method)(other != 0 ? &other->m_bfmeSubEVJ : 0);
	}

	m_bfmeVftAEVJ = bfmeVftAEVJ;
	m_bfmeVftBEVJ = bfmeVftBEVJ;
	m_bfmeSubEVJ.m_bfmeVftCEVJ = bfmeVftCEVJ;

	m_bfmeFlagEVJ = other->m_bfmeFlagEVJ;
}
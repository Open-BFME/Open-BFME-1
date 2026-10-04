// Both base calls go through five-byte incremental-link thunks, so retail calls
// the thunks and the ledger owns those addresses as ?j_<rva>@@YAXXZ; the calls
// below spell those names. The union of a cdecl entry with a member-function
// pointer is the tree's way to call such a thunk with `this` in ecx
// (GameNetwork/GameSpy/GameSpyInfoHost.cpp).
extern void j_0003f6d9();	// ?j_0003f6d9@@YAXXZ
extern void j_000344e6();	// ?j_000344e6@@YAXXZ

// The three vftables this constructor stores are pinned in
// targets/game/reverse/symbols.csv (_bfmeVftAEVK/_bfmeVftBEVK/_bfmeVftCEVK)
// but no object defines them yet, so they still need a data row.
extern "C" void *bfmeVftAEVK[];
extern "C" void *bfmeVftBEVK[];
extern "C" void *bfmeVftCEVK[];

class BfmeHostEVK;

class BfmeSubEVK
{
public:
	void *volatile m_bfmeVftCEVK;
	unsigned char m_bfmePadCEVK[0xc];
};

class BfmeHostEVK
{
public:
	BfmeHostEVK(BfmeHostEVK *other);

	void *volatile m_bfmeVftAEVK;
	int m_bfmePadAEVK;
	void *volatile m_bfmeVftBEVK;
	int m_bfmePadBEVK;
	BfmeSubEVK m_bfmeSubEVK;
	char m_bfmeFlagEVK;
};

BfmeHostEVK::BfmeHostEVK(BfmeHostEVK *other)
{
	{
		typedef void (BfmeHostEVK::*F)(BfmeHostEVK *);
		union { void (*entry)(); F method; } call;
		call.entry = j_0003f6d9;
		(this->*call.method)(other);
	}
	{
		typedef void (BfmeSubEVK::*F)(BfmeSubEVK *);
		union { void (*entry)(); F method; } call;
		call.entry = j_000344e6;
		(&m_bfmeSubEVK->*call.method)(other != 0 ? &other->m_bfmeSubEVK : 0);
	}

	m_bfmeVftAEVK = bfmeVftAEVK;
	m_bfmeVftBEVK = bfmeVftBEVK;
	m_bfmeSubEVK.m_bfmeVftCEVK = bfmeVftCEVK;

	m_bfmeFlagEVK = other->m_bfmeFlagEVK;
}
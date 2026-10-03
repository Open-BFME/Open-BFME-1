// bfmeVftCJA is ??_7Gen_000B5240@@6B@ at 0x010827DC, the vftable of the
// Gen_000B5240 class (see dir32_addresses.csv).
extern "C" unsigned char __identifier("??_7Gen_000B5240@@6B@")[];
#define bfmeVftCJA __identifier("??_7Gen_000B5240@@6B@")

// Retail's call target is the ILT thunk at 0x00013C73, owned by
// game/gen_small/thunks_009.cpp as ?j_00013c73@@YAXXZ.  It is declared here by
// its decorated symbol and called through a __stdcall typedef, the convention
// BfmeConv502.cpp and BfmeConv630.cpp use, instead of under a TU-local member
// name nothing defines.  __thiscall only adds ECX over __stdcall, and retail
// never reloads ECX for this call (this is saved into esi, not ECX), so the
// typedef reproduces the reference byte for byte.
extern "C" void __cdecl __identifier("?j_00013c73@@YAXXZ")();
typedef void (__stdcall *BfmeBaseCJAThunk)(void *what);

struct BfmeThingCJA
{
	BfmeThingCJA *bfmeInitCJA(void *what, void *owner);
	void *volatile m_bfmeVft;
	unsigned char m_bfmeGap[0x94];
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	void *volatile m_bfmeC;
};

BfmeThingCJA *BfmeThingCJA::bfmeInitCJA(void *what, void *owner)
{
	((BfmeBaseCJAThunk)&__identifier("?j_00013c73@@YAXXZ"))(what);
	m_bfmeVft = bfmeVftCJA;
	m_bfmeA = 0;
	m_bfmeB = 0;
	m_bfmeC = owner;
	return this;
}

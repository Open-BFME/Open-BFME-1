// Retail 0x00891E00 (65 bytes).  Straight-line teardown sequence: twelve unconditional calls to already-named
// (or already-dumped) release/globals-teardown routines, no branching, no args.
// The last call is a tail jmp at +0x3C; those five bytes were a generated
// gap-thunk row until this body claimed its full extent (nothing in the
// image targets 0x00891E3C).  No caller names it, so it keeps its address.
extern void rva008B8B80ReleaseAll();
extern void rva008B61D0ReleaseGlobals();
extern void rva008A4630ReleaseGlobals();
extern void rva008A47B0ReleaseGlobals();
extern void bfmeGo1062B();
extern void rva008A48D0ReleaseGlobals();
extern void bfmeGo1083A();
extern void bfmeGo1082C();
extern void bfmeGo1082B();
extern void rva008B2BD0ReleaseGlobals();
extern void d_008acac0();
extern void rva008A98B0ReleaseAll();
extern void Rva008A4AA0Invoke();
extern void __cdecl bfmeAppend(int first, int second, int third);
struct Rva008A1DF0State;
// retail 0x013377D8; defining spelling (BfmePicker1284.cpp), declared
// incomplete here because only the pointer value is passed on.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;
extern void *Rva008A1DF0(Rva008A1DF0State *state, int unused);
extern void d_008a1e80();

void rva00891DE0RegisterChain()
{
	bfmeAppend(reinterpret_cast<int>(g_bfmeHolderBU),
		reinterpret_cast<int>(&Rva008A1DF0),
		reinterpret_cast<int>(&d_008a1e80));
}

void rva00891E00ReleaseChain()
{
	rva008B8B80ReleaseAll();
	rva008B61D0ReleaseGlobals();
	rva008A4630ReleaseGlobals();
	rva008A47B0ReleaseGlobals();
	bfmeGo1062B();
	rva008A48D0ReleaseGlobals();
	bfmeGo1083A();
	bfmeGo1082C();
	bfmeGo1082B();
	rva008B2BD0ReleaseGlobals();
	d_008acac0();
	rva008A98B0ReleaseAll();
	Rva008A4AA0Invoke();
}

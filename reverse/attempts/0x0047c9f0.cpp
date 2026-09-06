// ?bfmeGateAS@@YGHPAVBfmeThingAS@@HPAX1@Z (identity unknown)
// partial score=0.92 date=2026-09-06
// 45/49 at exact size. 0x0047CA30 is a byte-identical twin apart from the
// call target (thunk 0x00003148 instead of 0x0003D07D), so this stash serves
// both. Control shape is exact: the null guard and the `kind != 2 && (flags &
// 0x800)` guard share one `xor eax,eax` block that sits BEFORE the call block,
// which is what writing them as two separate early returns produces.
// Residue: retail loads the last two arguments through ONE register, pushing
// between the loads (`mov edx,[esp+0x10]` / `push edx` / `mov edx,[esp+0x10]`
// / `push edx` -- same displacement, different esp), while MSVC preloads both
// into ecx and edx first. Tried named locals for both arguments and int
// instead of void* parameter types; both give the identical three-line diff.
class BfmeThingAS
{
public:
	unsigned char m_bfmeHeadAS[8];
	int m_bfmeFlagsAS;
};

int __stdcall bfmeRunAS(int kind, void *first, void *second);	// pin at thunk 0x0003D07D

int __stdcall bfmeGateAS(BfmeThingAS *thing, int kind, void *first, void *second)
{
	if (thing == 0)
		return 0;

	if (kind != 2 && (thing->m_bfmeFlagsAS & 0x800) != 0)
		return 0;

	return bfmeRunAS(kind, first, second);
}

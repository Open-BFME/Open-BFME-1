// ?bfmeEmitCJ@@YAXPAXDD0@Z (identity unknown)
// partial score=0.85 date=2026-09-07
// 57/66. The logic is exact: `xor eax,eax / test cl,cl / sete al / inc eax` is
// `(first == 0) ? 2 : 1`, and the two arms or in 8 or 4 before a cdecl 3-arg
// call. Both arms and both epilogues are byte-identical where they overlap.
// The 9 bytes are entirely MSVC HOISTING: it lifts the `target` and `extra`
// loads and the first `push ecx` above the branch so the second arm reuses
// them; retail reloads both inside each arm.
// Not reachable by flag: /Ot /Og /Gy /Ob0 all give 57, /Oy- gives 58.
// This is the third body this tick to differ only in a merge/duplicate/hoist
// decision (see also 0x0061DD60 and 0x0015A130) -- small call-chain bodies are
// dominated by these, so prefer larger ones from the same screen.
extern "C" void __cdecl bfmeSendCJ(void *target, int flags, void *extra);

void __cdecl bfmeEmitCJ(void *target, char first, char second, void *extra)
{
	int flags = (first == 0) ? 2 : 1;

	if (second != 0)
		bfmeSendCJ(target, flags | 8, extra);
	else
		bfmeSendCJ(target, flags | 4, extra);
}

// ?Rva009C2320Vp6FilterDiag4@@YAXPAX00HHPAH@Z
// partial score=0.28 date=2026-09-04
// cl: /O2 /Ob0 /Oy- /G6 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// 2026-09-10 structural correction (t=180min session, no byte progress vs
// the 0.28 baseline -- logged as a fresh blocked entry in re_attempts.log,
// this header note is the summary): this three-separate-loops model is
// WRONG.  Retail's real body is a single 8-iteration loop over y=0..7 that
// computes all three edge weights (vertical vs row-above, left, right)
// TOGETHER per row, writing vertical to a 128-byte buffer at
// ebp-0xb0..ebp-0x30 (8 rows x 16B, +0x10/iter) and left+right to a SHARED
// 256-byte buffer at ebp-0x1b0..ebp-0xb0, where LEFT for row y lands at
// offset y*0x10 and RIGHT for row y lands at offset y*0x10+0x70 off the
// SAME growing pointer -- the two ranges overlap by 16 bytes at offset
// 0x70 (row7 LEFT overwrites row0 RIGHT there; retail relies on that, not
// a bug).  Confirmed retail is genuinely hand-vectorized MMX/SSE2 (movd/
// punpcklbw/pcmpgtb/movq2dq into xmm, psraw 8 to sign-extend back to byte),
// so this scalar C body cannot byte-match regardless of loop-structure
// fixes -- a prior session already confirmed this independently.  The path
// forward is a literal MASM transcription (see reverse/attempts/0x009bebb0.cpp
// for the sibling recipe: real C prologue reproducing the frame below, one
// or more __asm islands with their own explicit register saves for the
// SIMD kernel, real C for/while control flow around the islands so the two
// backward jne's are genuine branches, not transcribed jumps).
//
// Prologue CONFIRMED empirically (build/probe/probe1.cpp, not checked in):
// two __declspec(align(16)) locals referenced from inside an __asm block
// reproduce retail's exact hybrid frame shape byte-for-byte in its opening
// moves, with OR WITHOUT /Oy- (frame-pointer omission does not gate it --
// the align(16) locals plus the presence of inline asm are what trigger it):
//   push ebx / mov ebx,esp / <align pad> / and esp,-16 / add esp,4 /
//   push ebp / mov ebp,esp / sub esp,<frame size>
// ebx keeps the pre-align esp (params read via [ebx+8], [ebx+0xc], ... --
// [ebx+8] itself is this function's unused first arg and is never read);
// ebp addresses the aligned locals.
//
// 2026-09-10 second session (t=110min, build/probe6/sweep*.cpp, not checked
// in): isolated BOTH remaining prologue elements to their true triggers,
// via a multi-function-per-TU harness (build.py compile_source +
// read_object_symbol_bytes, no ledger writes) --
//   - The ebx-anchor mechanism ITSELF (not just alignment) needs the __asm
//     island to use EBP AS ITS OWN SCRATCH REGISTER (push/pop ebp inside
//     the island, exactly like the esi/edi/ecx/edx/eax/ebx saves already
//     confirmed from the retail dump).  align(16) locals + an island that
//     only touches xmm/mm + eax/ecx/edx/ebx do NOT get the ebx-anchor at
//     all (plain `push ebp; mov ebp,esp; and esp,-16; sub esp,N` instead,
//     confirmed with the SAME 6-parameter signature as this function) --
//     EBP must be freed up as scratch to force the compiler onto a
//     separate EBX anchor for parameter access.  This alone reproduces
//     `push ebx/mov ebx,esp/<pad>/and esp,-16/add esp,4/push ebp/
//     mov ebp,esp` -- but pad is `push ecx` (4B) and ebp is loaded plainly
//     (mov ebp,esp), no [ebx+4] copy.  (sweep4.cpp probeP12, sweep7.cpp
//     probeP17 under /EHa: identical result either way.)
//   - The 8-byte pad (`sub esp,8`) AND the `mov ebp,[ebx+4]; mov [esp+4],
//     ebp` return-address copy are BOTH produced, byte-for-byte exact
//     through `mov ebp,esp` (all 10 prologue instructions), by EITHER (a)
//     a literal `__try { <asm island> } __except (K) { }` around the
//     island (K constant, any value 0/1 -- sweep1.cpp probeP3, sweep5.cpp
//     probeP13/P14), OR (b) /EHa PLUS a local C++ object whose destructor
//     is real (not provably no-op/throw()) -- sweep8.cpp probeP18.  BOTH
//     forms ALSO emit genuine SEH exception-registration code right after
//     the prologue (`push -1; push 0[; push 0]; mov eax,fs:[0]; push eax;
//     mov dword ptr fs:[0],esp`, ~20-30 more bytes) that retail's actual
//     764 bytes do NOT contain anywhere (confirmed: zero 0x64 FS-prefix
//     opcodes at real instruction boundaries in the full body, scanned via
//     build.read_target_bytes + capstone).  Tried to defeat the
//     registration emission: __except with an unreachable/constant filter
//     (0 and 1, both kept it), /EHa vs /EHsc (no difference alone), a
//     throwing ctor+dtor pair without /EHa or __try (no effect, plain
//     `push ebp;mov ebp,esp`), extern "C" callees (nothrow, no effect per
//     the existing lesson).  MSVC 7.1 appears to NEVER strip the runtime
//     SEH registration once __try or /EHa-implicit-object-protection is
//     lexically present, in every combination tried here.
//   REMAINING GAP: no source shape found yet that gets the exact 8-byte
//   pad + return-address copy WITHOUT also pulling in registration bytes
//   retail lacks.  Possible next angles, untried: a local object whose
//   dtor is protected under /EHa but whose corresponding scope entry gets
//   folded/shared with an OUTER caller's frame (unlikely, this is a free
//   function); a different MSVC-7.1-specific EH model flag beyond /EHsc
//   and /EHa; or the retaddr-copy idiom has a THIRD, non-EH trigger this
//   session's ~18 combinations did not hit.
//
// Once both reproduce, the compiler's OWN callee-saves for this body land
// as: single `push ebx` (real save, ebx is clobbered later) immediately
// after the C-level table lookups/stores, THEN `push esi; push edi`
// (another compiler auto-save) -- both BEFORE the __asm island's own
// explicit `push esi; push edi; push ecx; push edx; push eax; push ebx;
// push ebp ... pop` (reverse order) sequence around the SIMD kernel.
//
// 0x009C2620 (776 B) is a near-identical twin: byte-identical prologue and
// parameter/table-lookup C prefix through +0x76 (same 0x1b4 frame, same
// 0x012D8158 edge-tag table), diverging only inside the SIMD kernel/loop
// body. The same recipe applies to both; fix one, then port.

// The optimized VP6 block filter makes three signed-byte edge-weight planes
// (above, left and right), then folds them into an eight-row four-neighbour
// reconstruction.  The first argument is the dispatcher's unused context.

static int rva009c2320Weight(unsigned char a, unsigned char b,
	int selectorWeight, int edgeTag)
{
	int difference = (int)a - (int)b;
	int weight;

	if (difference < 0)
		difference = -difference;

	weight = selectorWeight + 0x20 - difference;
	if (weight < 0)
		weight = 0;
	if (weight > 3 * selectorWeight)
		weight = 3 * selectorWeight;

	// The retail MMX path marks a steep edge by OR-ing the signed tag into
	// the clamped byte.  This is the signed negative tap used by the final
	// psubusw/packuswb reconstruction.
	if (difference > selectorWeight + 0x60)
		weight = (int)((unsigned char)weight | (unsigned char)edgeTag);
	if (weight >= 0x80)
		weight -= 0x100;
	return weight;
}

static int rva009c2320ClipByte(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return value;
}

void __cdecl Rva009C2320Vp6FilterDiag4(
	void *, void *sourceArgument, void *destinationArgument,
	int stride, int selector, int *filterTable)
{
	unsigned char *source = (unsigned char *)sourceArgument;
	unsigned char *destination = (unsigned char *)destinationArgument;
	const int *edgeTable = (const int *)0x012D8158;
	int selectorWeight = filterTable[selector];
	int edgeTag = edgeTable[selector];
	__declspec(align(16)) short verticalWeight[9][8];
	__declspec(align(16)) short horizontalWeight[16][8];
	int y;
	int x;

	// The hand-written body keeps one extra vertical row for the lower tap;
	// the first eight rows are the rows materialized by its MMX loop.
	for (y = 0; y < 9; ++y) {
		for (x = 0; x < 8; ++x) {
			verticalWeight[y][x] = (short)rva009c2320Weight(
				source[y * stride + x], source[(y - 1) * stride + x],
				selectorWeight, edgeTag);
		}
	}

	for (y = 0; y < 8; ++y) {
		for (x = 0; x < 8; ++x) {
			unsigned char *row = source + y * stride;
			horizontalWeight[y][x] = (short)rva009c2320Weight(
				row[x], row[x - 1], selectorWeight, edgeTag);
			horizontalWeight[y + 8][x] = (short)rva009c2320Weight(
				row[x], row[x + 1], selectorWeight, edgeTag);
		}
	}

	for (y = 0; y < 8; ++y) {
		unsigned char *row = source + y * stride;
		unsigned char *out = destination + (y - 1) * stride;
		for (x = 0; x < 8; ++x) {
			int up = verticalWeight[y][x];
			int down = verticalWeight[y + 1][x];
			int left = horizontalWeight[y][x];
			int right = horizontalWeight[y + 8][x];
			int centre = 128 - up - down - left - right;
			int value = source[(y - 1) * stride + x] * up;

			value += source[(y + 1) * stride + x] * down;
			value += row[x - 1] * left;
			value += row[x + 1] * right;
			value += row[x] * centre;
			value += 64;
			if (value < 0)
				value = 0;
			out[x] = (unsigned char)rva009c2320ClipByte(value >> 7);
		}
	}
}

# DXTraceA: the MSVC 13.10 EBP-bias rule and the frame lever that reproduces it (2026-11-17, round 2)

Lane w48 DXTRACE round 2, model claude-opus-5-5, about two hours, base `5f60d90e6`,
census `e27899673e`, MSVC 13.10.3077, private outputs under `build/w48r2/` only.
Extends `tracea-bias-heuristic-20261117.md` (round 1) and `tracea-blocked.md`.
**Result: `game/Libraries/Source/DirectX/dxtracea.cpp` is EXACT 374/374 with 22
relocations** through a frame lever (below); identity evidence
`identity_evidence/dxerr9-summer2003-dxtracea.md`. DXTraceW and StringVPrintfWorkerW were
already source rows, so this landing retired `obj\i386\dxerr9.obj` (no ledger row reads
`dxerr9.lib`; `member-retirement-plan-20261117.md` "Outcome").

## Measured 13.10 bias rule (/O1 /G6, one compile per micro TU)

Repro with expected results: `tracea-bias-model-micro.cpp.txt`.

1. The bias is always `0x78 - 4*declared_args` (0x64 for DXTraceA).
2. The frame is biased when **at least three references** hit frame **slots** whose
   adjusted base `B' = slot_base + 4*unreferenced_args` satisfies `B' < -0x80 <= B' + bias`.
   Checked against `/FAsc` slot tables (`tracea-bias-validate.py.txt`) on 2330 private
   micro functions, 734 of them biased, including round 1's random corpus and its five
   "unexplained" frames: every biased frame meets the rule. The only misses are 17
   unbiased frames with exactly three references to a struct or union slot; such a slot
   also needs a fourth reference or two distinct referenced arguments. Arrays need three.
3. Only the slot base counts: three element reads `y[61..63]` that would move into
   disp8 range (a 256-byte `y` based at -0x180) do not bias.
4. Unreferenced arguments push the threshold down 4 bytes each: with all five
   arguments referenced a 132-byte buffer at -0x84 biases; with one unreferenced
   argument it does not, and 136 bytes at -0x88 does (round 1's "8 bytes past -0x80"
   and "two distinct arguments" observations are this term).
5. A never-written array (only read; not written, not address-taken) is packed into
   another buffer's slot, end-aligned, under the factor-of-two size rule of
   `docs/shape_levers.md`. The slot base is the larger member's base, and every member
   counts there: `char x[128]` with three `lea [ebp-0x80]` references plus a read of
   `int q[33]` gives a 132-byte slot based at -0x84, so x biases while still emitted at
   `[ebp-0x80]`. A zero-length intrinsic `memcpy` from such an array loses its
   `rep movs` after the frame decision (slot and bias stay) but leaves its
   `xor ecx,ecx; lea esi; lea edi` setup.

## Consequence for DXTraceA

Retail's frame is exactly the five buffers with no gap: slot bases -0x80 (line, 128),
-0x184 (file, 260), -0x284 (error, 256), -0x684 (msg, 1024), -0x123C (buffer, 3000), and
all five arguments are referenced, so `B' = slot_base`. The gain window for bias 0x64 is
[-0xE4, -0x81] and holds no slot base, so 13.10 never biases the plain body: no flag,
pragma, declaration order or scope can (table below). 13.00.9178 (`@comp.id` 0x001d23da)
biased it; the simplest reading (not testable without that compiler) is that its rule
counted a base of exactly -0x80 as out of range.

## The lever (landed)

Rule 5 supplies the missing slot. Starting from the round-1 bank (the plain 369 B body,
`attempts/0x00afd388.cpp` until this landing cleared it):

1. `long frameBiasSlot[33];` (never written) packs with `strBufferLine` into one 132-byte
   slot based at -0x84; the line buffer stays at `[ebp-0x80]`, so its three references
   bias the frame by 0x64 exactly as retail.
2. The slot is four bytes taller than the line buffer, so the popup file buffer is
   declared `[256]` (still passed 260): it then starts at retail's -0x184 and its last
   four bytes are the slot's lowest four, never used by anything else. Every other buffer
   keeps its retail address; frame 0x123C.
3. The slot needs one reference that emits nothing new: `return frameBiasSlot[37];`
   addresses -0x84 + 37*4 = +0x10, the `hr` argument, so it is the same
   `mov eax,[ebp+0x74]` retail ends with.

Measured on the way: steps 1-2 with `return hr | q[32];` gave 377 B, the first 0x169 bytes
equal retail modulo all 22 relocations and only the q read left over; step 3 made it
EXACT 374/374 (`tools/probe.py`). It compiles with C4700 (q used uninitialised). The out-of-
bounds read and the short declaration are deliberate layout devices whose behaviour is
fixed by this compiler and these flags; they do not describe the original source.
Without the lever the C++ route is closed for 13.10.3077, and the remaining alternative
was a MASM body.

Searched before step 3, none keeps the slot reference out of the code: zero-length
`memcpy`/`memcmp` leave setup code; `__assume`, dead reads, `x*0`, self-compares and
self-copies remove q before the frame decision; `try/catch` adds EH frames.

## Variants measured this round (bank body unless noted; unbiased unless noted)

| Variant | Result |
|---|---|
| `/O1`, `/Os /Oy-`, `/Og /Os /Oy-`, `/O1 /Oy-`, `/O2 /Os`, `/O1 /MD`, `/O1 /ML` | 369 B |
| `/O2 /Oy-`, `/Ox /Oy-`, `/Ot /Oy-`, `/Og /Ot /Oy-` (+`/Ob1 /Gs /GF /Gy`, +`/Oi`), `/Ox /Ot /Oy-`, `/O2 /Oy-` with `/Ob0`, `/Ob1`, `/Oi-`, `/G5`, `/GB`, `/Oa`, `/Ow`, `/Op`, `/MD` | 379 B |
| `/O2 /Oy- /G7` | 378 B |
| `/O2`, `/Ox`, `/Og /Ot /Oy`, `/O1 /Ot` | 418 B, ESP frame |
| `/O1 /Og-` 402 B, `/Od` 411 B | frame 0x1240 |
| top buffer as union with `double`, `int[32]`, `char[2][64]`, struct, reference, pointer alias, `double[16]`, `unsigned short[64]` (micro) | no bias |
| `__declspec(align(8))` top buffer (micro) | `and esp` aligned frame |
| enregistered scalar live across calls (micro) | no bias; spilled scalars sit above the buffer and move it |
| written, address-taken or block-local arguments (micro) | no bias |
| never-written `q[33]` + file buffer `[256]` + `return hr \| q[32]` | biased, 377 B |
| same with `return q[37]` | **EXACT 374/374** |

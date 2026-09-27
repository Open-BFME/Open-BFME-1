# Batched renderer at 0x00934940

The complete extent is 8,277 bytes, ending at the plain `ret` at
0x00936994 (+0x2054). Eleven INT3 bytes precede the next entry at 0x009369A0.
The generated carve and the independent read-only Ghidra decompilation agree.
The raw caller at 0x0079DEE0 and the ILT jump at 0x006E9B86 identify this entry,
but do not prove a semantic method name. Render2DClass::Render is independently
matched at 0x00933E50 and must not be reused for this distinct body. Retain
`?render@Rva00934940Renderer@@QAEXXZ` until independent evidence proves more.

The entry takes this in ECX and no stack arguments, has a 0x120-byte local
frame and no meaningful return value. Its last substantive operation calls
the independently matched Render2DClass::Reset at 0x00934820 on the original
receiver. That complete 276-byte owner independently witnesses the raw arrays
at +0x14/+0x24, the 24-byte dynamic vector at +0x34, texture at +0x4C,
current batch at +0x50, and dirty flag at +0x54. The 0x74-byte batch consists
of a texture pointer, seven linked-list heads at +4, and seven signed index
counts at +0x58. The intervening fourteen words stay opaque. The matching
assignment owner at 0x00933C60 independently supplies the same 0x74-byte
texture-bearing record. Name oracle has no BFME Render2DClass or DX8Caps
layout witness; it only reports incompatible later-reference layouts.

The old preferred source was a function-only, incomplete 3,743-byte later
Render2D render draft. This reconstruction restores the missing BFME loops:
copy 44-byte vertex records, flatten each batch's seven linked index lists
into the dynamic index buffer, then select texture/shader/stencil states and
draw each nonempty list. It restores the two multi-texture paths, signed
triangle-count division, snapshot string lifetimes, state resets, original
transforms, texture releases, and final owner reset. The 24-byte BoxDynamicVB
access ABI and 8-byte write lock reuse independently matched family owners.
All of the body and the scoped wrappers are native C++; no instruction lift,
new assembly, volatile barrier, speculative pin, or progress claim is present.

Two physical contracts differ from the inherited later-reference headers.
DX8Caps is read at byte +0x272 and signed word +0x278; the bank keeps these
address-derived fields. Existing BFME VendorSpecific_Hacks view and matched
ApplyDefaultState at 0x009095A0 independently corroborate +0x278. The texture
stage setter calls device vtable slot 67 (+0x10C), whereas this shim's direct
method declaration selects slot 70. Matched Set_DX8_Texture_Stage_State_Body
at 0x006C5840 (255 bytes, dxwrapper.cpp) and matched ApplyDefaultState at
0x009095A0 independently establish the stdcall device/stage/state/value ABI
and slot 67. A TU-scoped native copy preserves the state cache, snapshot
string, call counter, and texture-state counter. Its complete out-of-range
stage arm is retained: although all calls here have constant stages 0..3,
removing the arm changes VC7.1's nested StringClass constructor inlining in
the cleanup tail and adds 76 bytes. Transform slots 44/45 and render-state
slot 57 already agree with retail; they are not changed.

The final bank emits 8,275 bytes with 4,304 probe-masked differing positions
and a two-byte extent deficit. The measured positional score is
`1-(4304+2)/8277 = 0.479763199226773`. Normalized instruction shape is
separately 0.992, with fifteen structural differences. Almost all semantic
blocks agree; differing setup register assignments shift the body, so the
normalized score must not be used as the finish-queue byte score. Residue is
confined to early owner/zero register allocation, two global call-counter
schedules, the omitted redundant MOV before the vertex memcpy multiplication,
and one shader-global load schedule. Direct shader-bit mutation removes two
unneeded copies. Bounds accessors must load the array pointer inside their
selected branch; caching it early worsens the emitted shape.

Rejected levers: direct receiver layout versus a scoped view, inheritance
visibility, splitting shader-global values, sizeof-based vertex copy count,
the independently matched 82-byte BoxDynamicVB constructor made visible but
noinline, reduced inline depth, and direct macro expansion of the independently matched
state setter (8,384 bytes). The latter destroys the matrix frame and
snapshot shape. A bool-only StringClass constructor is the wrong contract
and is not retained. Full cleanup states and semantic behavior are preserved
in the selected bank. Relocation closure is not claimed: before landing,
prove all emitted DIR32 operands, in particular the unpinned stencil-reference
global Rva012D7180, and run the normal scoped gate. No source or pin was added
to game/ and no existing matched owner was moved.

The name-regression guard pairs old DX8Wrapper uses with the added
Rva00934940DX8 subclass. This is a false correspondence: the canonical named
base remains included and used throughout the source. The subclass is a new,
scoped access mechanism for the independently proven slot contract, not a
renamed game type. The correction record is restricted to this exact pair
of source hashes and changes no detector baseline.

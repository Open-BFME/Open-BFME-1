# Keep the member-motion distance local, retain the real length provider

Base `6005b4d951`; claimed RVA `00230BF0` (1,020 bytes), queue rank 6 at
`afbe8bafb6`. The only census blocker is this TU's wrong COMDAT copy of
`Coord3D::length`. Prior history supplies the x/z/y evaluation-order context;
no earlier linker repair of this source is recorded.

## Target facts and change

The native member-motion body computes its distance inline in x/z/y order.
Its complete native calls contain no call to the shared length function.
The TU nevertheless emits a 33-byte external length copy with a different
x87 schedule from native `000B6CA0`. The actual matched owner is already
`Rva0023C5E0.cpp`, using `basetype.h` and the ordinary x/y/z expression.
That owner's complete 33 bytes equal retail and have no relocations.

Expanding the existing three-step x/z/y calculation into a local float at
its sole call site preserves the original local operation and removes the
TU's shared method definition. The main body's entire 1,020 bytes and every
relocation remain unchanged. All 46 retained external code definitions and
their relocations are identical; only the bad length copy disappears, with
no added definition. Its only original incoming edge is `.debug$F`, type 7.
The real provider is not edited or removed. No header, pin, alias, class
layout, ledger row, compiler option or hatch changes.

The first minimal trial changed only `inline` to `__forceinline`. All 47
external definitions remained identical, including the bad length copy, so
it supplied no repair and is not retained. Actual-object controls preserve
both trials. This is a measured TU-local emitter repair, not a general
claim that the floating-point expressions are interchangeable.

The normal caller/provider gate passes 3/3 rows, 9 DIR32 references, 6
floating constants, two literals and the body guards. Frozen definitions pass.
Compiler: normal MSVC 7.1 `/O2` defaults with this TU's `/DNDEBUG /MD`,
STLport and declared WWMath/shim/Zero Hour include context.

## BFME 2 review and linking limits

Pinned donor `b5a7b8290a0c4c20b03a3664609d434904e228eb`,
`Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp`, uses the ordinary x/y/z
length expression. Its class/base declarations, inline provider and consumer
context were reviewed with the corresponding recipe. Directly imposing that
expression on this BFME 1 inline site would discard its witnessed evaluation
order. The donor's `/O1 /arch:SSE2` settings and addresses are not adopted.
The BFME 1 native body, existing owner and whole-object comparison establish
the repair independently; no donor class identity or body is newly claimed.

Against the unchanged official `afbe8bafb6` index (2026-10-31 12:37), the
caller changes from its census length loser/0 to LINKS/1,020 authored bytes.
The real provider keeps LINKS/824: cohort 824 -> 1,844 is a frozen-index
prediction only. The prior current-selection check still lacks over 22,000
ledger objects. No whole-cache rebuild or unchanged broad scan is repeated,
and no current-selection, new census or runtime gain is asserted.

Controls live in ignored `build/two-each-no-qwen-20261031-1559` and the
create-only diagnostic run of the same name at `W:/OpenBFME/diagnostics/`.
No local inference model was started; the shared ten-worker build limit stays.

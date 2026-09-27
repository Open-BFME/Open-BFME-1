# W3DBridge::load native bank

2026-09-27, GPT-6. No conversion credit, source ownership move, or pin change.

## Boundary and identity

RVA `006D8C10` has 2817 executable bytes, three alignment bytes, and four
switch destinations at offsets `B04..B13`, giving the existing 2836-byte
extent. INT3 padding follows. Linear disassembly treats the last table byte
as an instruction prefix and emits a false extent warning; it is inline data.

The four retail table destinations, as RVAs, are `006D8D4D`, `006D8DB4`,
`006D8E19`, and `006D8E81`. The native object labels are respectively at
function offsets `13D`, `1A4`, `209`, and `271`, so all four table destinations
agree independently of relocation masking.

The EA W3DBridge::load counterpart has the same four damage-state texture/model
selection, `.BRIDGE_LEFT`, `.BRIDGE_SPAN`, and `.BRIDGE_RIGHT` names, section
transform collection, vertex bounds, and sectional-overlap checks. The landed
W3DBridge constructor, init, destructor, and vertex methods witness its
`114`-byte layout, template string at `108`, and mesh/model slots. The buffer
constructor constructs an array of these same `114`-byte objects.

## Recovered contracts

The source uses the canonical string, render-object, texture, matrix, mesh,
and shared-buffer headers. The TerrainRoadType value-returning string getters
are the already witnessed BFME contracts, rather than the inline reference
getters in the ZH header. BFME obtains a texture handle from the existing
`BFMEGetWaterTrackTexture` helper and a render object from `Create_Render_Obj`.
All 24 native REL32 operands select the retail target through existing ledger
or pin candidates. No new pin is needed.

The shared geometry header puts its vertex count and array at `2C` and `34`.
Retail here and the landed W3DBridgeGetModelVertices source independently read
them at `28` and `30`. A scoped address-derived record expresses those two
slots without changing the shared header.

The virtual call at slot `14` returns a mesh pointer. MeshClass's independently
proved primary table `0113C390` selects `0092C710` there; that complete body is
`mov eax,ecx; ret`. The matched constructor/destructor install this table,
and the aligned loader reads the returned mesh's model at `C8`. The scoped
virtual view keeps an address-derived name and a pointer return. It does not
cast the shared header's opaque integer-return declaration to a pointer.

## Result and remaining difference

The EA/reference-header baseline emitted 4540 bytes. Canonical BFME contracts
and offsets recovered the setup but initially unrolled the vertex loops
fourfold. Putting the loop increment in the condition, and advancing the
vertex pointer at the end of each body, reproduces the scalar loops and the
full 2836-byte size.

The preferred bank differs in 15 of 2572 concrete bytes:

* Eleven ECX/EDX register operand bytes in the first vertex loop, from `+849`
  to `+913`.
* Four bytes in one commutative x87 load/multiply pair at `+8A2`.

All other bytes outside the 66 relocation operands agree. The recorded score
is `(2572-15)/2572 = 0.994168`. The first 2122 bytes, the other two vertex loops,
and the final length and overlap checks agree. The probe's four relocation
layout warnings are the four independently checked switch-table entries.

Natural iterator and coordinate lifetimes, counter types, declarations,
comparison spelling, scoped loop extraction, complete transform copies,
named input/product temporaries, and inline helper calling conventions did
not remove this residue. Alternate compiler flags, pointer-range loops, and
volatile operand probes worsened it; none is retained. The original naked
game body remains available. A further attempt needs a new allocation or x87
lever and should start from this bank.

# Texture initializer call: one source repair, zero new coverage

`BfmeConv1803.cpp` has one existing46-byte row at RVA006D4620. It used the
unresolved synthetic `bfmeBaseInitZQ` spelling for the already owned250-byte
`??0Rva006D51B0TextureBase@@QAE@IIIIII@Z` constructor at RVA0090CF90.
Only that call is corrected. The caller identity/extent and all46 raw bytes
remain unchanged; no new body or .text-union credit is claimed.

## Independent BFME1 contract

The full original caller pushes its four original DWORD parameters plus1,0,
keeps the original receiver in ESI/ECX, calls0090CF90 directly, installs the
existing table at VA0111DFB0, returns the original receiver and uses RET10.
The complete250-byte callee uses ECX as this, initializes its base and owned
fields, returns the same receiver and uses RET18: six stack DWORDs. The already
verified owning C++ source declares exactly six unsigned parameters.

The replacement is a declaration-only view of that existing constructor and
the established explicit qualified constructor-call syntax. It creates no
object, asserts no class size, base hierarchy or virtual slot, and introduces
no definition. Converting the four opaque pointer-typed arguments to unsigned
preserves their exact32-bit representations on the native x86 target. No claim
is made that their original EA types or the caller's original EA name are known.

Whole controls cover the caller plus both unchanged provider sources:
`Bfme/Rva006D51B0Ctor.cpp` (163+250B) and `Bfme/Rva006D5280Ctor.cpp` (163B).
The latter remains the sole owner of `?g_BfmeVftZQ@@3PAPAXA`,68B/17 pointer
slots at VA0111DFB0. Its data row, initializer and all bindings are unchanged.
The available canonical texture.h has a different unreconciled layout; it
does not declare the neutral Rva006D51B0TextureBase owner. No new header, data,
pin, alias, baseline, virtual declaration or compiler option is introduced.

## Donor and compiler evidence

Historical BFME2 reference: e2e99959950e6eebfe1ced5663aa05de320afc52,
`Code/GameEngine/Source/Common/BfmeConv1803.cpp`, reviewed history b5a7b8290a0c4c20b03a3664609d434904e228eb.
Its existing40-byte constructor at000EF272 already spells the base call as
an explicit qualified constructor. This is the source/ABI adaptation lead,
not independent BFME1 identity proof. Its class layout,18-slot table,
addresses and /O1 profile are not imported. BFME1's native default profile
and all actual includes/dependencies remain unchanged. `docs/shape_levers.md`
already records this qualified-construction spelling near the friend-selection
case; this transfer adds no new general compiler claim.

Exactly one private candidate was compiled with the full native home profile
and environment checked equal before compiling. It matched46/46 strictly.
The first JSON export incorrectly attempted to encode a bytes value; the
already existing object was analyzed again without another C++ compilation.
The expected uncacheable private-build receipt was not injected into the normal
cache. The production source was then built with the normal full-family gate.

## Verification and boundaries

- Normal family before and after:4/4 existing functions,1/1 existing data row,
  7 DIR32 references; BodyGuard0 and no baseline findings.
- Normal production object matches the private runtime/FPO graph exactly.
  Compared with original, all three runtime/FPO sections retain flags, raw
  bytes, section order, COMDAT, directives, data and relocs except the one
  independently bound REL32 name at offset30. No extra helper is emitted.
  Debug type/path records are not equated to runtime.
- Native source hygiene reports all definitions matched.
- Normal link_check before:0->0, only old synthetic initializer unresolved.
- Normal link_check after:0->46, linked. This is a current per-file preview
  against the existing census, not a new full-image link or census.
- Exact coverage delta for this task is0; no startup, memory or crash result.

Private diagnostics: `W:/OpenBFME/diagnostics/one-per-project-20261125-170839/bfme1`. It retains all original/candidate
sources and objects, normal dependency proofs, original complete caller/callee
disassembly, native builds and link outputs. MANIFEST hashes the compact
tracked proofs and the relevant full private artifacts. Reference cache was
validated natively with unchanged functions.csv and donor inputs; no rescan.

# DX8ErrorTranslator: remove the losing StringClass constructor copy

Queue #38, census 77a8439ee4. Task 7 of this session.

## Target and provider evidence

The existing `DX8ErrorTranslator` row is retail RVA 0x009064F0, 287 bytes.
Its two strlen loops are inlined into the caller. The independently established
70-byte constructor at 0x007AF3A0 (ledger owner
`game/Libraries/Source/WWVegas/WW3D2/hanimmgr.cpp`) uses the multibyte-length import; changing
this caller to `_MBCS` breaks its verified bytes. This difference is already
recorded by the previous StringClass attempts; no identity or pin changes
are part of this repair.

BFME 2 donor revision f6d845ecd439374ef476ce04c992a2b848eb2c99 was inspected
read-only in the host checkout while this worktree initialized its donor.
`Code/Libraries/Source/WWVegas/WWLib/wwstring_ctor_pbd_bool.cpp` independently
separates the `_mbslen` constructor from the assignment TU. Its path maps to
BFME 1 `game/Libraries/Source/WWVegas/WWLib/`; no donor source, compiler flag
or include was copied. The suppression technique follows the existing
`dllimport __forceinline` entry in `docs/shape_levers.md`.

## Measured trials

MSVC 7.1, existing `/O2 /DNDEBUG /MD /EHsc` context. Diagnostic sources and
objects were isolated under `build/queue-stringclass/`.

- Original header: caller passes the normal 287-byte gate; emits a losing
  74-byte `??0StringClass@@QAE@PBD_N@Z` COMDAT.
- `dllimport inline` constructor: no constructor symbol, caller 181 bytes.
- `dllimport __forceinline` constructor alone: no constructor symbol,
  caller 224 bytes; nested assignment no longer automatically inlines.
- Also force the existing C-string assignment inline: caller returns to
  exactly 287 bytes. The normal source build passes byte, literal, constant,
  DIR32-address and body checks. COFF contains neither the constructor symbol
  nor any `__imp` reference.
- Force assignment without importing constructor: caller 287 bytes, but the
  unwanted constructor COMDAT remains.
- A TU-only qualified constructor redeclaration is refused by MSVC C2761.

The header exposes an opt-in `BFME_STRINGCLASS_INLINE_CSTR_ONLY`, enabled
only by DX8ErrorTranslator.cpp. Other TUs retain their existing declarations
and inline bodies. It does not change StringClass layout or its provider.

## Linking and validation

Before: census queue records the losing 74-byte constructor copy. After the
normal build, `link_check.py --compile-limit 0` reports no COMDAT or selected
blocker for this source. Its final selection verdict is still UNKNOWN because
this cold worktree lacks current objects for other definers; no linked-byte
gain is claimed from that preview. Full header gate results are recorded below.

## Donor freshness

Initialized without recursive references and fetched official master. The old
pinned revision f6d845ecd439374ef476ce04c992a2b848eb2c99 is retained in local
submodule branch `bfme1-pinned-20261105`; the clean checkout advances to
upstream dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce. The StringClass header and
constructor donor, Common/Bfme5ThirtyFour.cpp, Common/DelayedLuaEventList.cpp
and Object/Contain/OpenContainCtor.cpp are unchanged between these revisions.
The inspected evidence remains applicable. No donor build source, include path
or compiler setting enters this BFME 1 change, and this fresh worktree has no
old donor trial or sweep cache to invalidate. BFME 1's full gate validates its
own unchanged build inputs plus the opt-in header annotation.

## Full gate and pre-existing ownership failures

The full run compiled 22,710 stale TUs and byte-verified all 173,475 function
rows. String checks (27,738 literals plus 2,441 empty strings), constants
(8,971 floats plus 123 local loads), all body guards, pin consistency and
22,337 source claims passed. Global DIR32 ownership reports six failures
outside this repair:

- 0x0110FE78: `??_7Rva005CE890Object@@6B@`.
- 0x0107388C: `?BFMEEmptyUnicodeString@@3QBGB`.
- 0x012ED5E0: `?RvaObject012ED5E0@@3UGen00014475@@A`.
- 0x012ED4EC: `?g_rva012ED4EC@@3VAsciiString@@A`.
- 0x0041579E: `?j_0001579e@@YAXXZ`.
- 0x0134FBA8: `__commode`.

None of these names occurs in the 406 header-dependent sources. An isolated
original DX8 object and the modified normal-build object have identical
287-byte masked caller bodies AND identical relocation tuples (offset, type,
name). Every other TU sees the unchanged default preprocessor branch.
Thus this annotation does not introduce those ownership failures. No baseline
entry was added and none of these unrelated identities was changed. The full
run is red on this existing global debt; it must not be reported as all-green.

The full run finished with exactly one red check: DIR32 consistency for those
six names. All 1,819 data rows, null relocations across all 173,475 function
rows, and the no-op patch passed. `gate_baseline.py --check` exits 1 because
no known-red list covers these six names; that result is retained unchanged.
The normal header-dependent commit gate is the next validation step.

## Current linking preview

After the full run, checked DX8ErrorTranslator.cpp and hanimmgr.cpp together.
The caller has no COMDAT/selected blocker and no constructor/IAT reference.
Selection remains UNKNOWN: 504 changed census objects cannot be read with
current proof. The unchanged hanimmgr provider also has the independent
unresolved `W3DExclusionListClass::Is_Excluded(HAnimClass *) const`.
No linked bytes are claimed; the concrete progress is removal of the losing
constructor emitter with identical caller bytes and relocation tuples.

# Native StringBase binding and banked AsciiString emission policy

BFME 1 input: fbd5b1c46d (production sources unchanged from 99ae58b84f).
Retail SHA256: `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

## Production change: use the native comparator identity

SkirmishBattleHonors_getFavoriteSideName now explicitly calls
`favoriteSide.StringBase<char>::compare(AsciiString::TheEmptyString)`.
The existing public base declaration suffices; no header policy is needed.

Independent BFME 1 identity evidence, not an equal-byte inference:

- PE export1398 names `?compare@?$StringBase@D@@QBEHABV1@@Z` at RVA000220C5.
  Its bytes `e9e6dd0300` jump to body RVA0005FEB0.
- The original Skirmish REL32 operand at RVA0009DFFE targets that exact ILT.
- No AsciiString-reference comparator export exists. The ILT oracle confirms
  Base and contradicts Ascii (`p_false=4.57e-04`). Existing alias rows remain
  untouched and are not ownership evidence. No alias or pin is added.
- Current StringBase.cpp emits the native92-byte Base body, independently
  byte-verified (normalized digest `2a1be83a1314`). The equal-byte Ascii copy
  in RvaTreeBoundsAsciiString does NOT establish an additional native identity.

The Skirmish object loses its unused Ascii comparator and empty literal.
Its22 retained nondebug sections preserve flags, bytes, owners and relocations
except the independently required Ascii-to-Base external binding. EH/jump local
labels are compared by section/value, not unstable compiler ordinals.
Private evidence: `build/string-compare-native-identity.json`, the two
`string-compare-{base,ascii}-oracle.txt` files, and
`build/string-compare-base-only-proof.json`.

## Banked policy: not active production code

`20261111-ascii-compare-inline-only.patch` contains only the canonical header
policy and the Rva002157C0Refresh/ScriptConditionsPlayerMask opt-ins. Apply it
with `git apply` after its prerequisites are reconciled, then run the mandatory
normal FULL header gate; scoped proof is not a substitute.

The original inline body, four-byte base subobject and length/data accesses
are unchanged. Opted-in fully inlined consumers use imported-forceinline to
suppress unused competing COMDATs; neither a comparator nor an __imp_ reference
remains. Other consumers retain their original compilation policy. This is
not authority to import a comparator at runtime or to keep a changed provider.

The corrected composite (production Base call plus banked policy) passed the
normal6-source **211/211** gate:6 literals,108 empty refs,1 float and371 DIR32
refs, none unverified. Paired object proof passed all3 consumers, preserving
22/12/572 retained sections. Exactly3 comparator sections and Skirmish's unused
empty literal disappear. Only its expected Base binding changes. Evidence:
`build/string-compare-base-qualified-build.log` and
`build/string-compare-base-proof-banked-composite.json`.

The initial frozen snapshot instead used a declaration-only Ascii call. It was
NOT publishable: native identity review disproved that binding, and its normal
full gate deterministically reported11 unowned DIR32 names. It completed
22,761 compiles and173475/173475 function checks, all literals/constants/body
checks, but final data/no-op checks were unfinished. At21:10Z, on supervisor
instruction, only the owned gate and private-prefix compiler processes were
SIGTERM'd. The hook/commit exited1, no commit was created, and all descendants
and private compilers were confirmed stopped before edits. This is FAILED /
CANCELLED PARTIAL evidence, never full-gate success. Original log, frozen
staged patch/index tree, cancellation manifest/result and stable-write check
remain in `build/string-compare-*`. No baseline was enlarged.

## Donor provenance and compiler context

Approved pinned donor: `76f0baefa6f285d54bc1ca922397674312a5913f`.
Technique paths reviewed:

- `reverse/attempt_support/kindof-emission-link-20261015/readme.md`
- `reverse/attempt_support/connection-auth-string-cleanup-20261028-codex.md`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_not_equal.cpp`

The first read used eeef5b702d6f4de0d2a7bf61a2bff65df2aed2c3; a path-limited
zero diff and per-file SHA256 equality establish identical content at the
approved pin (`build/string-compare-donor-equivalence.json`). The donor supplies
only the emission technique, not a BFME 1 name, layout, address or provider.
Its Code paths map to game paths. No donor inputs, compiler flags or gitlink
change are imported. MSVC7.1 13.10.3077 uses original /O2 /MD /EHsc contexts,
Wine11.16, approved private `build/wineprefix-sol12h-wow64`, WINEARCH=win64,
BUILD_POOL=2. Native Base identity comes solely from the BFME 1 evidence above.

## Rejected siblings and linking limits

Three OptionPreferences sources are restored unchanged. Uniform forceinline
preserved parents but changed their existing native194-byte _M_find and less
helpers. Declaration-only specializations (with/without noinline) and extern
template suppression ICE at STLport _tree.h459 (VC7.1 C1001 P2/main.c148).
Logs: `build/string-compare-repaired{2,3,4,5}.log`. Original find provider:
RvaTreeFindAsciiString.cpp, RVA00080600. Do not repeat these unchanged trials.

Daily census9ac0d06c54 gave historical previews326+295+1695=2316 nonpadding
bytes for all3 consumers. These are NOT confirmed gains. No new census was
launched; current dependency-aware linking remains UNKNOWN. The existing
TreeFind Ascii comparator copy has unknown native placement and is unchanged.
Full family closure and banked-header acceptance remain pending normal gates
and independent parent publication review.

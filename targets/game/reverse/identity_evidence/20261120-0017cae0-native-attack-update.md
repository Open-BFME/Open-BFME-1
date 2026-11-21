# AIAttackState::update, native BFME1 0x0017CAE0

Private worker handoff, 2026-11-20. Parent owns claim lease
`16c454bc301c4acab31cea79c586176e`, production edits, acceptance and publication.
No claim, ledger, symbol pin, gate, Git or production source was changed by this
worker. No asm/emit, imported helper, new alias or compiler flag is proposed.

## Concrete landing patch

Base checked: `6cf1e056f8ee1851032fe882160ce76143b9ea15`.
Package text hashes use canonical UTF-8/LF; the production installation keeps
the original line endings on unchanged lines. The existing #line 297 is
unchanged; no diagnostic #line directive is introduced.
Apply `attack-AIStates.patch` to
`game/GameEngine/Source/GameLogic/AI/AIStates.cpp`. The final small append is
`attack-AIStates-append.cpp.txt`; full candidate is
`attack-AIStates-candidate.cpp.txt`. The patch retires the old unregistered ZH
`AIAttackState::update` in that file and places the real method in the SAME TU.
Its blank line preservation keeps all later native source coordinates stable;
the diagnostic harness's leading #line and rewritten private include paths are
not part of the production patch. The final append uses a proper relative
include, no absolute path. Existing compiler profile/includes stay unchanged.

Original ledger row: `?d_0017cae0@@YAXXZ`, RVA0x0017CAE0,1108B,
`game/gen_asm/d_00177320.asm`, `matched`, `gen-dump;ghidra=FUN_0057cae0`.
New original symbol: `?update@AIAttackState@@UAE?AW4StateReturnType@@XZ`.
Root should perform regular add_match --replace-existing/--replace-rva and
remove only the replaced MASM body after acceptance; the shared asm file has
other targets and must not be deleted wholesale. No additional helper tasks or
coverage are claimed here.

## Native identity, ABI and source provenance

The native brief identifies EA's WorldBuilder1 source home as
GameEngine/Source/GameLogic/AI/AIStates.cpp. Existing preferred bank and narrow
history establish ctor0x0017C910 -> vtable0x0109A0C8 and the matched onEnter
0x00184580 / onExit0x0017D050 family. Full extent is1108B. The old best bank was
1100B/433 positional differences; prior references, != wrappers and register
variants were read and were not reswept. `related-ai-briefs.log` and
`ai-resweep-after-173470.md` preserve the admission/source evidence.

Current native StateMachine_internalSetState.cpp independently fixes owner+10,
defaultStateID+18 and currentState+1C. Object's canonical native object.h fixes
model flags+110, contain+1FC, AI+204, containedBy+214, team+23C and private
status+344. Matched attack siblings/bank establish machine+1C, attackMachine+28,
locked-weapon four-byte string+40, attack-object flag+45, weapon flag+4C and
remaining state fields through+50. The patch asserts these layouts at compile
time. Shared ZH class layouts are untouched and are not used as B1 field layouts.

The source-backed native AIUpdate provider fixes last-command-source at virtual
slot128 and notifyVictimIsDead at129. The old bank's mood-matrix name was wrong;
the private view now uses CommandSourceType getLastCommandSource() const and
preserves the native bit2 test. The still-unproven slot136 keeps an opaque name.
NativeByteField now calls the actual current unsigned-byte get() provider at
0x001E1770 rather than the old wrong bool prototype. The Gen_0016A1B0 query is
properly nonconst, matching its17B current provider; no shim pin was added.
Relationship goes through the existing ObjectGetRelationshipShim body, exactly
as the existing regular ObjectGetRelationshipThunk.cpp does. Other calls use
existing real provider declarations or typed calls to the already recorded
thunks; caller and callee stack/ECX conventions remain intact.

Native OVERRIDE<ThingTemplate> and the visible recursive Overridable walk are
the same header context proven by the prior AIMove recovery45c5152dca. No BFME2
binary placement was used as native eligibility or matching proof.

## Comparison exception contract: complete independent native proof

The exact current provider is
`?compare@?$StringBase@D@@QBEHPBD@Z`,90B,0x000A2BB0,
export/ILT0x0004B01A, game/Libraries/Source/string/StringBase.cpp.
`attack-native-compare-provider.decode.log` decodes its ENTIRE90B extent. It has
no CALL, allocation, callback, C++ throw or user-defined operation. It reads the
optional C string in a byte loop, reads the native header's length/data, performs
inline repe cmpsb, subtracts lengths and RET4. Its only memory writes are the
ordinary saved-register stack. Under /EHsc, asynchronous access faults are not
C++ exceptions. Thus the explicit local specialization declaration
`template<> int StringBase<char>::compare(const char*) const throw();` states
this proved provider contract, without changing its mangling or implementation.
It is introduced only at EOF for the new native view, after existing ZH code.

Measured controlled steps:

- True OVERRIDE member + visible walker:1108B/15differences under the old
  /EHs-c- bank profile. Receiver-reference aliases alone remain1100B/433diffs.
- Correct original TU /EHsc without the comparison contract:1230B with EH frame.
- Original TU /EHsc plus ONLY this compare throw() declaration:1108B/4diffs.
  Cleanup-bit initialization naturally moves after getName/load/test as retail.
- Materialize defaultStateID into an unsigned value before virtual setState:
 1108B/0diffs. The const-reference accessor remains4diffs; value accessor/local
 are exact. No register/optimizer flags or fabricated assumptions are used.
- Proper original TU view must retain the getMachine accessor at shouldExit:
 a direct field expression is1B shorter; the genuine accessor restores the
 native argument/receiver reload order and1108B exactly.

## Fresh verification and footprint

Native MSVC7.1 13.10.3077, original AIStates flags /O2 /MD /EHsc and STLport
context. Explicit private objects only, no shared match cache. Primary in the
FULL TU:1108/1108B,37relocations, strict_equal=true, masked=false, unresolved=[].

All104 existing ordinary rows are freshly strict/exact/unmasked with no
unresolved symbols in BOTH control and candidate objects; all existing row
bytes/relocation graphs and all retained same-size code definitions are
unchanged. `attack-whole-provider-proof.json` preserves each result. The only
removed COMDATs are old unregistered ZH update's getMaxShotCount and getStatusBits;
no existing registered provider is removed.

The final footprint has14 small view-method COMDATs plus4 canonical StringBase
COMDATs. EVERY one of those18 definitions was natively compared under its own
emitted symbol against a current matched/evidenced body or actual5B ILT;
all18 strict/unmasked, unresolved=[]. `attack-helper-proof.json` includes each
own symbol, native RVA, current provider row and resolved relocation graph.
Those are diagnostic comparisons, not proposed new aliases or ledger rows.
Three redundant old thunk wrappers were replaced by static forceinline free
helpers / the actual byte getter while preserving the exact main body. No
dllimport trick was tried or introduced; ordinary forceinline/anonymous
namespace controls were neutral and were reverted.

Owned new data are GondorTrebuchet16B and StringBase<char>::TheNullChr1B. Each
DIR32 consumer site's native address and the actual emitted data bytes are
checked in `attack-data-proof.json`, so a matching DIR32 mask alone is not the
data evidence. All owned data bytes equal their retail targets.

Root still must do normal production add_match,105-row build/gates,
find_declared_unmatched, provider/consumer checks and publication. This private
proof is not linked-byte, whole-image link or runtime/gameplay/crash proof.

## Reproduction (private, repository cwd)

Source environment: W:/OpenBFME/diagnostics/continue-20261107-0212/environment.ps1.
Python: W:/OpenBFME/.tools/python/Scripts/python3.exe. BUILD_POOL=4 maximum.
Scripts in this directory, in order:

1. attack-ai-states-integration.py -- fresh control/candidate proper-TU builds,
   primary strict and all104 row bytes/relocations.
2. attack-whole-proof.py -- all104 rows independently strict in both objects,
   precise new/removed/changed code footprint.
3. attack-helper-proof.py -- all18 emitted helper names strict against current
   recorded native providers, no masking/aliases/pins.
4. attack-package.py -- production-relative unified patch, independent DIR32
   data proof and SHA256 manifest.

`shape-lever-17cae0.md.txt` is ready for a concise docs/shape_levers.md addition.

## Name-check false pairing (exact production snapshots)

The deleted bank declares `struct Coord3D { float x,y,z; };` at line18.
Its `y` is a coordinate member; production uses the existing shared Coord3D
header instead of copying that structure. The same deleted bank already
declares `BfmeUnit1001::bfmeReady1001()` at line76 and calls it at line116.
Production preserves that declaration and call in the recovered update.
The unchanged pin `?bfmeReady1001@BfmeUnit1001@@QAEDXZ` at0x000331C7
independently identifies the callee; no name or pin was invented here.
The token-alignment report pairing coordinate `y` with `bfmeReady1001` is
therefore not a rename. The exact before/after snapshot correction records
only this pair, following docs/naming_evidence.md.

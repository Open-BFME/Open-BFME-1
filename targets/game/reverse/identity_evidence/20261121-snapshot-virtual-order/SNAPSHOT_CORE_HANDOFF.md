# Existing Snapshot header: one private declaration-order correction

**Certain, scoped result:**99/99 private sources compile before and after;
1126/1126 existing row checks are exact, unmasked and have no unresolved calls
in both phases. No new body/bytes are claimed. The actual four-slot Snapshot
CodeView order changes from destructor/name/load/transfer to the independently
retail-proven destructor/load/name/transfer order. Root still owns normal
admission, complete header gate, independent review, claims and publication.

## Exact review artifact

`snapshot-order-only-CANDIDATE.patch`, SHA256:

    d4d2d3df1ec0622c8254c9c05b0566e83f4da2988cff785aacfbbee9edc259fb

It changes only `game/GameEngine/Source/Common/System/snapshot.h`: moves the
existing LoadPostProcess declaration before the existing GetSnapshotName
declaration. No method name, return/parameter type, constructor/destructor
default, access, macro, guard or compatibility API changes. Production header
SHA256 at capture96299e295f364de1695ccb59693fbb47f2d975c534b04e8085c0d0715c1b891d;
candidate header37b054017a8321b5151f8a332fd6faa12be7e28de832bddf93e883b1b4bbdd1e.

This is a separate Core prerequisite. It does not adopt the incompatible
game/Common/Module.h hierarchy, close Behavior's41-slot interface or reconstruct
Foundation002BB170/1261. No CRC-as-name compatibility slot or generic callback
types were introduced.

## Original authority

`SHARED_CONTRACT_PROOF.json` freezes the real B1 parent tables and constructor
bodies. Snapshot01073744 has the deleting destructor and three pure slots.
The real Snapshot constructors/dtor and ObjectModule cleanup all install that
same parent table.17 export-bound B1 families independently name LoadPostProcess,
GetSnapshotName and DoXfer with the real types;78 original derived tables carry
all three named targets at1,2,3. GetSnapshotName returns const char* and is a
non-const member. DoXfer takes Xfer&. The verified Xfer::operator==(Snapshot&)
009D6410/19 dispatches through slot3.

The existing System/snapshot.h already had those types/names, but had name/load
in the reverse order. The actual authored B2 Moduleâ†’Snapshot repair at official
1e864b34e05f68568db539537b6959d94d104f57 was a useful discovery lead; the patch
is grounded in B1 retail, not an unchanged B2 header copy.

## Private context and controls

The native-current receipt cohort has76 sources using precisely this System
header,22 different game-header control sources, and the existing657B Foundation
source:99 total, **76 affected users+23 controls** (22 game-header users and
the one Foundation incumbent). Exact lists are `snapshot-core-sources99.txt` and
`snapshot-core-native-scopes.json`. This is not all1871 conservative candidates;
151 previously unknown/stale candidates remain outside the probe. No99-source
pass substitutes for the full header gate.

Native flags/retry include contexts were computed from the original live sources
and their current native receipts. The sources and162 non-input dependency files
were copied into a private path-preserving mirror;328 external/inputs files were
hashed and read unchanged. Only private output paths and ordinary include tracing
were added. All76 real header users resolve this exact private header, including
native traces which print a cwd-relative path. The full-path-only diagnostic
predicate was corrected from the already recorded traces; no recompile or source
change was needed for that correction.

Private compiler outputs live under
`build/agent-melee-20261120/foundation-shared-core-20261121/objects/`.
The compiler cwd is the private mirror. BFME_OBJSTORE=off,max4 compiler workers.
One candidate header form was used. A first control run hit a private footprint
parser's COFF.bss payload=None case; the parser was corrected to preserve its
zero-init extent and the identical control was repeated. This was not a second
header/codegen hypothesis.

`snapshot-core-inputs.json` freezes the inputs, original commands and receipts.
Production inputs, external dependencies, functions.csv and symbols.csv remained
byte-identical across the completed probe. A separate Xfer source+Z7 witness in
each phase proves Snapshot's slot order, and its entire runtime footprint equals
the corresponding normal object. The CodeView display flattens Xfer& to Xfer*;
the unchanged source and original mangling retain the reference contract.

## Results and full-footprint boundary

* 99/99 normal-profile compiles in each phase;1126/1126 row checks strict and exact.
* The657-byte Foundation incumbent is retained exact; target1261 was not compiled.
* All99 code/definitions/undefined-provider/COMDAT-association footprints unchanged.
* 84 whole runtime graphs identical.15 sources change41 four-slot vtables only.
* Each of those41 changes is exactly the relocation targets at offsets4/8 exchanged.
  Raw data,flags,size,destructor slot0 and transfer slot3 are unchanged.
* Native string checks in both phases:239 literals+18 empty-string refs,0 skipped.
* Correctly closed native DIR32 consistency context in both phases:
 689 symbols,7 existing whitelisted cases,0 new; same propose=False call.

`snapshot-core-final-receipt.json` is the current result summary.
`snapshot-core-probe.json` preserves the original compile/row/footprint results;
its initial DIR32 diagnostic is superseded by the exact context receipt below.

## The30 historical private DIR32 messages were a context error

They are **not30 production/master failures**. The compiler cwd override meant a
late native body_guard import captured the mirror as its ROOT. The mirror lacked
the unchanged native body_guard_baseline.csv input; all30 reported pairs are
already present in that exact real native baseline. This was an incomplete
private verifier context, not evidence requiring a name/pin/baseline repair.

The existing baseline was copied byte-for-byte into the same private relative
location. Original and copy SHA256:

    31a6829e788dc1302fa1fce2fdece8db66cd02e4968505bc695cfec56b48db12

Then only the identical native call
`build.verify_dir32_consistency(rows, propose=False)` was replayed on the existing
before/candidate objects. Both passed689/7/0. No compiler, source variant,
prototype, pin, whitelist, skip or production-baseline change accompanied that
replay. `snapshot-core-complete-guard-context.json` records the actual imported
native baseline path and hashes. Historical30-name diagnostics and all their
source references remain in `core-before-dir32-unowned.txt`,
`core-candidate-dir32-unowned.txt` and the incomplete-context analysis.

Root separately ran the unchanged99 production sources in9 regular build.cmd
batches, all exit0. I verified its result's exact source set matches the private
99. Root artifacts:
`R/bfme1/snapshot-native-baseline-result.json` and01..09.log.
These are regular **unchanged-production scoped** checks, not a candidate full
header gate. No full gate was started or duplicated by this worker.

## Original41-table comparison and retained provider limits

`snapshot-core-vtable-original-details.json` contains every changed table in all
15 sources, exact original table words, current matched-code address bindings,
current row identities, getter bytes/literals and before/after slot names.
The consistent classification is **31 full current name/address anchors+8 native
role witnesses+1 preexisting provider mismatch+1 unanchored table=41** across
15 objects. The eight role witnesses are Drawable2,InGameUI2,LightningDraw1,
Particle1,Object1 and W3DRenderObjectSnapshot1. LightningDraw's additional
abstract-table binding is retained as a preexisting limit. No claim that every
compiled table is retail-correct follows from the universal API-order correction.
The remaining cases are explicit, not admitted by shape:

* Drawable ctor/dtor: original010F154C slots1/2 are lower-case named loadPostProcess
 and an opaque6B getter returning `Drawable`. Current external capitalized names
 lack corresponding normal-map identities; role/literal evidence is available.
* InGameUI ctor/dtor: original010F5B24 has a one-byte slot1 and opaque6B getter
 returning `InGameUI`; same missing-name binding boundary.
* Particle,Object and W3DRenderObjectSnapshot: native slot1 load roles and slot2
 literal getters are recorded, but current typed external spelling is not fully
 bound. Particle's actual literal is `FXParticle`, preserving that type boundary.
* LightningDraw's real01110D38 table supports the new slot pair. Its existing
 compiler symbol also references abstract Snapshot01073744 through an old
 multiple-address artifact. Header reordering does not resolve that artifact.
* T1Base_005FDE80 binds original011130E0, whose slot2 literal is
 `DefaultModule<CAT_PHYSICS>`. Its source vtable references DefaultPhysicsModuleInfo
 methods. That provider-identity mismatch already existed and is **not repaired**
 by this header change.
* The bulk LightningEmissionModuleTemplate vtable has no direct code/address
 anchor in this99-source cohort. Its new role pair occurs in original tables,
 but that is not a unique class/provider identity proof.

Do not turn those limits into new pins, invented aliases or prototype changes.
No complete selected-provider link proof or startup/runtime improvement is
claimed. Root's independent review and normal candidate full gate decide whether
the narrowly correct Core order can be accepted with the remaining existing
context recorded, or needs a separately authorized prerequisite.

## Normal/root commands and reproduction

Root has already executed regular unchanged-production `.\\build.cmd <paths>`
for the9 batches in snapshot-native-baseline-result.json. Exact99-source lists,
14 sources involved in the historical private30-name diagnostic, and safe
argument-length batches are in snapshot-core-native-scopes.json. Do not label a
replay of only verify_dir32_consistency a complete build.cmd/full-gate run.

The private reproducible experiment is probe_snapshot_core.py. Its final version
includes the unchanged native baseline input at preparation time; it keeps the
same one order-only header candidate, explicit outputs and max4 workers.
verify_snapshot_guard_context.py reproduces only the no-compile metadata-context
replay. Do not rerun a full production gate concurrently with Root.

Foundation's exact source/algorithm bank remains unchanged. Its real primary
chain now has substantially better proof, but the41-slot Behavior ABI, ModuleData
and legacy macro API reconciliation remain open. This Core proposal receives
**0 new body /0 C++ byte credit**.

## Historical30-name diagnostic appendix (private context only)

Every pair below is in the unchanged current native body-guard baseline. These are not30 newly discovered production faults. The source references explain the incomplete-context report; the completed native guard and Root normal baseline pass.

* `0x00426A8A ??0List00442C90@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`.

* `0x0042254D ??0Map0044B780@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`.

* `0x0042AA81 ??0Message0043DBA0@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`.

* `0x004392AC ??1?$vector@PAVUpdateModule@@V?$allocator@PAVUpdateModule@@@_STL@@@_STL@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameLogic/System/GameLogicConstructor.cpp`.

* `0x00418949 ??1List00442C90@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x00438BBD ??1Map0044B780@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x004376AA ??1Message0043DBA0@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x0044454E ??1MoveHint0043AAD0@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x00423B41 ??1RadiusDecalTemplate@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x0042A8E2 ??1Rva00386070@@QAE@XZ`

  Sources: `game/GameEngine/Source/GameLogic/System/GameLogicConstructor.cpp`.

* `0x010F1560 ??_7Drawable@@6BGen_dtor_00132940@@@`

  Sources: `game/GameEngine/Source/GameClient/DrawableDestructor.cpp`.

* `0x010F154C ??_7Drawable@@6BSnapshot@@@`

  Sources: `game/GameEngine/Source/GameClient/DrawableConstructor.cpp`, `game/GameEngine/Source/GameClient/DrawableDestructor.cpp`.

* `0x010F1560 ??_7Drawable@@6BThing@@@`

  Sources: `game/GameEngine/Source/GameClient/DrawableConstructor.cpp`.

* `0x010EB560 ??_7GameLogic@@6BSnapshot@@@`

  Sources: `game/GameEngine/Source/GameLogic/System/GameLogicConstructor.cpp`, `game/GameEngine/Source/GameLogic/System/GameLogicDestructorThunk.cpp`.

* `0x010EA21C ??_7Gen_00378650@@6BSnapshot@@@`

  Sources: `game/GameEngine/Source/Common/Bfme5VectorMemberDtors.cpp`.

* `0x010EA230 ??_7Gen_00378650@@6BSubsystemInterface@@@`

  Sources: `game/GameEngine/Source/Common/Bfme5VectorMemberDtors.cpp`.

* `0x010F5B24 ??_7InGameUI@@6BSnapshot@@@`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x010F5B38 ??_7InGameUI@@6BSubsystemInterface@@@`

  Sources: `game/GameEngine/Source/GameClient/InGameUIConstructor.cpp`, `game/GameEngine/Source/GameClient/InGameUIDestructorThunk.cpp`.

* `0x0109EDD0 ??_7Object@@6BRva00C9EDD0Base@@@`

  Sources: `game/GameEngine/Source/GameLogic/Object/ObjectDestructor.cpp`.

* `0x0109EE00 ??_7Object@@6BRva00C9EE00Base@@@`

  Sources: `game/GameEngine/Source/GameLogic/Object/ObjectDestructor.cpp`.

* `0x0109EE28 ??_7Object@@6BRva00C9EE28Base@@@`

  Sources: `game/GameEngine/Source/GameLogic/Object/ObjectDestructor.cpp`.

* `0x0109EE44 ??_7Object@@6BSnapshot@@@`

  Sources: `game/GameEngine/Source/GameLogic/Object/ObjectDestructor.cpp`.

* `0x0109EE58 ??_7Object@@6BThing@@@`

  Sources: `game/GameEngine/Source/GameLogic/Object/ObjectDestructor.cpp`.

* `0x0107388B ?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB`

  Sources: `game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp`, `game/GameEngine/Source/GameLogic/Map/TerrainLogicEnableWaterGrid.cpp`, `game/GameEngine/Source/GameLogic/Object/Update/LaserUpdateClientUpdate.cpp`, `game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectDoXfer.cpp`.

* `0x012F1270 ?display00487F80@@3PAVDisplay00487F80@@A`

  Sources: `game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp`.

* `0x010AF400 ?g_010AF400@FXParticleSystem@@3QBDB`

  Sources: `game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp`.

* `0x01110500 ?g_01110500@FXParticleSystem@@3QBUModuleCategoryEntry@1@B`

  Sources: `game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system.cpp`.

* `0x01073758 ?g_vtbl_01073758@@3PAPAXA`

  Sources: `game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp`.

* `0x011122AC ?g_vtbl_011122AC@@3PAPAXA`

  Sources: `game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp`.

* `0x012B5AB0 ?gameWindowFieldList@@3PAUGameWindowParse@@A`

  Sources: `game/GameEngine/Source/GameClient/GUI/GameWindowManagerScriptParseWindow.cpp`.


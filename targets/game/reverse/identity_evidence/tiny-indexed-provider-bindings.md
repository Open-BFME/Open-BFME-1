# Tiny indexed forwarders: five native bindings, 92 sites

## Scope and existing identities

Only `game/GameEngine/Source/Common/TinyIndexedForwarders.cpp` changes. It has
**108 actual matched rows**, including 94 legacy constant-forwarding roots,
three already-correct const sound getters and scalar siblings. The old comment's
88 dominant calls was stale: the actual legacy source/native inventory is
**87** sound roots, two indexed-audio roots and five other singleton families.
This patch corrects that count, not any ledger identity.

All original root/base declarations and hierarchy/storage remain unchanged;
those opaque types are ABI views, not new original-EA inheritance assertions.
The existing macro now receives a call expression so differently typed native
interfaces can be used without forwarding helpers or aliases. Exactly five
old undefined provider names change across these 92 complete 8 B roots:

| Legacy family / count | Existing native member | Original ILT | Complete native provider |
| --- | --- | --- | --- |
| `Gen0001BFD1`, 87 | `ThingTemplate::getSound(int) const` | `0001BFD1` | `00416FA0`, 22 B |
| `Gen0003415D`, 1 | `LargeGroupBonusUpdate::notify(int)` | `0003415D` | `00297820`, 89 B |
| `Gen000398C9`, 1 | `SimpleObjectIterator::firstWithNumeric(float*)` | `000398C9` | `001DE040`, 51 B |
| `Gen00044A62`, 2 | `IndexedAudioEvent006B0210::select(int)` | `00044A62` | `006B0210`, 383 B |
| `Gen0003D172`, 1 | protected `W3DVolumetricShadow::Update(bool)` | `0003D172` | `007BF7D0`, 758 B |

`Gen00038951`'s original already-bound root and the enum-returning
`Gen00039BD5` family remain unchanged. The latter is intentionally NOT repaired
in this batch; its dependency failure is preserved below. No new matched bytes,
root names or original-EA identity claim is made. Other scalar/const-getter
siblings are verified unchanged, not counted as additional repaired sites.

## Header and access boundaries

The TU already contained a declaration-only BFME `ThingTemplate::getSound`
view for its three const getters. It is moved earlier and reused: inspected
sweep/Zero Hour `Common/ThingTemplate.h` has `getAudio`, not this existing BFME
`getSound`/`getPerUnitFx` API. No layout or inline header implementation is
copied. Other new public views declare existing native members only and are
used through pointers; no object size, fields, inheritance or lifetime model
is imported.

**SimpleObjectIterator is a different case.** The real Zero Hour
`GameLogic/ObjectIter.h` DOES have the compatible public
`Object *firstWithNumeric(Real*)`, inline as `reset(); nextWithNumeric(num)`.
The existing matched provider TU includes that real header. The supervisor
specifically permitted a signature-only view here to retain the native 8 B
out-of-line call boundary to the existing complete 51 B provider, without
copying its layout/inline body or importing a broader dependency/definition
context. This is not an API-absence/incompatibility claim. The exact Object*
return and float* NULL argument are preserved, not replaced by int types.

Fresh narrow access permission applies ONLY to `Rva007C0510::go`, with original
literal word 1 and ILT `3D172 -> 7BF7D0`. The native provider's actual declaration
is protected `void Update(Bool)` with Bool=bool, existing COFF spelling
`?Update@W3DVolumetricShadow@@IAEX_N@Z`. The source retains that protected
declaration, takes the exact external COFF reference and uses one fully
initialized local code/member-pointer union. Explicit four-byte checks cover
code pointer, member pointer and union. The native unadjusted receiver and
Bool true literal are unchanged. No access widening, new hierarchy, helper,
alias/pin, provider/header rewrite or generalized bridge is authorized.

## Full native route, stack and result proof

`callees.py` was run on EVERY complete 8 B consumer row before editing, including
the protected site. All 108 consumer rows are strictly byte-identical with zero
masking and unresolved relocations. Each legacy root is exactly:
`push IMM8; call REL32; ret`. At all 92 changed sites the original literal and
ILT remain exact; no instruction sets, adjusts or saves ECX. The native method
therefore receives the original receiver, and the one pushed word is at native
entryESP+4. All original scalar sound indices and both audio indices 0/1 remain.
The iterator's `Rva001DE030` root pushes full word 0 (NULL), while protected
`Rva007C0510` pushes full word 1 (true).

Each full provider is independently strict/unmasked with complete decoding.
All normal exits are RET4: one each for 22/89/51/383 B providers, two for the
758 B shadow provider. The unused enum family's actual complete 897 B
`stateReturn` body is also strict/RET4, but is NOT selected by a new binding.

**Result behavior is physical, not guessed from void roots.** The native sound
and iterator interfaces return their original pointer in EAX. The complete
8 B roots contain no return conversion, clearing, copy or post-call instruction
other than RET, so EAX passes through exactly as before even where the inherited
opaque C++ root declaration is void. This does not rename/retype that root or
infer its original EA signature. Existing const sound getters are likewise
unchanged. No hidden return buffer or by-value lifetime is introduced.

## Whole-object footprint and selection metadata

The complete actual before/current COFF inventories match by exact public
definition and associated-owner identity after ONLY the five intended external
callee substitutions:

- **218 sections**: 109 non-debug and 109 debug, every raw code/data/directive
  byte, relocation and section characteristic.
- All **218 complete section auxiliary records**, including COMDAT selection,
  checksum, length/counts, association identities and reserved/high fields.
- All **108 public definitions**, types/storage/relative offsets and scalar
  siblings. Five old undefined names disappear and four new ones appear:
  `getSound` was ALREADY an undefined reference from the const getter siblings.
- No extra helper/body/data/weak external/alias, changed cleanup or additional
  method copy. Physical section numbering/order is normalized by owner, not
  claimed ordinal-identical. Selection METADATA/eligibility is preserved;
  actual current-link winners and whole-image layout remain unverified.

Normalized all-section inventory SHA256:
`8cd1f2b35e74821fb3fcd210f9b32ff83d72e4d249194b35f96652901d41af25`.
The normal retail byte gates remain unchanged and independently pass.

## Omitted enum-return family: concrete handoff

`Rva001840D0` still calls its original `Gen00039BD5::handle(int)` spelling with
literal 0. The actual provider is the complete 897 B
`Gen00039BD5::stateReturn(bool) -> StateReturnType`, `0017BA90`, reached through
ILT `00039BD5`. No duplicate/invented enum, int-return substitute, extra raw ABI
bridge or header/provider edit is used to force that binding.

The supervisor permitted canonical StateReturnType only through its real
existing definition/dependency context IF the same whole-object footprint
could be retained. Two isolated compiler controls use explicit private output:

1. Including real `Common/StateMachine.h` with its mapped include directories
   under the original native-STL context fails in std::list/xhash declarations.
   This is a dependency-context failure, not evidence about the native body.
2. The actual STLport dependency context compiles, and its include receipt
   records the real headers, but public definitions grow **108 -> 646**:
   **538 extra public data definitions** (numeric limits/ios/string statics).
   This fails the explicit footprint admission contract before any enum-family
   production binding is attempted. Existing 108 definitions are all retained.

The family is therefore omitted unchanged under the approved contract. A class/
header reconciliation owner can revisit the real dependency boundary; do not
repeat this unchanged include control, invent an enum or generalize the shadow
bridge. Diagnostic sources/logs/objects/dependency receipts and the complete
538-definition delta are retained as `indexed-enum-*` under the private build
path; `indexed-enum-footprint-failure.json` gives the exact set. No production
include/flags are changed. This tracked note is the handoff for that prerequisite.

## Reference-source pass

Read-only BFME 2 `76f0baefa6f285d54bc1ca922397674312a5913f` reviewed:
`Code/GameEngine/Source/Common/CallForwarders8B.cpp`, relevant
`GameLogic/Object/Update/LargeGroupBonusUpdate.cpp::notify`, and
`GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowUpdate.cpp`.
The donor supports only general constant-forwarder/control-flow leads. Its
receiver layout, addresses and shadow fields are NOT transferred. Its notify
notes explicitly derive the purpose from BFME 1, not independent BFME 1 proof.
Native BFME 1 full bodies/ILTs and existing identity evidence establish this
repair. No donor tree, gitlink, compiler or build-input change is made.

## Normal checks and current limits

Normal before/after full consumer + actual six provider TUs: **124/124 functions
across seven TUs**, 35 DIR32 references, 10 float constants, 1 literal. The body
guard's existing ten static skips are unchanged, not newly exempted. All 108
consumer rows and all six complete protocol providers have additional strict,
unmasked diagnostics. `find_declared_unmatched.py` reports all definitions
matched. Builds retain the original consumer compiler context and approved
private WoW64 Wine prefix, WINEARCH=win64, BUILD_POOL=2, WINEDEBUG=-all, empty
desktop displays. Only the failed PRIVATE canonical-header control uses its
necessary STLport include context; no such flags reach production.

Scoped preview before **0/7 clean**, 242.9 s; after **0/7 clean**, 243.9 s.
Both have 4 UNKNOWN / 3 independent-debt verdicts; all seven selection sets are
stale and 22,750 cold/changed ledger objects cannot be read. Historical LINKED
**1,403 -> 1,403** is unchanged, NOT current confirmed coverage. Exactly five
old handle diagnostics disappear; all duplicate/COMDAT/other selected debt is
unchanged and no new diagnostic appears. Enum-family debt remains. No current
linked-byte gain, newly matched bytes or closure is claimed.

Private evidence `build/sol12h-bindings/`: `indexed-{before-build,after-build,link-before,link-after,routes,footprint}.log`,
`indexed-{callees,donor-search,link-delta}.txt`, `indexed-footprint.json`,
`indexed-before.{cpp,obj}`, `indexed-enum-*`, `indexed-sources.txt`, claim log,
`repair_indexed_bindings.py`, `check_indexed_routes.py`, `check_indexed_footprint.py`.

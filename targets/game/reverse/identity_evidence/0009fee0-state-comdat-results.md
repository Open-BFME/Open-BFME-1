# AI/State COMDAT family repair: linked coverage evidence

This investigation compares fixed game inputs from 4d92da13a1 (baseline
recorded at 4e2915d862) with the isolated final repair tree e730466093. The intermediate tree
4094737c79 is retained to expose and account for the vtable regression. Later
upstream changes are excluded from this measurement. The publication tree
is separately rebased and gated against current master.

## Proven causes and repairs

- `?getCurrentStateID@AIUpdateInterface@@QBEIXZ`: two ZH-derived header
  variants emitted interface+0x2c / State+8 loads under the BFME name.
  Declaration-only methods keep the established 000C3D90 owner, whose
  20-byte body reads interface+0x30 / machine+0x1c / State+4. Seven cleanup
  symbols were repinned using retail FuncInfo states after emission changed.
- `?getID@State@@QBEIXZ` and
  `?getMachine@State@@QAEPAVStateMachine@@XZ`: false old identities at
  00106670 and 00232180 reinforced the ZH +8/+0x20 layout. Independent
  constructor/layout evidence plus exact-name ILT evidence establishes the
  real getters at 0009FEF0 (+4) and 0009FEE0 (+0x1c). Preserve the old
  four-byte bodies under opaque address-derived identities. Correct only
  accessor offsets in three header variants; preserve their other layouts.
- The State accessor repair also corrects the eight wrong emitters of
  `?getCurrentStateID@StateMachine@@QBEIXZ` (0009FF60, 17 bytes).
- The COMDAT report now vetoes provider recommendations for contradicted
  identities. It does not rename anything or relax verification. Published
  separately as 444da23dc1; 34 focused tests pass.
- The exact existing data-ledger owner at 01075350 now takes precedence over
  historical spellings in the DIR32 guard; a known data owner at another
  address remains rejected. No aliases, new pins, ledger reordering or
  baseline additions were used.

## Verification

Original AI gate: 3,331/3,331 matched rows in 98 TUs. State gate:
3,403/3,403 in 109 TUs. Current-master integration gate: 3,404/3,404 in
110 TUs, 311 literals plus 15 empty strings, 189 float constants and three
readonly loads, 2,294 DIR32 references, and body guard all pass.
Pin consistency and name-regression checks pass with two documented identity
corrections. The data-address/record/ownership tests pass 111 cases (one
skipped); operator-correction tests pass 17 separately. Three combined-order
failures also reproduce on pristine base and are not caused by this repair.

Complete baseline emitter and undefined-consumer lists are recorded in the
adjacent measurement JSON. Defining TUs may consume their own emitted helpers.

## Final-link follow-up

The intermediate census confirmed 1,042 bytes in the three intended TUs,
but also exposed a 474-byte regression across 13 State-vtable consumers.
After getter ownership accounting, its actual net was only +564 bytes.
The earlier object position of TurretAI selected its wrong 12-slot State
vtable. Marking that partial State view `novtable` suppresses the emission;
no ledger ordering was changed. Two redundant, non-retail definitions of
the TurretAI constructor and AITNGuardIdleState::onEnter were also removed.
An explicit address-taking anchor preserves the existing matched placement
delete, and six cleanup symbols were rebound through retail FuncInfo states.
The follow-up passed 60/60 rows across four directly affected TUs and the
full 3,403-row, 109-TU header-dependent gate.

The separate AIAttackFireWeaponState vtable still requires a proven BFME
17-slot view. Its vptr store is inlined in a matched constructor, so it was
not suppressed or assigned guessed virtual identities. It caused no extra
previously-linked source loss in the intermediate measurement.

## Measured linking

Both final links passed (995s plain, 977s /MAP), all 1,787 data rows
passed, and the accepted census contains 22,895 objects with none missing.

| Revision | Authored LINKED | Total LINKED | Linked sources |
| --- | ---: | ---: | ---: |
| Baseline 4e2915d862 | 2,567,897 | 2,824,342 | 14,768 |
| Intermediate 4094737c79 | 2,568,461 | 2,824,906 | 14,759 |
| Final e730466093 | 2,568,935 | 2,825,380 | 14,772 |

The final net gain is **1,038 authored linked bytes**. Three existing TUs
change from blocked to LINKS: ActionManagerCanEnterObject (847 bytes),
AIUpdateInterfaceGetCurrentStateID (20), and GiantBirdGuardInnerState_update
(175). The old tiny-body TU loses eight bytes to correct identity ownership,
and the new opaque getter TU contributes four linked bytes: 1,042 - 8 + 4.
No previously linked source becomes unlinked. All 13 intermediate State
regressions recover their 474 bytes. Game-code coverage is unchanged.

All four getter families have zero remaining duplicate, COMDAT-loser or
wrong-selected charges. State vtable charges and the two redundant method
families also disappear. The only new wrong-selected name versus baseline
is AIAttackFireWeaponState's vtable, affecting six already-blocked sources;
it causes no newly unlinked source. Global selected-name classification
changes from 5,644 wrong / 5,032 unproven / 118,802 proven to
5,643 wrong / 5,030 unproven / 118,803 proven. Partial State tables remain
unproven; this measurement does not claim to reconstruct their full layout.

The stale current-object preview was UNKNOWN and is not used for these
gains. Four additional derived-vtable preview warnings had unchanged
section digests and do not survive as source regressions in the accepted
census. The current-master publication preflight also passes: 3,403/3,403
rows across 109 header dependents, all relocation/body checks, and 86
outgoing verification selectors.

The adjacent [measurement JSON](0009fee0-state-comdat-measurement.json)
contains the accepted before/after accounting, all eight families' complete
COFF definer and undefined-consumer inventories, getter bytes/selection
checks, blocker deltas, and final artifact hashes. Defining TUs can also
consume their own definitions. The inventories scan every census object
and validate reference-cache object hashes. The measured revisions remain
fixed; publication is rebased separately, so unrelated upstream changes are
not counted as this repair's gain.

## Remaining leads

- PlayerInfo copy constructor: 58,549 affected bytes / 13 consumers in the
  fresh baseline, with 1,250 conditional sole-family bytes. Retail owns
  three strings and ten dwords (52 bytes); ZH/peerdefs own only two strings.
  A string-only header swap or declaration-only copy constructor is unsafe.
- `setDesiredSpeed`: retail writes +0x44; ZH emitter writes +0x38. Six
  independent opaque retail matches currently reuse the latter emitter and
  need honest separate ownership before suppressing it. Fresh scope:
  6,803 affected / 156 conditional bytes / seven consumers.
- `getParentCell@PathfindCell`: shared header uses parent->cell+0x0c;
  three BFME private views use +0x28. Fresh scope: 1,450 affected / 1,175
  conditional bytes. No proven out-of-line retail home yet.
- `getCell@Pathfinder`: the claimed 003D4E80 identity is contradicted;
  establish ownership before aligning its differing emitters.

Scope/conditional counts overlap and are not claimed linked improvements.

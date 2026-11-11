# Pathfinder::classifyMap native provider bindings

Consumer: game/GameEngine/Source/GameLogic/AI/PathfinderClassifyMap.cpp,
existing complete366B row003F9140. Two obsolete caller declarations change to
existing provider names. Caller identity, fields, geometry, object storage,
providers, headers, ledger rows, pins, aliases and baselines remain unchanged.

## Native contracts and unchanged roots

| Old declaration | Existing provider | Original route | Native ABI |
| --- | --- | --- | --- |
| PathfindCell::setType(CellType) | Gen_003F68B0::bfmeSetMode(unsigned int) | ILT00017E27 ->003F68B0 | thiscall, one word, RET4 |
| BfmePathfindZoneManager::bfmeRebuildZones(void*,BfmePathfindLayer44*,BfmePathfindExtent*) | PathfindZoneManager::calculateZones(PathfindCell**,PathfindLayer[],const IRegion2D&) | ILT00020A13 ->00408F80 | thiscall, three pointer words, RET12 |

The49B mode provider remains in Common/Bfme5Seventy.cpp. Its opaque Gen name
is not promoted to a new EA identity. The complete target reads owner+0 and
mode bits at+C, preserves the other bits, and handles its existing owner
condition. The caller still passes the literal CELL_CLIFF=2, now through the
existing unsigned API; this conversion does not alter its32-bit argument.

The92B zone provider remains in AI/PathfindZoneManagerCalculateZones.cpp.
It retains its existing state/counter/vector clear and incremental loop.
MSVC's array-parameter QAV spelling is preserved by declaring PathfindLayer
layers[], not inventing a different pointer or by-value ABI. The map, layers
and bounds addresses are unchanged; the bounds reference binds the same
original memory, with no copy or construction.

The consumer keeps its existing BfmePathfindZoneManager storage view and every
Pathfinder/PathfindCell/BfmePathfindLayer44/BfmePathfindExtent field unchanged.
Only the existing manager member's address is passed through a method-only
native view. No native size/layout is asserted or imported. The complete
caller retains map+10, bounds+14, layers+85C and manager+C9C roots. The mode
receiver remains the same cell address; neither view introduces inheritance
or an ECX adjustment. No object is allocated, copied or destroyed by the edit.

## Why the existing Zero Hour header is not adopted

inputs/reference/shims/sweep/GameLogic/AIPathfind.h is explicitly a Zero Hour
layout override removing four bad inline copies, NOT a canonical BFME1
Pathfinder/manager layout. Its own lines922-925 document that the BFME map+10,
bounds+14 and layers+85C layout is absent and that retail-true pathfinder TUs
restate it. Its PathfindZoneManager begins with two pointers, unlike this
native BFME1 provider's state bytes/counter and vector near+2360C. Adopting
that header would change this caller's evidenced fields and is inapplicable.
No new shared header or provider reconciliation is attempted. The new method
views use existing names and only declarations; all existing storage stays
under its old view rather than pretending the method-only native view is a
complete embedded native object.

## Byte and definition-footprint checks

The verified original source/object were archived before editing. External
definition sets are IDENTICAL before/after; exactly the two obsolete undefined
spellings are replaced by the existing native names. No new outlined helper,
constructor, RTTI root or COMDAT is emitted.

The complete366B caller is strict/unmasked exact with no unresolved patch
references. Changed REL32 operands are+131(mode) and+162(zones), keeping the
routes in the table. The check follows both physical5B E9 thunks and verifies
both complete providers strict/unmasked:49B, two RET4 paths;92B, one RET12.
Existing classifyMapCell and prepare-refresh calls are unchanged.

Normal before gate1/1; consumer plus both provider TUs5/5functions, no literals,
constants or DIR32 roots, zero body-guard findings. Reproduce with the normal
three-source build, then
`python3 build/sol12h-bindings/check_pathfinder_classify_routes.py`.
Lane-private source/object/callee/gate/route/actual-preview artifacts use the
build/sol12h-bindings/pathfinder-classify-* prefix. Diagnostic objects are not
substituted for verified build receipts.

## Donor review and limits

Read-only BFME2 pin76f0baefa6f285d54bc1ca922397674312a5913f was reviewed at
Code/GameEngine/Include/GameLogic/AIPathfind.h and corresponding AI source.
Its target-evidenced layers are+60 with40hex stride and manager+460, unlike
this BFME1 caller's+85C/44hex/C9C roots. No donor header, layout, pointer
arithmetic, class identity, flag, body or build dependency is imported. This
is a primary-BFME1 binding repair; donor layout reuse is ruled out. Shallow
history does not establish a separate donor binding-repair commit.

Existing compiler context is unchanged: MSVC7.1 and lane-private Wine11.16
WoW64, WINEARCH=win64, BUILD_POOL=2. Actual before-preview is0of3clean in194.2s;
historical237->237bytes is unchanged, not current confirmed coverage or a
new gain. Cold current-definer gaps and independent provider debt stay outside
this repair. No matched-byte or inferred linked-byte credit is claimed.

Actual after-preview:0of3clean in190.7seconds, all three units UNKNOWN because
22777current objects cannot be read/rejudged here. Historical237->237remains
UNCHANGED. Explicit diagnostics remove the two obsolete unresolved names and
add none. Independent parent review approved pointer-only method views rather
than adoption of the incompatible Zero Hour layout and independently decoded
both raw retail routes and complete providers. No current linked unit or new
linked-byte gain is claimed.

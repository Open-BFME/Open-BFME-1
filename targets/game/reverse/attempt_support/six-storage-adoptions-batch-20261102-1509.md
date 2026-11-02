# Six BFME1 canonical-storage adoptions: bounded batch evidence

Initial outgoing base `829b5979abe8ecb17e70568b5f7a33bc844070f7`. Six separately claimed source units remove six
private Coord3D definitions and use the existing canonical storage header.
The normal gates preserve 6 existing function/EH rows (3186 bytes of
ledger extents), 59 retained external code bodies and their resolved
relocation targets. Independent named-static checking preserves 0
local C++ code definitions. Compiler-generated EH labels are covered by complete
BFME1 runtime-section comparison or BFME2 native parent EH verification.
Added/removed code components are checked for runtime incoming references;
new emitted constructors/iterators are checked against measured exact profiles.
No new matched-row or native/authored-byte progress is claimed.

- [Use canonical Coord3D storage in worker repair target coordinates](worker-repair-target-coord3d-20261102-1509.md): 1 rows, 519 bytes, 12 retained external code definitions.
- [Use canonical Coord3D storage in worker new-task coordinates](worker-new-task-coord3d-20261102-1509.md): 1 rows, 791 bytes, 10 retained external code definitions.
- [Use canonical Coord3D storage in nearest contact-point coordinates](nearest-contact-coord3d-20261102-1509.md): 1 rows, 529 bytes, 8 retained external code definitions.
- [Use canonical Coord3D storage in physics completion coordinates](physics-completion-coord3d-20261102-1509.md): 1 rows, 512 bytes, 18 retained external code definitions.
- [Use canonical Coord3D storage in target eligibility coordinates](target-eligibility-coord3d-20261102-1509.md): 1 rows, 400 bytes, 2 retained external code definitions.
- [Use canonical Coord3D storage in AI path-priority coordinates](path-priority-coord3d-20261102-1509.md): 1 rows, 435 bytes, 9 retained external code definitions.

The linking-first picker still serves RefHandle008958D0,846B across three
sources, at bb53b24f2b. These sources last changed at e8b16ffa12; the current
review read the prior inline-depth/helper-visibility attempts and the Oct28
handoff. No changed prerequisite supports repeating those trials, and this
inspection is not counted among the six tasks. The donor reference remains
59e3f8f825b698775df9e1728265fe962a5d0c02, with successful Nov1 13:06 UTC check
still within72h. Its unchanged donor evidence was reused without a broad scan.
All non-debug sections of each changed BFME1 object preserve bytes and resolved
relocation positions. Owning acceptance controls historical queue retention;
the queue is never edited manually.

Final bounded preview (not a new census, complete current selection or runtime):

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateFindGoodBuildOrRepairPositionAndTarget.cpp: LINKS  LINKED 519 -> 519 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 519)

game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateNewTaskBfme.cpp: LINKS  LINKED 790 -> 790 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 790)

game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceFindNearestLabeledContactPoint.cpp: LINKS  LINKED 529 -> 529 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 529)

game/GameEngine/Source/GameLogic/Object/Update/PhysicsBehaviorRva0029B4E0.cpp: does not link  LINKED 512 -> 0 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 512)

  unresolved  __imp_?__stl_throw_out_of_range@_STL@@YAXPBD@Z

game/GameEngine/Source/GameLogic/Object/Update/TargetEligibility00290990.cpp: LINKS  LINKED 400 -> 400 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 400)

game/GameEngine/Source/GameLogic/Object/Update/AIUpdatePathPriority.cpp: LINKS  LINKED 435 -> 435 bytes (census 2026-11-01 13:17 at bb53b24f2b; file's own bytes 435)

link_check: 5 of 6 link cleanly; LINKED 3,185 -> 2,673 bytes (43.6s)
```

Missing receipts, differing indexes or other unverified provider/consumer
selection remain UNKNOWN/INCONCLUSIVE. A full engine link, gameplay and any
RAM/leak/crash/FPS gain are unproved. No shared header, compiler flag, native pin,
alias, new identity, gate or baseline is changed. Scratch controls live under
build/six-each-full-resources-20261102-1509. BUILD_POOL=14 per independent
repository process, aggregate28 workers on28 logical CPUs; all system resources
were authorized, without a local inference or GPU workload. Claims are released
after ordinary publication.

## Paired original/current physics prerequisite

The current frozen-index preview reports the STL imported out-of-range helper
`__imp_?__stl_throw_out_of_range@_STL@@YAXPBD@Z` unresolved for
PhysicsBehaviorRva0029B4E0.cpp. An additional read-only diagnosis checks the
immutable original object and current verified object at the same original
object-name/link-order position against bb53b24f2b. Both yield exactly that
single unresolved name, with no duplicate, losing COMDAT, selected, alias or
unknown-selection finding. Non-debug bytes/relocation positions already agree.
Thus this change introduces no blocker in that paired frozen-index diagnosis;
the reported512->0 comparison is against the older census, not a before/after
regression caused by this adoption. Current complete provider selection remains
unproven and the binding prerequisite is not fixed or counted as a seventh task.
Controls: bfme1-physics-paired-index.json and pair_b1_physics.py in the ignored
diagnostic package. These snapshot diagnostics do not create or replace any
current-object receipt, census, gate verdict or dependency binding.

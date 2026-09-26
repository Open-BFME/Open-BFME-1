# Twelve-hour cleanup execution

Started: 2026-09-07 16:41:55 UTC (2026-09-08 01:41:55 JST).
Deadline: 2026-09-08 04:41:55 UTC (13:41:55 JST).
Execution base: `8fe7448503316d344fb623d467f3b107126cd9c5`.
Status: phase 4 naming and ownership work is active; 105 cleanup/prerequisite
units are published through `dd0cca379a`. Full integration at that snapshot
completed with the same 174 function failure pairs and 97 DIR32 inconsistency
identities/address sets as hour eight. Three categories remain red;
the full gate has not passed. See [README.md](README.md) for the standing runbook.

## Ownership

All worker roots are under ignored `build/cleanup-20260907/`, with separate
branches, indexes and build outputs. Coordinator alone publishes master.

| Worker/root suffix | Current exclusive responsibility |
|---|---|
| cleanup_metrics / metrics | Independent final reviews, landed samples and full-gate attribution |
| cleanup_placement / placement | HeaderTemplate creation and INI parser cohesion |
| cleanup_evidence / evidence | SidesList donor drained; selecting next bounded identity cleanup |

Existing contributor worktrees are preserved. No new service, port, database,
shared writable cache or external fleet configuration is required.

## Baseline

Initial check_csv: 161,804 function rows, 85,625 symbol rows, one known row-less
source. `BUILD_POOL=4 ./build.sh` covered the execution base above; log:
`build/cleanup-20260907-baseline.log`. Session 75817 ended with exit 1 around
17:27 UTC and must not be polled or restarted by accident.

- 214/161,804 function comparisons failed.
- 98 new DIR32 inconsistencies; XferSave.cpp has zero matched rows.
- Null-relocation count is 65 versus baseline 66; attribution is needed before
  lowering it. Never raise baselines or restore false pins to hide failures.
- No-op patch unavailable because function verification produced no patchset.
- All 19,403 string literals and 1,111 empty-string references passed.
- The drive-map dependency fingerprint migration invalidated almost the entire
  old cache: 13,632/13,816 TUs compiled. This explained the roughly 45-minute
  gate; compiler children kept advancing. Source/pin history predates migration.

First valid readability snapshot: `9eb87c82a0` (before clean rebase to
`c142e08ecb`), log `build/cleanup-20260907-readability-baseline.log`.
Rounded ALL: Body 71, Ident 19, Types 79, Iface 50, Local 28, SSoT 21,
SrcIdent 60, BRI 47. There are 13,999 tracked sources, 298 outside measured
areas. The malformed parent has no valid score; no repair delta is invented.

## Publications

### Integration checkpoint: 19:46:30–19:53:12 UTC

Tested SHA: `b7bb936fc0e3916fe9102d9674922dc71fba6d8b`.
`BUILD_POOL=4 ./build.sh` exited 1 after 401.77s; log:
`build/cleanup-20260907/integration-b7bb936fc0.log`. Session 43369 and PID
2021076 are terminal. No coordinator source/ledger/pin changes occurred in flight.

- Functions: 190/161,803 failures, down from 214. Exact identity comparison found
  zero new failures. All 24 removed failures were directly touched by this
  team's published patches: five same-identity/range source repairs, three
  corrected range claims, and sixteen misleading names retired while preserving
  their covered ranges. This is not a claim of 24 runtime bug fixes.
- DIR32 inconsistencies: 97 versus 98; the false Water cell type is removed.
- Source claims: pass for 13,304 sources; row-less XferSave is repaired.
- String references: 19,429 literals plus 1,111 empty references pass.
- Null-relocation baseline remains stale at 65 versus 66. No-op patch remains
  unrunnable after failed function verification. Full gate: four red categories.
- Warm reuse: 13,789 current TUs, 99 compiled of 13,888. The initial cold gate
  compiled 13,632 of 13,816; these different source snapshots are not a controlled
  performance benchmark.
- Across the 49 published prerequisite/source patches, Code source lines total
  2,417 added and 2,424 removed (net -7), including file moves and real-C++
  replacements. This excludes other contributors and the pending cohesion queue.
  No patch modified game/gen_small or game/gen_asm. Naming/identity corrections
  dominate this phase; concrete per-unit reductions are listed below.

### Integration checkpoint: 21:32:58–21:39:30 UTC

Tested SHA: `1fe94e9dede43ff7aab5df1e4d808d9cd417b634`.
`BUILD_POOL=4 ./build.sh` exited 1 after 392.019s; log:
`build/cleanup-20260907/integration-1fe94e9ded.log`. Session 11606 and PID
2222877 are terminal. The coordinator snapshot remained unchanged throughout.

- Functions: 184/161,800 failures, an exact subset of the previous 190 and the
  initial 214. There are zero new symbol/source failure pairs. The six removed
  since the last full check are three retired false aliases, two corrected EH
  labels and one sentinel allocator repair. The cumulative 30 comprise six
  same-identity/range source repairs, two EH labels, three range corrections and
  nineteen misleading names retired. These are not 30 runtime bug fixes.
- All 30 directly intersect this team's published patches across 24 old ranges;
  none has a direct external source/row touch among the 205 intervening commits.
  This does not exclude indirect dependency effects. The remaining iterator and
  Drawable claims at 1DDFD0 still fail and are not credited as repaired.
- DIR32 inconsistencies: 96, down from 97; the additional reduction is not yet
  attributed to a specific patch. Source claims pass for 13,337 sources.
- All 19,476 literals and 1,122 empty-string references pass. Null relocation
  passes at 65 findings in 19 bodies, with 740 unreadable rows below the
  unchanged 1,000 limit. The no-op check remains unrunnable. Three categories
  remain red; this is not a passing full gate.
- There were 64 compiled TUs and 13,857 cache hits. Different snapshots and
  changed TUs prevent treating 401.77s versus 392.019s as a controlled speedup.

The null-baseline correction `7f8af23610` is separate bookkeeping for the
pre-run external fix `fcf825b4f7`: that fix retired the false 9-byte FXNugget
constructor at 61D90. Historical comparison and an independently reproduced
object relocation identified exactly the missing finding. Only rows 66 to 65
changed; the 19-body count and unreadable limit stayed fixed. No source-fix
credit is assigned to this correction, and no baseline was raised.

### Published units

Eighty cleanup/prerequisite commits are confirmed ancestors of origin/master:
79 cleanup units and one prerequisite. Planning and review-only commits are
excluded. Worker and published identities are separate; this table lists final
published SHAs. Hourly counts below retain their actual cutoff times.

| Improvement | Published SHAs | Integrated verification |
|---|---|---|
| Empty-record guard; exact stray LF removal | c142e08ecb | 75 tests; independent byte-preservation audit |
| 75 WeaponTemplate fields / 225 uses | 3406b8eabc, 03748815ed, 65316044a3 | Same 1,185-byte assignment; 1/1 each |
| Five ownership markers | cc09850f21 | 5/5 |
| Timed operation filenames | 435e677296, e48c028bed, 85435d54df | 2/2, 1/1, 2/2 |
| Nine FESL identifiers | 4a49123237 | 2/2 and four literals |
| Bezier family placement | 344947accd | 75/75 |
| Sort and PSRequest/PSResponse deque placement | 17924caf0f, f183a6ff46, dabeba4b0f | 5/5, 1/1, 1/1 |
| GameState setter; stale GameSlot duplicate | 64547bf46d, 030c21d0b7 | 75-byte match; 2/2 surviving |
| Wide construction; ASCII range destruction | 411ccb6d11, 18493b9cc5 | Exact 66/33-byte bodies; caller/callee identity |
| Canonical XferSave source, 375 lines removed | 3d5c9a24f5 | 2/2; reference bodies preserved |
| Archive forwarding / Detailed pair | dfea7264bf | 43/43 |
| ClearNuggets callback | 39d20f0a2c | 132-byte match; retail table |
| Detailed construction and EH ownership | 7e528a2f37 | 45/45 |
| ArchivedFileInfo pair identities | 119cc727c7 | 172/172 across affected family |
| Six vector payload repairs and helpers | e9ab38ad66, ab278985a2, f8a7496214, df39e0b0d9, 780a03ae7c, f3e2f9d63a | 29/29 through 39/39; all 24 routes re-derived |
| Bezier difference-vector name | f96e28e852 | 7/7 |
| IP enumeration cohesion and opaque storage | 4b7e57c577, 82b6229606 | 6/6; one TU and 40 lines removed |
| Water array types, owner, paths and point fields | 61de60bf96, b215debf16, 6059ef5c6f, 94be7599a6 | 2/2 then 3/3; false pin removed; unknown original owner explicit |
| Honest 48-byte record; simpler archive pair | 98527989b3, f6ae151a4b | 2/2 and 1/1; archive pair removes three lines |
| Actual multiplayer color pair and STLport | 41d7fb7883 | 98/98 across six sources |
| LadderPref copy, pair/EH ownership and map placement | ac87dfbfd0, df88350659, 38603315c2, 904b626b31 | 3/3 through 6/6; map 1/1; 95 bytes converted to real C++ |
| STLport out-of-memory allocator identity | 15a90a0d51 | 3/3 family; 78 bytes converted; 95-line dump becomes 40 lines |
| Subsystem setter; retire false Player alias | fc22cf46e6, 577c439483 | 1/1 each; matched caller evidence |
| Wide pair; honest unknown narrow setter | e36a1744d7, 4bd89709c0 | 2/2 and 1/1 |
| LAN username and slot-lookup filenames/navigation | fac2890274, 49dc6716e0 | 15/15, then 20/20 across six affected sources |
| LadderInfo destructor placement | ac9cfb8113 | Root 1/1; worker family 25/25 |
| Real DataChunk output constructor | 85d714075b | 45/45; 168 bytes converted, 186 to 72 lines |
| TeamPrototype evidence comments | d09089d3db | 7/7; 95 lines removed, code tokens unchanged |
| LAN runtime cohesion | a58337603f | 16/16; 181 to 110 lines, two TUs to one |
| Water cohesion | 31a596d059 | 3/3; 283 to 211 lines, three TUs to one |
| Honest block-writer stack and body | 0470769e29, db868e1d89 | Exact 50/230-byte real C++; 1/1 then 2/2 |
| NetPacket chat-reader cohesion | 8c9c7f8252 | 68/68; 206 to 127 lines |
| Actual MouseThread destructor owner/path | 2f938bd5fb | 21/21 with W3DMouse family; initializer/atexit witness |
| Retire false BuddyInfo/GroupRoom aliases | f4805c1355 | Retained Ladder family 7/7; two ledger rows retired |
| TeamPrototype shared view and honest argument alias | 6a5a353a53 | 7/7; duplicate 13-line view removed |
| PeerDefs unwind object-symbol roles | e5c550c72c | 168/168 across implementation and unchanged reference TU |
| Actual network sentinel pool allocator | a820be5b88 | 28/28; existing 127-byte mismatch repaired |
| Watchdog thread and Win32 API declarations | cbff26b98f | 1/1; 105 to 82 lines, import-table evidence |
| DataChunk output cohesion | 4d40a07918 | 45/45; 219 to 166 lines |
| Neutral owners for false thread constructors | 80b48e98af | Worker 30/30, integrated 14/14; old false pin removed |
| Nine FX constructor filenames | f0bef83407 | 9/9; source bytes identical, readability unchanged |
| ThreadClass construction and priority cohesion | 4082dba47a | 3/3; 42 source lines removed |
| Real ThreadClass virtual destructor | d2e5776d43 | 3/3; seven-byte body converted to C++ |
| Retire false NetCommandList destructor aliases | c5ad1c6252 | Retained canonical family 6/6 |
| NetCommandList reset and append cohesion | cd43adc013 | 8/8; 37 source lines removed |
| Remove retired FXNugget claims from prose | 9022232d55 | 1/1; body and pin address unchanged |
| ExperienceTracker progression cohesion | 1fe94e9ded | 7/7; 23 source lines removed |
| ThreadClass runtime ownership and callback ABI | 03d4a2485e | 32/32; four source consumers, source net +6 lines |
| LightPulse effect cohesion and accurate radius view | 5599cb2410 | 2/2; 195 to 105 source lines; same field offsets |
| Guard callers when ledger candidates disappear | f411837246 | 45 integrated tests; both hooks stop on selector failure |
| Iterator/reference-state split and Clump free route | 574bd43ec1 | 16/16; three strict bodies; false pins removed |
| Laser effect cohesion and accurate base view | 0d8e6c93b3 | 2/2 plus two literals; 291 to 203 source lines |
| Camera effect field units and source name | ca60aa9def | 2/2; three fields and two parameters clarified |
| Correct iterator constructor ledger identity | 4837296cf9 | 20/20 plus 1,245 unchanged caller claims; source untouched |
| RayEffect construction and dispatch cohesion | c8d5bfe7c5 | 2/2; 150 to 121 source lines, method texts unchanged |

The last vector push raced another contributor, then published after a clean
rebase; final published additions/deletions equal the reviewed worker patch.
The first 26 source units were published before 18:41:55; the final vector unit
published during the hour 2 review. Initial planning commits: 26e52f92a2,
72482bb98a, 577f32a077; hour 1 checkpoint: 81a06ec1cf; hour 2: b64e8e92db.
The next 21 source units were published after that review and before 19:40 UTC.

## Reviewed integration queue

The reviewed queue is drained through RayEffect worker `ea441e239f`, published
as `c8d5bfe7c5`; publication session 75474 is terminal. Full integration session
38481/PID 2304858 is also terminal. Preserve worker order and compare exact
patches before commit and after rebase; ledger union merges can import unrelated
changes even when source ownership is disjoint.

Placement committed reviewed four-path reference-state destructor
`ae72d7ce85`, ready for publication: retain the 88-byte release, replace the false 40ADF0/70 alias,
remove the false Drawable clear pin at 15479, and add one tombstone. Direct PE
exports now prove its base is Snapshot; the child original class remains
unknown. All 1,899 required claims passed, with exact unmasked destructor and
EH routes independently reviewed. The connected eight-path Drawable lifetime
and false VectorClass-alias repair is now authorized for implementation.

Evidence is on `cleanup-20260907-evidence-h6` from `c8d5bfe7c5`, studying the
9F2800 destructor with an opaque owned state instead of an unsupported map.
Its exact scratch body is approved; the minimal complete alias repair is authorized.
The coordinator studies the independently proven true FXListStore constructor
and destructor at 42E020/42DE50. Metrics reviews and attributes the completed
gate. Older branches remain preserved. Superseded helper `61ace767d7` and
duplicate prerequisite `bb1c5efd0e` must never enter the publication queue.

## Hourly reviews

Reviews due at each elapsed hour through hour 12. Record actual times and
observed results; do not prefill reviews or claim unmeasured speedups.

### Hour 1: reviewed 17:41–17:46 UTC

- Delivered: prerequisite and planning publication above. Prepared source work
  is not delivery; other agents' changes on master are not this team's progress.
- Independent sample: empty-record guard and mixed-terminator tests; highest-risk
  pending GameState setter and vector route repairs. Setter caller, char-string
  callee and field offset support its name. Vector payload keeps an honest
  address name because original identity remains unresolved; equal size did not
  justify the old coordinate-pair identity.
- Prepared results include 75 evidenced WeaponTemplate names, coherent family
  moves and false-identity corrections. Names preserve unknown storage/types
  where retail evidence ends. Aggregate readability did not move for these
  member names; that metric does not measure local naming quality.
- Bottleneck: approximately 45 minutes in initial full verification. No accurate
  edit/review/rebase time split was captured, so none is estimated. Placement
  restored one byte-green draft after route-name validation rejected it.
- Prior experiment: stop repeated cold worker readability scans. This prevented
  known duplicate scans, but no timed before/after comparison proves a speedup.
  Retain provisionally; coordinator metrics are now warm (557 remaining cold
  blobs on the first successful snapshot).
- Next adjustment: make a target-identity/route matrix before editing identities
  with relocations. Hypothesis: zero post-compilation route rejects, at most two
  scoped compilations per unit. Review at hour 2. Cache observations remain
  measurements, not extra workflow changes: ClearNuggets used 2.832s scoped
  verification plus 17.546s normal commit; hook compiled 0/1 with current cache.
- Next owners are above; coordinator drains the reviewed queue and keeps the
  pre-existing full-build debt explicit. Next review: 18:41:55 UTC.

### Hour 2: reviewed 18:42–18:45 UTC

- Delivered: the 27 source units above, plus the hour 1 prerequisite. All 28
  commit ancestries were checked. Prepared Water/IP/neutral-record/color work is
  excluded. Twenty-six source units landed before the second-hour boundary;
  the final vector unit landed during this review. This drew on work prepared
  during hour 1 and is not a steady-state throughput forecast.
- Independent sample: final vector overflow is exactly the previously reviewed
  blob c05c90e0ebb00d60e4959e15826a4735e15104f2. All old-object reads precede
  destruction; placement construction then initializes the same complete,
  nonconst vector from locals. A destroy-then-write draft was caught before
  publication. XferSave source preservation and the 172-claim archive integration
  were also checked. Unknown original payload names remain visibly unknown.
- Concrete outcomes include 75 evidenced field names, coherent filenames,
  removal of duplicate source and false aliases, and exact clean-C++ replacements
  for some generated claims. No generated source files were edited. Existing
  full-gate failures remain explicit; the row-less XferSave defect is repaired,
  but a fresh full gate is still pending.
- Readability: most naming/path units have no measurable delta. Three observed
  co-location increments were +0.01 pp each; the final truthful vector payload
  correction has SrcIdent -0.01 pp. Accuracy takes precedence over the score.
  Total byte coverage usually changed +0.00 pp; category reclassification is
  reported separately. Whole-repo movement from other contributors is excluded.
- Hour 1 experiment retained: the four later vector units used the target/route
  matrix with zero post-compilation route rejects and 2, 1, 1, 2 scoped compile
  rounds. The color-pair unit separately needed three drafts to emit its exact
  destructor; a successful matrix is not a universal one-pass guarantee.
- Timing: 19 fully recorded normal publication loops had median 67.03s and total
  1,263.40s. These omit manual units and push-retry delays, so they are not the
  complete hour's integration cost. Five warm metadata hooks averaged 16.887s
  with no duplicate compilation. No timed counterfactual proves a percentage
  speedup from centralized readability scans or avoiding probe/build duplication.
- Integration defect caught before commit: out-of-order ClearNuggets cherry-pick
  imported a dependency tombstone through the union merge driver. The hook
  rejected it. Restored only the three owned paths, integrated the dependency
  first, and verified success. Added an untracked publication check comparing
  exact patch additions/deletions; it reproduced rejection of the captured bad
  patch. Path whitelists alone did not protect append-only ledger contents.
- Next single adjustment: send stable caller/type evidence during implementation
  so the independent final review focuses on the completed delta. Pilot readiness
  to approval was 42.772s; semantic review had already finished. Measure the next
  two readiness-to-approval intervals and record findings at hour 3. The pilot's
  13.256s hook also skipped pin checks, so its speed is not credited to overlap.
- Next: drain the reviewed queue in dependency order, then run the full gate on
  a frozen integration SHA using the warm cache. Workers continue in isolated
  roots. No full gate currently runs. Next review: 19:41:55 UTC.

### Hour 3: reviewed 19:42–19:43 UTC

- Delivered: 49 source/prerequisite commits, all ancestry-confirmed; 48 are
  source units. Twenty-one source units landed since the hour 2 review, plus
  the final vector unit during that review: 22 in the elapsed third hour, or
  7.3 per nominal worker-hour across three lanes. This includes carried-over
  preparation and is not a measurement of editing effort. Prepared queue work
  above is excluded.
- Independent landed sample found no material regression. Water's constructor
  allocation/initializer and bounding-box call establish the small object's
  point storage, count and validity fields; its original class name remains
  explicitly unknown. Ladder copy/destruction now uses real string lifetimes
  and the vendor pair; retail callback routes and both unwind maps were checked.
  Repeated ledger names and unmatched reference callers were not counted as
  independent identity witnesses. No unchanged green source was rebuilt by the
  reviewer.
- The highest-risk pending block writer was byte-green but lacked evidence for
  the original XferSave class spelling. Review caught that before publication.
  The corrected queue uses Rva009D8630BlockWriter, a descriptive position-stack
  helper and RTTI-backed XferException metadata. The old helper commit is kept
  on an explicit branch, not published. A normal member call also resolved all
  16 register differences in the banked body in one roughly 0.8s probe: verify
  callee ABI/visibility before trying speculative register shapes.
- Concrete outcomes include the 40-line IP reduction, coherent Water ownership,
  truthful LAN string identities, and 173 bytes of naked code replaced by real
  LadderPref/allocator C++. Most naming/path metrics remain unchanged. Local
  moves included +0.01 pp and -0.01 pp results; honest unknown Water ownership
  reduced SrcIdent by 0.01 pp. These are not reasons to restore false claims.
  Whole-repository coverage movement from other contributors is excluded.
- Hour 2 experiment: early evidence packets remain useful, but no overall
  speedup is established. Two later review waits were 93s and 307.277s. Across
  13 recorded packets the median was 120s, range 42–307.277s. Fifteen complete
  normal publication loops had median
  63.65s and total 888.20s; this omits retries/manual paths and is not total
  integration time. Push races were a separate recurring delay.
- Two stale-branch union merges imported unrelated ledger changes. Exact patch
  checks caught both before compilation/commit; restored only owned paths and
  reapplied the reviewed original patch without a merge. The guard now compares
  additions/deletions both before commit and after rebase. One worker's broad
  ledger byte replacement was also caught and narrowed before commit. Baselines
  were never increased. Metrics was refreshed at a clean, drained boundary;
  whether that reduces coordinator merge rejection is still unmeasured.
- Next single experiment: assign one named final reviewer upfront, retaining
  early evidence sharing. Target readiness-to-approval under 120s for three
  packets; also record when the author resumes to expose delivery/handling
  delay. TeamPrototype pilot: approval 116.702s, author resume 182.863s, so the
  first threshold passed but end-to-end speedup is not established. Placement
  reviews that unit; metrics reviews the next approved evidence-lane unit.
  Explicit original-owner evidence or an unknown-owner statement is now part
  of ordinary identity review after the block-writer finding.
- Next: publish this checkpoint, freeze the coordinator tree and run one full
  gate with BUILD_POOL=4 and unbuffered logging. The cold baseline still has
  five red categories. Its complete failure census is 214; an earlier narrow
  parser omitted 32 reference-path failures, now retained in the ignored
  baseline-failures.json. Compare exact failure identities, not just totals.
  Workers keep isolated reviewed commits and bounded read-only investigations.
  Next review: 20:41:55 UTC.

### Hour 4: reviewed 20:42–20:45 UTC

- Delivered by the 20:41:55 boundary: 57 cleanup/prerequisite commits, all
  confirmed ancestors of origin/master; 56 cleanup units and one prerequisite.
  Eight landed during this elapsed hour, or 2.7 per nominal worker-hour across
  three lanes. This includes earlier preparation and is not editing effort.
  Subsequent publications in the table are excluded from that hourly count.
- Independent landed sample: DataChunk's constructor source is identical to the
  reviewed 72-line body, preserving its 168-byte range. The block writer's
  constructor/vtable, same-this helper, position-stack route and XferException
  RTTI were freshly decoded. No material regression or unsupported original
  owner claim was found. The descriptive owner and unresolved int/long spelling
  remain explicit; generated bodies and unrelated aliases are untouched.
- Concrete reductions include LAN 181 to 110 lines, Water 283 to 211, NetPacket
  206 to 127, TeamPrototype comments 491 to 396, and the DataChunk constructor
  186 lines of naked code to 72 lines of C++. Across all 57 patches, Code source
  totals 3,079 additions and 3,412 deletions: net -333 across 81 distinct paths.
  This excludes other contributors, banked attempts and unpublished work. No
  generated source was edited. Placement and honest naming often leave the
  readability score unchanged; no renamed-symbol quota is used.
- The completed full integration check is detailed above: 214 to 190 function
  failures, zero new failure identities, source claims repaired, four remaining
  red categories. The 401.77s warm gate and roughly 45-minute cold baseline use
  different snapshots, so their difference is not a controlled speedup. Later
  scoped fixes are not counted as a new full-gate result.
- Hour 3 experiment retained with a correction: the next three named-reviewer
  packets took 16.444, 27 and 67.299s, all below the 120s target. Nine recorded
  packets including the pilot and one failed handoff have median 45s and range
  16.444–301s. The 301s supplement waited because a message did not activate an
  idle reviewer; new review requests now use followup_task. Water's author took
  another 13s to act after approval. A later Watchdog review took 41s plus 28s
  author reaction. Fast approval alone does not establish end-to-end speedup;
  these samples do not establish causation.
- A normal hook caught an existing destructor alias that the declaration scan
  could not connect to its object-symbol. Two truthful comments identify the
  already-declared body; no fabricated claim or weakened detector was added.
  A sub-second staged declaration precheck now catches this class of omission
  before requesting final review. One stale STLport version comment was also
  corrected from the actual vendor header before publication.
- Four completely recorded normal publication loops totaled 281.88s, median
  70.655s. These omit four units' retries and other coordinator work, so they are
  not the hour's total integration cost. Repeated remote advancement was a real
  bottleneck, especially for Water; every retry retained hooks and exact-patch
  checks. A final refresh alone still raced and is not a proven cure.
- Next single measured adjustment: sequentially publish an explicit queue of
  independently approved units. Keep one mutation in flight, all existing
  checks, and at most three retries only for a confirmed remote race; stop on
  any other failure. The trial began at 20:40. Measure completion-to-next-start
  delay for three transitions, targeting under 2s without new patch/verification
  defects. This addresses observed coordinator idle time after terminal tools;
  it does not promise to eliminate other contributors' pushes.
- Next owners: metrics consolidates DataChunk; placement corrects Watchdog and
  screens a bounded next family; evidence works on ThreadClass lifecycle after
  a clean refresh. The coordinator drains reviewed units and investigates the
  stale null-relocation baseline without changing it on a guess. Next review:
  21:41:55 UTC. Deadline remains 04:41:55 UTC.

### Hour 5: reviewed 21:40–21:57 UTC

- Delivered by the 21:41:55 boundary: 72 cleanup/prerequisite units, 15 since the
  previous boundary, plus the separate external-fix baseline bookkeeping above.
  Runtime `03d4a2485e` landed after the cutoff and is excluded. The 72 patches
  add 4,238 and remove 4,804 Code lines: net -566 across 119 distinct source
  paths. Other contributors, unpublished work and baseline bookkeeping are
  excluded. No generated source was edited. Units include ledger/tool repairs
  and are not a count of newly reconstructed functions.
- Independent landed sample: a nonauthor compared the published neutral and
  real ThreadClass sources against the frozen integration snapshot, rechecked
  their distinct constructor arguments, layouts and vtable slots, and confirmed
  five same-range rows retain separate truthful owners. The old two-argument
  pin is removed; unknown original names and allocation extent remain explicit.
  No unsupported identity or source drift was found; no duplicate build ran.
- The completed full result above improves the initial failure census from
  214 to 184 with zero new failing identities. Null-relocation bookkeeping is
  supported by the retired claim's history and independent object evidence.
  Three categories still fail. Filename-only and prose-only FX cleanup has no
  measurable readability-score improvement; runtime accuracy costs six source
  lines. Neither is represented as a line-count reduction.
- Hour 4 publication experiment met its three-transition target: actual
  in-queue completion-to-next-start delays were 0.000199, 0.000107 and 0.000191s,
  all below 2s. No new patch or verification defect occurred in those batches.
  Retain sequential publication. Gaps between separate queue invocations are
  excluded from that specific measure, not from elapsed work; this does not
  establish faster end-to-end throughput or eliminate remote push races.
- Named review activation remains useful, with observed reviews of 34–110s,
  but coordinator reviews of NetCommandList and ExperienceTracker took 138s
  and 125.182s, missing the 120s target. Author reaction also took 55s and 77s
  on two coordinator units. The hourly checkpoint itself was finalized late.
  These are real coordination delays, not compiler cost. Keep a named reviewer
  and record both approval and author action; do not claim instant handoffs.
- Next single measured adjustment: audit lost callable names before the first
  extraction compile, targeting zero late consumer-scope additions over the
  next three identity units. A 237-byte queue destructor was discovered late
  during ThreadClass scratch work because removing a ledger-provided callable
  can affect callers without deleting a pin. It was corrected before commit.
  The bounded tool patch reuses retail/COFF consumer selection, mirrors the
  resolver's ordered last-row semantics, includes overlapping owners, and
  checks selector exit status in both hooks. Pure fixtures cover these actual
  failure modes. No coverage gate or conservative missing-object rule is relaxed.
- Next owners: placement implements the approved iterator/reference-state
  split; evidence implements the bounded consumer guard; metrics independently
  reviews both. Coordinator publishes this checkpoint and drains reviewed units.
  Next review: 22:41:55 UTC. Deadline remains 04:41:55 UTC.

### Hour 6: review 22:38–22:52 UTC

- Delivered by 22:41:55: 80 cleanup/prerequisite units, eight this elapsed hour,
  excluding the hourly checkpoint and external-fix baseline bookkeeping.
  Team patches total 4,952 Code lines added and 5,698 removed: net -746 across
  135 distinct source paths. This hour contributes net -180. The three FX
  consolidations remove 207 lines and three files; the runtime, iterator and
  Camera improvements add 27 lines. No generated source was edited.
- Independent landed sample: Laser's published/current source equals the
  reviewed hash, both method texts equal their donors, and the retail parser,
  C8 allocation, B4 base, field table and virtual routes were re-decoded.
  The caller guard's five published files equal the reviewed/current files;
  ordered resolver semantics, overlapping owners and checked hook captures
  were reinspected against the 45 passing fixtures. No drift or unsupported
  new claim was found. Tests and builds were not repeated for this sample.
- Full check: `c8d5bfe7c56490f1cfbf9e465f79b8960858882a`, 22:31:19.070997 to
  22:37:53.692649 UTC, 394.622s, exit 1, snapshot preserved. There are 180
  function/source failures, all subsets of the previous 184 and initial 214.
  Two newly removed failures are this team's iterator destructor-call and
  Clump free-route repairs. Two 75-byte NetCommandMsg alias emitter corrections
  belong to external `8dfd94179e`; they are excluded from team credit. Thus 32
  of the initial removed failure pairs directly intersect team changes, two
  external changes. This is not a count of runtime bug fixes.
- Strings 19,492 plus 1,122 empty references pass; source claims pass for
  13,371 sources; null relocation passes at 65/19 with 741 unreadable rows.
  The unchanged unreadable limit is 1,000. DIR32 is 97 versus 96 previously;
  external `0729f041ab` introduces the additional `_PresetAlphaShader` binding
  at VA 0x12D6E18; three unchanged callers bind 0x12D6E14. Historical source
  and object evidence accounts for the other 96 findings. No team change adds
  a DIR32 inconsistency. No-op remains unrunnable, so three categories remain red.
  There were 59 compiled TUs and 13,896 cache hits. Warm timings near 395s use different snapshots and do not
  establish a controlled performance improvement.
- Readability: LightPulse improves Iface by 0.03 pp and Local by 0.01 pp;
  Laser and Ray each improve Local by 0.01 pp and remove one file. The iterator
  split improves Local by 0.01 pp while honest unknown ownership lowers
  SrcIdent by 0.01 pp. Runtime, Camera and constructor identity cleanup have
  no measurable score change. Keep that uncertainty and meaning rather than
  optimizing the metric with invented names.
- The consumer-audit experiment has one completed prospective identity unit
  of its three-unit target. The 0.827s pre-compile constructor audit proved an
  existing canonical body sufficed, so no extraction TU was needed. Five
  predicted conservative sources were verified (20 family plus 1,245 generated
  caller claims); zero unexpected consumers appeared. Current object evidence
  then narrowed the hook's caller set to zero, agreeing with the audit. Keep
  the trial for the next two identity units; no elapsed-time saving is claimed.
- Reviews caught and corrected a current-pointer/tail note, a false reference
  attribution for LightPulse's argument count, and ambiguous VA/RVA wording.
  Named decision times include 108s for the guard, 87s for the iterator plus a
  47s note supplement, 141s for LightPulse, 179s for Laser, 22s for the iterator
  constructor follow-up, and 54s for Ray. The 120s target was not universal.
  Camera's 102s decision reached its author at 281s from readiness; the 179s gap's cause is
  unestablished, and direct-send order was confirmed. Author action after
  approval took 48s for LightPulse, 19s for Laser, 27s for the constructor, and
  20s for Ray. Decision, delivery and author action stay separate measurements.
- Ray's stale-branch cherry-pick imported old neighboring Laser/LightPulse
  ledger rows. Exact-patch comparison caught two extra changed lines and one
  missing reviewed line before compilation. Restored only owned paths and
  applied the original reviewed patch directly; no merge resolution was kept,
  and normal verification/push passed. This recurrence identifies a possible
  future improvement to integration, but the current consumer trial remains
  the single measured adjustment. Clean branch refreshes and exact-patch
  checks are retained; no broad hook weakening or new framework is justified.
- Next: publish this review and the reviewed reference-state destructor.
  Placement repairs Drawable lifecycle identities; evidence repairs the
  unrelated 9F2800 owner, and the coordinator prepares true FXListStore cohesion after its identity
  dependency is resolved. Next review is 23:41:55 UTC; the deadline remains
  04:41:55 UTC. The eight-unit count stops at the actual hour boundary.

### Hour 7: review 23:37–00:01 UTC

- Delivered by 23:41:55: 90 cleanup/prerequisite units, ten this elapsed hour.
  Team patches total 5,366 Code lines added and 6,351 removed: net -985 across
  164 distinct source paths; this hour contributes net -239. The count excludes
  the hourly document and a reviewed Drawable consolidation still awaiting
  publication. No generated source was edited.
- Concrete outcomes include true FXListStore and FXList lifecycles, one neutral
  owner replacing unrelated 9F2800 destructor aliases, and Drawable icon types,
  slot indexes and local names matching their actual layout. Three callbacks
  falsely described as FX parsers now use ObjectCreationList types and paths
  for InstantDeath, CritterEmitter and StructureTopple. Raw registration/field
  tables establish module ownership; unknown original class or static-method
  spellings stay explicit. Byte equality alone is not identity evidence.
- Independent landed samples of FXList and the three OCL parsers match all four
  reviewed source hashes and seven exact rows. The reviewer re-read primary PE
  return-type exports and raw OCL/SpawnObject field records. No source drift or
  unsupported new identity was found; no duplicate build was run for sampling.
- Full check: `4e8be7d877e273e1a600f7e6c6ff7bbe29785855`, 23:35:04.399279 to
  23:41:18.567221 UTC, 374.168s, exit 1, snapshot preserved. All 175 function
  failures are subsets of the previous 180 and initial 214. Three removed pairs
  are our retired false VectorClass scalar aliases; external `ce23dcdd6e` fixes
  a NetPacket serializer binding and `1235860512` repairs a falsely named factory.
  Cumulatively, 35 removed pairs intersect team changes and four external
  changes. This is not a count of repaired runtime behaviors.
- All 97 DIR32 inconsistency identities and their full address sets are unchanged
  from hour 6. A separate read-only scan took 73.495s. Ninety-five site lists
  are identical; exception-list claim churn and three newly truthful OCL parser
  references explain the other two. Existing conflicting OCL global references
  remain. Strings 19,500 plus 1,123 empty references, 13,395 source claims, pins
  and null relocation pass. Null relocation is 65/19 with 739 unreadable rows,
  below the unchanged 1,000 limit. No-op remains blocked, so three categories
  remain red. The gate compiled 45 TUs and reused 13,933 current cache entries.
- Reflection on the early-caller-audit trial: all three prospective units had
  correct REL32 consumer predictions. Precompile audit ordering is documented
  for two; the neutral 9F2800 audit timing is unrecorded. Its 1.709s measurement
  is compile time, not audit time. Its mandatory C61E10 exception-cleanup row
  was discovered after the exact scratch body existed, before tracked edits.
  Thus two units avoided late dependency expansion; a universal success claim
  is unsupported. Keep early caller audits and explicitly inspect EH ownership.
  No controlled elapsed-time saving has been measured.
- Reviews caught misleading parser types, false owner names and layout claims.
  Most recorded decisions took 45–102s. The 9F2800 decision was complete at
  22:58:50 but reached its author at 23:01:44; reviewer context compaction
  intervened before sending. This is a coordination delay, not proven transport
  latency. Send decisions directly before further work. The full check ended
  before the boundary, but checkpoint publication is late; preserve actual
  timestamps and continue rather than backdating the review.
- Next measured adjustment: select extra integration callers from the
  coordinator's current objects instead of copying the worker's conservative
  cold-cache list. Always include every changed surviving Code TU and both
  checked callable/pin selector outputs; retain normal hooks and all full-gate
  triggers. For the next three identity units record worker versus coordinator
  source/claim counts, selector and build durations, and unexpected consumers.
  FXList needed 19 worker sources/6,799 claims while current coordinator evidence
  already excluded all retained callers; this is an opportunity, not an observed
  speedup. Use existing selectors and publication arguments, without new tooling.
- Next owners: placement finishes animation collection cohesion, evidence
  corrects the CritterEmitter factory and constructor, and metrics independently
  reviews both. Coordinator publishes held Drawable cohesion and checks the
  separately discovered Anim2D draw prefix claim. Next review is 00:41:55 UTC;
  the deadline remains 04:41:55 UTC.

### Hour 8: reflection begun 00:41 UTC; verification finalized 00:49 UTC

- By the hour boundary, 97 cleanup/prerequisite units are published, seven this
  elapsed hour. Code totals are 5,977 added and 7,096 removed: net -1,119 across
  179 paths. This hour contributes net -134. Held template and builder units
  are excluded. No generated source was edited.
- Drawable cohesion removes two files and 54 lines. InstantDeath and animation
  collection cohesion each remove 69 lines and one file. Correct Critter
  factory/destruction identities add 12 lines; their separate TUs are justified
  by observed exception/vtable behavior. The full Anim2D drawing repair adds
  30 lines and restores 145 bytes missing from a truncated claim. The phase
  parser work adds 16 lines, truthful five-phase types, and a newly verified
  138-byte OCL callback. Line reduction is not substituted for correctness.
- Full integration at `4e1c238e8311d76a4db895bf3c5d24c08a04c312` ran from
  00:39:41.974471 to 00:46:02.767796 UTC: 380.793s, exit 1, snapshot preserved.
  All 174 function failures are subsets of the prior 175 and initial 214.
  The sole removed pair belongs to external camera repairs `375c3263af` and
  `6078b3684d`, preserving the old range under cameraUpdate and recovering
  zoomCamera at its actual address. Cumulative attribution is 35 team-related
  removals and five external, not 40 repaired behaviors. This hour adds no
  team credit to that failure-removal count.
- All 97 DIR32 identities and complete address sets are unchanged. The terminal
  read-only scan took 77.796s; only exception-list and OCL-global site lists
  changed, on already established bases. Strings 19,504 plus 1,126 empty
  references, 13,430 source claims, pins and null relocation pass. Null remains
  65/19, with 738 unreadable rows under the unchanged 1,000 limit. The full gate
  compiled 53 TUs and reused 13,960; functions, DIR32 and blocked no-op remain
  the three red categories. These warm snapshots are not controlled benchmarks.
- Independent landed samples of Anim2DDrawing and CritterDestructor equal the
  reviewed/current source hashes and four expected rows. The reviewer re-read
  the full draw endpoint/Display call and constructor/scalar/base-vtable routes.
  Unknown original owners remain explicit; no source drift or unsupported
  identity was found. Sampling repeated no build and read no active objects.
- The current-object selection experiment reduced explicit source/claim scopes
  on all three units:4/1003 to2/3,4/37 to2/25,6/1505 to2/3. Normal hooks agreed,
  with zero unexpected extra callers. Selector durations were3.509,2.971 and
  3.507s. The first standalone build duration was not captured; a small ignored
  publisher logging change records subsequent command durations and exit codes.
  The latter builds took7.151 and3.019s, versus worker scoped gates7.373 and
  4.659s on different worktrees. Including selection gives10.122 and6.526s;
  this does not establish an end-to-end speedup. Retain truthful current-object
  selection and all mandatory checks; stop presenting smaller counts as timing.
- Reviews rejected a combined Critter lifecycle after proving that novtable
  would give the constructor the wrong vtable despite a superficially green
  byte gate. The held field-builder patch preserves a neutral containment builder rather
  than inheriting an unsupported ActiveBody label; neither range is discarded.
  Template review found three reverse links to bodies absent from the canonical
  file; the corrected worker commit is held and therefore not credited as published.
- Coordination has larger observed delays than the scoped-build differences.
  Template proposal review took309s. The root phase packet was ready00:34:15
  but handed off late; its final decision00:37:10 includes174.625s end-to-end,
  while the reviewer's first tool clock00:36:04 to decision was66s. Record
  coordinator handoff, review, delivery and author action separately. The full
  gate began later than the desired00:35 freeze, so this reflection is drafted
  during the gate and will be published after the immutable snapshot completes.
- Next measured adjustment: split queued final reviews between non-authors.
  Metrics handles coordinator-authored patches and integration attribution;
  coordinator reviews ready worker patches when metrics is occupied. Send
  decisions directly before additional logging or analysis. For the next three
  queued final reviews record readiness-to-handoff, readiness-to-verdict and
  approval-to-author-action; no duplicate reviewer build or weaker gate.
- Reassignment alone has not demonstrated faster review: the first two held
  patches still waited 119s from the refined template packet (466s from its
  initial packet) and 403.122s for the builder. Coordinator publication and
  checkpoint work occupied the other reviewer too. Reserve review time before
  taking more editing work, and keep the existing 120s target visible. The
  following two-comment correction was approved in 54s after exact diff proof.
- Secondary opportunity: compare the unchanged donor's full symbol and
  relocations before trying codegen variants. An inherited trailing CC byte
  caused one unnecessary template probe; baseline comparison would have avoided
  it. No padding workaround was added.
- Next: publish this reflection and the reviewed template, reverse-link and
  field-builder commits, then continue the bounded Bfme807 family cleanup. Next review01:41:55 UTC; deadline04:41:55 UTC.

### Hour nine review — 2026-09-08 01:41 UTC

- Published eight more reviewed units, reaching 105 through `dd0cca379a`.
  Code changes total 6,510 lines added and 7,687 removed, net -1,177 across 195
  distinct source paths. This hour removes 58 net lines. No generated source
  was edited; a six-byte voice-table getter moved from a generated claim into
  real C++. Other units preserve existing ranges while correcting names,
  placement, lifetime models and stale provenance.
- Template/collection cleanup removes 30 lines; the StructureCollapse lifecycle
  removes 55, INI animation cohesion 63 and constructor navigation one. Clearer
  field builders add 88 lines and typed trigger callbacks add three. Report the
  mixed tradeoff rather than treating all identity work as code reduction.
- The lifecycle now represents ObjectModule's actual 12-byte subobject and the
  behavior/update/death interfaces. An implicit ObjectModule destructor retains
  its virtual base lifetime and matches the teardown; no synthetic destructor
  emission helper remains. All 174/32/30 bytes, actual vtable bases and the EH
  cleanup route were independently checked. Only the obsolete fake-base pin
  was removed; unchanged callers were proved not to consume it.
- INI parser cohesion uses private StringBase inheritance and an owning 8-byte
  exception view. Review confirmed the two destructor implementations have the
  same cleanup semantics, without inventing a byte-identical alias or new pin.
  The inherited post-throw CC byte was compared against the unchanged donor
  immediately, avoiding another candidate shape or padding workaround.
- Recent final readiness-to-verdict intervals were 33.697,120.178,98.062,
  85.932 and77.431 seconds; four of five met the 120-second target. These are
  different changes, not a controlled speed benchmark. The callback's initial
  packet still needed a naming revision, taking 435.456 seconds end to end.
  Check newly moved functions' argument/local names before freezing a packet;
  preserved bytes alone do not mean the readability work is complete.
- Approval-to-author receipt still took 45.617,81.860,72.951 and84.486 seconds
  for the four recent worker commits. Next experiment: workers freeze staged
  packets; after exact independent review, coordinator runs the normal commit
  directly in that worker tree, then releases the worker. Both lanes acknowledged
  sole coordinator commit ownership for the next packets. Measure the next two
  approval-to-command intervals; preserve every hook and all publication checks.
- Precompile analysis prevented an incomplete module-data cleanup: four vector
  callbacks are shared with SlowDeath, ModuleFactory emits the scalar destructor,
  an EH row must follow its parent, and the similarly named DieMux constructor
  pin targets another body. The larger change is deferred. An isolated 58-byte
  prerequisite now has primary field-table evidence and a first-attempt exact
  scratch body, with no old-name consumers and no pin/EH scope.
- Full integration on clean `dd0cca379a` ran 01:36:26.905–01:43:37.533,
  430.629 seconds, exit 1, with the snapshot preserved. All 174 failure pairs are
  identical to hour eight: zero introduced or removed. The initial 214 comparison
  still attributes 35 removed pairs to team work and five to external changes.
  This checkpoint receives no new failure-removal credit.
- All 97 DIR32 identities and complete address sets are unchanged; independent
  scan 78.246s. Only an UpdateModule source rehome and exception-list sites changed.
  Strings 19,505 plus 1,126 empty references, 13,443 source claims and pin checks
  pass. Null remains 65 rows/19 bodies/738 unreadable under the unchanged limit.
  The gate compiled 19 of 14,026 TUs and reused 14,007. Functions, DIR32 and the
  blocked no-op patch remain red; this is not an all-green full gate.
- Independent landed samples of the lifecycle and INI cohesion match the reviewed,
  published and frozen hashes and all five rows. Actual lifetime/vtable/exception
  evidence is unchanged. Object hold was released after the terminal comparison.
- Freeze began 86.905 seconds after the 01:35 target while the final reviewed
  publication finished. Drafting this reflection began before the hourly boundary;
  publication waited for exact terminal attribution.
- First post-checkpoint commit experiment: the reviewed SidesList packet started
  its normal worker-tree commit 0.000280 seconds after approval and completed
  in 18.633 seconds, all hooks passing. Its final review still took 128.264 seconds,
  so direct commit removes the handoff delay in this trial without solving review
  time. Worker commit `d53908bc11` is held and is not part of the 105-unit snapshot.
- Next: finish the remaining SidesList donor, land the bounded DieMux prerequisite,
  and select the next INI cohesion from observed source contents. Next review
  02:41:55 UTC; execution deadline 04:41:55 UTC.

## Resume

Integrate one worker commit at a time with no-commit cherry-pick, review staged
paths, byte-verify affected surviving sources, measure staged readability, and
commit normally. Pull/rebase, check_csv, progress, normal push, final pull and
published-ancestry confirmation. Never weaken gates for pre-existing failures.
Use PYTHONUNBUFFERED=1 for subsequent logged builds to expose live output.

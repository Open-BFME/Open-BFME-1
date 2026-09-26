# Twelve-hour source cleanup

Execution status and the twelve-hour clock are recorded in [cleanup-run.md](cleanup-run.md).
Read this runbook and the five phases together. This scoped
cleanup assignment overrides the default dump-conversion queue in AGENTS.md.

## Outcome

Make real source easier to understand: evidence-backed names, descriptive paths,
related implementations together where their compilation requirements permit,
and concise explanations of genuine uncertainty. Preserve byte matches, ABI,
identity evidence, and every unrelated contributor's work.

Inspecting a candidate is not a delivered improvement. Success is independently
reviewed source changes present on origin/master, passing the applicable gates,
with twelve hourly reviews and a final account of what improved and remains.
Measure throughput in hour one before setting a delivery forecast; do not impose
a rename or commit quota that rewards trivial edits or invented names.

## Schedule

These windows set the primary emphasis; workers continue safe independent work
across a phase boundary when the coordinator has confirmed its prerequisites.

| Elapsed time | Phase | Acceptance |
|---|---|---|
| 0:00–0:30 | [Baseline and queue](phase-1.md) | Valid measurements, isolated roots, full baseline gate |
| 0:30–3:00 | [Proven names](phase-2.md) | Evidenced names/paths, scoped byte checks, published units |
| 3:00–7:00 | [Ownership and cohesion](phase-3.md) | Compatible moves/folds, preserved claims and byte matches |
| 7:00–10:30 | [Deeper naming debt](phase-4.md) | Reviewed identity evidence, pin/caller checks, appropriate gate |
| 10:30–12:00 | [Final verification](phase-5.md) | Full integration gate, verified publication, complete report |

## Observed starting point

Audited 2026-09-08 at `783d4d4c1239`; recheck all candidates after pulling.

- `check_csv.py` passes: 161,804 function rows, 85,613 symbol rows, one known
  row-less source. No full build was run while preparing this plan.
- `readability_metric.py` fails on empty ledger record 161470. Thus there is no
  valid starting readability score yet; do not report one.
- `merge_cluster.py --list` fails on the malformed marker in
  `game/GameEngine/Source/GameClient/System/CampaignConstructor.cpp`.
- The placement audit found five malformed markers and 158 multi-file marker
  destinations. These are triage counts, not proven merge opportunities.
- Existing tools already implement filename proposals, cluster moves, field-name
  evidence, identity checks, and seven readability axes. Reuse them.
- `docs/readability_plan.md` and `docs/drain-status.md` contain useful historical
  lessons, including low merge eligibility; their old counts are not forecasts.

## Team and ownership

Use four concurrent agents total, including the coordinator:

| Role | Ownership |
|---|---|
| Coordinator | Publication checkout, work assignments, integration, independent review, shared-header scheduling, hourly log, all origin/master pushes |
| Naming worker | One assigned owner/TU at a time: proven fields, parameters, locals, functions/classes when identity is established |
| Placement worker | One assigned destination family at a time: filenames, ownership markers, compatible sibling consolidation |
| Evidence worker | Independent identity/ownership research and review; implements a separate proven unit when review demand permits |

Every writer gets a separate branch and worktree or clone, with its own index
and writable build outputs. Verify hooks, toolchains, retail inputs, and scoped
builds in each root. Worktrees share configuration and the stash stack; inspect
the absolute hooks path before starting. Never share writable build/match output.
Workers are not alone in the repository: never revert others' changes, and adapt
to their edits. Assign explicit paths, destination, symbols/RVAs and exclusions
in each brief. No overlapping class/header ownership. Finish the file's eligible
work before changing families; complete or revert each body before the next.

Run at most one full gate at a time, including coordination with existing local
writers. Start with conservative build parallelism and measure contention. Poll
running builds; do not restart them because they are quiet. Other fleets remain
outside this assignment.

## Working rules

- A plausible name is insufficient. Prefer a matched caller naming the symbol;
  corroborate with retail boundaries, xrefs, vtables, field tables and matching
  reference implementations. Upstream vocabulary is evidence, not proof of BFME
  offsets, virtual ordering, or class identity.
- Keep honest unknown names where evidence ends. Never rename padding or
  anonymous slots simply to improve a score. Preserve types/layout and expression
  order during a naming pass. Class renames need review of mangled references,
  declarations, pins, callers and known type collisions.
- A merge marker is a lead, not authority. Confirm the body belongs in the
  destination; reconcile layouts and compiler visibility explicitly. Keep
  separate TUs when inline/EH/code-generation requirements demand it.
- Preserve concise reasons and unresolved evidence. Remove obsolete narration
  only after preserving necessary evidence in an existing suitable record;
  completed historical prose is recoverable in git history. Do not erase
  unmatched reference bodies just because the ledger does not compile them.
- Do not edit game/gen_asm or game/gen_small. Do not mint generated or naked
  replacements. Do not introduce fallbacks, weaken gates, or increase baselines.
  Prefer TU-local changes over new shared abstractions.
- Bound an uncertain item to roughly 30 minutes without improved evidence or
  byte progress. Restore only that attempt, record the concrete blocker, and
  move to the next eligible sibling. Bank real reconstruction near-misses using
  `re_log.py` and its required score/body flags; a rename-only failure needs a
  checkpoint entry, not a fictitious reconstruction claim.

## Publication loop

Publish every completed unit; aim for a green source publication every 30–60
minutes across the team after setup. Build duration may extend that interval;
record why instead of pushing incomplete work. One converted body per commit;
one atomic naming or placement unit per cleanup commit. A source move and its
ledger update must land together.

1. Worker verifies every affected surviving source using `./build.sh <paths...>`,
   stages explicit paths, inspects the diff/index and commits normally with hooks.
   It provides the commit, purpose, identity evidence, affected rows and checks.
   State the original-owner witness explicitly, or say the owner is descriptive
   and its original spelling unknown. Name one final reviewer before starting;
   record readiness, approval and author-resumption times separately.
   Activate a new final-review request with followup_task; send_message alone
   does not wake an idle reviewer.
2. Coordinator independently reviews the diff and evidence, pulls/rebases master,
   runs `python3 tools/check_csv.py`, then integrates one worker commit with
   `git cherry-pick --no-commit <worker-sha>`. Inspect every staged path.
3. Rebuild all affected surviving TUs on the integrated tree. Run
   `python3 tools/readability_metric.py --staged` and `git diff --cached --check`.
   Record the real readability result and concrete improvements, including zero
   metric movement where appropriate. Commit normally so hooks run again.
4. Pull/rebase, check the ledger, and reverify if upstream changed dependencies.
   Resolved conflicts, headers, shared shims, and vendored-reference changes
   require `./build.sh` in full. Hooks do not enforce every one of these triggers;
   the coordinator must. Check generated tracked output before including it.
5. Run `python3 tools/progress.py origin/master`, then `git push origin HEAD:master`.
   On rejection, rebase, check the ledger and relevant gates, then retry. Never
   force-push or bypass hooks. Pull/rebase again and confirm the published SHA
   using `git merge-base --is-ancestor <published-sha> origin/master`.
6. Record worker and final published SHAs, evidence, check results and timings in
   the checkpoint. Keep one publication in flight, so rebases cannot obscure
   which unit still needs delivery. Never use bare stash/pop or `git add .`.

For pins, run `pin_consistency.py --symbol '<name>'` before changing the pin and
`--check` afterward; use `--routes` when routed pins are involved. Run
`identity_guard.py` for semantic naming changes and directly investigate any
flagged identity. Green byte matching never substitutes for identity evidence.

## Hourly reflection and improvement

At elapsed hours 1 through 12, the coordinator reserves 5–10 minutes for a
review; workers can finish safe independent work while it runs. Record the
actual time if a gate delays the checkpoint. Maintain a compact durable
`docs/plans/cleanup-run.md` during execution, including:

`hour | published SHAs/paths | concrete improvements | readability delta |
conversion delta | edit/build/review/rebase minutes | rejects/reverts |
sample reviewed | bottleneck | experiment | result/keep-or-drop | next owners`

Each review must:

1. Reinspect at least one landed unit and the highest-risk rename or move from
   that hour. The reviewer must not be its author; findings become a correction
   task immediately. If no unit landed, inspect the blocker and pending diff.
2. Answer whether the names communicate evidenced meaning, the file contains
   coherent content, uncertainty remains visible, and code/duplication actually
   decreased where intended. Look for a pattern the next worker could repeat.
3. Compare delivered units per worker-hour and time lost in gates, repeated
   discovery, conflicts and rejected guesses. Distinguish whole-repo movement
   from this team's accepted commits; external fleets also change master.
4. Evaluate last hour's experiment, then choose at most one measured workflow
   adjustment: reuse a family evidence brief, narrow ownership, shrink batches,
   keep a cache warm, serialize expensive work, or retire an exhausted queue.
   State the hypothesis and next-hour result to check. Keep improvements only
   when observed time or quality supports them; record insufficient evidence.
5. Update ownership, rejected hypotheses, pending process IDs/checks and exact
   next commands. Commit the hourly log with the next completed publication, or
   separately if needed; log-only commits are not source-cleanup progress.

Self-improvement means adapting this run's process from observed results. Spend
at most 15 minutes per hour implementing a small demonstrated tool improvement,
with an appropriate regression test; do not build a new agent platform or
weaken verification. User updates summarize outcomes and the next adjustment.

Use the existing seven axes plus reviewed counts of better names, corrected
paths, coherent folds and removed redundant declarations/prose. The metric's
Local axis measures co-location, not local-variable names. Filename and local
renames can be valuable with zero score movement. Track conversion coverage
separately: `+0.00 pp` can be an honest result for this explicit cleanup lane.

## Completion and interruptions

Hour 10.5 closes intake of risky work; reserve the remaining time for completion,
full verification and publication. Adapt earlier if measured gate time needs a
larger reserve. At twelve hours, leave no unfinished reconstruction in game/;
keep useful unfinished evidence on its worker branch/checkpoint and identify
unpublished work explicitly. Do not claim success while a required gate runs.

The checkpoint makes session, tool, authentication or usage interruptions
resumable. It does not guarantee unattended execution after the session stops.
Do not let blocked publication accumulate an unbounded queue: preserve verified
commits, diagnose the actual failure, and report anything requiring user action.

Final delivery: published commit list, before/after examples, measured cleanup
and coverage deltas, gate results with tested SHA, all twelve review entries,
which speed experiments helped, and the next evidence-backed backlog.

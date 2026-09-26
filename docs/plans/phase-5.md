# Phase 5: Verify the complete result and hand off

## Objective

Use elapsed 10:30–12:00 to finish safe units, verify the integrated repository,
publish all accepted work and deliver an auditable result.

## Implementation

- Stop opening risky investigations. Finish or restore each active attempt;
  preserve useful unpublished evidence with its exact status and next action.
- Coordinator integrates remaining reviewed units and completes the source
  review early enough to reserve the measured full-gate runtime. Serialize long
  builds and poll existing processes. Do not sacrifice required verification to
  meet the clock.
- Run hours 11 and 12's reviews. Have a non-author review the highest-risk
  accepted identity/placement edits and a representative simple naming change.
  Fix discovered defects through normal gated commits.
- Run the final full gate after all accepted source corrections, on a recorded
  SHA. If this team changes source or build-affecting inputs afterward, repeat
  that gate. Later documentation-only checkpoints need no extra full build.
- Finish the hourly log: all twelve review entries, accepted versus rejected
  speed experiments, published SHAs, before/after examples and remaining queue.
  Keep durable lessons in this run record; update an existing instruction/doc
  only if an observed reusable lesson warrants the additional change.
- Publish remaining commits and the final checkpoint; final pull/rebase and
  ancestry verification follow the runbook. If new upstream code changes the
  verified snapshot, recheck affected dependencies and state which SHA the full
  gate proves; resolved conflicts require another full gate.

## Verification

- `./build.sh` completes successfully after the last accepted source correction
  at the recorded integration SHA; record the final published SHA separately
  and confirm any later team commits change only documentation.
  `python3 tools/check_csv.py`, `python3 tools/pin_consistency.py --check` and
  `python3 tools/identity_guard.py` pass on the publication state.
- Sweep this team's rows with narrow filters: one real body per address, no
  duplicate claims, lost rows, unknown-source paths or generator-owned edits.
- Compare `python3 tools/readability_metric.py --at <valid-baseline-sha>` with
  `--at <final-sha>` and run `python3 tools/progress.py <execution-start-sha>`.
  Label these whole-repository deltas if external agents contributed; separately
  report this team's per-commit changes, so their work is not attributed to us.
- Confirm every accepted published SHA with
  `git merge-base --is-ancestor <sha> origin/master`. Inspect all worker and
  publication statuses: no active rebase, unfinished source attempt, or
  unidentified staged edits. Preserve unrelated work.
- Final report gives commit links, real improvements, tested SHA/gate results,
  limits, unpublished blockers and what sped up based on measurements. Any
  incomplete required check is reported as incomplete, never as success.

# Phase 1: Establish a trustworthy queue and baseline

## Objective

Use elapsed 0:00–0:30 to establish isolated workers, valid measurements and a
small proven cleanup queue, extending only for a demonstrated prerequisite.

## Implementation

- Follow docs/plans/README.md; record the execution start SHA/time and twelve-hour
  deadline. Pull/rebase, check the ledger, inspect existing local writers and
  initialize three isolated build-capable worker roots with exclusive ownership.
- Diagnose the empty record that passes check_csv but breaks readability_metric.
  Apply the smallest valid ledger/parser-contract repair, preserving other
  records and line endings; do not silence malformed nonempty rows or return a
  fabricated score. If checker code changes, add a regression for this defect.
- Audit malformed ownership markers in CampaignConstructor.cpp,
  Campaign_newMission.cpp, W3DWaypointBufferDestructor.cpp,
  Gen_00732960_W3DTreeBufferVariant_FreeTreeBuffers.cpp and
  ConnectionManager_areAllQueuesEmptyTwin.cpp. Correct destinations only from
  evidence; express ordinary notes as prose instead of invalid machine markers.
- Re-inventory filename proposals and merge candidates. Do not infer eligibility
  from historical counts. Set initial exclusive families from phase 2 and 3.
- Capture the first valid metric baseline after any prerequisite repair and label
  it with its SHA; retain the original failure as evidence. Start one full baseline
  build and poll it to completion before publishing game-source cleanup. Read-only
  research and isolated preparation can proceed while that build runs.

## Verification

- `python3 tools/check_csv.py` passes; `python3 tools/readability_metric.py`
  produces a valid table; `python3 tools/merge_cluster.py --list` completes.
- `python3 tools/rename_addressed_sources.py --under game/GameEngine/Source/Common --limit 8`
  prints proposals. Its default is preview; it has no --plan flag.
- `./build.sh` completes and its baseline SHA/result is recorded. Diagnose and
  repair baseline failures under the same gates before dependent publications.
- If relevant tools change, run their existing pytest modules plus the focused
  new regression, such as `python3 -m pytest -q tools/tests/test_readability_metric.py tools/tests/test_readability_guard.py tools/tests/test_readability_partial.py`.
  Marker-only edits need source byte verification, not new tests of wording.
- Each worker proves its root can run a scoped build on its first assigned TU.
  Record independent root/path ownership, working hooks and valid queue entries
  in docs/plans/cleanup-run.md. Reforecast if setup consumes the intended pilot window.

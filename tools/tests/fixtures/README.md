# Replay fixtures

Two frozen populations for `test_boundary_validator.py`. They are committed
rather than rebuilt in-test because both derive from inputs the fleet rewrites
every few minutes (`targets/game/reverse/functions.csv`, `targets/game/reverse/re_attempts.log`,
`targets/game/reverse/zh_sweep/drift_report.csv`), and a measurement whose population moves
under you is not a measurement. The Ghidra inventory is pinned the same way, by
the commit named in that test.

- `dead_ends.csv` — 2,291 `no-match` rows from `targets/game/reverse/re_attempts.log` whose
  boundary could be resolved to an rva and a size (from the row's own evidence
  text, else the drift candidate it was queued from, else the ledger). Each one
  is a work slot the fleet already spent proving the address was wrong.
- `structural_queue.csv` — the 3,923 structural candidates over 1,200 addresses
  the queue served at that commit, after `drop_logged`.

To re-cut them, enumerate the same two populations and write the three columns
each file carries. Re-pin the counts asserted in `test_boundary_validator.py`
in the same commit: they are exact by design, so a moved population must show
up as a deliberate edit rather than a silently different number.

# WHALE-1 automatic progress

Started 2026-09-16 on branch `whale1-auto` from `origin/master`.

## Checkpoint — 2026-09-16

- `0x008BF100`: one source reconstruction banked as a partial verdict. The
  best candidate is 16,229 bytes versus 18,655 retail bytes, with 4,878 of
  18,655 masked bytes equal (score 0.2615). Retail evidence proves 178 calls
  to `0x0089E680`, a `0x2c8` frame, 178 EH cleanup states, and a final
  `hashCount` allocation tail. The ABI/name mismatch in the existing ledger
  remains explicitly documented.
- Commit/push: commit `fd5ee19206` is on `origin/master`. The first push
  raced another writer once, then passed the normal rebase/retry sequence and
  the final pull is up to date.
- Bodies added to `reverse/unlocked.txt`: none. No shared shim, pin set, or
  byte-verified layout landed.
- Next: inspect and work `0x007C7FD0` from its current evidence pack, then
  continue the ordered WHALE-1 pool. Re-run `next_work.py --ranked` only
  after the listed pool has recorded verdicts.

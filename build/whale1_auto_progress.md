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
- `0x007C7FD0`: identity-supported `FlatTerrainShaderPixelShader::set`
  candidate banked as a partial. The best source-backed candidate is 1,811
  bytes versus 12,130 retail, with 1,295 non-relocation differences and
  masked score 0.0425; the alternate `FlatTerrainShader2Stage::set` is 2,274
  bytes and also diverges at the EH/frame start. The full callee/layout/
  lever record is in `docs/whales.md`.
- Commit/push: pending for this checkpoint; no ledger row or unlock row was
  changed by this body.
- Next: pull/rebase/push this verdict, then inspect and work `0x00934940`.

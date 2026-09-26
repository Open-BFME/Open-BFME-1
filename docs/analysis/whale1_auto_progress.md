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
- Bodies added to `targets/game/reverse/unlocked.txt`: none. No shared shim, pin set, or
  byte-verified layout landed.
- `0x007C7FD0`: identity-supported `FlatTerrainShaderPixelShader::set`
  candidate banked as a partial. The best source-backed candidate is 1,811
  bytes versus 12,130 retail, with 1,295 non-relocation differences and
  masked score 0.0425; the alternate `FlatTerrainShader2Stage::set` is 2,274
  bytes and also diverges at the EH/frame start. The full callee/layout/
  lever record is in `docs/whales.md`.
- Commit/push: pending for this checkpoint; no ledger row or unlock row was
  changed by this body.
- `0x00934940`: the expanded Render2D-shaped renderer was banked as a partial.
  Current and Zero Hour `render2d.cpp` candidates were both 3,743 bytes versus
  8,277 retail; the best had 2,548 non-relocation differences and 1,195
  masked-equal bytes (score 0.1444). A 128-combination mechanical EH search
  produced only invalid syntax variants or no improvement. The existing
  `Render2DClass::Render` identity at `0x00933E50` and the anonymous target's
  unresolved owner make a rename or pin unsafe.
- Commit/push: pending for this checkpoint; bodies added to
  `targets/game/reverse/unlocked.txt`: none.
- Next: pull/rebase/push this verdict, then inspect and work `0x007DD180`.

## Checkpoint - 2026-09-16 (WHALE-1 continuation)

- `0x007DD180`: identity-supported `TerrainShader2Stage::set` candidate
  banked as a partial. The best BFME-expanded candidate is 7,083 bytes versus
  6,636 retail, with 3,141 non-relocation differences and 3,495 masked-equal
  bytes (score 0.5267). Retail proves the `0xA4` EH frame, the 35/35 snapshot
  string contract, 28/7 state-name calls, six `bfmeGet` texture lifetimes,
  and the two filter/matrix j-thunk routes. The candidate's `0x8C` frame and
  467 relocation-layout drifts remain the blocker.
- Commit/push: the `0x007DD180` verdict was published in the prior checkpoint;
  this checkpoint adds the `0x005674F0` bank, its immutable attempt history,
  and its fresh `partial` evidence row before publication.
- Bodies added to `targets/game/reverse/unlocked.txt`: none; both `0x007DD180 w3d-render`
  and `0x007DF1F0 w3d-render` were already present.
- `0x005674F0`: matched caller proves `BfmeConsumerED::bfmeApply` with a
  24-byte polymorphic `BfmeArgED`; the best candidate is 5,745 bytes versus
  5,762 retail, with 420 relocations, 3,796 non-relocation differences, 269
  masked-equal bytes, and score 0.06617. The exact 37-manager-write count,
  41 Ascii literal count, preference offsets, and compact returned-number
  helper are recorded; the `0x68` versus `0x64` frame and 393 relocation-layout
  drifts remain. The streak local-copy lever was tested and rejected at 6,522
  bytes. No unlock rows were added.
- Commit/push: pending for this checkpoint; the fifth body's source bank,
  `targets/game/reverse/re_attempts.log`, recipe, and immutable attempt history are ready
  to publish.
- Next: publish this verdict, run `python3 tools/check_csv.py`, then inspect
  `python3 tools/next_work.py --ranked` for the next open body above 4 KB not
  listed by WHALE-2, recording a verdict for each body.

## Checkpoint - 2026-09-16 (post-fifth publication)

- `0x005674F0` verdict, bank, recipe, and attempt history are published in
  commit `8b712700d6` on `origin/master`. Pre-commit passed ledger and
  identity checks; pre-push passed pin consistency and source verification.
- Bodies added to `targets/game/reverse/unlocked.txt`: none. The fifth body's preference
  layout and APT callee set did not prove a shared blocker for a smaller dump.
- Next ranked open dump above 4 KB not listed by WHALE-2: `0x0095CE80`,
  `?RenderStreak@StreakRendererClass@@...`, 12,206 bytes, starting from its
  existing score-0.6 bank. Run `tools/callees.py` first and keep its work
  separate from the two WHALE-2 reservations.

## Checkpoint - 2026-09-16 (ranked continuation)

- `0x0095CE80`: the existing `StreakRendererClass::RenderStreak` bank was
  rechecked from its complete 23-target callee contract. The best source is
  12,095 versus 12,206 retail (score 0.6), with the known `0x5A78` versus
  `0x5A84` frame and 138 relocation-layout drifts. A fresh volatile 12-byte
  frame-pad candidate was compiled and rejected at 12,111 bytes with 10,633
  non-relocation differences; the bank is retained and the new blocked verdict
  is recorded.
- Bodies added to `targets/game/reverse/unlocked.txt`: none. No safe pin or shared layout
  proof was established.
- Next: inspect the ranked queue after this blocked recheck; the next eligible
  large dump is `0x00084510` (4,499 B) unless a larger non-WHALE-2 open body is
  exposed by the refreshed ranking.

## Checkpoint - 2026-09-16 (GlobalData extent correction)

- `0x00084510`: full-range callee extraction corrected the served 4,499-byte
  estimate to the 4,621-byte retail extent. The existing constructor bank is
  2,804 B versus 4,621 B (score 0.2), with 2,331 non-relocation differences and
  20 relocation-layout drifts. Explicit vtable-store, virtual-destructor, and
  `+0x9C` array-element candidates were compiled; none improved the bank. The
  new blocked verdict records the 14-target contract, the `0x10138` frame, and
  the unresolved first member-init wall.
- Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: refresh `python3 tools/next_work.py --ranked` and take the next open
  dump over 4 KB not listed by WHALE-2, with exact boundary evidence.

## Checkpoint - 2026-09-16 (PopulatePlayerInfoWindows verdict)

- `0x004DBE80`: the ranked `PopulatePlayerInfoWindows` candidate was taken
  through the verified BFME GameSpy and PSPlayerStats layouts. The best bank
  emits 3,953 bytes versus 4,126 retail, with 229 relocations, 1,344
  masked-equal bytes, 2,609 non-relocation differences, 199 relocation-layout
  drifts, and honest score `0.326`. The callee table, stack/map layout, and
  tested levers are recorded in `docs/whales.md`; the direct
  `readAdditionalDisconnectsFromUserFile` call at `0x004DB0B0` and GameSpy
  slots `+0x70/+0x90/+0x170/+0x174` are preserved in the bank.
- No exact candidate, ledger row, pin, or shared unlock proof was found.
  `targets/game/reverse/unlocked.txt` remains unchanged. The partial verdict and immutable
  attempt history are ready to publish.
- Commit/push: pending for this checkpoint.
- Next: run the ledger gate, publish this verdict with the normal pull/rebase,
  push, and final-pull sequence, then refresh `python3 tools/next_work.py
  --ranked` and continue with the largest eligible dump over 4 KB.

## Checkpoint - 2026-09-16 (WHALE-1 pool exhausted)

- The `0x004DBE80` verdict, bank, recipe, and immutable attempt history were
  published in commit `df16e53aec` on `origin/master`. The final pull was
  already up to date; `git status --short` was clean and `check_csv.py`, the
  pre-commit ledger/identity checks, and the pre-push checks passed.
- Bodies added to `targets/game/reverse/unlocked.txt`: none. No body in this session landed
  byte-exactly, and no shared shim, pin set, or class layout was proven broadly
  enough to unlock a smaller neighbour.
- Pool result: the refreshed `python3 tools/next_work.py --ranked` lists
  `0x003FA5B0` next at 3,951 bytes. Therefore the requested continuation pool
  of open dumps over 4 KB, excluding WHALE-2's reservations, is exhausted.

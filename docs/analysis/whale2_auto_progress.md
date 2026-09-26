# WHALE-2 automatic progress

## 2026-09-16 — session start

- Branch: `whale2-auto`, based on the current `origin/master`.
- Ledger gate: `python3 tools/check_csv.py` passed (`161951` function rows, `88309` symbol rows).
- 0x00960A30: preferred 51-byte bank retained; 12 explicit SIB/pointer shape variants produced no improvement, so the candidate is recorded as a plateau and left available for a future genuinely new lever.
- 0x007DF1F0: identity resolved to `TerrainShader8Stage::set`; best clean candidate banked at score `0.416` after 31 minutes, with 5,431 non-relocation differences and 796 relocation-layout mismatches. No exact source or ledger change.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: inspect and convert `0x007CE290` after publishing this verdict commit.

## 2026-09-16 - checkpoint after 0x007CE290

- Commits pushed: `df77ac4e0f` (the previously published 0x00960A30/0x007DF1F0 work); the 0x007CE290 verdict is prepared for its own publication.
- 0x007CE290: corrected identity to `FlatTerrainShader2Stage::set`; banked the BFME-expanded semantic candidate at score `0.44` after 35 minutes. The scoped build passed, and the probe measured 7,168 versus 8,147 bytes, 651 relocations, 4,403 non-relocation differences, and 632 relocation-layout mismatches. No exact source or ledger change.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none; the pre-existing `0x007ce290 w3d-render` line was not duplicated.
- Next: publish this verdict, then inspect `0x007C5690` from `d_007afaa0.asm`.

## 2026-09-16 - identity correction for 0x007CE290

- 0x007CE290 was corrected from the earlier FlatTerrain hypothesis to `TerrainShader2Stage::set`. The class/function neighborhood proves `FlatTerrainShader2Stage::set` is the separate 0x007C5690 body, and the target’s five `BoxSetTexture` calls match Terrain’s five texture-set sites.
- The corrected Terrain candidate is banked at score `0.36`: scoped probe `ours=9265` versus `retail=8147`, `821` relocations, `5045` non-relocation differences, and `802` relocation-layout mismatches. The prior FlatTerrain-labelled bank remains rejected evidence only.
- The correction is not yet published; no production source, function row, pin, or unlock row changed.
- Next: publish the correction, then work the explicit 0x007C5690 body.

## 2026-09-16 - checkpoint after 0x007C5690

- Commits pushed: `df77ac4e0f` (0x00960A30/0x007DF1F0) and `a3fd75789c` (corrected 0x007CE290 identity and bank). The 0x007C5690 verdict is prepared for its own publication.
- 0x007C5690: identity resolved to `FlatTerrainShader2Stage::set`; best candidate banked at score `0.34`. Probes covered helper-only, state-cache, address-state shape, handle-aware, and late-state variants; best was `7093` versus `7909`, with `4415` non-relocation differences and `600` relocation-layout mismatches. No exact source, ledger change, pin, or unlock row.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: publish this verdict, then inspect `0x009B8130` from the explicit pool.

## 2026-09-16 - checkpoint after 0x009B8130

- Commits pushed: `9ff170e3c8` (0x007C5690 bank and prior WHALE-2 records). The 0x009B8130 blocked verdict is prepared for its own publication.
- 0x009B8130: VP6 MMX body reviewed from the retail prologue, callee sweep, existing stale scaffold, and aligned-frame sibling compile. No exact clean transcription, pin, or unlock row; verdict recorded as blocked with evidence.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: inspect `0x009D9D90` (the next explicit pool body with an existing 0.55 stash).

## 2026-09-16 - checkpoint after 0x009D9D90

- Commits pushed: `7a46240bd1` (0x009B8130 blocked verdict). The 0x009D9D90 evidence update is prepared for publication.
- 0x009D9D90: retained the identity-resolved `_bfme_dumpXferStream` stash at score `0.55`; current source is 3,046/5,472 with the wrong parser/throw ladder and frame. No exact source, pin, or unlock row.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: inspect `0x0057A470` from its 0.47 stash.

## 2026-09-16 - checkpoint after 0x0057A470

- Commits pushed: `b54a6e4b30` (0x009D9D90 blocked verdict). The 0x0057A470 evidence update is prepared for publication.
- 0x0057A470: retained the identity-resolved Skirmish profile updater stash at score `0.47`; exact frame but unresolved retail profile/global dispatch ladder. No exact source, pin, or unlock row.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: inspect `0x0073E050` from its 0.30 stash.

## 2026-09-16 - checkpoint after 0x0073E050

- Commits pushed: `40051c076b` (0x0057A470 blocked verdict). The 0x0073E050 evidence update is prepared for publication.
- 0x0073E050: retained the W3DView draw twin as scratch evidence at score `0.30`; retail no-EH/display-global shape is not represented. No exact source, pin, or unlock row.
- Bodies landed: none. Bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: inspect `0x003EEB90` from its 0.55 stash.

## 2026-09-16 - checkpoint after 0x003EEB90

- Commits pushed: `23d7284f1d` (0x0073E050 blocked verdict) and `c1ba024f78` (0x003EEB90 blocked verdict and closing WHALE-2 evidence).
- 0x003EEB90: retained the identity-resolved Pathfinder twin at score `0.55`; BFME seven-argument/Object* path logic and frame remain unresolved. No exact source, pin, or unlock row.
- Pool status: all nine explicit WHALE-2 bodies have a recorded verdict; bodies landed: none; bodies added to `targets/game/reverse/unlocked.txt`: none.
- Next: report the verified remote state and the remaining recorded stashes/blockers.

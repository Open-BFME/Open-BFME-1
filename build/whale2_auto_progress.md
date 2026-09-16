# WHALE-2 automatic progress

## 2026-09-16 — session start

- Branch: `whale2-auto`, based on the current `origin/master`.
- Ledger gate: `python3 tools/check_csv.py` passed (`161951` function rows, `88309` symbol rows).
- 0x00960A30: preferred 51-byte bank retained; 12 explicit SIB/pointer shape variants produced no improvement, so the candidate is recorded as a plateau and left available for a future genuinely new lever.
- 0x007DF1F0: identity resolved to `TerrainShader8Stage::set`; best clean candidate banked at score `0.416` after 31 minutes, with 5,431 non-relocation differences and 796 relocation-layout mismatches. No exact source or ledger change.
- Bodies landed: none. Bodies added to `reverse/unlocked.txt`: none.
- Next: inspect and convert `0x007CE290` after publishing this verdict commit.

## 2026-09-16 - checkpoint after 0x007CE290

- Commits pushed: `df77ac4e0f` (the previously published 0x00960A30/0x007DF1F0 work); the 0x007CE290 verdict is prepared for its own publication.
- 0x007CE290: corrected identity to `FlatTerrainShader2Stage::set`; banked the BFME-expanded semantic candidate at score `0.44` after 35 minutes. The scoped build passed, and the probe measured 7,168 versus 8,147 bytes, 651 relocations, 4,403 non-relocation differences, and 632 relocation-layout mismatches. No exact source or ledger change.
- Bodies landed: none. Bodies added to `reverse/unlocked.txt`: none; the pre-existing `0x007ce290 w3d-render` line was not duplicated.
- Next: publish this verdict, then inspect `0x007C5690` from `d_007afaa0.asm`.

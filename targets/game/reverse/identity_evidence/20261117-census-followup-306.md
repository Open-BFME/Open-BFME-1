# Full census after continuation task 306

Successful [run 44007239027](https://github.com/Open-BFME/Open-BFME-1/actions/runs/44007239027)
measures exact input `7a2623f4f86d3c887237d00344ffa5bafb584be2`.
Both downloaded ZIP artifacts were SHA-256 checked against GitHub artifact
digests. Index and history independently identify `7a2623f4f8`, 2026-11-17 04:29.

Compared with run 43970549635 / `86c8ac5443`:

| Metric | Before | After |
|---|---:|---:|
| LINKED bytes | 3,095,587 | 3,095,587 |
| Linked authored bytes | 2,824,483 | 2,824,483 |
| Link-clean files | 15,536 | 15,536 |
| Unresolved references | 88,684 | 88,682 |
| Blocking names | 87,928 | 87,926 |
| Data blockers | 2,927 | 2,925 |
| COMDAT conflicts | 6,951 | 6,951 |

No clean-file gain or loss occurs. The original 200-task cohort retains
152/200 clean sources. The first 306 continuation tasks touch 302 unique
sources, retaining 121/302 clean in both snapshots. Later tasks are outside
this input. Two fewer unresolved references do not establish new LINKED bytes.

The previous rule would report 3,180,624 bytes / 15,967 clean files, versus
3,179,290 / 15,966. These alternate-rule counters are not substituted for
the current LINKED result above. No successful executable launch, gameplay,
memory improvement or crash fix is established by this measurement.

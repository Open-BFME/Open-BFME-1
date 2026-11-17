# Full census after the 500-task continuation

Run `44065495031` completed successfully against
`f85160db0383f60ba060ec2324fbed22e7001bcd`. Both ZIP artifacts were downloaded
and SHA256-verified: census `912a2591881a1d094a5f10766aefba857bd9678a29c2f22cd7a95d462b028c92`;
index `2ce7cc1364228b32045eced26a43ce35e85c5d18b8c5a46fb18d3559d7a56d51`.

Compared with successful run `44007239027` / `7a2623f4f8`:

| Measure | Before | After |
| --- | ---: | ---: |
| LINKED bytes | 3,095,587 | 3,095,587 |
| Linked files | 15,536 | 15,536 |
| Unresolved names | 88,682 | 88,682 |
| Blocking names | 87,926 | 87,926 |
| COMDAT conflicts | 6,951 | 6,951 |

There are no linked-file gains or losses. The 500 counted source tasks cover
464 unique sources; their linked subset remains 218/464. The preceding
200-task cohort remains 152/200 linked without loss. The only changed source
status is `BaseHeightMapRenderObjClassDestructorThunk.cpp`: COMDAT losers4 to3;
it remains blocked by duplicates and wrongly selected copies. This is not a
linked-byte gain. Historical alternative-rule counters are not substituted for
the current LINKED metric.

This census covers all original500 tasks. It does not cover the later
class-contract forward-reference fix `ddbd0363589` or the grouped list-header
adoption `e27899673e1`. Their scoped checks remain separate evidence. No game
startup, crash fix, memory saving, leak repair,64-bit, multicore or FPS gain is
inferred from this census or the source reconciliations.

The measured index was adopted at a clean, published501-task boundary, retaining
the previous frozen index privately. The working current-provider snapshot
remains separately receipted; a refreshed preview is not a new full census.

## Newer daily run covers the following repair too

Daily run `44094222765` also completed successfully, against
`e27899673e1102b5b6c1fa8723d4fdd9bf523214`. Its census and publish jobs both
succeeded; upstream recorded the result in `42e77361643`. This input includes
the forward-reference checker fix and grouped renderer list-header adoption.
There are no source-status changes, linked-file gains or losses against
`44065495031`; all aggregate counts above remain unchanged. The501 counted
source tasks still cover464 distinct sources, of which218 link. A source can
contain distinct, separately verified class reconciliations.

Both newer artifacts were SHA256-verified: census
`135b07c2764c0882011ec8bd0d5beaeab7b1ebbc7b2d0cb8528dd1853ad6e0ff`;
index `85b548fde94a627616cf7d21ce55018d4fdee8146673c838a06acfe884da8100`.
The newer measured index is selected for the next continuation. The earlier
run and old frozen index remain available as comparison evidence.

# Full census after continuation task207

Successful run [43970549635](https://github.com/Open-BFME/Open-BFME-1/actions/runs/43970549635)
measures input `86c8ac544382435ff31acb6f6d1baffb755428de`.
The artifact index and history independently identify `86c8ac5443`,
2026-11-16 23:24. Both artifacts were downloaded and inspected.

Compared with successful run43936402752 at `1ac768d4cf`:

| Metric | Before | After |
|---|---:|---:|
| LINKED bytes |3,095,420|3,095,587|
| Linked authored bytes |2,824,316|2,824,483|
| Link-clean files |15,535|15,536|
| COMDAT conflicts |6,952|6,951|
| Unresolved references |88,684|88,684|
| Blocking names |87,928|87,928|

No previously clean source became blocked. The sole newly clean source is
`game/GameEngine/Source/Common/BfmeConv561.cpp`, contributing167B.
This is an additional linked consumer, not a new reconstructed function.

The original200-task cohort is present in full:152/200 clean before and
after, with no gain or loss. The first207 continuation tasks touch203 unique
sources, including repeated independent repairs of some units;73/203 are
clean in both measurements. Neither task counts nor source counts are
substituted for full-image linking results.

## Selected-provider evidence

Native `link_check.kept_definition` and `kept_verdict` on both frozen
artifact indexes show `?isEmpty@AsciiString@@QBE_NXZ` changing from:

- `INIMapCache.obj`, digest `11b7cc24445b`, verdict `wrong`;
- to `W3DModelDraw.obj`, digest `378d5c8a69ec`, verdict `retail`.

The two strong BfmeConv561 function providers remain in BfmeConv561.obj.
Its status changes from exactly one wrong-selected dependency to clean.
This supports the167B gain following the task117-120 unused-boolean-copy
cleanup, which removed the former INIMapCache emitter and intervening
unused copies while preserving complete ordinary runtime graphs and native
row verification. The consumer itself was not rewritten for this gain.

Compared with run43870552474, the combined905B gain consists of the
previously documented738B plus these167B. The earlier243B FX provider gains
remain credited to Yannick Molinghen's separate work; they are not counted
as our continuation tasks.

The later source cohorts are outside this run's207-task input. Scoped
previews on a frozen index remain distinct from a new full-image census.
No successful executable launch, gameplay, crash fix, leak fix, or memory
optimization is established by this measurement.

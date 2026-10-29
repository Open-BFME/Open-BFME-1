# GameEngine::execute 0x0006BBE0 (959 B): frame-slot trials, session 486

Start: archived draft `targets/game/reverse/attempt_history/0x0006bbe0/f1c4b9ad...json`
(3 non-reloc diffs, struct `{float oldScale; GameEngine *self;}` at -32, catch `e` at -24).
Retail slots (from the 959-byte body): catch reference `e` -0x20, `self` -0x1C,
`oldScale` -0x18, headroom/fild temp -0x14; -0x24 unused in both builds.
All trials: `/FAsc` added to the draft's `// cl:` line, `probe.py --size 959`.

| variant | slots (e / oldScale / self) | diffs |
|---|---|---|
| draft (pair struct oldScale,self) | -24 / -32 / -28 | 3 |
| pair struct reversed (self,oldScale) | -24 / -28 / -32 | 5 |
| separate `GameEngine *self = this; float oldScale;` | **-32** / -28 / -24 | 4 (only self/oldScale swapped) |
| `this` everywhere, no self copy | -32 / -28 / this -24 | 945 B, regalloc differs (esi this, ebx zero) |
| mixing `this` and `self` at any one site | extra `_this$` slot | 948-953 B |

Inert on the separate-scalar form (slots unchanged): declaration order, `const self`,
`GameEngine &self`, `void *`/`unsigned` self, 1-member struct wrappers for either,
block-scoped oldScale, block-scoped self or oldScale around the loop, renaming
either local (no alphabetical rule), dead self-assignments / `(void)` refs to
oldScale (folded before slot assignment), a trailing dead ref at loop end.

Observations: 8-byte aggregates go below the 4-byte catch object; among the
4-byte objects the order e < oldScale < self never moved. Generated memory refs are
identical to retail (self: store + one post-catch reload; oldScale: store + fadd),
so whatever retail differed by is not visible in code bytes. Untested: a source
shape where self carries a different IL weight (e.g. referenced in a catch body
that optimises away), compiler flag variants.

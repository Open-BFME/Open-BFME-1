# 0x004E0A70 ReplayMenuSystem — constant-register mechanism PROVEN, 12 B to go

Bank (production `ReplayMenu.cpp` copy): 1247/1248 B, 815 non-reloc diffs,
shape 0.940. Sole structural residue per prior analysis: retail keeps literal
0 in EBX, ours keeps 3 in EBX + 0 in ESI (extra `push esi` at +0x20).

## Experiment (this pass): `Int selected = 0;` in the 4 GBM_SELECTED branches

```diff
-					Int selected;		(analyze/load branches)
+					Int selected = 0;
-				Int selected;			(delete/copy branches)
+				Int selected = 0;
```

Semantically neutral (out-param always overwritten by
`GadgetListBoxGetSelected`); raises literal-0's weight before register
allocation, per `docs/shape_levers.md` "A store repeated in both arms makes
a constant worth a register".

## Result (probe, 89 relocs): 1260/1248 B, 600 diffs, shape 0.984

- The `push esi` is GONE; `cmp/push ebx` and `bl` EH stores now match retail
  everywhere else. EBX=0 confirmed achieved.
- Full side-by-side: the only inserts are three `mov [slot],ebx` zero-stores
  (`[esp+0x10]` ×2, `[esp+0x14]` ×1 = +12 B); the fourth init merged away.
  Every other window matches, including the `selected` reload+`cmp eax,ebx`
  sequences (retail provably does NOT pre-zero `selected`).
- Artifact: `build/rd970/ReplayMenu_zeroinit.cpp` (untracked scratch; this
  diff is the complete record — do NOT bank the experiment as a stash, its
  four stores are provably non-retail).

## Residue and next steps (not tried)

The landing needs EBX=0 at ZERO byte cost. Candidates:

1. Subset search: 1–2 of the 4 inits may suffice to flip the allocator while
   merging free (the merged branch proves cross-jumping can absorb one).
   ~4 probes worst case, each ~4 min.
2. First-store order theory: if the allocator takes EBX for the FIRST
   materialized constant, find what makes retail store state 0 before state 3
   (temporary declaration order?); then no hack is needed at all.
3. Lower 3's weight instead: restructure a temporary to cut a state-3 store
   (counts are currently tied, so -1 may flip it back at zero cost).

Do NOT repeat: per-branch filename objects (1290 B), direct-init filename
per branch (1206 B), filename-after-controlID (812 diffs) — all refuted.

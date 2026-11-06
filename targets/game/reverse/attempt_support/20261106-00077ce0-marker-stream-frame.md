# 0x00077CE0 handoff: frame residue solved; marker streams remain the only blocker

Target `?apply@Rva00077ce0@@QAEXH@Z` (placeholder; the candidate defines
`?apply@Rva00077ce0@@QAEXK@Z`), RVA 0x00077CE0, 339 bytes, ledger row is the
gen_asm dump `game/gen_asm/d_0006bc3e.asm`.

## Result

- Bank `targets/game/reverse/attempts/0x00077ce0.cpp` reproduces as logged:
  339 bytes, 8 non-reloc diffs (`sub esp,0x2c` vs `0x48`, receiver spill and
  two switch homes 28 bytes too high).
- **Diagnostic EXACT (modulo relocation slots)**:
  `targets/game/reverse/attempt_support/20261106-00077ce0-diag-markers-exact.cpp.txt` (scratch build/wf/00077ce0/diag_markers_exact.cpp). It still uses the two inline-asm
  marker blocks, so it is NOT a clean conversion and must not land in `game/`.
- Clean C++ (markers removed, `best_clean.cpp`): 214 bytes, 178 diffs. No clean
  spelling can be exact: retail carries 54 marker bytes
  (`push eax; mov eax,0xCFCECDCC; mov eax,<self+0xF>; mov eax,0; mov eax,0;
  mov eax,0xCFCECDCC|0xCECDCCCB; pop eax`) and, without them, the function is
  no longer demoted to /Od-style code (see mechanism 1).

## Mechanisms established (measured with tools/probe.py)

1. **TU flags are the project default `/DNDEBUG /MD /EHsc /O2 /Ob2`, not
   `/Od /Ob0 /Og`.** An inline-asm label referenced by `mov eax, OFFSET label`
   demotes the whole function to `/Odty`-style code (listing:
   `Function compile flags: /Odty`), which yields retail's two-snapshot
   `sub`-chain switch. Using a literal `0477CEFh` instead of the label under
   /O2 gives a fully optimized 232-byte body (198 diffs) -> the label is what
   demotes. `/O2`, `/Ox`, `/O2 /Ob1`, `/Og /Ob1|2` all produce identical code;
   `/O1`, `/Od /Og /Os` do not.
2. **The 28-byte unaccessed frame region is inline-candidate locals.** In a
   demoted function with inlining enabled (/Ob1+), callees that are inline
   candidates are NOT expanded, but their locals/temporaries still reserve
   frame slots below the caller's temporaries (control: `inline int get2(R*r)
   { int x = r->op; return x; }` adds 4 unused bytes; each STLport `find` adds
   12). Bank flags /Od /Ob0 suppressed this entirely (frame 0x2c); /O2 /Ob2
   with the bank source gives 0x38 (12-byte hole).
3. **`Rva00077C70Receiver::method` is an in-class inline member** whose body
   is the 0x00077C70 marker-bracketed `set::insert(key)`. Defining it inline in
   the class adds exactly the missing 16 bytes -> frame 0x48, this at -0x40,
   switch homes at -0x44/-0x48: EXACT. The same source also reproduces
   0x00077C70 (`?method@Rva00077C70Receiver@@QAEXK@Z`, 89 bytes) EXACT modulo
   relocs, including its previously unexplained 8 extra frame bytes.
4. Sibling check: the 0x00077A90 bank recompiled with `/O2 /Ob2` and a label
   marker (instead of its literal immediate under /Od /Ob0) is also EXACT
   (373 bytes) -> the three bodies share one /O2 /Ob2 TU.
5. Keys are `unsigned long`: `??$find@K@?$set@K...` and `?end@?$set@K...`
   and the `_Rb_tree_base_iterator` ==/!= spellings are ILT-oracle CONFIRMED.
   The map find/end/operator*/pair-copy and `method` spellings remain
   CONTRADICTED (map value/record type names are wrong, not the shape).

## Ruled out this run (all with bank source, markers retained)

Flags with /Od /Ob0 /Og plus /Oi /Ot /Oy /Ow /Oa /G6 /G7 /GF /Gy /Op /GR /GX
/Zi: unchanged 0x2c. /Od /Og /Os, /O1: 253 diffs. Plain /Od: cmp-chain switch
(123 diffs). Unused named local (`int pad[7]`) lands among named locals, not
below temporaries (4 diffs, wrong slots) -> not the mechanism. Pair-copy
spellings (block copy, unblocked, converting `pair<K,R*>` ctor, temporary)
change the hole only via inline-candidate packing; without the inline
`method` none reach 0x48.

## Remaining blocker

`codegen-order/unrepresentable-marker-stream`: retail's 54 marker bytes (and
the label they require to demote codegen) need inline asm, which the clean-C++
rule forbids. If the project ever admits a SecuROM-marker mechanism (e.g. a
reviewed shared macro), `20261106-00077ce0-diag-markers-exact.cpp.txt` is ready: flags
`/DNDEBUG /MD /EHsc /O2 /Ob2`, `// stlport`, key `unsigned long`, inline
`Rva00077C70Receiver::method`. Callee bindings for the map helpers still need
the correct record/value type names before a strict gate can pass.

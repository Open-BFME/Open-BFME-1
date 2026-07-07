# The ZH sweep pipeline (highest-yield path)

BFME forked from **Zero Hour** — `reference/CnC_Generals_Zero_Hour/GeneralsMD/` IS the ZH source
("MD" = Mission Disk), proven binary-side in `reverse/zh_provenance/FINDINGS.md` (51% of ZH-unique
strings appear in lotrbfme.exe vs 4% of Generals-unique). **Always port from `GeneralsMD/`, never
`Generals/`.** Many ZH functions still match BFME verbatim; this pipeline finds and lands them in bulk.

## The loop

```
python3 tools/sweep_generalsmd.py --area GameEngine/Source --skip-done   # hours; resumable
sort -t, -k3 -rn reverse/zh_sweep/report.csv | head -20                  # ranked winners
python3 tools/land_zh.py Dict MessageStream GameAudio                    # land them (basenames)
./build.sh && git add -A src/zh reverse && git commit                    # full verify runs in the hook
```

- **sweep** compiles each never-attempted reference `.cpp` against the reference's own engine
  headers (only Windows/SDK walls are shimmed — `reference/shims/sweep/`), then fingerprint-locates
  every emitted function in the binary (`tools/locate.py`: unique masked placement + callee
  validation; no export entry needed). Appends to `reverse/zh_sweep/report.csv`.
- **land_zh** copies the reference file **verbatim** into `src/zh/` with a 2-line head
  (`// cl:` flags carrying the `/I` include chain + `// stlport`), locates, emits the
  functions.csv/symbols.csv rows, **byte-verifies via build.py**, then marks every drifted sibling
  definition with the `present-unmatched` convention (`tools/zh_annotate.py`) so the pre-commit
  gate passes without pretending they're matched.

## Growing the shims (when the sweep reports blockers)

The sweep summary histograms blockers. Fix the top one, delete its rows from the report
(or rerun without `--skip-done` on those files), re-sweep. Rules learned the hard way:

- Never edit the reference tree. Shadow-patch instead: copy the header into
  `reference/shims/sweep/<same relative path>` and fix it there (shims precede the reference in
  `/I` order). Precedent: `GameClient/Display.h` (a VC6-only default-arg on a function typedef).
- `windows.h` stand-in declarations must be `__declspec(dllimport) __stdcall` with exact SDK
  signatures — that's what makes call-site codegen byte-identical. STLport re-declares some
  (`InterlockedIncrement(long volatile *)`); any signature drift is a C2733 hard error.
- `#define __PLACEMENT_VEC_NEW_INLINE` before `<new>`: GameMemory.h defines array placement
  new itself (its scalar one is commented out, so the CRT's must stay visible).
- Constants in stubs must be the real SDK values (DIK_* scancodes, MB_* flags…) — they compile
  into instruction immediates.

## Traps

- **grep on reference files silently returns nothing** (the © byte makes them "binary"): use
  `grep -a`.
- Quoted includes resolve file-relative *first*: a swept file placed in `src/game/` picks up
  `src/game/prerts.h` instead of the sweep shims. That's why landed files live in `src/zh/`.
- `locate.py` CONFLICT/AMBIGUOUS lines are conservative skips, not errors — leave them; never
  hand-force an address.
- A landed file whose excised/annotated sibling was *inlined* by a matched function will fail the
  byte-verify — land_zh reverts it; reconcile manually or drop that file.
- The pre-commit hook runs the full build (several minutes); don't bypass it, budget for it.

## State

`reverse/zh_sweep/report.csv` is the sweep ledger (resumable via `--skip-done`).
`src/zh/` files are verbatim ZH sources: reconciling a `present-unmatched` sibling against the
binary is a normal `docs/matching.md` task afterwards — start from the ZH text, not from scratch.
147 files exist ONLY in ZH (never in Generals): ranked candidates in `reverse/zh_provenance/FINDINGS.md`.

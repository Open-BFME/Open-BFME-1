# Agent `translate-fx`: translate the FX particle system asm → C++

**Read `plans/deepseek/README.md` first.** Your agent name is **`translate-fx`**. Your
**exclusive** file ownership:

- `src/game/fx_particle_system_bulk.cpp`  (~299 naked blocks — big)
- `src/game/fx_particle_system.cpp`  (~5 naked blocks)

No other agent edits these files. Goal: replace `__declspec(naked)` asm blocks
with real C++ that MSVC 7.1 compiles to the **identical bytes**. The
`reverse/functions.csv` rows stay unchanged (same name/rva/size) — you only change
the `.cpp` source.

## Loop

1. `python3 tools/list_naked_candidates.py src --all` and focus on YOUR file(s).
2. Pick one naked block. Read its asm and mangled name. Write equivalent C++.
   - Study already-converted functions in the **same file/family** for the idiom
     (this repo already converted ~40 of these — copy their shapes).
   - Reference logic (drifted, the binary is truth):
     `reference/CnC_Generals_Zero_Hour/` matching source.
3. `./build.sh src/game/<file>.cpp` (or `src/math/…`).
   - **green** → keep it.
   - **red** → `python3 tools/explain_mismatch.py '<mangled>'`, try ≤3 shapes
     (see `docs/matching.md` for MSVC scheduling traps). Still red → **restore the
     exact original naked block** and SKIP (log it). **Never leave the file red.**
4. Commit via the README's SAFE PUSH RITUAL. Update `PROGRESS-translate-fx.md`.

The easy blocks are largely done; the remainder is hard MSVC-scheduling / vtable /
allocator asm. Real yield is picking off the tractable stragglers — SKIP freely,
never spin, never fake with asm as the "answer".

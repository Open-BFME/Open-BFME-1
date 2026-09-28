# Structural reconciliation (manual RE)

Drift rows classed `structural` or `register-swap` have source that compiles
to a different shape. Expect 30-60 minutes per function.

1. `python3 tools/next_work.py --tier structural` draws one candidate. Start
   from any `stash:` body it prints (it reached the score shown).
2. `python3 tools/explain_mismatch.py '<sym>' --rva <rva> --size <size> --source <src>`.
   Read the classification line before the disassembly.
3. Fix in this order; earlier classes mask later ones:
   a. **Unresolved REL32 call**: `python3 tools/decode_calls.py <src> --rva <rva>`
      prints the `symbols.csv` pins. Add them and re-explain.
   b. **Misplaced candidate**: target bytes opening like another function's
      tail (`ret`/`int3` within a few bytes) mean the drift vote shifted. Find
      the true start in `targets/game/reverse/ghidra_functions.csv`; where
      Ghidra merged functions, trust a `ret` boundary plus export evidence.
   c. **Field-offset diffs** (`[reg+0xNN]` vs `[reg+0xMM]`, same shape): BFME
      relaid a struct, or retail has a real bug. Change the member access (the
      header only when verified siblings permit), then byte-verify the file.
   d. **Literal diffs** (immediates, string addresses): fix the constant.
   e. **Shape diffs** (branch layout, register choice, inlining): try early
      return versus nesting, inverted arms, hoist/sink, declaration order,
      temp versus re-read, split/merge conditions. Stop chasing x87 operand
      order or register renames after two attempts.
4. If exact, `python3 tools/add_match.py '<sym>' <rva> <size> <src> --model <model>`
   validates, appends, strips the marker and re-verifies; commit it.
5. If not, bank it and revert (record `blocked` if nothing is worth banking);
   keep no nonmatching body in `game/`:
   `python3 tools/re_log.py record '<sym>' <rva> <size> partial '<diff> t=<min> model=<model> blocker=<family>' --stash <src> --score <0..1>`

An interior-only body is probably inlined; compiler-only machinery (SEH
array-constructor, `_initterm` stubs) may need the naked-assembly precedent.
Either way, verify the evidence, revert and take another candidate.

When this queue thins, `python3 tools/next_work.py --tier ghidra` serves
string-anchored absent functions under the same rules.

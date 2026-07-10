# Structural reconciliation — the manual-RE workflow

For drift rows classed `structural`/`register-swap` (and parked unmatched ledger
rows): the source exists but compiles to differently-shaped code. This is real
reverse engineering; expect ~30-60 min per function, not minutes. It is also
most of what remains of this game.

## The loop for ONE function

1. Take a candidate from `python3 tools/next_work.py --tier structural`
   (highest aligned% = closest to matching). Read its `[tried Nx: ...]` note —
   do not repeat a logged approach.
2. `python3 tools/explain_mismatch.py '<sym>' --rva <candidate_rva> --size <size> --source <src>`
   Read the classification line first, then the side-by-side disasm.
3. Fix in dependency order — earlier classes mask later ones:
   a. **unresolved REL32 call** — resolve callees FIRST:
      `python3 tools/decode_calls.py <src> --rva <candidate_rva>` prints the
      symbols.csv pins. Add them, re-explain; the real diff often shrinks
      dramatically or vanishes.
   b. **misplaced candidate** — if the first target bytes look like another
      function's tail (`ret`/`int3` within a few bytes), the drift vote is
      shifted. Find the true start in `reverse/ghidra_functions.csv` (but
      ghidra merges some splits — trust a `ret` boundary + the export table
      over either single source).
   c. **field-offset diffs** (`[reg+0xNN]` vs `[reg+0xMM]`, same instruction
      shape): BFME changed a struct layout — or the retail code has a genuine
      bug. Verified example: retail's SegLineRenderer inline getters are
      field-SWAPPED; replicating the bug matched both ParticleBufferClass
      getters. Change the member access (or header layout, if no matched
      sibling depends on it), byte-verify the WHOLE file after.
   d. **literal diffs** (immediates, string addresses): fix the constant.
   e. **shape diffs** (branch layout, register choice, inlining): the hard
      class. Levers that provably move MSVC 7.1 codegen, try in this order:
      early-return vs nested-if restructuring; swapping `if`/`else` arms with
      inverted condition; hoisting/sinking a common subexpression into a
      local; local variable declaration order (register allocation follows
      first-use order); replacing a temp with a re-read (or vice versa);
      splitting/merging compound conditions (`&&` chains emit in source
      order). Do NOT chase x87 operand order or pure register renames beyond
      two attempts — docs/matching.md's negative patterns list the known
      dead ends.
4. Byte-verify: candidate matches -> `python3 tools/add_match.py '<sym>' <rva> <size> <src>`
   (validates, appends, strips the marker, re-verifies). Then the loop's
   commit-pull-push from AGENTS.md.
5. **Log the attempt WHATEVER happened** (this is not optional — unlogged
   failures get re-paid by the next agent):
   `python3 tools/log_attempt.py '<sym>' <landed|no-match|dead|blocked> 'note'`
   For `dead`, the note must carry the proof (e.g. "inlined at all 3 call
   sites, no standalone body" / "SEH prologue not emittable from C++").

## Judging "dead"

* Body appears only inside other functions' bodies -> inlined; log `dead`.
* Identical bytes already claimed by another symbol -> ICF fold; the address
  belongs to whoever byte-verified first; log `dead` with the owner's name.
* Needs compiler machinery C++ can't request (SEH array ctor prologue,
  `_initterm` stubs) -> log `dead` unless you find the whale-style asm route
  (see reverse/whale_*/ for the naked-asm precedent).

## Escalation beyond drift rows

When the structural queue thins: `reverse/zh_sweep/drift_report.csv` class
`absent` (BFME rewrote the function — reconstruct from the binary via ghidra
+ string anchors in `reverse/string_xrefs.tsv`), and the parked rows listed
in `reverse/unclaimed_sources_whitelist.txt`. Same loop, same logging.

# Data coverage: the other half of a 1:1 rebuild

`tools/progress.py` measures the code section. A clean link of lotrbfme.exe
also needs every byte of `.rdata` (2.3 MB) and `.data` (0.7 MB). Until
2026-09-15 nothing measured those. `tools/data_coverage.py` does, and it is
deliberately a SEPARATE tool with its own denominator: it never feeds the
headline, progress.py never imports it, and a test enforces that. Do not add
the two percentages together.

    python3 tools/data_coverage.py            # summary, ~5 s, no compiler
    python3 tools/data_coverage.py --todo 20  # largest globals needing a definition
    python3 tools/data_coverage.py --json

## What the buckets mean

- **comes free from code we hold** -- string literals, vtables, switch tables,
  small constants and zero-initialised blocks referenced only by landed C++
  (authored, vendored, generated) or attached libraries. The compiler emits
  these from that source, so a link reproduces them with no extra work.
- **global data, needs a source definition** -- referenced by landed C++ but
  not something the compiler emits by itself: a hand-written table or
  initialised global. Each needs a C++ definition whose bytes match retail.
  This is the fleet-shaped work on the data side (`--todo` lists it).
- **... referenced only by dumps/unclaimed** -- the same two classes, but the
  referencing code is still a dump. They move to the buckets above as those
  bodies convert; nothing to do on the data side yet.
- **referenced-from-data-only** -- reachable only through pointers in other
  data (string pointer tables, nested structures). Needs attribution work
  before it can be assigned.
- **outside this measure** -- `.idata` (falls out of linking with the right
  libraries), `.rsrc` (copy from retail), STLPORT_, and a 737 KB unnamed
  trailing section that is most likely copy protection and cannot be
  recompiled: the 1:1 target must decide whether it is in scope.

## Limits

The reference scan is a 4-byte byte scan, not a disassembly (the same method
`tools/fleet/vtable_rank.py` uses), so a coincidental immediate can create a
false site. Extents are gap-derived: an object nothing references is folded
into the extent before it, and composition (mostly strings / mostly pointers /
mostly zero) decides the class of a long extent. Read the numbers as a map of
where the data work is, not a byte-exact ledger. Baseline figures are in
`docs/baseline-2026-09-15.md`.

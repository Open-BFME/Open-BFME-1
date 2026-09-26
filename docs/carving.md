# Carving unclaimed `.text`

`tools/carve_unclaimed.py` serves a second anonymous lane for bytes that are
not covered by `targets/game/reverse/functions.csv`. A carved row is a temporary boundary
claim, not an identity claim. Its name is `?d_%08x@@YAXXZ`, its source is
`targets/game/reverse/carved.csv`, and `eligibility.carved_rows()` removes it as soon as a
new ledger row covers its range.

## Evidence and columns

The carver merges every ledger interval, subtracts it from the retail `.text`
section, removes `0xCC` padding runs, and emits only candidates with positive
evidence:

| Column | Meaning |
| --- | --- |
| `rva`, `size` | The decoded body extent; the serving layer derives the address-based anonymous name. |
| `start_evidence` | `rel32-call/jmp` means a direct relative call or jump landed at the start; `ghidra-start` is an advisory inventory start. |
| `callers` | Number of direct REL32 call/jump sites that targeted the start. |
| `end_evidence` | A decoded `ret` or tail `jmp` before padding/end, or a Ghidra extent. |
| `ghidra` | The advisory Ghidra name when one exists; empty means the name is unknown. |

Every candidate goes through `BoundaryValidator.check_start`,
`check_end`, and its padding check. Candidates crossing a known function,
an internal `int3` run, a claimed range, or another carved candidate are
discarded. Absence from Ghidra never rejects a start. Regeneration is
deterministic and shrink-on-land.

## Working a carved row

Use the same workflow as an anonymous body. Start with the retail boundary
(`tools/dis_retail.py`), then read the evidence pack:

```text
python3 tools/brief.py --rvas 0x003B92D0
python3 tools/callees.py 0x003B92D0 296
```

Keep the address token in the name unless a caller, vtable, string, layout, or
other independent evidence proves a real identity. Write clean C++ under its
official `game/` path and land it with the ordinary `tools/add_match.py`
command. A partial reconstruction is banked with `re_log.py --stash`, just as
for a dump body; no carved-specific ledger exception is needed.

`tools/fleet/pick_anon.py` includes carved rows in its expected-bytes ranking.
`tools/next_work.py --tier carved` selects only this lane, and the default
queue checks it immediately after the finish tier. `brief.py` and
`context_pack.py` resolve carved addresses so callers through an ILT thunk,
strings, vtables, witnessed layouts, and landed neighbours remain available.

## Live pool measurement

Before the proof landings the ledger reported **1,147,215** unclaimed
non-padding `.text` bytes; the three five-byte landings leave **1,147,200** in
the live `progress.py` denominator. Running `python3 tools/carve_unclaimed.py
--summary` on this checkout produced
7,688 positive-evidence candidates covering 760,051 bytes (the three proof
landings removed three five-byte candidates):

| Size band | Candidates | Candidate bytes |
| --- | ---: | ---: |
| 32-299 B | 7,099 | 85,193 |
| 300-999 B | 397 | 217,258 |
| 1,000-2,499 B | 140 | 224,768 |
| 2,500+ B | 52 | 232,832 |
| **Total** | **7,688** | **760,051** |

The candidate total is a measured, evidence-backed subset of the larger
unclaimed denominator; bytes without a positive start and end remain unserved
until later evidence appears.

## Ends are decoded, never taken from Ghidra

The first eight served candidates whose end came from Ghidra's function size
were all refuted as `no-boundary` on 2026-09-16 (0x003A2700, 0x003FEBB0,
0x003ED070, 0x003E6EE0, 0x004CC980, 0x00713780, 0x000DA610, 0x0068C400): Ghidra
stops 3 to 13 bytes before the real `ret`, inside the epilogue. Since then the
carver takes an end only from a decoded terminal instruction: `ret+int3` /
`jmp+int3` (terminal followed by padding) or `ret-tail` / `jmp-tail` (terminal
immediately before the next positive start or the gap end, no padding between).
A Ghidra start with no decoded terminal before the next fence is not served.
Regenerating after the fix re-carved all eight at exactly the sizes the
refutations measured.

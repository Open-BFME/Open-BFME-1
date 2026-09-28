# Carving unclaimed `.text`

`tools/carve_unclaimed.py` serves a second anonymous lane: bytes that no row
in `targets/game/reverse/functions.csv` covers. A carved row is a temporary
boundary claim, not an identity claim. It is named `?d_%08x@@YAXXZ`, lives in
`targets/game/reverse/carved.csv`, and `eligibility.carved_rows()` drops it as
soon as a ledger row covers its range.

## Evidence and columns

The carver subtracts every ledger interval from retail `.text`, removes `0xCC`
padding runs, and keeps only candidates with positive evidence at both ends:

| Column | Meaning |
| --- | --- |
| `rva`, `size` | The decoded body extent. The anonymous name derives from the address. |
| `start_evidence` | `rel32-call/jmp`: a direct relative call or jump lands on the start. `ghidra-start`: an advisory Ghidra inventory start. |
| `callers` | Number of direct REL32 call/jump sites that target the start. |
| `end_evidence` | A decoded terminal: `ret+int3`/`jmp+int3` (followed by padding) or `ret-tail`/`jmp-tail` (immediately before the next positive start or the gap end). |
| `ghidra` | Ghidra's advisory name, if any; empty means unknown. |

Ends are never taken from Ghidra: its sizes stop short of the real `ret`,
inside the epilogue. A Ghidra start with no decoded terminal before the next
fence is not served, but absence from Ghidra never rejects a start.

Every candidate passes `BoundaryValidator.check_start`, `check_end` and its
padding check. A candidate crossing a known function, an internal `int3` run,
a claimed range or another carved candidate is discarded.
`python3 tools/carve_unclaimed.py` regenerates the file deterministically and
prints counts by size band; landed ranges drop out.

## Working a carved row

Work it like any anonymous body. Start from the retail boundary
(`tools/dis_retail.py`), then read the evidence pack:

```text
python3 tools/brief.py --rvas 0x003B92D0
python3 tools/callees.py 0x003B92D0 296
```

Keep the address token in the name unless a caller, vtable, string, layout or
other independent evidence proves the identity. Write clean C++ at its
official `game/` path and land it with the ordinary `tools/add_match.py`
command. Bank a partial reconstruction as for a dump body:
`re_log.py record ... partial ... --stash <file> --score <0..1>`.

`python3 tools/next_work.py --tier carved` serves only this lane; the default
queue checks it right after the finish tier. `tools/fleet/pick_anon.py`
includes carved rows in its expected-bytes ranking. `brief.py` and
`context_pack.py` resolve carved addresses, so callers through an ILT thunk,
strings, vtables, witnessed layouts and landed neighbours stay available.

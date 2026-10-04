# drawTrapezoidWater: loop-end lifetime probes, 2026-10-04

RVA `0x007A8FF0`, 4,953 bytes. This session tested a bounded hypothesis:
explicitly materializing the index-fill loop ends might change the lifetime
and reload order of the spilled outer bound. It did not improve the bank.
There is no production conversion or new binding in this result.

## Fresh control and original evidence

The control was the preferred bank at commit
`91af3cfb8f5b3bd0a7cf19017461901bd8cedbcc`:
`targets/game/reverse/attempts/0x007a8ff0.cpp`, SHA256
`d55ff67d4db990329ea1eb4d58d6867659db49abc127d6fa3a0a3f29aa605eb1`.
Original MSVC 7.1 through Wibo reproduced 4,953 bytes and 233 relocations,
with four non-relocation byte differences at offsets `0x2BB`, `0x2BD`,
`0x2BF`, and `0x2C1`. The bank's old ten-difference header is stale.
Its `vVec2 -= Vector3(uVec1)` temporary already fixes the x87 length order;
that expression was retained in every probe.

An actual Ghidra 12.1.2/PyGhidra MCP stdio session freshly read all 4,953
original bytes, decompiled the body, listed its xrefs, and disassembled the
index-loop window. The project copy was opened read-only and closed with
`save=False`. The full byte response equals the pinned retail PE
(`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`).
The body's SHA256 is
`ff26326bd92777e9e010fc2b3e4eaccb4fc8f119345ba9f5797f069aa8857ccf`.
It ends in `ret 8` at `+0x1356`. Caller RVA `0x007AA820` and the GeneralsMD
`W3DWater.cpp` algorithm remain the identity/argument evidence; the
decompiler's inferred C types are not ABI or matching proof.

The original index loop establishes these live values:

- EBP is the incremented `uCount`, saved at `[esp+0x50]`.
- ESI is `j`, saved at `[esp+0x14]`.
- EBX holds `vCount-1`, saved at `[esp+0x10]`.
- EDI holds `rectangleCount`, saved at `[esp+0x18]` before construction.
- The inner loop borrows EBX and EDI for the two row-index products, then
  restores the loop and post-loop values.

At the inner-loop exit, original and bank have the same register assignments
and stack slots. Only two independent loads are exchanged:

| Offset | Retail | Bank |
| --- | --- | --- |
| `+0x2B6` | `mov esi,[esp+0x14]` | same |
| `+0x2BA` | `mov ebx,[esp+0x10]` | `mov edi,[esp+0x18]` |
| `+0x2BE` | `mov edi,[esp+0x18]` | `mov ebx,[esp+0x10]` |
| `+0x2C2` | `inc esi` | same |
| `+0x2C3` | `cmp esi,ebx` | same |

## Tested shapes

All probes retain the original algorithm and compiler options. Locals below
are real values used by their loop condition, not padding or dead code.
All resulting objects are 4,953 bytes with 233 relocation records.

| Probe | Source change within the index-fill work | Differing non-relocation bytes | Misaligned relocation sites |
| --- | --- | ---: | ---: |
| control | unchanged preferred bank | 4 | 0 |
| outer end | `const Int vEnd=vCount-1` after `curIb`; outer loop uses `vEnd` | 17 | 0 |
| inner end | `const Int uEnd=uCount-1` before outer loop; inner loop uses `uEnd` | 2148 | 81 |
| outer then inner | both ends before outer loop, outer declared first | 2148 | 81 |
| inner then outer | both ends before outer loop, inner declared first | 2148 | 81 |
| outer split, early declaration | declare `vEnd` before `rectangleCount`; assign after `curIb` | 17 | 0 |
| outer split, indices declaration | declare `vEnd` with `i,j`; assign after `curIb` | 17 | 0 |
| outer before lock | initialize outer end before `WriteLockClass` construction | 49 | 1 |
| outer before buffer | initialize outer end before `DynamicIBAccessClass` construction | 170 | 2 |
| inner in outer | initialize inner end inside each outer-loop iteration | 13 | 0 |
| outer preincrement value | `const Int vEnd=vCount++` replaces the separate increment | 1378 | 39 |

The 13- and 17-difference forms still restore EDI before EBX at the same
offsets. Naming the outer end also swaps the initial outer-bound/index spill
stores at `+0x264/+0x268`; it does not swap the desired reloads. Those nearby
forms disturb the x87 component/lighting schedule despite preserving the
existing Vector3 copy expression. Hoisting the inner end changes register
pressure, stack layout, and instruction alignment considerably.

Numbers from layout-divergent probes are diagnostic masked-byte counts,
not a strict match score: COFF relocation sites no longer correspond to
the same retail operands at the listed number of positions. No candidate
was exact, so none was sent to `add_match.py` or advertised as passing the
233-site strict relocation audit.

## Outcome and remaining scope

Keep the existing four-difference bank. These ten loop-bound materialization
shapes are negative evidence, not proof that all source lifetime or
front-end forms are exhausted. The earlier broad rotation sweep was
cancelled, not exhausted; this session did not repeat it. No flags,
precision controls, assembly, volatile shaping, headers, resolver logic, or
pins were changed.

The two shader helpers at `0x007A6AA0` and `0x007A7240` already have matched
providers. Their existence is not a blocker and is not new matching credit.
If a future source shape becomes exact, use their current canonical
declarations and prove any required route binding independently before the
full strict gate. This session did not reclaim or modify either helper.

# Rva009A8880Release calls the free thunk at 0x009A5980

`Rva009A8880Release` (0x009A8880, 129 B, `Rva009A8880Release.cpp`) frees four
buffers. Its four `call rel32` sites (+0x14, +0x27, +0x3A, +0x4D) all land on
**0x009A5980** in retail, not on 0x009A58E0.

| address | ledger row | body |
|---|---|---|
| `0x009A5980` | `?Rva009A5980@@YAXPAX@Z` (`BfmeReleaseSetBZB.cpp`) | 5-byte separately padded tail jump, `route=0x009A58E0` |
| `0x009A58E0` | `?bfmeGo930C@@YAXPAX@Z` (`BfmeConv930.cpp`) | 29-byte free body the thunk jumps to |

The source spelled the callee `bfmeGo930C`, so the object's relocations named
the 0x009A58E0 body; the byte gate masks call displacements, so it still
matched, but the link census's retail-truth check (`link_census.RetailTruth`)
saw every call land on 0x009A5980 and judged the copy wrong. The callee is
therefore the matched `Rva009A5980` row, an address-derived name, and
`bfmeGo930C` remains the correct name of the 0x009A58E0 body it forwards to.

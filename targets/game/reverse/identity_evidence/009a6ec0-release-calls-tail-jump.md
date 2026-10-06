# 0x009A6EC0 calls the tail jump at 0x009A5980, not 0x009A58E0

`?Rva009A6EC0Release@@YAXPAPAX@Z` (0x009A6EC0, 94 B) makes three direct
calls. In the retail baseline (`retail-1.03-unpacked`) all three land on
0x009A5980:

| call site    | rel32 target |
|--------------|--------------|
| 0x009A6EDA   | 0x009A5980   |
| 0x009A6EF9   | 0x009A5980   |
| 0x009A6F10   | 0x009A5980   |

0x009A5980 is `E9 5B FF FF FF`, a 5-byte `jmp 0x009A58E0`, ledgered as its own
matched row `?Rva009A5980@@YAXPAX@Z` (BfmeReleaseSetBZB.cpp, route=0x009A58E0).
0x009A58E0 is a different body, `?bfmeGo930C@@YAXPAX@Z` (BfmeConv930.cpp).

The source formerly declared and called `bfmeGo930C`. The byte gate accepted
that through the route, but it names the wrong callee: link_census's
RetailTruth judged the copy `wrong` because each relocation must land where
retail's call lands. The source now calls `Rva009A5980`, and the verdict is
`retail`.

This is not a rename of one function: `bfmeGo930C` keeps its name and row.
The name_regression checker pairs the removed `bfmeGo930C` identifier with the
added `Rva009A5980` one; the two are different addresses.

# 0x00664680 string result and cleanup C440C8

Retail parent 0x00664680 is 153 bytes: RET 4 at 0x00664716 ends at
0x00664719, followed by INT3. Ghidra raw bytes agree with the unpacked PE.
The object in ECX supplies integer fields at +0 and +4; negative first values
add 0x10000. The format string at VA 0x0111A248 is `%d(%d)`.

The actual direct callees establish the string identity independently:
- 0x006646CD calls StringBase<char> construction from text at 0x00888BC0.
- 0x006646D7 calls canonical AsciiString::format at 0x00888FF0.
- 0x006646EA copies to the hidden result via StringBase<char> at 0x00887B60.
- 0x00664700 releases the local via canonical releaseBuffer at 0x00887940.

The previous local StringBaseNarrowAH/AsciiStringAH pair is a synthetic alias
of those existing canonical types, not another retail identity. Its generated
cleanup required an unproven AsciiStringAH destructor alias. Including the
canonical header and using AsciiString eliminates this false dependency.

No full owner/method name is supported: BfmeFrameAH::bfmeLabelAH was a legacy
Bfme<Role><Suffix> placeholder. Neither symbols.csv nor another native TU
names that method; the call index finds no direct caller to the body or its
ILT 0x0002D385. Therefore the owner/method are retained conservatively as
Rva00664680::method, rather than giving the formatting behavior an invented
semantic identity. Existing field identifiers are retained; no new layout
semantics are asserted. name_oracle has no witnessed layout for this owner.

Ownership of cleanup 0x00C440C8 is independent of adjacency:
parent prologue push at 0x00664682 -> handler0x00C440E1 ->
FuncInfo0x00E33950 -> unwind map0x00E33940 state0 predecessor-1 -> C440C8.
It tests EBP-14 mask1, clears that bit, loads the hidden result at EBP+4,
and tail-jumps through ILT0x0000D828 to canonical AsciiString destructor
0x0005EE90. Its conditional RET is 0x00C440E0, proving all25 bytes.
The canonical parent first reproduced all153 instruction bytes in scratch;
the production parent and action must both pass strict relocation verification.

Rebase integration: master already changed AsciiStringAH to derive from canonical
AsciiString (67fca66cad). The remaining synthetic return-type wrapper still has
no independent identity. Retain the canonical AsciiString result directly and
the proven cleanup; no distinct function from master is removed.

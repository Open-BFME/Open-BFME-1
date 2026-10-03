# Include the player rank return in its matched extent

The 464-byte claim at RVA 000D7E30 ends after MOV AL,1 at 000D7FFE..000D7FFF. Retail continues with POP ESI at 000D8000, ADD ESP,10h at 000D8001..000D8003 and RET 4 at 000D8004..000D8006. INT3 starts at 000D8007, establishing the complete 471-byte body. The rank-change comparison JE at 000D7FEF and the final call at 000D7FF8 both reach the shared epilogue starting with POP EDI at 000D7FFD. All direct branches stay inside the decoded stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA004D7FE0 independently agree.

The existing native Player_setRankLevel.cpp already emits the omitted tail. Verify the complete body, scoped siblings and references without changing any source, pin or inherited identity. This correction establishes the extent only.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

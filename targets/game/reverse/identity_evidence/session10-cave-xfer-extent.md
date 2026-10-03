# Include the cave transfer return in its matched extent

The old 336-byte claim at RVA 00378A70 ends after ADD ESP,18h at 00378BBD..00378BBF, omitting RET 4 at 00378BC0..00378BC2. INT3 padding starts at 00378BC3, proving a complete 339-byte body. The loop exit at 00378BAD falls through the common epilogue at 00378BAF; the zero-count branches at 00378AD5 and 00378B3D also reach that epilogue. All 11 direct branches target decoded instructions inside the complete stream, with no overlapping matched row. Local retail PE/Capstone and Ghidra read_memory VA00778BA0 agree.

The existing native CaveSystem.cpp emits the omitted return. Extend only the ledger extent and verify the full body, scoped sibling/caller claims and complete references. Source, pins and inherited identity stay unchanged.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

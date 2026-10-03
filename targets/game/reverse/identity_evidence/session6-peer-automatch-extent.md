# Complete the Peer auto-match entry epilogue

The old 308-byte claim at RVA 00859560 stops after POP ESI at 00859693. Retail continues with POP EBP; POP EBX; RET at 00859694..00859696, followed by INT3 padding at 00859697. Guard exits reach the shared epilogue at 00859692. The full entry-to-return extent is 311 bytes. Local PE/Capstone and Ghidra read_memory at VA 00C59680 agree, and no other live claim overlaps this complete interval.

The existing peerMainBlockingOperations.cpp native emission matches all 311 bytes with its original bindings. Its header identifies the adapted GameSpy Peer SDK peerMain.c 2007 source. Preserve peerStartAutoMatchWithSocketA and every existing declaration; only the ledger extent changes, with no padding or new identity claim.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

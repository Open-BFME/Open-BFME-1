# Include the status circle initialization return

The old 377-byte claim at RVA 00725C00 ends after the first byte of ADD ESP,18h at 00725D78..00725D7A. Retail then executes RET at 00725D7B, followed by INT3 padding from 00725D7C. This proves a complete 380-byte executable body. The final call at 00725D64 falls into the saved-register and FS-chain restoration before this stack cleanup. All nine direct branches target decoded instructions inside the span, and no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA00B25D60 independently agree.

The existing native W3DStatusCircle.cpp emits the complete body. Extend only the ledger extent and verify its full emission, scoped sibling/caller claims and complete references. Preserve source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

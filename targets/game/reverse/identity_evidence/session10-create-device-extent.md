# Verify the complete device creation epilogue

The old 436-byte claim at RVA 0090AE60 includes only the first byte of ADD ESP,580h at 0090B013..0090B018. The terminal RET at 0090B019 is followed by INT3 beginning 0090B01A, establishing 442 executable bytes. The final initialization call at 0090B00B and the success MOV AL,1 / POP EDI lead directly into this omitted cleanup. All 17 direct branches target instructions inside the complete decoded stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA00D0B000 agree on the full tail.

The inherited ledger note already cited the terminal RET address, but its numeric size truncated the body. Extend only the claim and verify the existing native dxwrapper.cpp emission, scoped sibling/caller claims and complete references. No source, pin or inherited identity changes.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

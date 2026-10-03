# Include the local real scanner return in its extent

The old 304-byte claim at RVA 009D2970 ends after MOV FS:[0],ECX at 009D2A99..009D2A9F. Retail continues with ADD ESP,18h at 009D2AA0..009D2AA2 and RET 4 at 009D2AA3..009D2AA5. INT3 starts 009D2AA6, proving a complete 310-byte body. The string cleanup call at 009D2A8B falls through the shared epilogue, including the true return-value assignment at 009D2A96. Every direct branch targets an instruction in the full decoded stream; no other matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA00DD2A90 agree.

The existing native LocalFile.cpp emits the full body. Extend only its ledger size and verify all scoped claims and complete references. Preserve source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

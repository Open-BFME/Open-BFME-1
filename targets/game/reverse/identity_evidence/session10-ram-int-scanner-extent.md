# Verify the complete RAM integer scanner boundary

The old 268-byte claim at RVA 009D1DE0 cuts ADD ESP,10h at 009D1EEA..009D1EEC after two of its three bytes. RET 4 at 009D1EED..009D1EEF completes the body at 272 bytes. The separately ledgered next function starts exactly at 009D1EF0 with PUSH -1 and a new FS registration prologue; no alignment gap is required. The final string cleanup at 009D1ED5 reaches the saved-register/FS restoration and this terminal return. All 11 direct branches target instruction starts in the full decoded stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA00DD1EC0 and VA00DD1EE0 independently agree.

The existing native RAMFile.cpp emits the full body. Extend only the numeric ledger size and verify all scoped claims and complete references. Preserve source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

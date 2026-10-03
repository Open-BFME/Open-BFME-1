# Correct the owning heap helper terminal boundary

The old 329-byte claim at RVA 009CCF60 cuts ADD ESP,0Ch at 009CD0A8..009CD0AA after its first byte. RET is at 009CD0AB, not 009CD0A8 as the inherited note stated. INT3 padding begins 009CD0AC and the next body starts 009CD0B0. This proves a complete 332-byte executable span. The final cleanup call at 009CD094 leads into the saved-register/FS restoration and terminal return. All 18 direct jumps target instruction starts inside the complete stream; no matched row overlaps it. Local retail PE/Capstone and Ghidra read_memory VA00DCD090 agree.

The existing native BfmeStepVOU.cpp emits the full body. Correct the numeric size and the contradictory return-address note; verify the full body, scoped sibling/caller claims and complete references. Preserve source, pins and inherited identity.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

# Include the sink transfer epilogue in its matched extent

The old 661-byte claim at RVA 008FB0B0 ends after the seven-byte MOV FS:[0],ECX at 008FB33E..008FB344. Retail continues with ADD ESP,10h at 008FB345..008FB347 and RET 4 at 008FB348..008FB34A. INT3 padding starts at 008FB34B, establishing a complete 667-byte executable body. The final virtual transfer call at 008FB333 falls into this common saved-register/FS epilogue. Local PE/Capstone and Ghidra read_memory at VA00CFB330 independently agree. All direct branch targets stay within the complete decoded stream and no other matched row overlaps it.

The existing native BfmeSinkB::bfmeAccept implementation already emits the complete epilogue. Reverify the full span, all scoped sibling/caller claims and complete references. Preserve its inherited identity, declarations and pins; this finding establishes the boundary only.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

# Retire the truncated cached-bone validator dump

The 3983-byte claim at RVA 00778590 stops immediately before RET 0Ch at 0077951F..00779521. The shared epilogue starts at 00779507, reached directly from 00778618, restores FS and saved registers, and adds 188h to ESP. INT3 starts at 00779522, proving 3986 executable bytes. Local PE/Capstone and Ghidra read_memory VA00B79500 agree on the entire tail. The naked object symbol is _bfme_ModelConditionInfo_validateCachedBones_778590. Its inherited semantic label is not newly validated by this finding. The separate present-unmatched implementation in W3DModelDraw.cpp remains untouched for native recovery.

The source contains exactly 3983 literal __emit bytes equal to retail. All 1118 instructions in the complete 3986-byte stream decode from the entry; every direct jump targets this stream and there are no indirect jumps. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and orphaned dump with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

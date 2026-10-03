# Retire the truncated supply-truck queue dump

The 2330-byte claim at RVA 00165D50 ends at 0016666A, inside ADD ESP,0D0h at 00166666..0016666B. Retail completes that instruction and returns at 0016666C; INT3 begins at 0016666D. This establishes 2333 executable bytes. The shared epilogue at 00166654 restores FS and saved registers before this omitted tail. Local PE/Capstone and Ghidra read_memory VA00566650 independently agree. Retire only the incomplete naked source and its claim; the inherited queueSupplyTruck identity is not newly validated or replaced.

The source contains exactly 2330 literal bytes equal to retail. All 649 instructions in the complete 2333-byte stream decode from the entry; every direct jump targets this stream and there are no indirect jumps. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and orphaned dump with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

# Retire the truncated texture-filter initializer dump

The 438-byte claim at RVA00920D10 ends at00920EC6 inside MOV [01340568],EAX at00920EC3..00920EC7. Retail completes that store, executes the loop JB at00920EC8..00920EC9, pops EDI/ESI/EBX and returns at00920ECD. Two INT3 bytes at00920ECE..00920ECF separate the next entry00920ED0. This proves446 executable bytes. Local PE/Capstone and Ghidra read_memory VA00D20EB0 independently agree.

Retire the truncated naked initializer and its matched row with a tombstone. No replacement body or identity is introduced; full native recovery remains pending.

The removed definition contains exactly 438 literal bytes equal to retail. All 104 instructions in the complete 446-byte executable stream decode from the entry; every direct jump targets this stream. All 0 indirect jumps have independently bounded owned pointer tables whose entries target decoded instructions within this stream. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and its dump definition with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

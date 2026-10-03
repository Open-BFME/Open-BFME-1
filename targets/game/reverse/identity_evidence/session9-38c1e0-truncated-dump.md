# Retire the truncated 0038C1E0 assembly claim

The 2876-byte MASM claim at RVA 0038C1E0 cuts MOV ECX,[ESP+7Ch] at 0038CD19..0038CD1C before its final displacement byte. Retail continues with POP EDI, MOV FS:[0],ECX, POP ESI/EBP/EBX, MOV ESP,EBP, POP EBP, and RET at 0038CD2B. INT3 starts at 0038CD2C, establishing 2892 executable bytes. Branches including the early JZ at 0038C217 reach this final epilogue. Local PE/Capstone and Ghidra read_memory VA0078CD10 agree on the tail. The inherited popSleepyUpdate label is disputed separately; this retirement relies on the independently contradicted extent and does not assign a replacement identity.

The source contains exactly 2876 literal bytes equal to retail. All 825 instructions in the complete 2892-byte stream decode from the entry; every direct jump targets this stream and there are no indirect jumps. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and orphaned dump with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

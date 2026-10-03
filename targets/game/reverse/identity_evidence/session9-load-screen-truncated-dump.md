# Retire the truncated load-screen definition from GameLogic

The 1473-byte claim at RVA 0038D100 cuts MOV FS:[0],ECX at 0038D6BE..0038D6C4 after only three of its seven bytes. Retail continues with POP EBX, ADD ESP,18h and RET at 0038D6C9, giving 1482 executable bytes. The shared epilogue at 0038D6B5 is reached by the final JE at 0038D6AC. After alignment 8B FF, the eight-entry owned switch table occupies 0038D6CC..0038D6EB, giving a complete 1516-byte code-plus-table span followed by INT3. CMP EAX,7 / JA default at 0038D33F/0038D342 bounds the table indexed by the jump at 0038D348; all eight pointers target decoded instructions in this body. Local PE/Capstone and Ghidra read_memory VA0078D6B0 agree.

Remove only the naked GameLogic::deleteLoadScreen definition and its matched row, preserving every other function and the remaining bytes of GameLogic.cpp. Its inherited identity is not newly validated or replaced. The normal scoped build must reverify the retained translation-unit claims; complete native recovery of the retired span remains pending.

The removed definition contains exactly 1473 literal bytes equal to retail. All 391 instructions in the complete 1482-byte executable stream decode from the entry; every direct jump targets this stream. All 1 indirect jumps have independently bounded owned pointer tables whose entries target decoded instructions within this stream. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and its dump definition with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

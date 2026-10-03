# Retire the truncated LAN update dump

The 2030-byte claim at RVA 006870F0 cuts MOV ECX,ESP at 006878DD..006878DE. Retail continues through packet dispatch, temporary-string cleanup, player notification and timed work to the epilogue at 00687A10 and RET at 00687A25. This proves 2358 executable bytes. After two alignment bytes (8B FF), the owned 19-entry pointer table occupies 00687A28..00687A73, giving a 2436-byte code-plus-table extent followed by INT3 from 00687A74. The dispatch at 006871F0 indexes this table after CMP EAX,12h and JA default at 006871E0/006871EA; all 19 pointers target decoded instructions inside this body. Local PE/Capstone and Ghidra read_memory VA00A87A00 independently agree.

This independently corroborates the existing bank and earlier recorded SIB-codegen blocker. Retire the truncated naked provider; preserve the bank, separate native source, pins and inherited identity without claiming the bank is exact. Full native recovery remains pending.

The source contains exactly 2030 literal bytes equal to retail. All 722 instructions in the complete 2358-byte executable stream decode from the entry; every direct jump targets this stream. All 1 indirect jumps have independently bounded owned pointer tables whose entries target decoded instructions within this stream. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and orphaned dump with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

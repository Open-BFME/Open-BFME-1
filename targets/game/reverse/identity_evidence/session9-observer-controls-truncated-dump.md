# Retire the truncated observer-controls initialization dump

The 1047-byte claim at RVA004A9CD0 ends immediately after POP EDI at004AA0E6. Retail continues with POP ESI, POP EBP, MOV FS:[0],ECX, POP EBX, ADD ESP,28h and RET at004AA0F4. INT3 starts004AA0F5, proving1061 executable bytes. The preceding loop exits into the shared epilogue at004AA0E2, which reloads the saved FS chain from[ESP+2Ch]. Local PE/Capstone and Ghidra read_memory VA008AA0D0 independently agree.

Retire only this truncated naked provider and its matched row. The separate ControlBarObserver.cpp native draft remains untouched. This boundary evidence does not newly validate the inherited initObserverControls identity; complete native recovery remains pending.

The removed definition contains exactly 1047 literal bytes equal to retail. All 311 instructions in the complete 1061-byte executable stream decode from the entry; every direct jump targets this stream. All 0 indirect jumps have independently bounded owned pointer tables whose entries target decoded instructions within this stream. The only ledger row intersecting this span is the incomplete claim.

Rule: AGENTS.md File placement requires matched rows backed by real source and byte verification; Verdicts and near misses says "A __declspec(naked)/__emit lift is not a conversion". Severity WRONG: the omitted executable return contradicts the matched extent independently of any naming question. Retire the incomplete claim and its dump definition with a deletion tombstone; complete native recovery remains pending. No new identity or native coverage is added.

Validation: the pre-removal ordinary scoped build reproduces the old prefix. Normal commit checks validate the retirement and remaining ledger. No pins or baselines change; modern progress accounting already excludes this dump from authored C++.

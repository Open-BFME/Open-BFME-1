# RVA 008B0EE0: session4 guard bank

2026-10-03, gpt-6-astra. This remains a partial; no production row, pin or
cleanup claim is added. Start from the current preferred attempt, which now
includes the corrected nonempty allocation cleanup contracts.

The starting source was immutable alternative ba16d5160f1e1d9a2f18d7b7974bd92af3f1cc28f73ccc53570f71a0c444b64b,
not the old preferred source with empty deletes. Fresh probe reproduced7110B,
476 relocations and5076 positional masked differences against7162B retail.

Splitting the first kind/active condition into a named bool before the lookup
keeps both original flags and kind live. It puts these in retail EBP/EBX and
reloads the key from its incoming stack slot; the old bank kept key in EBP and
specialized the fallback branches. The new bank remains7110B but has4779
positional masked differences. Score including52 missing bytes is
1-(4779+52)/7162 =0.325467746439542, improved from0.28399888299357723.
Normalized shape0.892 is diagnostic, not the score or byte proof.

Other bounded trials: owner accessors produce7058B/5036 differences; a kind
accessor and six-bit field leave7110B/5076; a snapshot wrapper produces5102;
a barrier produces4780; a one-case switch equals the named bool4779. The
named bool was kept because it adds no access or barrier. A state getter,
state reference, owner local and outer state declaration all retain4779.
No change to canonical provider definitions, caller semantics, or compiler
flags was used to force the remaining ESI/EDI mirror.

The first remaining divergence is+1B: retail saves EDI then loads owner into
EDI; ours loads owner into ESI before saving EDI. The state and pooled return
values mirror those registers, and broader branch/tail differences remain.
438 relocation sites do not yet align. Existing experimental declarations,
callback/global views and bindings still require independent promotion review;
this positional score cannot prove them.

Fresh Ghidra xrefs identify caller VA00CC3E5A; its decompilation of the parent
agrees with the dispatch and two lookup paths. Raw retail final RET is at
RVA008B292D. Bytes008B292E/F are MOV EDI,EDI alignment; owned switch tables
and remap extend to008B2AD9 before INT3. The complete7162B boundary is retained.
Probe's linear disassembly warning at the tail is table data, not an instruction
extent correction.

Both the latest compiler object and retail parent have35 states with identical
predecessors. Parent prologue+8 -> handlerC58A4F -> FuncInfoE47D14 establishes
the following shard actions (all complete15B ending in RET):

| Action | State | Predecessor | Bytes requested | Saved pointer | Target |
| --- | --- | --- | --- | --- | --- |
| C58850 | 0 | -1 | 16 | EBP+4 | 891A80 |
| C588B2 | 7 | -1 | 36 | EBP+4 | 897670 |
| C5890C | 13 | -1 | 36 | EBP+4 | 897670 |
| C58957 | 18 | -1 | 36 | EBP+4 | 897670 |
| C589A2 | 23 | -1 | 36 | EBP+4 | 897670 |
| C589ED | 28 | -1 | 36 | EBP+4 | 897670 |
| C58A40 | 34 | -1 | 36 | EBP+4 | 897670 |

The native labels are L1814,L1783,L1789,L1794,L1799,L1804,L1808 in that order.
They cannot be promoted while their parent remains unmatched. Scratch probes
and the exact latest object locator are in build/b1/session4/; no production
source was introduced for this investigation.

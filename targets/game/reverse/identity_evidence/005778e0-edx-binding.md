# Score-screen helper: EDX scheduling and call bindings

2026-10-03, n2, model=gpt-6-astra. Complements `005778e0-score-rows.md`.

The bank's two non-relocation differences at +3DF/+3E5 disappear when the
region lookup carries the campaign pointer in EDX through a typed fastcall
adapter. This is an x86 call adapter, not a claim that the target takes an
extra semantic argument. Retail loads campaign VA 012F1028 into EDX, loads
ECX from campaign+28, pushes the name at record+4C, and calls ILT 0002BF0D.
That ILT reaches the independently matched 214-byte member 003C8A50.
Its receiver is ECX; both returns pop four bytes. Its first EDX access writes
EDX before any read. Ghidra creation/decompilation and raw retail decoding
agree. Thus the additional register value does not change the callee ABI,
and the adapter adds no instruction, stack argument, or memory access.

The complete caller now probes 1639/1639 bytes with 65 relocation sites and
zero non-relocation differences. Its final RET is 00577F46 and the following
byte is INT3. Owner evidence remains constructor 00578160 and caller
005780E0 via ILT 000490A8; the method retains its address-derived name.
`ScoreScreenInitGadgets.cpp` supplies the +310 persistent-units list-box name.
The bank's unsupported `CampaignManager` receiver view is now an address-qualified
layout view; the global uses the real `LivingWorldLogic*` declaration backed by
its data row, the GameEngine init label, and the constructor's name vtable.

## Three body pins

The first strict caller gate reported exactly these three missing bindings.
They are pinned at physical bodies, letting the resolver discover their ILTs;
no new thunk-routing aliases or helper ledger claims are introduced.

| Typed call | Retail route | Independent evidence |
| --- | --- | --- |
| `GameLogic::rva00388BE0()` returning `vector<LivingWorldPlayerArmy*>` | 0000D1E8 -> 00388BE0 | Complete 33-byte body takes hidden result storage, adds 170 to its receiver, forwards storage through 00031507 -> 00364E70, returns the original storage in EAX, and ends in RET4. The collection operation and owning return are documented in the existing score-row evidence. A fresh native wrapper emission matches all 33 non-relocation bytes. The prior `BfmeThingDPH` view represented hidden storage as an explicit pointer; its artificial volatile slot is not used here. |
| `Rva00573580Lookup::number(int)` returning `AsciiString` | 0000FD3A -> 00573580 | Complete 158-byte body constructs a numeric ASCII key with `%d`, copies its by-value lookup argument, forwards hidden output storage through 00047992 -> 00572A60, releases the key, returns that output pointer, and ends in RET8. This agrees with the existing `BfmeNumberedLookupAI.cpp` implementation and native owning-string helper in the 00575B70 bank. Fresh emission matches 158 bytes and ten relocation sites. The receiver/method remain address-qualified. |
| native `vector<ScoreRowSortValue>::_M_insert_overflow` | 00037047 -> 005740A0 | Complete body reads the three vector words, grows by max(size,count), copies two words per element, inserts one or count copies, optionally copies the suffix, deallocates old storage, and updates the three vector words. Five stack arguments end in RET14 at +12E, proving 305 bytes; Ghidra's 302-byte body omits alignment. The actual native instantiation freshly probes 305/305 bytes with four allocator relocations. The prior row is an address-only `dup_005740a0` emission alias, not proof of an OCL element identity. The score-row sort and caller establish this eight-byte record use. |

The wrapper/number experiments use native definitions retained in
`attempts/0x00575b70.cpp`; production only declares these already-existing
callees. Their experiment-only `collect`/`lookup` wrapper names are not
production pins or extra definitions. A direct strict helper experiment
reported `collect` unresolved, so its masked wrapper result alone is not
claimed as strict helper verification. Retail decoding supplies the nested
call route and owning-return contract independently.

Replacing all three production calls with member-pointer wrappers was also
tested: it grew the caller to 1693 bytes and is discarded. No such wrapper
specialization is included in the production file. The accepted source keeps
native container/string lifetimes and only changes the region-call register
adapter from the original bank. All other direct calls retain the bank's
existing named bindings and address-qualified ILT adapters.

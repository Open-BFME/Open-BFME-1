# 0x003855F0 transition call routes

The generated row spans 117 bytes through a plain `ret`. Its sole direct caller is the matched `GameLogic::logicMessageDispatcher` at 0x00397540 via ILT 0x00022890. That caller passes its GameLogic receiver in ECX. The retail body keeps that receiver in ESI, forms a subobject at +0x170 in EDI, reads an integer at +0xA8, and makes these direct calls in order:

| Retail call route | Physical target | Observed receiver and argument |
| --- | --- | --- |
| 0x0002C8F9 | 0x00361D10 | `this+0x170` in ECX; no stack argument; target ends in `ret` |
| 0x00031313 | 0x00365DF0 | `this+0x170` in ECX, `this+0xA8` on stack; target ends in `ret 4` |
| 0x00041FF1 | 0x0060D3D0 | singleton at 0x012F706C in ECX; byte predicate matched as `BfmeLivingWorldManager::isCampaignVictorious` |
| 0x00048068 | 0x00612070 | same singleton in ECX, then a tail jump; the matched target is free helper `rva00612070Post` and does not establish a member name |
| 0x0001C46D | 0x00396B00 | saved receiver in ECX, Boolean arguments `1,0`; the clear-game-data body is independently identified by its named message-dispatch caller |
| 0x0000E458 | 0x00366130 | the +0x170 subobject in ECX; matched `BfmeSubBZF::bfmeOneBZF` |
| 0x0001BC75 | 0x003BDC50 | global at 0x012F1028 in ECX; matched `Rva003BDC50::run` |
| 0x00029357 | 0x003BFAB0 | same global in ECX and Boolean zero on stack; matched `Rva003BFAB0::run` |

The `0x00048068` route is represented in the new source by an address-qualified `Rva00048068Dispatch::invoke` call. This asserts only the observed call ABI and ILT address, not a semantic method on the singleton. The first two subobject calls likewise keep their physical target addresses in their names. The new body's original descriptive name is not independently proved, so `Rva003855F0Owner::reset_003855F0` retains its own address token. The typed source probe emits 117/117 instruction bytes with 13 relocation operands. Strict `add_match` resolves ten operands and rejects the three address-qualified routes at 0x0002C8F9, 0x00031313 and 0x00048068 as unresolved. Adding `route=` pins for those signatures fails `pin_consistency --check`: the first two physical targets are generated rows with no established C++ identity, and the third is a distinct matched free helper. Those pins were removed. A future landing needs a source-level call shape or independently proved callee identity that satisfies both the strict relocation gate and pin consistency; byte equality with unresolved relocations is insufficient.

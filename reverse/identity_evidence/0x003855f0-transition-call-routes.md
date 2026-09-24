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

The original member name is not independently proved, so `Rva003855F0Owner::reset_003855F0` keeps its address token. An earlier typed source probe emitted 117/117 instruction bytes, but strict verification could not resolve three local method names to their retail ILTs. Adding `route=` pins failed `pin_consistency --check`: the first two targets are still generated bodies with no established C++ identity, and the third is a distinct matched free helper. Those pins were removed.

The landed source calls the existing `j_0002c8f9` and `j_00048068` thunk symbols through typed `__fastcall` casts to pass their observed ECX receivers. For `j_00031313`, a union of a free-function pointer and a single-inheritance member pointer expresses the observed `thiscall`: ECX carries `this+0x170`, and the integer at `this+0xA8` is pushed on the stack. This union pattern already compiles in `Code/GameEngine/Source/GameClient/GameClientDestructor.cpp`. It keeps a direct relocation to the existing thunk rather than claiming a new semantic callee identity. The scoped `add_match` gate verified 117/117 bytes and resolved all 13 relocations, including these three routes; no new pin was added.

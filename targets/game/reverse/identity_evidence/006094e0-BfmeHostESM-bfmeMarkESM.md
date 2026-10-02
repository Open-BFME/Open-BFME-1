# BfmeHostESM::bfmeMarkESM identity at RVA 0x006094E0

The 94-byte matched body at RVA 0x006094E0 in `game/GameEngine/Source/Common/Open2Conv017.cpp` is the member `void BfmeHostESM::bfmeMarkESM(BfmeThingESM *, int)`. The prior address-derived claim `?Rva006094E0@@YGXPAVOpen26094E0Owner@@D@Z` declared it as a free `__stdcall` function, which gives it the wrong linkage name for its callers.

`targets/game/reverse/symbols.csv` already pins `?bfmeMarkESM@BfmeHostESM@@QAEXPAVBfmeThingESM@@H@Z` to the ILT thunk at RVA 0x00030963, whose five-byte jump reaches RVA 0x006094E0. Two matched callers spell that member: `BfmeHostESM::bfmeRunESM` at RVA 0x00609DA0 (`BfmeConv1975.cpp`) and `Rva003C7B60Owner::create` at RVA 0x003C7B60 (`Rva003C7B60CreateRenderObject.cpp`).

Retail's caller at RVA 0x00609DA0 pushes the flag and the object, then executes `mov ecx, esi` at offset 0x25 before its call at offset 0x27 to ILT 0x00030963. It loads ECX the same way at offset 0x2D before calling ILT 0x00044693, the matched sibling `BfmeHostESM::bfmePrepESM` at RVA 0x00609AC0. This witnesses a thiscall member contract on the same receiver as the neighbouring matched members `bfmePrepESM` (0x00609AC0), `bfmeDoESM` (0x00609BA0) and `bfmeRunESM` (0x00609DA0).

The body itself never reads ECX and returns with `ret 8`, so the member and the former `__stdcall` free function compile to the same bytes. The flag is consumed as its low byte, which the definition expresses as `(char)flag == 0`.

The correction preserves the function body and its exact 94-byte extent. It renames only the local placeholder owner type and the definition's signature to the pinned member. It adds no alias, forwarder, or pin. A changed instruction, a thunk routed elsewhere, or a caller lacking the witnessed ECX member contract would refute this correction.

Raw retail probes are retained locally under `build/rlink/`: `body-disassembly.txt`, `caller-run-disassembly.txt`, `caller-create-disassembly.txt` and `thunk-disassembly.txt`, with the gate logs `gate-owner-final.txt`, `gate-caller-run.txt` and `gate-caller-create.txt`.

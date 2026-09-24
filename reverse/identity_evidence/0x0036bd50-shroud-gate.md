# 0x0036BD50: address-qualified shroud gate

The retail body is 96 bytes and ends in `ret 4`: ECX is a module receiver and one caller-supplied stack word is unused. No named caller, vtable slot, or declaration proves a semantic owner, so the C++ claim keeps `Rva0036BD50` in the class name.

The body reads the owner pointer at `[ecx-4]` and its position at owner+0x38. It checks the logic mode at global 0x012F0898 + 0x10C for 1, 5, or 2; every accepted mode reaches the same query. It obtains the local player from global 0x012ED748 + 0xC and its index at +0x24. The shroud pointer comes from global 0x012ED5BC. The query calls the matched `PartitionManager::getShroudStatusForPlayer` body at 0x008F7430; status 1 triggers the matched ILT 0x000099E9 to `BfmeThing916C::bfmeGo916C` at 0x001C7AE0 with the owner and index. The two callee targets and their argument cleanup were checked against retail before compiling the source.

`Code/GameEngine/Source/Common/Rva0036BD50ShroudGate.cpp` compiled to 96/96 matching bytes with five aligned relocations. The strict `tools/add_match.py` scoped gate resolved all five against existing symbols. No new pin or semantic class assertion was needed.

# 0x009F7256 is the import stub for msvcr71.dll!_CIacos, owned by address

Retail's six bytes at 0x009F7256 are `FF 25 01359230`, `jmp [IAT]` through the
slot retail's import directory assigns to msvcr71.dll!_CIacos (RVA 0x00F59230).
The import library's short import object for that function defines both
`__imp___CIacos` and the call stub `__CIacos`, so a TU that also defines `__CIacos`
links only under /FORCE (LNK2005 in a strict link).

The row keeps the bytes under the address-owned name `?Rva009F7256_CIacos@@YAXXZ` and
its body calls the real import `__imp___CIacos`;
`__CIacos` stays the import library's own name. Proven by
`python3 tools/import_binding.py check game/Libraries/Source/WWVegas/WWLib/Rva009F7256CrtForwarders.cpp` (strict link, no /FORCE).

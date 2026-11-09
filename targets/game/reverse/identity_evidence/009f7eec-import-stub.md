# 0x009F7EEC is the import stub for msvcr71.dll!_XcptFilter, owned by address

Retail's six bytes at 0x009F7EEC are `FF 25 01359258`, `jmp [IAT]` through the
slot retail's import directory assigns to msvcr71.dll!_XcptFilter (RVA 0x00F59258).
The import library's short import object for that function defines both
`__imp___XcptFilter` and the call stub `__XcptFilter`, so a TU that also defines `__XcptFilter`
links only under /FORCE (LNK2005 in a strict link).

The row keeps the bytes under the address-owned name `?Rva009F7EEC_XcptFilter@@YAHKPAX@Z` and
its body calls the real import `__imp___XcptFilter`;
`__XcptFilter` stays the import library's own name. Proven by
`python3 tools/import_binding.py check game/GameEngine/Source/Common/XcptFilterImportThunk.cpp` (strict link, no /FORCE).

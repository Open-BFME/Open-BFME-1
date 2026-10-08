# 0x009F6C2E is the import stub for gdiplus.dll!GdipCloneImage, owned by address

Retail's six bytes at 0x009F6C2E are `FF 25 013591CC`, `jmp [IAT]` through the
slot retail's import directory assigns to gdiplus.dll!GdipCloneImage (RVA 0x00F591CC).
The import library's short import object for that function defines both
`__imp__GdipCloneImage@8` and the call stub `_GdipCloneImage@8`, so a TU that also defines `_GdipCloneImage@8`
links only under /FORCE (LNK2005 in a strict link).

The row keeps the bytes under the address-owned name `?Rva009F6C2E_GdipCloneImage@@YGHPAXPAPAX@Z` and
its body calls the real import `__imp__GdipCloneImage@8`;
`_GdipCloneImage@8` stays the import library's own name. Proven by
`python3 tools/import_binding.py check game/GameEngine/Source/Common/GdipCloneImageImportThunk.cpp` (strict link, no /FORCE).

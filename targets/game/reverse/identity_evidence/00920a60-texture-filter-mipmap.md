# TextureFilterClass::Set_Mip_Mapping at 0x00920A60

BFME 1 has a ten-byte thiscall body between INT3 padding bytes. It takes
one four-byte argument, stores it at this+8 and returns with ret 4.
The matched shroud unit at 0x0071A730 calls it twice immediately after
acquiring its texture filter, with the FILTER_TYPE_NONE argument. The
Zero Hour W3DShroud.cpp counterpart calls Set_Mip_Mapping(NONE) on the
same filter objects. Other BFME 1 callers also pass the matching filter
enum values, and texturefilter.h places MipMapFilter at +8.

Pinned BFME 2 dbde7dbe3be16481b2c8d6f2f9577bc322f6b7ce owns the same setter
in Code/Libraries/Source/WWVegas/WW3D2/texturefilter.cpp at 0x0013ED10
(10 bytes). Its Zero Hour body is the single member assignment. BFME 1
uses its own header and compiler flags. The old Gen_00920a60 ledger row
is a generated setter scaffold. No generated source file was edited.

Compiled object comparison keeps all caller bytes. 15 REL32 call sites now
name the typed retail provider. One unit renumbers compiler-local labels. Its full COFF graph preserves the target sections and offsets.

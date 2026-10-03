# EnvironmentMapperClass::Needs_Normals at RVA 009214C0

The Zero Hour twin in `GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mapper.h`
declares `EnvironmentMapperClass::Needs_Normals` as a public non-const virtual
bool method returning true. The same definition exists in the local canonical
mapper.h and is emitted by the unchanged vertmaterial.cpp constructor provider.

Retail constructor 00921460 calls TextureMapperClass's constructor then stores
table VA 0113BFD8 at 0092146D. That table's independently anchored methods are
slot 1 deleting destructor 00921F80, slot 2 Mapper_ID body 00921480, slot 3 Clone
00921490, slot 5 Apply 00967480 and slot 6 Reset 009213C0. These preserve the
Zero Hour declaration order and place Needs_Normals at slot 7, VA 0113BFF4,
which contains VA 00D214C0. Its complete body is `b001c3`, MOV AL,1; RET,
followed by INT3. Ghidra and the baseline agree on store, entry, body and padding.
Thus the twin and per-family slot alignment prove the full method identity;
the three-byte return value by itself would not.

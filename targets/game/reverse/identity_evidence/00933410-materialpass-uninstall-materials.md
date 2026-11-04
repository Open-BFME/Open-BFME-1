# 0x00933410: MaterialPassClass::UnInstall_Materials

2026-11-04, model=claude-opus-5-5. Link queue #44 (`??_7MaterialPassClass@@6B@`, losers).

## Retail evidence (BFME 1 target)

- `??_7MaterialPassClass@@6B@` is recorded at VA 0x0113C884
  (dir32_addresses.csv); the next recorded table starts at 0x0113C894, so it
  has four slots: ILT 0x00005D5D -> 0x005F38C0 (`?Delete_This@RefCountClass@@UAEXXZ`),
  0x00933570 (`??_GMaterialPassClass@@UAEPAXI@Z`), 0x00933590
  (`?Install_Materials@MaterialPassClass@@UBEXXZ`) and 0x00933410.
- 0x00933410 is a one-byte `ret` (previously `?Rva00933410Noop@@YAXXZ`). A scan
  of the whole retail image finds exactly one dword pointing at it: the
  table's slot 3 at VA 0x0113C890. Retail has no identical-COMDAT folding.
- It lies in the matpass.cpp run: ctor 0x009333A0 (104 B, ends 0x00933408),
  this body, dtor 0x00933420, Get_Material 0x00933530, deleting dtor 0x00933570,
  Install_Materials 0x00933590.

## Source evidence

Zero Hour `GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/matpass.h` (also
BFME 1's `game/Libraries/Source/WWVegas/WW3D2/matpass.h`) declares, after
the destructor, `virtual void Install_Materials(void) const;` and
`virtual void UnInstall_Materials(void) const { };` -- the third and fourth
virtual slots after RefCountClass's Delete_This and the destructor.

## Repair

MaterialPassClassDestructor.cpp's local view declared only the destructor, so
it emitted a two-slot `??_7MaterialPassClass@@6B@` COMDAT (the link-queue
loser). Adding the two virtuals reproduces the four-slot table, and its inline
`UnInstall_Materials` COMDAT takes the 0x00933410 row.

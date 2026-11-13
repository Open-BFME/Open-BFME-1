# 0x0095C860 is StreakRendererClass::operator=

Previous row: `??4Rva0095C860@@QAEAAV0@ABV0@@Z` (address-derived, 140 B,
game/GameEngine/Source/Common/TextureRefAssignOperators.cpp).
Corrected name: `??4StreakRendererClass@@QAEAAV0@ABV0@@Z`.

## BFME 1 target evidence

- The matched `??0StreakRendererClass@@QAE@ABV0@@Z` (0x0095FE50, 145 B,
  game/Libraries/Source/WWVegas/WW3D2/StreakRendererCopyCtor.cpp) ends its
  member initialisation with `*this = that`, which retail encodes as a direct
  `call 0x0095C860` at +0x78. A matched caller naming the symbol is the
  strongest naming evidence; symbols.csv already pinned
  `??4StreakRendererClass@@QAEAAV0@ABV0@@Z` at 0x0095C860 from the
  StreakLineClass::operator= call displacement.
- The body is a one-argument thiscall returning `this` (`mov eax,esi; ret 4`)
  with a self-assignment guard, an inline add-ref (16-bit `inc` at +4) of the
  source's pointer at +0 and an out-of-line release of the old one: the
  `REF_PTR_SET(Texture, that.Texture)` shape. It then copies every dword
  from +0x04 to +0x40 and leaves +0x44/+0x48 alone, which is the
  StreakRendererClass layout the copy constructor initialises (Shader +0x04,
  Width +0x08, Color +0x0C, Opacity +0x18, SubdivisionLevel +0x1C,
  NoiseAmplitude +0x20, MergeAbortFactor +0x24, TextureTileFactor +0x28,
  LastUsedSyncTime +0x2C, CurrentUVOffset +0x30, UVOffsetDeltaPerMS +0x38,
  Bits +0x40; m_vertexBufferSize +0x44 and m_vertexBuffer +0x48 are "don't
  modify" in Zero Hour's operator=).

## Reference evidence (lead, not proof)

- Zero Hour GeneralsMD streakRender.cpp:102 defines the same guarded
  operator=, copying the same members but with TextureTileFactor,
  LastUsedSyncTime and the two UV vectors commented out; BFME 1 copies them.
- BFME 2 donor f6c3838e7b `reverse/functions.csv` rows
  `??4StreakRendererClass@@QAEAAV0@ABV0@@Z` at its 0x00743100 (141 B,
  Code/Libraries/Source/WWVegas/WW3D2/streakRender.cpp), noting the restored
  UV state: the same BFME-era change.

Bytes are unchanged by the rename; the class view in
TextureRefAssignOperators.cpp keeps its scalar field names.

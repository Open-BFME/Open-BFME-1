# 0x003D3A00 is vector<unsigned int>'s copy constructor

The gen-alias row `?dup_003d3a00@@YAXXZ` (76 bytes) borrowed
ObjectCreationList.cpp's `vector<ObjectCreationNugget*>` copy constructor, whose
real body is the matched 0x001D7300. Since f4b01f3dc5's twin rule it failed: its
`get_allocator` call goes through ILT 0x0002CE4E to 0x003D32D0 and its
`_Vector_base` constructor call through ILT 0x0000799B to 0x003D3540, while the
nugget vector's helpers resolve to 0x001D95A0 and 0x0003F418/0x0001D949.

- Bytes: `_Vector_base(n, get_allocator())`, then one `memmove` through the
  MSVCR71 import (IAT 0x0135945C): a trivially copyable 4-byte element.
- ilt_oracle CONFIRMS all three decorated names for element `unsigned int` (`I`):
  `??0?$vector@IV?$allocator@I@_STL@@@_STL@@QAE@ABV01@@Z` at 0x003D3A00,
  `?get_allocator@?$vector@IV?$allocator@I@_STL@@@_STL@@QBE?AV?$allocator@I@2@XZ`
  at 0x003D32D0 and
  `??0?$_Vector_base@IV?$allocator@I@_STL@@@_STL@@QAE@IABV?$allocator@I@1@@Z`
  at 0x003D3540. Across 176,314 candidate element types (every class/struct
  pointer, const pointer and enum in ilt_oracle's class dictionary plus the
  primitive types) no other type fits more than one of the three slots.
- The ObjectCreationNugget spelling is CONTRADICTED at 0x003D3A00.

Landed as the explicit instantiation in
game/GameEngine/Source/Common/UnsignedIntVectorCopyConstructor.cpp, with
symbols.csv pins for the two callees.

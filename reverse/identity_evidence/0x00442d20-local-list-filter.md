# 0x00442D20: address-qualified local list filter

The 144-byte retail body is a no-argument thiscall returning a pointer in EAX to the list at receiver+0x1C. It clears that list by deallocating its 12-byte nodes, then walks a second list at receiver+0x18. Each source node holds an entry pointer; entry+0xFC is an `Object*`. The body retains entries whose object passes `Object::isLocallyControlled` and appends a 12-byte node to the filtered list.

The retail calls are the matched STLport 12-byte node deallocator at 0x0082E5F0, `Object::isLocallyControlled` through ILT 0x0001FF91 to body 0x001BE570, and the matched STLport allocator at 0x0082E540. Their caller argument and cleanup forms agree with the typed C++ source. No named caller or vtable slot establishes the list owner's semantic class, and no existing native source emits this body, so `Rva00442D20Owner` retains the address token.

`Code/GameEngine/Source/Common/Rva00442D20ListFilter.cpp` compiled to 144/144 matching bytes with three aligned relocations. The strict scoped gate verified all three call destinations when it replaced the generated dump row.

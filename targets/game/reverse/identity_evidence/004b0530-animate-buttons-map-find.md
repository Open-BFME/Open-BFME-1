# 0x004B0530: find of AnimateButtons004B1C80's button map

Retail 0x004B0530 (71 bytes, `ret 8`) is an STLport `_Rb_tree::find` body
with an unsigned key compared at node+0x10 (JB/JAE) and a hidden iterator
result.

## Facts from BFME 1 retail

- The matched `AnimateButtons004B1C80::update` (0x004B1C80,
  `game/GameEngine/Source/GameClient/GUI/AnimateButtons004B1C80.cpp`) calls
  0x004B0530 with ECX = this+0x44 (the button map) and the window pointer as
  key, then compares the result with the map header.
- The same map's `operator[]` (0x004B1B90) is already matched in that TU as
  `_STL::map<Rva004B1880Key, Rva004B1880Value>`.
- Retail has no identical-COMDAT folding, so the find a TU calls is its own
  map type's instantiation. The previous row `?dup_004b0530@@YAXXZ` was a
  gen-alias home borrowing StateMachine.cpp's State-map find COMDAT, and the
  caller spelled the call `Rva004B12F0Map::rva004B0530`, a name nothing
  defined.

## Source

update() now calls the real STLport `find` through the TU's existing map
view; the emitted `find<Rva004B1880Key>` COMDAT is byte-identical to
0x004B0530 and update() still matches. The key/value names stay
address-derived TU views.

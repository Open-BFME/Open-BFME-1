# 0x001B2070 BfmeNamedContain::getContainCount (7 B)

Facts from BFME 1 retail:
- 0x001B2070: `mov eax,[ecx+0x2C]; mov eax,[eax+0x0C]; ret` (thiscall, no
  arguments).
- Reached only through ILT 0x000347E3, from 0x000FA1FD, 0x00323CF8
  (matched evaluateNamedHasFreeContainerSlots in
  ScriptConditionsNamedContain.cpp, which already spells
  `?getContainCount@BfmeNamedContain@@QBEHXZ`, pinned at ILT 0x000347E3) and
  0x0032C8C7.

The previous row `?dup_001b2070@@YAXXZ` was a gen-alias to a byte-equal
MeshGeometryClass::get_polys copy; it named no identity for this address and
nothing defined the caller's spelling (link queue #300, census 1d5131d3f1).
The pinned placeholder name and the unproven class view are kept.

Placement: Rva001B1F40TinyBodies.cpp (the carved leaf bodies around
0x001B1F40..0x001B20C0). Defining it in ScriptConditionsNamedContain.cpp, even
`__declspec(noinline)`, let VC7.1 see that the body preserves ECX and changed
the caller 0x00323CD0 (60 B -> 54 B).

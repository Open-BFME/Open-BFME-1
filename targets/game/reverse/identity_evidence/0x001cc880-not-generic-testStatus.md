# Retail 0x001CC880 is not Object::testStatus

The 126-byte row at 0x001CC880 was named `?testStatus@Object@@QBE_NW4ObjectStatusTypes@@@Z`.
`python3 tools/dis_retail.py 1CC880 126` shows it is not the generic status accessor:

- it tests the bit in a status mask at Object+0x110 (`lea ebx,[eax*4+0x110]`), then, when the bit is
  clear, takes `m_template` (+4), calls the template's final-override ILT 0x000022BB, tests template
  flag 0x1000 (`test ch,0x10` on +0xD4) and otherwise reads `containedBy` (+0x214), requires it to be
  KindOf 0x6c (`push 0x6c`, ILT 0x0003251F) and tests the same bit in that container;
- retail's generic status test is the 41-byte body at 0x000C4D40
  (`mov ecx,[esi+edx*4+0x90]`; `and eax,ecx`), pinned via ILT 0x000016A4. Generic testStatus is
  therefore inlined at Object+0x90 in retail, and this 126-byte body is a different method;
- the body is reached through ILT 0x0003C295 (`jmp 0x5cc880`) by two callers
  (`logicMessageDispatcher` 0x00397540 and `Drawable::react0041EBD0` 0x0041EBD0).

Nothing here proves the method's meaning, so the row takes the address-derived name
`?testStatusRva001CC880@Object@@QBE_NW4ObjectStatusTypes@@@Z`. The out-of-line declaration in
`inputs/reference/shims/bfmeobject/GameLogic/Object.h` and the one TU-local caller view in
`DrawableReaction0041EBD0.cpp` follow it.

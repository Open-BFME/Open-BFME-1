# 0x002131B0 constructor identity

Retail 0x002131B0 is a complete 50-byte constructor ending in `ret` at
0x002131E1. At +0x0B it writes literal vtable VA `0x010A8268` to `[esi]`.
`tools/vtable_lookup.py 0x010A8268` identifies its slot 0 as ILT
0x00029609, which reaches the separately matched
`FlightDeckBehaviorModuleData` scalar-deleting destructor at 0x002131F0.
The separately matched complete destructor is pinned through ILT
0x000275BB. This vtable identifies the object constructed by this body;
the constructor's masked byte match alone does not.

`tools/dis_retail.py 0x0011FAD0 110` shows matched
`FlightDeckBehavior::friend_newModuleData` allocate 0xD0 bytes and call
ILT 0x0000CC3E at +0x36. The ILT jumps to 0x002131B0. The matched
`ModuleFactory.cpp` registration names `FlightDeckBehavior` at line 762.
`tools/callers_of.py 0x002131B0` reports this factory as the only named
caller. The only `DetachableRiderBodyModuleData` references in current
game/reverse are the disputed duplicate source, its ledger row, and one
stale explanatory symbol note; no Detachable module-data factory call
supports that name here.

The existing `??0FlightDeckBehaviorModuleData@@QAE@XZ` row and ILT pin
already own the exact 50-byte body. The additional
`??0DetachableRiderBodyModuleData@@QAE@XZ` row claimed an ICF fold but
would require this body to install a different class vtable. The distinct
vtable address is a relocation operand that byte matching masks. Retire
only the unsupported duplicate row and its duplicate C++ source, recording
a tombstone; keep the FlightDeck row, extent, source, vtable pin, and bytes.

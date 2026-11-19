# 0x001CABE0 callers: `ObjectAttemptDamageFlagHook::value` retired, call the matched row

Two callers still spelled the ILT 0x0002CA61 target as
`?value@ObjectAttemptDamageFlagHook@@QAEHXZ`: `Rva0076B6E0View::rva0076B6E0`
(Select0076B800.cpp) and `BfmeThingEGF::bfmeSyncEGF` (Rva00271B40ShadowSync.cpp).
Commit 221a96741 removed that pin from symbols.csv, together with `bfmeValueZD`.
It was described as an "address-derived callee of Object::attemptDamage at 0x001D0490".
The matched row it removed it for is `?rva001CABE0@BfmeSubBIC@@QAEHXZ` (0x001CABE0, 376 B, route=0x0002CA61);
c8defd46a restored its definition name. Since then both callers fail the byte gate with an unresolved call.

BFME 1 facts that refute the old descriptive name:

- `?j_0002ca61@@YAXXZ` (0x0002CA61, gen-thunk) jumps to 0x001CABE0. That is
  the body matched in game/GameEngine/Source/GameLogic/Object/ObjectRva001CABE0.cpp.
- That body returns a colour, not a damage flag. In order it returns:
  - the apparent or disguised player's `getPlayerColor()`;
  - `m_indicatorColor`;
  - the controlling player's colour;
  - the ARGB default `0xff000000`.
- Both callers use the result as a colour. Select0076B800.cpp passes it as
  the decal colour argument of draw slot 24. Rva00271B40ShadowSync.cpp
  forwards it with mode 1 to the guarded colour slot.

The callers now include the shared `GameLogic/BfmeSubBIC.h` and call `rva001CABE0()`.
This is what 94adfea7e already did for BfmeConv553.cpp. No row, pin or new name is added.
The ledger's existing opaque identity is kept until evidence proves a real name.

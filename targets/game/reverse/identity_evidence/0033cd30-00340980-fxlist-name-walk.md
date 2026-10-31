# 0x0033CD30 hashtable begin / 0x00340980 FXList name walk

BFME 1 target evidence (retail 1.03):

- 0x00340980 (149 B, `ret 4`, INT3 after): stdcall, one pointer argument.
  Loads `TheFXListStore` (0x012F144C, dir32_addresses.csv), calls ILT
  0x000068B1 -> 0x0033CD30 with ECX = store+8 and a hidden iterator pointer,
  then for each node passes `node+0x14` AsciiString's str() (empty literal
  0x0107388B when null) to virtual slot 0 of the argument. The advance is
  STLport `_Ht_iterator::operator++` with `_M_skip_to_next` inlined; the key
  at node+4 is hashed by identity (`key % bucket_count`, no call).
- 0x0033CD30 (78 B) is reached only through ILT 0x000068B1 (callers
  0x0033ECF6, 0x00340949, 0x00340992). Its previous name was the
  byte-identical Player.cpp `hashtable<pair<const int, Relationship>>::begin`
  object-symbol alias (tg_0033cd30); retail links without ICF, so it is the
  begin() of the identity-hashed map at TheFXListStore+8, and lands as the
  address-derived `Rva0033CD30Table::begin`.

Unproven (kept address-derived): the walker's name and caller, the sink
class, and the mapped value type (0xC bytes, then the AsciiString name).

Byte evidence: game/GameEngine/Source/GameClient/Rva00340980FXListNameWalk.cpp
compiles both bodies exact. The walker only matches with the begin() body
visible in its TU and a per-step const_iterator copy (see
targets/game/reverse/attempt_support/0x00340980-stlport-iterator-20261028.md
for the spellings that fall short).

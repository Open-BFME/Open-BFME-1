# 0x00677950 is NetPacket::isRoomForRequestPlayerLeaveMessage

## Caller proof

The matched ledger row `?addRequestPlayerLeaveCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z` (0x00679E10)
makes exactly one isRoomFor call, through ILT 0x9016 -> 0x00677950
(`python3 tools/callees.py` on the caller). Its source already declares and
calls `NetPacket::isRoomForRequestPlayerLeaveMessage`, and `symbols.csv` pins that name at 0x00677950.
Every NetPacket add*Command opens with its own isRoomFor*Message check.

## Retired row

`?a_00677950@@YAXXZ` was a gen-alias whose object-symbol was `isRoomForDisconnectFrameMessage`, a name
that belongs to its own matched body at 0x00677A90. Retail was linked without
ICF, so 0x00677950 has its own identity; the gen-alias escape hatch is removed and
the body is compiled under the caller's name.

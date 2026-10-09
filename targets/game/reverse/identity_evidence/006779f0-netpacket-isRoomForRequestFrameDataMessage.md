# 0x006779f0 is NetPacket::isRoomForRequestFrameDataMessage

## Caller proof

The matched ledger row `?addRequestFrameDataCommand@NetPacket@@IAE_NPAVNetCommandRef@@@Z` (0x0067A100)
makes exactly one isRoomFor call, through ILT 0x4a732 -> 0x006779f0
(`python3 tools/callees.py` on the caller). Its source already declares and
calls `NetPacket::isRoomForRequestFrameDataMessage`, and `symbols.csv` pins that name at 0x006779f0.
Every NetPacket add*Command opens with its own isRoomFor*Message check.

## Retired row

`?a_006779f0@@YAXXZ` was a gen-alias whose object-symbol was `isRoomForInformPlayerLeaveFrameMessage`, a name
that belongs to its own matched body at 0x006778B0. Retail was linked without
ICF, so 0x006779f0 has its own identity; the gen-alias escape hatch is removed and
the body is compiled under the caller's name.

# 00677240: NetPacket::FillBufferWithDisconnectKeepAliveCommand

The complete retail body is 46 bytes at RVA 00677240, directly after the
46-byte `NetPacket::FillBufferWithKeepAliveCommand` at 00677200 (matched in
NetPacket.cpp). Both write the same 'T' type, 'R' relay, 'P' player and 'D'
tags, as Zero Hour's two serialisers do.

## Caller

The only direct caller is `NetPacket::FillBufferWithCommand` at 0067F430
(`callers_of.py 0x677240`), matched from
game/GameEngine/Source/GameNetwork/NetPacket_FillBufferWithCommand.cpp. Its
NETCOMMANDTYPE_DISCONNECTKEEPALIVE arm calls
`FillBufferWithDisconnectKeepAliveCommand`, which symbols.csv pins at
0x00677240, and that matched body's bytes verify with the call landing here;
the NETCOMMANDTYPE_KEEPALIVE arm calls `FillBufferWithKeepAliveCommand`
(00677200). A matched caller naming the symbol is the strongest identity
evidence.

## Why the old row is wrong

The old row `?dup_00677240@@YAXXZ` used NetPacket_fill.cpp's emitted
`?FillBufferWithKeepAliveCommand@NetPacket@@...` as its object symbol: a
second exclusive definition of the name NetPacket.cpp owns at 00677200, so
neither file could link. Retail had no identical-COMDAT folding, so the two
addresses are two functions.

## Provider

NetPacket.cpp already compiles Zero Hour's
`NetPacket::FillBufferWithDisconnectKeepAliveCommand` (it was marked
present-unmatched); link_census.RetailTruth judges its 46-byte copy retail's
body at 0x00677240, and the byte gate verifies it there. The row now names
that definition, and NetPacket_fill.cpp drops its duplicate keep-alive copy.

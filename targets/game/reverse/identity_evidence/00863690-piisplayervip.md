# 00863690: GameSpy peer piIsPlayerVIP

The 36-byte body at 0x00863690 was matched as the placeholder
?bfmeHasFlag@@YAHPBVBfmeThingDV@@H@Z. symbols.csv pins _piIsPlayerVIP
(vendored=gamespy-2004) at this address. The matched vendored
_piPickPingPlayersMap (0x00862960) calls it twice as
piIsPlayerVIP(player, StagingRoom), as GameSpy peerPing.c does. The body is
the GameSpy predicate: NULL player -> false, !inRoom[roomType] -> false, else
(flags[roomType] & (PEER_FLAG_OP 0x20 | PEER_FLAG_VOICE 0x40)) != 0. Bytes
unchanged; only the name gains C linkage.

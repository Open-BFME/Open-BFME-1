# 00863460: GameSpy peer piFindPlayerByIP

The 30-byte body at 0x00863460 was matched as the placeholder
?bfmeGoEMB@@YAXPAUBfmeThingEMB@@PAX@Z. symbols.csv pins _piFindPlayerByIP
(vendored=gamespy-2004) at this address. The matched vendored _piPinged
(0x00862750, peerPingPlayerJoinedRoom.c) calls it directly with (peer, IP),
as GameSpy peerPing.c piPinged does. The body loads connection->players
(peer+0xAB4), passes &IP and a map callback to the table walk at 0x00867010
and returns its eax: piFindPlayerByIP(PEER, unsigned int IP). Bytes unchanged;
only the name gains C linkage.

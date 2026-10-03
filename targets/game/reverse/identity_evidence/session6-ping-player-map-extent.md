# Include the ping-player selection callback epilogue

The 389-byte claim ends after POP EBP at RVA 00862AE4. Retail continues with POP EBX; POP ESI; RET at 00862AE5..00862AE7, then INT3 padding begins 00862AE8. Early guards, including JE at 00862977, target the omitted POP ESI at 00862AE6. Therefore 392 bytes are required by both entry control flow and the complete terminal boundary. Local PE/Capstone and Ghidra read_memory at VA 00C62AD0 agree. No other live claim intersects this interval.

The existing peerPingPlayerJoinedRoom.c C emission matches the complete 392-byte span with its original bindings. The source passes this static callback to TableMap from piPickPingPlayers. Preserve the inherited callback identity and source; this correction adds only the missing epilogue, without padding or new names. It does not assert that the locally reconstructed Peer source is pristine 2004 upstream code.

Rule: AGENTS.md requires matched rows backed by real source and byte verification; docs/matching.md requires the exact decorated-symbol check. Severity WRONG: the old claim omits executable bytes. This evidence corrects the extent only; it does not newly validate inherited semantic names.

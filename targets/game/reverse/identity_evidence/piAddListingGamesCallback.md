# piAddListingGamesCallback at 0x0085E420

The 233-byte body at 0x0085E420 is `_piAddListingGamesCallback`. The prior `?generateGameSpyGameResultsPacket@GameSpyStagingRoom@@` claim identified a naked byte lift incorrectly. The actual staging-room packet builder is pinned at 0x006386F0.

The named REL32 references in the matched peer callers resolve to 0x0085E420 in the retail executable. `_piSBGamesEngineCallback` calls it at 0x008646B6. `_piSBGamesListCallback` calls or jumps to it at 0x00864594, 0x008645CD, 0x008645FC, 0x00864633 and 0x00864643. `_piSBStartListingGames` calls it at 0x0086525F. Each operand was decoded from retail at the matching object's `_piAddListingGamesCallback` relocation offset.

The SDK callback declarations in `peerMainBlockingOperations.c` and the peer SB callers agree on the four arguments: peer, success, server and message. The local SDK reconstruction in `peerCallbacks.c` supplies `piListingGamesParams` with the five fields name, server, staging, message and progress, the type-3 callback marshaller, `piClearServerCallbacks` and the static `piAddCallback` implementation. Its upstream callback definition is absent, so the conversion reconstructs that definition from retail rather than claiming a verbatim upstream source comparison.

Retail clears queued server callbacks for message 2, reads the hostname and gamemode, compares gamemode with `openstaging`, computes progress from the server-list length and the two query queues, then queues a 20-byte parameter block with callback type 3 and ID -1. These values and the parameter layout agree with the SDK marshalling source. `piAddCallback` receives peer in EBX and parameter size in EAX; retaining its static definition in the same TU preserves this compiler-derived convention.

The clean C conversion in `peerCallbacks.c` preserves the complete 233-byte extent through the final RET. The byte gate verifies every instruction, named call target and literal relocation. The existing bodies in that TU must also remain byte exact. This identity would be refuted by a named caller targeting another address, an incompatible SDK parameter layout or a failing byte gate.

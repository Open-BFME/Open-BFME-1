# GameSpy Chat/Peer reconstruction provenance

This is a metadata-only correction of 31 existing matched rows. Their names,
extents, source code and instruction coverage are unchanged. It adds no retail
bytes and makes no new identity claim.

AGENTS.md says: "`vendored=<lib>-<ver>` rows carry the upstream's real
identities, and the header comment names the exact release." The checked-in
`game/GameEngine/Source/GameNetwork/GameSpy/PROVENANCE.txt`, under "Chat and
Peer: opened 2026-08-21", explicitly distinguishes these reconstructions from
the 2004 carrier, which contains no Chat/Peer directories: "They therefore
carry no `vendored=gamespy-2004` note". The relevant source headers describe
2007 SDK bodies with local declarations, or reconstruction from retail bytes
(`peerHost.c`). They cannot support a blanket pristine-2004 vendor tag.

Replace only that tag with `reconstructed-gamespy;
provenance=GameSpy/PROVENANCE.txt`. Do not relabel these files as vendored 2007;
the reconstruction qualification matters. Existing identity notes remain
unchanged and are not independently re-proved by this metadata correction.

Fresh origin rows were checked before claims. RVA 0x00862960 is held by another
worker and remains unchanged, including its pending provenance debt.

Validation: the eight unchanged source files compile under the team Wine
environment. `./build.sh` reports 60/60 function matches, two owned data rows,
26 literal and six empty-string references, and 37 DIR32 references passing.
These are scoped checks, not a whole-ledger or whole-initializer proof.

| RVA | Size | Existing name |
|---|---:|---|
| 0x0085DF30 | 41 | `_piCallAutoMatchRateCallback` |
| 0x00862380 | 87 | `_chatConnectSecureA` |
| 0x008624C0 | 119 | `_chatRetryWithNickA` |
| 0x008625E0 | 150 | `_piXpingTableCompareFn` |
| 0x00862680 | 1 | `_piXpingTableElementFreeFn` |
| 0x00862690 | 189 | `_piProcessPing` |
| 0x00862750 | 41 | `_piPinged` |
| 0x00862780 | 154 | `_piPingInit` |
| 0x00862820 | 77 | `_piPingCleanup` |
| 0x00862870 | 93 | `_piPingerReplyMapFn` |
| 0x008628D0 | 52 | `_piPingerReply` |
| 0x00862910 | 67 | `_piPingPlayer` |
| 0x00862AF0 | 135 | `_piPickPingPlayers` |
| 0x00862B80 | 243 | `_piXpingPlayer` |
| 0x00862C80 | 87 | `_piPickXpingPlayerMap` |
| 0x00862CE0 | 76 | `_piPickXpingPlayer` |
| 0x00862D30 | 214 | `_piPingThink` |
| 0x00862E10 | 116 | `_piPingInitPlayer` |
| 0x00862E90 | 82 | `_piPingPlayerJoinedRoom` |
| 0x00862F10 | 137 | `_piPingPlayerLeftRoomTableMapFn` |
| 0x00862FA0 | 236 | `_piPingPlayerLeftRoom` |
| 0x00863090 | 110 | `_piFindXping` |
| 0x00863100 | 120 | `_piAddXping` |
| 0x00863180 | 102 | `_piUpdateXping` |
| 0x008631F0 | 57 | `_piGetXping` |
| 0x008646C0 | 52 | `_piSBStopListingGames` |
| 0x00865410 | 53 | `_piStartHosting` |
| 0x00865450 | 73 | `_piStopHosting` |
| 0x00872810 | 149 | `_ciGetUserBasicInfoA` |
| 0x00872A40 | 156 | `_piSendPing` |
| 0x00873370 | 341 | `_pingerPing` |

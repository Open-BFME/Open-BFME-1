# WOLLobbyMenuInit, 004FBBE0

Retail FunctionLexicon record VA012A99FC contains `{0,01086C0C,00435878}`.
The literal at VA01086C0C is `WOLLobbyMenuInit`; ILT 00035878 jumps to 004FBBE0.
The named pair is also present in FunctionLexicon.cpp. The callback has two
cdecl pointer arguments, WindowLayout* and void*. Its full 1711-byte extent ends
with the native RET at +06AE, followed by INT3 padding; there are no switch tables.

The callback uses the already recovered LobbyUpdate TU so its private room
listbox helper preserves the retail register argument contract without an
emission-only call or duplicate helper ownership. The same TU supplies canonical
strings and the witnessed GameWindow/room layouts. All existing five body claims
are verified again with Init.

The 18 distinct direct targets are existing contracts. CustomMatchPreferences'
192-byte constructor and 11-byte virtual destructor already have native owners;
the real header provides its 20-byte object. The PeerRequest 220-byte constructor
and 555-byte destructor in PeerDefs.cpp independently establish the 0x194 record.
The callback writes request kind 7, the start-game-list request, and its payload
restrictGamesToLobby byte at +E4. The known queue interface takes the request by
const reference at virtual slot 18. GameSpyConfig's restriction getter is +38.

The registerTextWindow call is virtual slot E4, also used by the independently
matched WOLGameSetupMenuInit. Its native 30-byte target 00626060 inserts the
GameWindow* into GameSpyInfo's +6E0 pointer set, independently distinguished from
the signed profile-ID set immediately following it. GameSpyStagingRoom reset is
virtual +8. The window manager uses the existing +DC lookup and +B0 focus slots.
The public GameWindow methods retain native bool arguments and tooltip callback
(GameWindow*,WinInstanceData*,unsigned) rather than guessed integer contracts.
The tooltip address itself is the already identified 1517-byte playerTooltip
body 004FA800; it is not a new claim in this change.

The original reference WOLLobbyMenu.cpp remains as the emitter for its existing
EH funclets. Only the naked Init file is removed. This change adds 1711 native
bytes, no symbol pins, no helper ownership changes and no shared-header edits.

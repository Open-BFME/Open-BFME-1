# 0x004C8B40: callee spelling in LanLobbyMenu.cpp

LanLobbyMenu.cpp declared its game-info refresh callee as
`RefreshGameInfoWindow`, a name with no functions.csv row and no symbols.csv
pin. The body it calls (ILT-resolved from the retail call site in
LanLobbyMenuSystem, 0x004CEC00) is the landed row
`?Rva004C8B40GameInfoWindowRefresh@@YAXPAVGameInfo@@VUnicodeString@@@Z`
(0x004C8B40, 1,026 B). The 0x004CEC00 landing (gpt-6-astra, byte-exact)
calls it by that ledger identity, which the scoped gate links and verifies;
the unbacked spelling is retired, not an established identity renamed.

# Direct-connect remote-IP list identity at 0x004D2D80

The retail `JoinDirectConnectGame` body at 0x004D3650 calls ILT
0x0000343B at `+0x1C2` with no pushed arguments, immediately followed by a
call to ILT 0x0000E543 at `+0x1C7`. The first ILT jumps to **0x004D2D80**;
the second jumps to the already matched `PopulateRemoteIPComboBox` at
0x004D2540. The native and vendored `NetworkDirectConnect.cpp` both call
`UpdateRemoteIPList()` immediately before `PopulateRemoteIPComboBox()` from
`JoinDirectConnectGame`.

The target is a 1291-byte physical function. It begins with an SEH prologue,
ends at `+0x50A` with a plain `ret`, and is followed by INT3 padding. It
constructs LAN preferences, reads the remote-IP combo box and selected text,
parses an IPv4 address, walks the other entries to avoid duplicates, writes
`RemoteIP0` and formatted `RemoteIP%d` keys, writes `NumRemoteIPs`, and
persists preferences. These actions follow the native and vendored
`UpdateRemoteIPList()` implementation. The body neither consumes a `this`
pointer nor reads a `LANMessage*` or sender-IP argument. The vendored
`LANAPI::handleJoinAccept(LANMessage*, UnsignedInt)` has those arguments and
handles a game-join response, so the old ledger name was a wrong identity
despite its byte match.

`Code/GameEngine/Source/GameNetwork/LANAPIhandlers.cpp` currently emits the
verified retail bytes under
`?handleJoinAccept@LANAPI@@IAEXPAULANMessage@@I@Z`. The ledger's
`object-symbol=` alias retains that existing byte-exact implementation while
recording the proven free-function identity `?UpdateRemoteIPList@@YAXXZ`.
This ledger correction does not assert that the native
`NetworkDirectConnect.cpp` definition byte-matches the retail body.

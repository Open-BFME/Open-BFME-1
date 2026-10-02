# Peer connection callback provider bindings

This correction changes only two external declarations and their address uses
in `piNewConnectOperation` (retail RVA 0x0085F2F0, full 422-byte extent).
It does not rename either callback implementation or change a ledger identity.

The prior `piChatDisconnectedA` and `piChatPrivateMessageA` declarations had
no defined symbols. The existing DIR32 address evidence maps them to
VA 0x00C6B2D0 and VA 0x00C6B360 respectively (image base 0x00400000).
These exact RVAs already have matched C providers:

- `Rva0086B2D0Disconnected`, RVA 0x0086B2D0, 29 bytes, in the Peer source
  `Rva0086B2D0Disconnected.c`. Its cdecl signature takes chat, reason, and
  a connection pointer; it sets connection +0x1F04 and dispatches the reason.
- `Rva0086B360Dispatch`, RVA 0x0086B360, 203 bytes, in the Peer source
  `Rva0086B360Dispatch.cpp`. Its C cdecl signature takes chat, nickname,
  message, mode, and peer. Its private helpers stay in their owning TU.

The new declarations use those exact provider signatures and names. The
callback assignments retain the disconnected/privateMessage field roles.
The naming detector compares undefined declarations to the provider spellings;
this is an external binding correction, not a descriptive body being renamed.
The exact snapshot corrections cover only these two declarations and uses.

Validation: all 22 functions in the caller TU byte-match, with all 22 DIR32
references checked. With the current callback providers refreshed against the
frozen a62cc2fa61 census, the caller's five unresolved names become three:
`piConnectFillInUserCallbackA`, `piDisconnectTitle`, `piStartedEnteringRoom`.
No provider identities, symbol pins, or function ledger rows are changed.

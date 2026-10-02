# Peer main existing-provider bindings

This change preserves all 74 C ledger symbols in the Peer main translation
unit while compiling it as C++. Only four external declarations and their
uses are rebound to existing matched C++ providers. No provider implementation
or function-ledger identity is renamed; the ledger change is the caller's
source suffix only. The object filename and census position stay the same.

The independently decoded direct retail calls identify these providers:

- `peerGetProfileID` calls RVA 0x00860700, the existing
  `Rva00860700::get(const unsigned *)`. It returns the DWORD at +0x8B0.
  Both caller declarations pass one pointer and return the same EAX bits.
- `peerKickPlayerA` calls RVA 0x00861510, the existing
  `dup_00861510(void *, const char *, const char *, const char *)`.
  It guards chat/connected, defaults a null reason, and sends the KICK format
  with the caller's channel, nickname, and reason in that order.
- `piShutdownCleanup`, `peerInitialize`, and `peerShutdown` call
  RVA 0x0085EFA0, the existing `Rva0085EFA0(Rva0085EFA0Owner *)`.
  It frees the operation array at +0x1798 and clears the field. The cdecl
  call still takes one peer pointer; only its local view type changes.
- `peerStartGameA` and `peerSetPasswordA` call RVA 0x008667A0, the existing
  `Rva008667A0(Rva00866770Owner *)`. It forwards the nonnull query-reporting
  pointer at +0xAF0 to `qr2_send_statechanged`, taking one cdecl peer pointer.

`tools/callees.py` resolves these targets from the caller bodies, independently
of the obsolete declarations. Full provider signatures were read from their
existing source files. The compiler verifies all 74 caller-TU ledger rows and
all 15 DIR32 references after the language move. Callback declarations and
function-pointer conversions are unchanged; the added casts are object views.

The name detector pairs the formerly undefined `chatKickUserA`,
`piOperationsCleanup`, and `piSendStateChanged` declarations with the existing
provider spellings. Exact-snapshot corrections cover only these declaration
bindings. They do not authorize renaming descriptive implementations. Each
pair has both the individual-commit and aggregate two-commit snapshot, because
the preceding cleanup-only repair changes four other calls in this same TU.

Current source and all four providers refreshed against frozen census
`a62cc2fa61` reduce the caller's six blockers to two: `bfmePiDisconnect` and
`chatGetUserID`. The other provider's already-clean 178 bytes appeared in both
before and after previews and are not a gain from this repair.

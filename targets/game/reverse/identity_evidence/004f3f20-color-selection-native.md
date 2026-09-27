# Setup color selection at 0x004F3F20

2026-09-27, GPT-6. The just-matched WOLGameSetupMenuSystem names its
560-byte cdecl `handleColorSelection(int)` callee. The complete retail
identity/ABI proof and original static source definition were already retained
in 004f5d10-setup-system-native.md when its dependency pin was added.
The target reads one stack index, validates the chosen color against the
palette and occupied slots, then updates the host or sends the client's
Color=%d peer request. Its bare RET ends at +0x22F; INT3 padding starts
at 0x004F4150. This is a new native560B transition from
its existing assembly dump; the earlier pin-only repair received zero credit.

Starting from the complete original body, fresh corrections are confined to
its BFME type views: existing Info slots +C4/+C0/+CC; local-name hidden-string
result at +68; and MultiplayerSettings color map at +30 with cached count
at +3C. `name_oracle --class MultiplayerSettings --offset 0x3c` independently
reports m_numColors with confidence1.00. The already matched275B
MultiplayerSettings_findMultiplayerColorDefinitionByName.cpp independently
proves the native color-map header at +30; the original getNumColors algorithm
lazily uses that map's size. Native map storage is used, not a raw byte patch.

Canonical AsciiString data access reuses the existing BfmeStartAsciiString
helper. PeerRequest and all other lifetimes remain the established native
0x194-byte model. Fourteen direct retail targets were inventoried before
editing. No additional symbols pin, header, generated file or identity
baseline changes are needed. Receipts are build/four-hour-setup/color-*.txt;
the complete menu and its newly landed2352B caller passed17/17 with
91 literals and28 empty-string references. Strict:560/560,31relocations,
zero unresolved and zero byte differences.

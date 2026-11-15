# Canonical StringBase adoption: tasks 176-192 of 200

Baseline `8d8f829de4f433da934bf4dd6de7b007d25b42ec`.
Replace only the local StringBase template with the existing native string_base.h.
No source-level local AsciiString body is present in this family. Existing
UnicodeString views remain unchanged. One source adoption is one task; dependent
cleanup locator repairs are not counted again. This is reconciliation of existing
code, not new function reconstruction or authored-byte progress.

## ABI, compiler and object proof

The native BFME1 string_base.h describes the settled four-byte buffer-pointer
object and narrow/wide method identities. Per-source CodeView requires every
original concrete StringBase instantiation to remain present, with sizeof4,
one pointer field at offset0, no bases, no virtual pointer or slots. Companion
UnicodeString size, direct fields, base identities/offsets and virtual state
must remain exactly equal between controls. A size1 empty incomplete facade is
admitted only with exact complete runtime inventory identity and no other concrete
object layout containing or deriving from it. The settled native header and
verified providers independently establish its real4B pointer ABI; no size1
retail-type claim is made. No size-dependent caller code may change.
Private controls use the same physical input path and original include context.
The independent normal-before/normal-after comparison retains all ordinary
runtime bytes, section flags and relocation sites/kinds/targets. Local EH graph
roles, action offsets and resolved SafeSEH handlers remain equal. A strict full
ordered inventory can additionally prove disconnected local tables without
guessing a mapping. Weak external contracts remain identical.

New or changed callable COMDATs require an existing matched ledger identity
and native full-byte/relocation-target RetailTruth proof. Removed definitions
must be canonical copies independently proven wrong. No unknown new body is accepted.
The only additional data exception recognizes the original narrow/wide
StringBase::str TheNullChr exports from exports.csv: exact original RVA,
scalar1/2B size, readonly non-executable section, no relocations, exact zero
initializer read at that original address. This is not callable proof from a pin.
Only the three compiler aliases already emitted by unchanged verified providers
can be duplicated; any newly duplicated alias remains unused by the consumer.
No source alias, pin, header, compiler flag, verifier or baseline changes.

## Reference context

The read-only BFME2 revision f6c3838e7b58025531e09913bc42b810f1a01216 and its
Code/Libraries/Source/WWVegas/WWLib/string_base.h inform the common-owner pattern.
Native BFME1 evidence and existing headers determine the buffer layout, ABI,
addresses, method bodies and exception ordering. No donor address or flag is copied.
The BFME2 binary-source sweep was refreshed earlier in this round; unchanged
Zero Hour inputs and previously refuted link blockers are not rescanned per unit.

| Task | Source | Retained RVAs | New / corrected retail implementation copies |
|---|---|---|---|
| 176 | `game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Gadget/W3DPushButtonDrawNumber00794B70.cpp` | `0x00794B70` | 0 / 0 |
| 177 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/Rva004EF980AcceptBuddyRequest.cpp` | `0x004EF980` | 0 / 0 |
| 178 | `game/GameEngine/Source/GameNetwork/GameSpy/GameSpyInfoHandleText.cpp` | `0x006260C0` | 0 / 0 |
| 179 | `game/GameEngine/Source/GameClient/GUI/OnlineQuickMatchPopulateMaxPing.cpp` | `0x00558A30` | 1 / 0 |
| 180 | `game/GameEngineDevice/Source/Win32Device/Common/Win32LocalFileSystemGetFileList.cpp` | `0x009CE190` | 0 / 0 |
| 181 | `game/GameEngine/Source/Common/BfmeConv1839.cpp` | `0x0052D8F0`, `0x00534F60` | 2 / 1 |
| 182 | `game/GameEngine/Source/Common/Gen0000D33CCtor004354F0.cpp` | `0x00434FF0`, `0x004354F0` | 2 / 1 |
| 183 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenInGameChatFriendPanel.cpp` | `0x00512050` | 2 / 0 |
| 184 | `game/GameEngine/Source/GameNetwork/ConnectionManagerProcessDisconnectChat.cpp` | `0x006655C0` | 0 / 0 |
| 185 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PopupReplayInit_Thunk.cpp` | `0x004DE270` | 2 / 1 |
| 186 | `game/GameEngine/Source/GameClient/GUI/BfmeAptScreenOnlineLogin_onInitGadget.cpp` | `0x00551DD0` | 0 / 0 |
| 187 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenLanLobby_onInitGadget.cpp` | `0x005187F0` | 2 / 1 |
| 188 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/ScoreScreenInitInternet.cpp` | `0x004E8B80` | 2 / 1 |
| 189 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineCustomMatchOnInitGadget.cpp` | `0x0053A710` | 2 / 1 |
| 190 | `game/GameEngineDevice/Source/Win32Device/Common/Win32LocalFileSystem.cpp` | `0x009CDDE0`, `0x009CDE20`, `0x009CDE30`, `0x009CDEC0`, `0x009CDDC0`, `0x009CDE50`, `0x009CDDA0`, `0x00C609D0` | 0 / 0 |
| 191 | `game/GameEngine/Source/GameNetwork/NAT_establishConnectionPaths.cpp` | `0x00672A60` | 2 / 1 |
| 192 | `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/BfmeAptScreenInGameChatInitGadgets.cpp` | `0x00515E60` | 2 / 1 |

## Ordinary gates and link prediction

26 retained rows preserve 8461B.
Combined normal gate: 200/200 functions across
21 sources, 480 DIR32 references, body guard OK,
including the four unchanged canonical provider sources.
1 cleanup locators are corrected only by eh_state_pins.py --fix.
Frozen before: 4/17 LINKS, 1161B.
Frozen after: 4/17 LINKS, 1161B.
No formerly linkable file is lost. Staged current-provider preview: 17/17 UNKNOWN, 0/17 LINKS, 0/17 blocked. Unknown results authorize no LINKED claim.
The complete earlier census43711614660 separately confirms the preceding450B
and total3,088,824 LINKED B; it predates these adoptions. No new full-link, runtime,
memory improvement or crash-fix claim. Reservations, row-specific prior attempts,
snapshots, layout controls and complete private/native proofs remain in this
round's batch diagnostics. Failed trials are neither applied nor counted.

Native state-proven cleanup locators:
- `0x00C609D0`: `$L26141` -> `$L26305`.

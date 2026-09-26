# Buddy-response handler contracts (RVA 004EE510)

The original ZH `WOLBuddyOverlay.cpp::HandleBuddyResponses` and ten retail
callers through the ILT identify this dispatcher. Matched callers include
`GameEngine::_bfme_updateNetworkAndLogic` at 0006BAE0 and
`WOLGameSetupMenuUpdate`. BFME adds response kinds 5 and 6, the GP/FESL
error dialogs, automatic handling of ignored/existing buddy requests, and
full BuddyMessage notification dispatch.

The extent is 3624 bytes: native instructions through RET at +0xE0A, one
alignment NOP, then the seven-entry switch table at +0xE0C..+0xE27.
The table routes kinds 0..6 to +0x5B, +0xF4, +0x523, +0x69F, +0x936,
+0x2FD and +0x75. The next bytes are INT3 padding. The apparent invalid
instruction at the probe's end is switch data, not a truncated epilogue.

## BuddyInfo assignment, 004E9B70 / 85 bytes

The existing byte-verified `Rva004E9B70Assign.cpp` independently implements
assignment of an integer at +0, three narrow strings at +4/+8/+0xC, an
integer at +0x10, and two wide strings at +0x14/+0x18. Its five calls are
to StringBase<char>::set( const StringBase& ) at 00887C90 and the wide
equivalent at 00888530. It returns its original ECX in EAX and RET 4.

This is the seven-field BuddyInfo layout from PeerDefs.h. The independently
landed map operator[] at 004EE3D0 and its 004E9FD0 copy-construction target
establish the mapped type and layout; the named destructor at 004EA090
releases the same three narrow and two wide strings. In this dispatcher,
the aligned calls at +0x7FD and +0xAD1 use the map operator[] result as
ECX and pass the local BuddyInfo by const reference. The single new
`BuddyInfo::operator=` pin names the already-verified assignment body.

## Address-qualified tree erase, 004EE060 / 91 bytes

The entire independent body is a thiscall integer-key erase. It saves ECX
as the tree, passes its one reference argument to equal_range through
ILT 00046826 -> 004EB4C0, counts iterators with the canonical increment
at 0082B870, calls range erase through ILT 00024EA1 -> 004ED040, returns
the count in EAX and ends in RET 4. Range erase independently uses the
header pointer at tree+0 and count at tree+4, and frees 0x30-byte nodes
(16-byte tree node header plus int key and 28-byte BuddyInfo). Its value
cleanup is 004EA1B0. These agree with the map returned by the buddy-request
getter and the integer key passed by this dispatcher.

The canonical BuddyInfo tree erase spelling already refers to a different
retail copy at 00225BE0. The new Rva004EE060Tree::erase declaration therefore
keeps the address token and models only this independently established ABI;
it does not add another address under the existing spelling. Existing
004EE060 generated ownership and coverage remain unchanged.

## Existing notification contract view, 004ECD10 / 557 bytes

The old ledger name says showNotificationBox(AsciiString,UnicodeString),
but the body consumes a 24-byte BuddyMessage by value. Independently, its
prologue establishes the first argument at original ESP+4; reads of the
sender nickname and message occur at argument+8 and argument+0x14; and
its epilogue calls the named BuddyMessage destructor at 004EA4B0 on the
whole first argument before a plain RET. The caller constructs exactly
24 bytes using the matched BuddyMessage copy constructor at 004EA520.
The new dispatcher uses the already-pinned address-bearing object symbol
`_bfme_showNotificationBox_4ECD10` with this correct contract, without
claiming a new semantic identity or changing the old row.

The TU-local notification globals preserve the original source's storage
class. Their addresses and widths are independently corroborated by the
004ECD10 stores at +0x183/+0x189 and the existing native 004E9CF0 teardown.
BuddyResponse's 0x864 extent is independently proved by its deque copy;
PeerResponse's 0x330 extent and +0xF4 union are proved by the landed
PeerResponseCopies.cpp and queue bodies. Unknown BFME kind/flag fields
remain address-qualified. No raw assembly is used.

## Exact source-move naming audit

Moving the three existing helper rows makes name_regression compare whole
source files, including declarations unrelated to those helpers.
`buttonDeleteBuddyID` is retained unchanged in WOLBuddyOverlay.cpp; it is
not the new boolean at VA012F4248. The old `noticeLayout` is a ZH
WindowLayout pointer, whereas the retail tail tests a single byte at
VA012F4248, independently cleared by 004E9CF0; the new address-qualified
boolean intentionally avoids claiming it is a layout pointer.

The two-string `showNotificationBox` calls in the ZH twin map to the
already-proven Rva004EBA70NotificationDispatch contract. This is distinct
from the 24-byte BuddyMessage callee at 004ECD10 discussed above.
WOLBuddyOverlayRequestBuddyAdd.cpp already used this exact dispatcher
before this change and is untouched; its finding comes solely from
repointing the naturally emitted _Construct helper. The four exact
source/name pairs in name_corrections.json document these bounded facts,
not a broader permission to discard names.

# RVA 0055A240: complete quick-match response dispatcher

The 2,357-byte generated row is one function, including its switch tables.
Retail opens an FS exception registration and allocates 0x864 bytes. Both
response-processing loops share the epilogue at 0055AB2C; RET is at 0055AB44.
Three alignment bytes precede seven switch targets at 0055AB48 and the
17-byte selector at 0055AB64. INT3 padding begins at 0055AB75. Ghidra's
843-byte function inventory omits reachable switch arms; it is not the extent.

The source starting point is the matched WOLQuickMatchMenuUpdate.cpp
Rva00506720Layout::update and the matched AptOnlineQuickMatch.cpp handler at
00559840. Both agree with the Zero Hour WOLQuickMatchMenuUpdate logic:
post-game disconnection reporting, NAT state handling, PLAYERUTM statistics
and NAT messages, disconnect cleanup, and quick-match status processing.
The BFME APT version removes the window-based UI feedback and calls the
00559840 handler via ILT 00044D00 at 0055AA7B with the original ECX receiver
and the PeerResponse local at ESP+50. This establishes the same receiver
view, without establishing an original member spelling. The reconstruction
uses Rva00559840QuickMatch::rva0055A240.

Independently checked differences from the donor:

- The in-game disconnection arm only appends to the score-screen listbox
  when it exists; there is no fallback InGameUI message.
- NAT DONE calls launchGame and returns without leaveStagingRoom.
- NAT FAILED clears TheNAT, writes receiver+3C = 3, constructs the
  single-binding callback holder via 00559280 / ILT 0002D722 with the
  original receiver and ILT 00021328, and sends the localized error through
  00522D20 / ILT 0002E0B9. This callback's cleanup is not optional:
  FuncInfo 00E23824 state 2 names 00C33E96, which loads the saved temporary
  address and jumps through ILT 000336C7 to 004C5790. That 26-byte body
  decrements the pointee's reference count and conditionally dispatches
  virtual deletion. A trivial POD callback holder gives the wrong argument
  evaluation order and lifetime.
- The NAT-failure APT call passes CloseFoundAndReset. The QM_MATCHED call
  passes DoOpenFound and then calls the existing matched handler. Both use
  global VA 012F4ABC -> +34 -> +250 as the level and global VA 012F19E8 as
  the receiver of 004675F0 / ILT 00015235. The eight stack arguments are
  level, CallChild, 1, selector, 0, 0, 0, 0.
- PSPlayerStats is 0x1C4 bytes; PeerResponse is 0x330 bytes. Retail's frame
  slots and copy arguments agree with the existing matched donor views.
- The remaining formatted status strings are constructed and destroyed,
  but never passed to GameSpyInfo::addText. The switch still has cases 1,
  4, 8, 9, 16 and 17 with the default arm, exactly as its raw selector shows.

All addresses above are RVAs unless explicitly marked VA. Retail was read
from inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe, independently
of Ghidra's draft decompilation. The production method keeps its address-qualified identity. No new symbol
pins are needed: the scoped add_match gate verifies both this 2357-byte body
and the existing 1251-byte handler, plus 20 literals and one empty string,
and 53 DIR32 references. Existing donor declarations are retained in place.

The stored callback is independently decoded as the existing matched
Rva005584F0::set(int) at 005584F0 (18 bytes, RET 4), reached through
00021328. It reads its one stack argument and clears receiver+3C only when
that argument is zero. The single-inheritance member pointer is therefore
four bytes and carries one explicit int argument when invoked; the dispatcher
only stores its bits in the holder, it does not invoke it.

The last byte-shape lever was to retain the QM_MATCHED level and manager as
separate block-scoped locals, in that order, before bfmeBuildAN. This resolves
all 118 residual bytes, including the receiver/register assignment and shared
format tails; no volatile access, barrier, inline assembly or compiler-flag
change was required.

# Setup start-position selection at 0x004F44E0

2026-09-27, GPT-6. Full497-byte native body, ending at bare RET0x004F46D0
and followed by INT3 padding. The just-matched2352-byte setup-system callback
calls the existing TU-private handleStartPositionSelection(player,startPos)
helper three times. Full target identity and ABI evidence was recorded in
004f5d10-setup-system-native.md before adding its dependency pin: the target
reads startPos fromECX and player from its sole caller-cleaned stack argument,
checks occupancy using slot+10, updates it and either broadcasts or sends
StartPos=%d in aREQ/ peer request. Retaining the original static definition
and real callers lets MSVC reproduce its private optimized convention; no
assembly, fabricated external thiscall prototype or register barrier is used.

The original full body was the starting point. Only already-proven BFME
GameSpyInfo virtual slots and canonical narrow-string access were corrected.
The callback's recovered context gives the complete497-byte exact shape;
older isolated-body attempts could not reproduce its private calling ABI.
The full retail call inventory was read before edits. No new pins or header
changes are required; the earlier pin-only repair had zero native credit.
This commit replaces the497-byte gen-dump claim with authored native C++.
The generator file itself is untouched.

Strict scratch result:497/497,26relocations,zero unresolved,zero byte diffs.
All existing cleanup behavior is retained: options/host-name strings,
Unicode by-value copies and the complete194-byte PeerRequest destructor.
Receipts are build/four-hour-setup/start-callees.txt,start-native.txt and
start-strict.txt. The complete menu is gated with the body and its caller.

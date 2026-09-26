# updateBuddyInfo at 004EBE30 (1771 bytes)

The previous naked lift called this body
`?getLocalProfileID@GameSpyBuddyMessageQueue@@UAEHXZ`. That name and ABI are
incorrect: the body is a no-argument free function ending in RET, starts from
the global buddy queue, and does not read an incoming receiver.

The independently matched ShowDiplomacy calls `?updateBuddyInfo@@YAXXZ`
through ILT 0002549B, which routes to 004EBE30. The named pin predates this
conversion. The matched HandleBuddyResponses now published at 004EE510 also
calls the same route twice. WOLBuddyOverlayInit has another aligned call, and
the native Zero Hour updateBuddyInfo provides the same two list-population
loops, selection preservation, status strings and listbox APIs. This is an
identity correction, not an inference from an RVA neighbour or body size.

The complete 1771-byte extent begins with the EH prologue and ends in RET at
+06EA. No switch data or following padding is counted. The reconstruction is
all native C++, with 117 relocations and no naked/inline assembly.

## Independent callee contracts

Before reconstructing, `callees.py 004EBE30 1771` identified 23 direct targets
plus imported wcslen/_wtoi. Existing pins resolve all except the GroupRoomMap
integer-key tree find. The visible StringBase and UnicodeString delegates use
the already-matched constructors, setters and releases. The 28-byte BuddyInfo
copy/destroy are independently established by 004E9FD0/004EA090 and the sibling
response-handler evidence. The GameText overload ABI, listbox argument order,
queue isConnected slot+10 and info buddy-map/request-map/ignored slots
+54/+58/+12C are unchanged from the proven sibling layouts.

The one added pin binds the exact native STL integer-key tree-find symbol for
`map<int,GameSpyGroupRoom>` to 004EB610. Independent 71-byte target decoding proves:

* thiscall receiver points at an 8-byte tree object, whose first word is the
  header pointer; root is header+4, left/right are node+8/+C;
* ordered key comparisons read signed int at node+10;
* it returns either the lower-bound node or header sentinel through a hidden
  iterator-result pointer, returns that pointer in EAX, and ends in RET 8
  (hidden result plus const int reference).

The payload identity/layout is independently supported by already matched
PeerDefsGroupRoomMapOperator.cpp at 006357D0, its insert_unique 00633BB0, and the
32-byte GameSpyGroupRoom copy at 004F97B0. The matched SetUpGameSpy ABI view
independently identifies info slot+0C as getGroupRoomList. The group-room name
read is node+14 (16-byte node header, 4-byte key, name at value+0), agreeing with
those independent bodies and the native source. The helper row currently owned
by PeerDefs.cpp stays at 004EB610; no extra byte claim or ownership move is added.
Pin consistency had no existing binding for this exact symbol and remains clean.

## Compiler lever and verification

A declaration-only empty no-case traits object allocated one extra stack slot:
1771 bytes with 54 differing frame/stack operand bytes. The listing gave the
one-byte `_traits` object its own four-byte-aligned slot. Exposing the actual
89-byte comparator while keeping it noinline made the complete body exact.
The comparator implementation is the independently matched
StringBaseWideCompareNoCaseRaw.cpp body at 0009ECA0: three arguments, RET 12,
repeated imported towlower, no receiver access. It introduces no new callee pin
and makes no claim for extra coverage.

Removing the old native definition leaves all 36 pre-existing WOLBuddyOverlay
rows emitted and byte-exact. No helper ownership transfers, artificial calls,
explicit emission directives or shared-header edits are needed. The retired
naked lift is deleted. Strict relocation verification checks every direct call
and data operand; only the main 1771-byte body counts as new native coverage.

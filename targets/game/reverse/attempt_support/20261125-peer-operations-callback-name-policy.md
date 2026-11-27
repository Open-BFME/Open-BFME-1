# Operations callback retirement blocked by native name policy

Baseline c5b6f6bc563565b1d73f8a41191e87dbddd04149. This attempt changes
no retained Source/ledger/record, earns zero tasks/bytes/LINKED, and did not
compile the candidate. Round 2 remains open for independent work.

## Proven lead and single attempted form

peerOperationsListGroupRooms.cpp has 22 matched rows. Original completion
constructors 85FD30/69 and 860060/69 pass callbacks 85FCD0/89 and 860020/56
through DIR32+0x30. Original connect constructor 85F2F0/422 registers
callbacks 86B2D0/29 and86B360/203 through DIR32+0x49/+0x51 (aggregate slots
+4/+8). The existing provider names are piChangeNickCallback,
piAuthenticateCDKeyCallback, Rva0086B2D0Disconnected and Rva0086B360Dispatch.
Their existing C contracts match the caller's 5/4/3/5 arguments; all primitive
and opaque pointer types, C linkage, layouts, profiles and provider definitions
were retained. No EA name is inferred from an address. One frozen Source
form replaced four declarations/references and corrected two misleading
A-variant comments; the sibling zero-context patch banks that form only, not CSV edits
(inspect with git apply --unidiff-zero; normal writers remain mandatory).

Existing native C-owner fix 8337c57e34 and published R01 exercised the changed
code-owner prerequisite. All four provider code-owner checks returned no
problem. This does NOT establish retirement admission: the native writer
has a separate name-regression guard.

## Exact normal refusal and rollback

Normal BEFORE exit 1, 723.5s: LINKED 0->0, own 3615 B; exactly four unresolved
names (_piChangeNickCallbackA, _piAuthenticateCDKeyCallbackA,
_piChatDisconnectedA, _piChatPrivateMessageA). The native near-packet request
also refused the whole file at census 42237e2367; that result is retained,
not presented as an accepted near task or a fresh global census.

After indexing the single candidate, normal dir32_record.py retire accepted
the first two completion callbacks. The third refused:

    _Rva0086B2D0Disconnected is an address-derived/placeholder name; it may not replace descriptive _piChatDisconnectedA

No fourth retirement, candidate compiler or AFTER ran. This is the stated
native naming policy, not a byte mismatch or a privately declared verifier
false rejection. Do not preserve a two-name partial fix, leave obsolete
records as a bypass, relabel the neutral providers, invent aliases/pins,
or weaken that guard. Future naming work requires independent evidence and
the prescribed native admission, not simply a wanted descriptive spelling.

Restored the exact Source b23fd3cb018de87c30b8cdf47993601c947158c0c802c2ac3eca83ba9d6dbdbc
and complete record transaction to baseline, including both accepted drops.
Normal restored five-TU control passes 164/164 + 87 DIR32, 14 literals + 4 empty
strings, static_ok 6, seven jump-table entries and zero baseline findings.
All five actual runtime/FPO/COMDAT/EH/CRT/SafeSEH/weak/directive graphs
are identical to the original controls; the actual caller object is restored
SHA 62685565020d983208cfa0fffdab559d87684835d599e0a77a4ef9b961bb9dcf.
Seven owned claims were released unlanded with fresh remote owner/UUID/token
CAS, followed by native remote owner 0 proof. No foreign claim was targeted.

## Unchanged limits and donor

Both 69 B callers retain native UNKNOWN at their existing static piAddOperation
edge; Dispatch203 retains UNKNOWN for its three existing private/static helper
edges. The dispatcher anchors remain preexisting unchanged emitters, not
newly proven retail. peerCallbacks.c is normally whole-source verified but
uncacheable; ordinary-current=false is preserved. The UTM COMMON 8/512 buffers
already have their current peerParseUTM.c/143 provider. No data repair was
needed or admitted. No full-image link/runtime claim is made.

Reviewed fresh historical BFME2 e2e99959950e6eebfe1ced5663aa05de320afc52,
corresponding peerOperations.c and peerOperationsListGroupRooms.c (C in donor,
C++ here), relevant history and prior callback handoffs. Donor keeps obsolete
zero-argument declarations and forbidden alternatename directives. Neither
is ported. Original B1 operands and existing B1 provider APIs establish the
physical/ABI lead; they do not waive the native naming rule.

The compact sibling manifest binds useful original/restore receipts. Full
Source/object/context/decode/partial-transaction artifacts remain host-private
under diagnostics/ten-rounds-20261125-2054/bfme1/r02. No unchanged retry is
recommended until a legitimate naming prerequisite changes.

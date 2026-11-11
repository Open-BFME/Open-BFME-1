# Append helper emitter removal

Queue rank 68 at census 90c15cdeca reports the inline wrapper
`?helper@Gen_00896320@@QAEXPAX00@Z` as a non-retail COMDAT. The wrapper
forwards to the existing address-derived raw 316-byte owner at 0x008961E0;
it is not a reconstruction of that owner.

Marking this TU-local wrapper `__declspec(dllimport) __forceinline` removes
its out-of-line definition and all references under that helper name.
COFF symbol inspection confirms no imported helper reference either.
Normal scoped verification passes both append (54B) and resize (179B),
with unchanged compiler flags and dependencies. No ledger identity, alias,
pin, raw owner or shared header changes. The existing reconstruction bank
and stack-slot mismatch at 0x008961E0 are unaffected.

Read the helper's prior attempt-log entries and
`008961e0-gen00896320-helper-insert.md` before testing. Reviewed BFME 2
76f0baefa6 `Code/GameEngine/Source/Common/Bfme5ThirtyFour.cpp`; its real
insert implementation uses different iterator arguments and remains a
semantic lead, not a proven replacement for this target. This emission
repair uses the established local suppression convention. It imports no
donor layout, name or flags.

Census before: loser helper, 233 historical consumer bytes blocked.
Current linking is checked separately and remains unknown without current
dependencies; removing the wrong wrapper does not establish a linked-byte
gain. This records source-level linking progress, not new recovered bytes.

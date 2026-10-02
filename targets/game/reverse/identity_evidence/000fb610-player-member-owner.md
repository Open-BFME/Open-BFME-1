# RVA 0x000FB610 serializes the contained Player +0x684 record owner

The clean matched RecordVectorXfer000FB610::xfer(Xfer*) is 477 bytes.
Its authentic owning class spelling remains unproven. This evidence narrows
ownership without renaming it to the suggestive UnitRevivalTracker file name.
All addresses were checked against retail-1.03-unpacked lotrbfme.exe, base
0x00400000, with pefile and capstone.

## Native table and containing Player constructor

ILT RVA 0x00022543 (VA 0x00422543) is an E9 to target 0x000FB610.
Its sole absolute-pointer reference is table VA 0x01086090. That one-entry
virtual table is installed at receiver +0 by the matched constructor
0x000FB260 (BfmeOwnCCConstructor.cpp): MOV [ESI],0x01086090 at 0x000FB27E.
The constructor zeroes vector words at +4/+8/+C and copies its single input
pointer to +0x10 at 0x000FB298. The adjacent zero/floating constants are not
additional function slots.

The matched Player::Player(int) at 0x000DD980 (898 bytes,
Common/RTS/PlayerConstructor.cpp) supplies that input: PUSH ESI at 0x000DDC1F,
LEA ECX,[ESI+684h] at 0x000DDC20, CALL ILT 0x00010EB5 at 0x000DDC2B.
That ILT reaches 0x000FB260. This is a contained 20-byte object at
Player +0x684 whose +0x10 points back to its containing Player. It is not
an inferred secondary base or an owner guessed from function adjacency.
Matched PlayerInit and PlayerDestructor independently operate on +0x684.

## Serializer semantics corroborate the layout

The target transfers version/count and iterates the native 96-byte record
vector beginning at receiver +4. It serializes the player index obtained
from the pointer at +0x10, and restores it through ThePlayerList::getNthPlayer
on load. Its element serializer/copy constructor/erase/insertion contracts
are already matched. The existing source preserves this opaque owner rather
than pretending that the containing Player and contained receiver coincide.

RET 4 at RVA 0x000FB7EA is followed by INT3 at 0x000FB7ED, confirming
477 bytes. There is no corresponding Zero Hour Player member or BFME literal
that proves the contained class spelling; name_oracle Player+0x684 reports
no witnessed member name. UnitRevivalTracker.cpp is only an existing source
path, not binary name evidence. Keep the current address-derived class name.
This commit changes no game source, function row, pin, data or byte credit.

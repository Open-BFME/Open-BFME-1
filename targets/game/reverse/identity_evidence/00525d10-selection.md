# MpGameSetup::rva00525D10

The matched dispatch at RVA00529EC0 calls this exact existing spelling for
window-array+88 selections. This does not prove EA's method spelling: the
address remains. Retail is368 bytes, ending RET4 at00525E7D. Ghidra was
created at VA00925D10 and its368-byte extent cross-checked with Capstone.

The function validates receiver+8/+C through owner slot+24, clears byte+17,
reads the selected value through a four-byte adapter for receiver+88[index],
and obtains the GameSlot through canonical GameInfo::getSlot. It rejects
values below-1, unchanged/out-of-range values, and values used by another
slot, then returns the byte from owner slot+0C. The slot value at+C and the
settings view+34/+3C are kept as offset-based accesses rather than invented
member identities. Global TheMultiplayerSettings is VA012ED5FC.

Independent callee decoding:4B5A60 copies the pointer passed by reference
into[ECX] and RET4;4B5A70 is RET;4B5BC0 returns the selected row via an
out-pointer;4B5C30 accepts one row-sized argument and RET4;61E8B0 loads
receiver+14[index] and RET4. Existing Gen_004b5a60/Gen_004b5a70,
BfmeC1040/BfmeThingCCH declarations retain the existing ledger spellings.
No new semantic callee pin is introduced. The actual GameInfo header is
included; GameWindow and MultiplayerSettings remain incomplete pointer types.

EH ownership is independently proved by prologue handlerC30358 ->
FuncInfoE202B0 -> one unwind entry -> cleanupC30350, which addresses the
four-byte local[EBP-10] and jumps via ILT3EB53 to empty4B5A70. A normal C++
scoped adapter supplies this lifetime. This is ordinary VC7.1 cleanup,
not the protection/foreign-frame mechanism suggested by older verdicts.

Shape: a typed bridge for getSlot produced333B; its actual canonical member
call produced376B with merged guards. Separate early returns reproduced368B
exactly modulo relocations, including the split saved-register epilogues.
Strict add_match validation is required before promotion.

Strict add_match passed all 368 bytes and its singleton DIR32 operand.

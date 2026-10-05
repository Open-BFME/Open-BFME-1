# Remove-friend callback 00514DA0

2026-10-03, n2, model=gpt-6-astra.

The retail constructor at RVA 005160E0 registers the literal
`AptInGameChat::OnBttnRemoveFriend`: RVA 005163EC pushes VA 011055CC,
005163F5 loads EBP with ILT VA 00418DD1, and 0051641E stores that callback
into the registration record passed at 00516429/00516435. The five-byte ILT
00018DD1 jumps to body 00514DA0. The constructor selector proves the
callback name is `OnBttnRemoveFriend`. The source uses that name.

Raw unpacked retail bytes end in RET 4 at 00514FFE..00515000, with INT3
starting at 00515001: 609 bytes. Ghidra independently created a 609-byte
function and decompiled the same selected-ID vector, localized confirmation,
callback-pair construction, and vector cleanup. The singleton is VA 012F4988;
its friends-list field is +264. The selector label does not identify new fields.

The served bank emitted 613 bytes, reloading vector begin in cleanup.
Putting the genuine existing 511-byte selection helper 00513BF0 in the same
TU makes the pointer nonescaping to MSVC and removes the reload. Removing
the bank's `_ReadWriteBarrier` then restores the load/count-test order and
matches all 609 bytes. The helper itself remains exact at 511 bytes, ending
RET 10 at 00513DEC..00513DEE before INT3. Its source algorithm is unchanged;
no invented pure stub, volatile storage, or compiler switch forces the result.
The helper stays in its original source and retains its sole ledger row.

The canonical WWLib UnicodeString and StringBase headers replace both local
string classes. Ordinary inline constructor/destructor/assignment definitions
retain the existing StringBase copy, set, and releaseBuffer calls. The explicit
qualified StringBase constructor call is the established MSVC spelling used by
Rva00784900GetText.cpp; placement-new instead transposed six EH setup bytes.
No shared header changes are required.

The existing lookup binding at 0003DAF5 -> 00512890 is retained. That body
ignores incoming ECX and returns with RET 8; the caller's member ABI view
preserves the retail singleton load without adding another identity or pin.
The existing selection helper binding 00017373 -> 00513BF0 has four stack
arguments and RET 10. The callback pair and dialog declarations retain the
already verified Open2/Bfme5 holder ABI and original callback ILTs 00040584
and 0002B878. The string labels are the shipped `APT:RemoveFirendTitle`,
`APT:RemovieFriendMessage`, and `APT:RemovieFriendMessageMulti`.

The add-friend twin 005151F0 is held by another worker and is not changed or
claimed here. Its bank helped establish the shared pattern, but supplies no
additional coverage in this commit.

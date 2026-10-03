# In-game chat AddFriend callback, RVA 0x005151F0

The already matched `BfmeAptScreenInGameChat` constructor at RVA 0x005160E0
registers the shipped selector `AptInGameChat::OnBttnAddFriend`:

- RVA 0x00516391 pushes VA 0x011055F4, the selector string.
- RVA 0x0051639A loads EBP with ILT VA 0x0041CE63.
- The following binding stores that pointer as the callback and the screen
  receiver alongside it. The matched constructor source shows the same binding.
- ILT RVA 0x0001CE63 is `E9 88 83 4F 00`, targeting RVA 0x005151F0.

This proves the method name independently of the byte match. The established
owner spelling remains `BfmeAptScreenInGameChat`; the Apt selector is its runtime
registration name. Ghidra creates exactly 609 bytes at VA 0x009151F0. Retail's
last `ret 4` is RVA 0x0051544E, followed by INT3 at 0x00515451.

## Source context that closes the near miss

The bank emitted 613 bytes, reloading the selected vector's start at cleanup
instead of retaining EDI. Including the **real, already matched** selection
helper definition (RVA 0x00513BF0, 511 bytes) before this caller eliminates that
reload. With the bank's `_ReadWriteBarrier` still present, six scheduling bytes
remain; removing the barrier gives all 609 bytes. Merely declaring the helper
or changing pointer lifetimes had failed in earlier attempts.

The callback now lives in the helper's existing TU. There is no synthetic
caller/helper and no unmatched companion. Both the 511-byte helper and the
609-byte callback pass strict byte and relocation verification together.
The TU adopts the canonical UnicodeString/StringBase headers, so destruction
names `releaseBuffer` directly instead of the bank's ambiguous destructor pin.
The original helper body and its owner layout are preserved. No symbol pins
or shared headers change.

# RVA 0x008D6010: packed reference release, native owner unresolved

This recovery deliberately retains the address in `Rva008D6010Node`.
No native class or method spelling is claimed. All binary facts below were
checked against `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`
with pefile and Capstone (image base 0x00400000).

## Extent and dispatch evidence

The body starts at VA 0x00CD6010 with `push esi; push edi`, ends at
0x00CD60B2 with `ret`, and is followed by INT3. Its extent is 163 bytes.
There is also a virtual tail dispatch at +0x9D to receiver slot +8.

No executable E9 stub targets this body. Its VA occurs as a dword at exactly
three addresses: 0x011376D4, 0x01137724 and 0x01137774. GhidraMCP's
`search_byte_patterns("10 60 CD 00")` returned the same addresses.
These are slot 1 of vtables at 0x011376D0, 0x01137720 and 0x01137770.
Their slot 0 is body 0x008D5F40, which increments the packed count, and
slot 2 is body 0x00891810. Retail stores the first two table bases at
0x00CD5FD0 and 0x00CD5FF0; a constructor stores the third at 0x00CD6126.
Those owners and neighbours remain address-derived in the ledger, so this
is dispatch and family evidence, not a native identity proof.

## State and callees

The count occupies bits 16..27 of the dword at receiver +4. Receiver +0x14
holds a pointer with low-bit tagging. The guard checks a non-null masked
pointer against the global at VA 0x013379BC, count 2, and the pointee's
packed kind/flag/count dword. It conditionally calls pointee slot +4,
clears receiver +0x14 and reloads the count from the word at +6.

The one direct call at +0x6E targets RVA 0x008D1F80. Its matched source
names it `BfmeThing936F::bfmeGo936F`; independent retail decoding confirms
that it decrements a word at its receiver +0x60 and triggers further work
when that word becomes zero. The recovered body calls it on receiver +0x2C.
The body clamps the decremented count to 0xFFF, inserts it into the packed
dword, and dispatches receiver slot +8 if the decremented count is zero.

## C++ shape and verification

The preserved bank emitted 163 bytes with a seven-byte adjacent swap at
+0x57/+0x59: its null store preceded `xor esi,esi`, whereas retail zeroes
ESI before the store and then loads SI from receiver +6. Making just the
late high-word view volatile, and removing the `_ReadWriteBarrier`,
reproduces the full instruction stream. Making the entire bitfield view
volatile emits a dword load and shift instead, which is wrong.

The source uses a union of the packed dword, bitfields and two words, with
only the +6 word view volatile. It declares this recovered body as virtual
slot 1, agreeing with all three retail tables. The native identity remains
unresolved; byte matching does not change that conclusion.

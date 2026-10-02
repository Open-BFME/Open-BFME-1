# RVA 0x007986C0: seven-word text drawing helper

The pinned ten-argument drawTextEntryText spelling is not a valid ABI for this
native body. The caller pairing supports a text-entry drawing role, but both
caller identities remain address-derived; no authentic helper spelling is claimed.

Retail entry routes are direct calls at 0x00799111 from body 0x00798F30 and
0x007994EC from body 0x007991A0. Neither body nor entry has a stored pointer.
First caller pushes EAX at 0x00799102, EDI at 0x00799107, EDX at 0x00799108,
EAX at 0x0079910D, ECX at 0x0079910E, EDX at 0x0079910F, and ESI at
0x00799110; after the call it adds ESP,0x1C at 0x00799116. Second caller
pushes at 0x007994DD/E2/E3/E8/E9/EA/EB and likewise reclaims 0x1C at
0x007994F1. Thus seven cdecl stack words are independently witnessed twice.

The callee obtains a window-associated text record through ILT 0x00046538
(target 0x00478C70), repeatedly reads/copies UnicodeString state and calls
virtual display-string methods. Its input stack loads and plain RET agree with
the callers. Zero Hour W3DTextEntry.cpp has a similarly placed TU-static text
helper with ten arguments, but source order and semantic similarity cannot
prove BFME's original spelling or repair its decorated signature.

RET at 0x00798D77 and INT3 at 0x00798D78 delimit 1720 bytes. All push/call/
cleanup instructions and routes were checked against retail-1.03-unpacked
lotrbfme.exe via pefile/Capstone. This evidence does not change the pin or
production dump, and does not claim a conversion.

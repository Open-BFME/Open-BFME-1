# BannerUI body at 0x005841D0

## Identity and extent

The already matched Gen_002ed8c0 forwarder loads VA 0x012F4B70 into ECX
and tail-jumps via ILT RVA 0x0003514D to this body. The existing
INIBannerType.cpp documents the BannerUI constructor at 0x005849E0 passing
"TheBannerUI" to the subsystem base constructor; the matched BannerType
parser uses this receiver's hash table at +8. These establish the owner,
not a recovered EA method name. Retain `BannerUI::rva005841D0`.

Independent Capstone decoding of the unpacked retail image shows the final
RET at RVA 0x005842E7 (+0x117), followed by INT3. The contiguous extent is
280 bytes. Ghidra's VA 0x009841D0 decompilation confirms the local pair,
entry fields, ignored scan result, slot loop, BannerRohan lookup and append.

## Source change

The bank emitted 282 bytes with an extra `xor ecx,ecx` for the second
zero argument. Zeroing the pair's array with ordinary `memset` restores
280 bytes and all register choices, leaving ten differing bytes from three
reordered instructions. Moving that pair construction after the movie-entry
initialization also restores the `xor ebx,ebx` schedule: all 280 bytes match.
The emitted code contains no memset call. The canonical `ascii_string.h`
retains the exact result; no shared header is edited.

The scan still passes the zero pair by value and discards its return value.
The following loop tests the original local. This surprising retail behavior
is not silently repaired. The existing 64-byte scanner at 0x00581B70
independently walks 28-byte entries, checks each +4 tag against 2 and writes
only its by-value pair and returned pair. Its visibility did not improve the
caller. An explicit pair copy constructor grew the caller to 293 bytes;
the sibling fill constructor gave 282 bytes. Neither trial was promoted.

## Dependencies and validation

The existing scanner, hash lookup at 0x00583580, AddBanner at 0x0050D400,
and vector append at 0x00583AE0 supply the existing ABI bindings. The
matched BannerType parser establishes the AsciiString-keyed hash map with
four-string mapped value; its field names remain opaque. The entry's
28-byte stride and +4 tag agree with the scanner and existing append body.
No new symbol pin or helper identity is introduced.

`add_match.py --replace-rva 0x005841D0` passed the strict scoped gate:
1/1 function, all call bindings, and the one BannerRohan string literal.

# RVA 0x00846AD0 / 0x00846AF0 / 0x00846B10 wrappers

Retail decoding independently establishes these three complete functions,
formerly combined into one 109-byte generated dump:

- 0x00846AD0: RET at +0x1E, INT3 at +0x1F; 31 bytes.
- 0x00846AF0: RET at +0x1E, INT3 at +0x1F; 31 bytes.
- 0x00846B10: RET at +0x2C, INT3 padding follows; 45 bytes.

The preceding function returns at 0x00846ACC; three INT3 bytes precede the
first entry. All 107 executable bytes are recovered; only the two internal
INT3 separators leave the function ledger.

## Wide name-matcher ABI

The calls at 0x00846AE6 and 0x00846B06 target 0x00837190 and 0x00836F50,
respectively. Both callees are independently matched in
`game/Libraries/Source/WWVegas/WWLib/TimeGetWideMatch00836F50.cpp` and each
has 375 retail bytes. Their explicit instantiations establish wide input
iterators (`unsigned short`, VC7.1's default wchar_t representation), but
narrow `basic_string<char>` locale-name tables. This is not an automatic
substitution of wstring into the narrow wrapper.

The original native STLport `_time_facets.c` template and these verified
providers establish two input-iterator references, two narrow string
pointers, and the distance-type pointer. The long and int specializations
are distinct names and addresses. Each wrapper forwards its four incoming
slots plus a null distance pointer, cleans 20 bytes, and propagates the
callee's result. Explicit specialization declarations prevent extra local
provider emission.

## Wide stream-copy ABI and exact target

0x00846B10 calls 0x0083A2D0 at 0x00846B31. The existing address-specific
`bfmeRva0083A2D0CopyWide` declaration and pin are already used by the matched
wrapper in `game/stlport/WideStreamCopy.cpp`; the existing duplicate ledger
row owns the native STLport `__copy` specialization in
`game/stlport/NumFacetsInstantiations.cpp`. No new pin or identity is added.

Independent decoding confirms the callee's complete 106-byte extent, RET
at +0x69 followed by INT3. Its pointer difference is shifted right by one;
it loads/stores 16-bit characters, advances the source and output put
pointer by two, compares the virtual overflow result with 0xFFFF, and
stores a two-word iterator result through the hidden return pointer.
This establishes the native wide iterator ABI separately from the narrow
114-byte body. Seven cdecl slots are forwarded: hidden result, first,
last, two-word output iterator, category reference, and null int pointer.
The caller cleans 28 bytes and returns the hidden result pointer.

Ghidra 12.1.2 read-only inspection on 2026-10-03 independently reports
31-, 31-, and 45-byte entries plus the 106-byte wide copy callee. Inferred
Ghidra return types are not used as ABI proof. Each wrapper keeps an
address-derived identity because its precise original template name is
not established by this shared forwarding shape.

The three fresh probes are exact modulo relocations. `add_match.py` and
the combined scoped build validate real direct-call destinations and
recheck the prior narrow wrappers in the same source file.

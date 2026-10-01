# RVA 0x00769B60: adjusted string forwarding

The retail interval `[0x00769B60, 0x00769BFF)` contains 159 executable
bytes. Its `ret 12` starts at offset `0x9C`; INT3 padding begins at `0x9F`.
The incoming receiver is retained in ESI. Three incoming pointer arguments
are forwarded, and the result is returned in AL. No semantic owner or original
method name is asserted: `Rva00769B60Interface::forwardString` retains the
address and describes the observed operation.

The body constructs an empty narrow string, then selects either its receiver's
string at `+0x1F8` when nonempty or the string at `+0xE8` of the object pointer
stored at receiver `-8`. The emptiness test reads the buffer's 16-bit length at
`+4`. It assigns the selected string, makes a by-value copy, adjusts the
receiver by `-0x0C`, and forwards through ILT `0x00012C92` to `0x00766AA0`.
The three string calls are the canonical `StringBase<char>` set, copy and
release bodies at `0x00887C90`, `0x00887B60`, and `0x00887940`.

The matched neighbor `0x00769C30` implements the same operation with field
offsets `+0x1FC` and related-object `+0xEC`. Its independent callee proof is in
[00769c30-string-forwarder.md](00769c30-string-forwarder.md). This recovery
uses the same existing address-qualified callee declaration and pin; it adds
no alternate identity, route, or pin for that body.

Current retail decoding confirms ILT `0x00012C92` is a five-byte jump to
`0x00766AA0`. The callee's entry reserves `0xBC` local bytes and saves four
registers, giving an entry-to-current-ESP displacement of `0xD8`. Its pointer
outputs are read at current ESP `+0xE4` and `+0xE8` and cleared when nonnull.
The established callee proof also identifies its nullable buffer argument at
`+0xDC`, by-value narrow string at `+0xE0`, both string cleanup paths, bool AL
result, and `ret 16` epilogue. The existing pin passes the current symbol-scoped
consistency check against the full 3386-byte body.

The C++ includes canonical `ascii_string.h`; it redeclares neither string
layout nor a known semantic owner. Its local `StringBase<char>::isEmpty`
specialization is the same source shape used by the matched neighbor.
`name_oracle.py` reports no witnessed layout for the address-qualified wrapper.
The final `add_match.py` scoped gate verifies all 159 bytes and the call
targets. Probe independently reports 159/159 bytes, eight relocation sites,
and no differences outside those sites.

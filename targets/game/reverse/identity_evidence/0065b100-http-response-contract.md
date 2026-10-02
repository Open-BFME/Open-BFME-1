# RVA 0x0065B100: address-qualified HTTP response member

Native C++ owner and method spelling remain unproved. The conversion keeps
the existing receiver name Rva0065B350 and uses `method0065B100`, retaining
the body address. This preserves the bank's existing address-qualified label; no native method identity is claimed.

## Receiver, arguments and extent

Retail callback RVA 0x0065BCC0 (already matched in the same TU) loads the
final context argument into ECX, guards null, pushes the five request
argument words, and calls ILT VA 0x0043EA59 at VA 0x00A5BCE7. That ILT
targets this body. The function uses receiver+0x5C as the same pointer-map
subobject that the existing response member and erase helper use.

The body consumes key, status, text and two timestamp words. Its normal
epilogue has RET 0x14 at RVA 0x0065B295 (+0x195); the final error block
ends with a jump back to that epilogue at +0x1D0. Complete extent is 466
bytes. The final context belongs to the callback, not the member signature.

The retail guard order is missing map entry, null payload, then status.
On success it trims the text, finds a comma, rejects a missing/empty second
field, parses both fields, rejects zero values, and queues a type-3 response
before erasing the request key. Response values reside at offsets 0x1C8,
0x1CC and 0x1D0; its existing PSPlayerStats constructor/destructor and
1F0-byte response layout are retained.

## Dependency evidence and verification

`tools/callees.py 0x0065B100 466` identifies seven direct targets and the
strstr import. The actual calls are the existing pointer-map find/erase
instantiations, StringBase<char> constructor/trim/release, and PSPlayerStats
constructor/destructor. The map erase declaration already exists in this TU;
the old scratch bank omitted it. No dependency pin or shared header changed.

The adapted bank compiles to exactly 466 bytes with 20 relocation sites.
`tools/probe.py` reports EXACT modulo relocations. `tools/add_match.py` and
the scoped build validate the actual retail call and data bindings before
the source and ledger conversion are committed. This supersedes the stale
missing-declaration/build-timeout blocker without asserting a native name.

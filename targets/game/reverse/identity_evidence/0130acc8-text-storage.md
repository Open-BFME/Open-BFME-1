# Address-derived text storage at VA 0x0130ACC8

This defines the existing `char g_Rva0130ACC8Text[20]` view of a witnessed
20-byte retail storage interval and capacity. It does not assert an original
vendor array name or exact vendor source declaration. The address-derived name,
caller and formatter signatures remain unchanged; there are no new pins,
aliases, headers or function rows.

## Independent retail witnesses

- Matched address formatter caller RVA `0x007FFB50`, 186 bytes, pushes capacity
  `20` at VA `0x00BFFBB4`, pushes buffer VA `0x0130ACC8` at `0x00BFFBB6`, calls
  matched formatter RVA `0x007FF860`, and returns the same buffer pointer with
  `mov eax,0x0130ACC8` at `0x00BFFBC7`.
- Independent matched record creator RVA `0x008064A0`, 223 bytes, reads its
  epoch DWORD at VA `0x0130ACDC` in the instruction at `0x00C064DA` and writes
  it at `0x00C064E8`. That datum starts exactly 20 bytes after this buffer.
- The whole `[0x0130ACC8,0x0130ACDC)` interval is inside the PE `.data` virtual
  tail beyond its declared raw extent, hence genuinely zero-filled. A scan
  of every PE raw section finds only the two buffer operands above and the
  independent epoch operands at the interval boundary, with no interior
  literal-address references. The data ledger has no other overlapping owner.

Together these witnesses delimit the nonoverlapping storage interval and
agree with the existing 20-byte capacity view. They do not exclude a shorter
original source allocation followed by padding; no such stronger claim is
made. The actual formatter's maximum dotted-quad text length is not used to
infer the allocation size.

## Compiled provider and strict controls

The only functional source edit changes the existing array declaration into
a definition. MSVC emits one external COMMON symbol with its own size 20.
Official `add_data_match.py` verifies those 20 zero-filled bytes at the retail
address using that independently compiled COMMON size, without a raw size
override. The scoped gate passes data 1/1, functions 10/10 and four DIR32
references; before the edit it passed functions 10/10 and the same four DIR32
references. Independent original/candidate object comparison confirms all ten
matched bodies and their named relocation records are unchanged.

The strict DLL control retains the actual 186-byte caller, actual 303-byte
formatter and native COMMON provider from the compiled object. It uses
`/DLL /NOENTRY /OPT:NOREF`, no `/FORCE`, and the corrected Linux path handling.
Positive LINK exits 0 and emits a valid fresh PE/MAP. Both buffer operands
address the MAP-selected native provider, which contains 20 zeros. The caller
and formatter match retail outside original relocation fields, and all their
REL32 operands land on their actual named MAP destinations. The omitted
provider control uses the original object and excludes this symbol from
stubs: LINK exits 96 with LNK2019 on `_g_Rva0130ACC8Text` and LNK1120.

Unrelated dependencies are explicitly labelled link-only stubs in the
receipts: RTC helpers, security-cookie helpers/data, and three other address
helpers in the shared text section. The real formatter is not stubbed. This
proves selected caller/provider binding, not runtime execution or complete
image closure.

Scratch evidence is under `build/datum_text/`: `retail_span.json`,
`before.obj`, `after.obj`, `after_gate.log`, `controls.py`, `controls.json`,
positive PE/MAP/log and missing-provider log. The historical queue projection
is 1,900 bytes; no new census or closure gain is claimed. This adds exactly
20 verified data bytes and zero authored function bytes.

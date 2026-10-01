# Address-derived DWORD storage view at VA 0x012EF418

The original global identity and signedness are unproven. This repair defines
only an opaque unsigned 32-bit storage view, `g_Rva00EEF418`, and replaces the
three existing unsigned `g_bfmeDirtyBG` views with that address-derived name.
It makes no native semantic-name claim. No native header covers this BFME
datum: the available PolygonTrigger header declares a list and ID counter,
but no corresponding global. Built-in `unsigned int` and the existing native
`UnsignedInt` typedef provide the unchanged four-byte ABI view.

## Independent physical witnesses

| Matched body | Extent | Retail storage instructions |
|---|---:|---|
| `Rva0018EEF0Owner::scaleTriples` at RVA `0x0018EEF0` | 121 | VA `0x0058EEF4`: `or dword ptr [0x012EF418],1` |
| Address-derived polygon-parser constructor at RVA `0x00190E10` | 135 | VA `0x00590E76` loads the DWORD; VA `0x00590E82` stores it |
| `WaterRenderObjClass::update` at RVA `0x007A7D70` | 1342 | VA `0x00BA7DDA` tests bit zero; VA `0x00BA7DEF` ANDs the DWORD with `0xfffffffe` |

These independently compiled callers witness the same storage width and
address through mutation and consumption, without deriving a global name
from an old pin. The four bytes are entirely within the PE `.data` virtual
zero-filled tail, and no other data row owns or overlaps them. The separately
referenced list-context cell at `0x012EF41C` begins immediately afterward.
The original signedness cannot be recovered from these bit operations; the
unsigned declaration is explicitly a storage view, not an original type claim.

Backend claims were checked before edits: no globals or strings family lease
was active. All signed and other candidate aliases, including
`TheBfmeDrawableDirtyFlags`, retain their existing declarations and pins. No
compatibility alias or second provider is created, and no closure of those
other references is claimed. The complete unsigned-reference audit found
exactly these three TUs.

## Verification and adversarial controls

- Official `add_data_match.py` proves `sizeof(::g_Rva00EEF418)==4` under the
  real build flags, a four-byte COFF allocation, and four retail zero bytes.
  No explicit size override is used.
- Scoped gates before and after pass all three bodies, 32 float constants
  and 33 DIR32 references; the after gate also passes data 1/1.
- Independent original/candidate object comparison proves identical body
  bytes and identical named relocations after replacing only the old global
  identifier with the address-derived identifier.
- Existing pin-consistency checks pass. No pin or shared header changes.
- Strict positive LINK exits 0 without `/FORCE` and emits a fresh PE/MAP.
  The actual native data section from the compiled owner is selected, with
  four zero bytes. All five actual caller operands reach that provider;
  all three bodies match retail outside original relocation fields and all
  REL32 operands reach their named MAP destinations.
- Missing-provider control retains the repaired callers but omits only the
  real provider and excludes its name from stubs: LINK fails with LNK2019
  and LNK1120. Old-alias control supplies the real provider to original
  callers while excluding their obsolete global name from stubs: it also
  fails with LNK2019 and LNK1120. Exact exit codes and logs are in the receipt.

Unrelated functions, literals, globals and import-shaped dependencies are
explicitly labelled link-only stubs in `build/scalar_flags/controls.json`.
This is selected native datum binding proof, not a native-import or runtime
closure claim. No gain is inferred from the historical 1,463-byte queue
projection; the repair adds four verified data bytes and zero authored code.

Scratch evidence: `build/scalar_flags/` contains original and candidate
objects, three native caller slices, the actual native provider object,
strict positive/missing-provider/old-alias PE/MAP/log artifacts,
`controls.py`, `controls.json`, scoped gate logs, callee output and pin check.

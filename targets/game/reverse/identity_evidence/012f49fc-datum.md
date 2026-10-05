# Datum identity at VA 0x012F49FC

The selected storage declaration is `BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

The body at RVA 0x00545310 tests and publishes this receiver and registers the EA string AptOnlineCustomMatch::InitGadgets. Destructor RVA 0x00538CE0 compares and clears the slot. Factory RVA 0x0055BCA0 rejects another instance when this slot is set. symbols.csv already carries this exact pointer spelling and destructor evidence. RVA 0x00539350 and RVA 0x00539370 load the pointer into ECX before forwarding a boolean argument through ILT RVA 0x0000C955. The s_popBackExtra local view belongs to that same object slot; it is not separate storage.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x004F0750` | R |
| `0x004F0760` | R |
| `0x00538CE0` | R, W |
| `0x00539350` | R |
| `0x00539370` | R |
| `0x0053A710` | R |
| `0x0053EDD0` | R |
| `0x00545310` | R, W |
| `0x0055BCA0` | R |
| `0x00672A60` | R |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?Data00EF49FC@@3PAVGen0000C955@@A` | 0 |
| `?TheBfmeOnlineCustomMatch@@3PAVBfmeAptScreenOnlineCustomMatch@@A` | 4 |
| `?g_Va012F49FC@@3HA` | 1 |
| `?g_s4Guard0055BCA0@@3PAXA` | 1 |
| `?s_popBackExtra@@3PAVRva00537C00@@A` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A constructor publication or destructor comparison with a different receiver, or a different object allocation stored here, would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49fc-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

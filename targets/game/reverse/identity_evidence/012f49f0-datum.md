# Datum identity at VA 0x012F49F0

The selected storage declaration is `BfmeAptScreenOnlineChat *TheBfmeOnlineChat`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

Constructor RVA 0x00536DC0 tests and publishes this receiver. Its EA strings identify AptOnlineChat callbacks. Destructor RVA 0x0052D7C0 compares the same slot with its receiver and clears it. The factory at RVA 0x0055BB20 rejects another instance when this pointer is set. symbols.csv already pins TheBfmeOnlineChat with this exact class pointer spelling and the destructor evidence. The alternate struct and erased guard spellings describe views of the same scalar pointer, not additional identities.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x0052CE20` | R |
| `0x0052D7C0` | R, W |
| `0x00534A60` | R |
| `0x00536DC0` | R, W |
| `0x0055BB20` | R |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeOnlineChat@@3PAVBfmeAptScreenOnlineChat@@A` | 3 |
| `?g_bfmeObjECE@@3PAUBfmeObjECE@@A` | 1 |
| `?g_s4Guard0055BB20@@3PAXA` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A constructor that publishes a different receiver, another factory-owned object in this slot or a destructor comparison with a different address would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49f0-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

# Datum identity at VA 0x012F4A0C

The selected storage declaration is `void *TheBfmeOnlineHomeSlot`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

Constructor RVA 0x005484E0 publishes its unadjusted BfmeAptScreenOnlineHome receiver when the cell is null. Its EA strings name the AptOnlineHome callback family. Destructor RVA 0x00545FF0 compares and clears the cell. Factory RVA 0x0055BAA0 uses the same slot as a duplicate-instance guard. The existing role name is pinned in symbols.csv. All existing declarations of both spellings use void *, so the correction retains that erased storage type while documenting the independently proven OnlineHome pointee role. It introduces no invented alias type or class hierarchy.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x00545FF0` | R, W |
| `0x005476C0` | R |
| `0x005484E0` | R, W |
| `0x0055BAA0` | R |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeOnlineHomeSlot@@3PAXA` | 3 |
| `?g_s4Guard0055BAA0@@3PAXA` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

An OnlineHome constructor publication to another slot or a different receiver stored here would refute this choice. A direct original declaration would settle whether retail used the erased pointer type or a typed class pointer.

Raw evidence: `build/rlink/identity-012f49-20261005/012f4a0c-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

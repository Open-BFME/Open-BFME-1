# Datum identity at VA 0x012F4978

The selected storage declaration is `AsciiString g_guiFxFile`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

RVA 0x00C6BBD0 pushes the EA literal GuiFX.apt from VA 0x011051E0, loads this datum address into ECX and calls ILT RVA 0x00012C42. Its five bytes are E9 29 C2 04 00 and reach the existing AsciiString constructor at RVA 0x0005EE70. RVA 0x00510FA0 passes the address to the char StringBase copy constructor at RVA 0x00887B60 before the Apt window load. Cleanup RVA 0x00C701C0 passes the same address through ILT RVA 0x0000D828, then the five-byte jump at RVA 0x0005EE90, to char releaseBuffer at RVA 0x00887940. This is a single string object containing one buffer pointer, rather than a pointer slot or the unrelated invented Gen class.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x00510FA0` | ADDRESS |
| `0x00C6BBD0` | ADDRESS |
| `0x00C701C0` | ADDRESS |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeObject_00C701C0@@3VGen_00C701C0Target@@A` | 1 |
| `?g_guiFxFile@@3VAsciiString@@A` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

An initializer using another literal or constructor, a cleanup route to the wide-string body, or an access beyond the four-byte string object would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f4978-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

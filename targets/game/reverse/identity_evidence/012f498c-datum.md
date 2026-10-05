# Datum identity at VA 0x012F498C

The selected storage declaration is `UnicodeString g_unicode12F498C`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

Startup RVA 0x00C6BC00 loads this address into ECX and calls ILT RVA 0x00041C95. The five-byte E9 jump reaches the default string constructor at RVA 0x00083D10, which zeroes exactly the first dword. It registers cleanup RVA 0x00C701D0. That cleanup follows ILT RVA 0x0003B304 to the five-byte jump at RVA 0x0005EEA0, then to the wide releaseBuffer body at RVA 0x008881D0. RVA 0x00512670 assigns the GadgetTextEntryGetText UnicodeString result to this object through the existing wide assignment body at RVA 0x00888530; its empty arm supplies UnicodeString::TheEmptyString. RVA 0x00515E60 copies it through the wide StringBase copy body at RVA 0x00888400 before setting the chat entry text. The existing UnicodeString definition is retained; the invented Gen cleanup receiver is respelled to this same object.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x00512670` | ADDRESS |
| `0x00515E60` | ADDRESS |
| `0x00C6BC00` | ADDRESS |
| `0x00C701D0` | ADDRESS |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeObject_00C701D0@@3VGen_00C701D0Target@@A` | 1 |
| `?g_unicode12F498C@@3VUnicodeString@@A` | 3 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A cleanup route to the char releaseBuffer body, a copy through the char StringBase body, or a receiver extent different from one data pointer would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f498c-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

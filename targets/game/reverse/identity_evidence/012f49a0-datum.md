# Datum identity at VA 0x012F49A0

The selected storage declaration is `AsciiString g_aptLivingWorldCachedName`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

RVA 0x00C6BC20 pushes LivingWorldUI.apt from VA 0x01105F90, loads this address into ECX and calls the same AsciiString constructor ILT as g_guiFxFile. It registers cleanup RVA 0x00C701E0. That cleanup reaches the char releaseBuffer body through the exact same two five-byte E9 jumps as g_guiFxFile. RVA 0x0051AB40 copies this object through char StringBase copy construction before the Apt window load and registers the AptLivingWorldUI callback family. The BFMERetailAsciiString declaration is a local string view; the actual constructor identity establishes AsciiString. Defining the literal-initialized object also emits its existing 27-byte startup body. The generated startup row retains its name and extent and is repointed to the owner using object-symbol=_$E1. The generated assembly file is not edited.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x0051AB40` | ADDRESS |
| `0x00C6BC20` | ADDRESS |
| `0x00C701E0` | ADDRESS |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeObject_00C701E0@@3VGen_00C701E0Target@@A` | 1 |
| `?g_aptLivingWorldCachedName@@3VBFMERetailAsciiString@@A` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

An initializer using another literal, a route outside the AsciiString constructor and char cleanup bodies, or a byte change in the existing 27-byte startup body would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49a0-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings.

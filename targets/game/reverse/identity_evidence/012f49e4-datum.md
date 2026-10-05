# Datum identity at VA 0x012F49E4

The identity is unresolved. No datum definition or spelling change is authorized by the evidence below.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

RVA 0x0052C660 tests this cell and publishes its receiver at VA 0x0092C6D3. It registers both AptObjectivesMenu and AptPlayerStatus callback strings. Its ledger name is BfmeAptScreenObjectives. Destructor RVA 0x0052BEC0 compares and clears the same cell, while its ledger name is AptPlayerStatus. Other bodies use PlayerStatus.apt and Objectives.apt through this instance and write receiver fields. This establishes one zero-initialized four-byte object-pointer slot and rejects the integer view as an object identity. It does not settle which existing competing receiver class names is authoritative. The original two datum spellings are left unchanged.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x0052ADE0` | R |
| `0x0052AFE0` | R |
| `0x0052B2A0` | R |
| `0x0052BEC0` | R, W |
| `0x0052C660` | R, W |
| `0x00588800` | R |
| `0x00598950` | R |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?g_Va012F49E4@@3HA` | 1 |
| `?g_obj12F49E4@@3PAXA` | 6 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A proven vtable owner identity or a matched independently named factory that establishes the receiver class and reconciles the constructor and destructor names would settle the pointee type.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49e4-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

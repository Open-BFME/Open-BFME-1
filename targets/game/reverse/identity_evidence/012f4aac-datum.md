# Datum identity at VA 0x012F4AAC

The selected storage declaration is `BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

Constructor RVA 0x005538A0 publishes its receiver in this cell and registers the AptOnlineLogin callback family. Destructor RVA 0x0054CB60 compares and clears it. Factory RVA 0x0055BA20 uses it as the duplicate-instance guard. Login submission and locale-acceptance bodies use it as a member-call receiver. symbols.csv already has the exact selected pointer spelling, including the destructor evidence. The integer getter returns its pointer bits in EAX; the struct and erased views do not establish another datum identity.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x004E9B20` | R |
| `0x004EE510` | R |
| `0x0054CB60` | R, W |
| `0x0054CC60` | R |
| `0x00551DB0` | R |
| `0x00551DD0` | R |
| `0x005533F0` | R |
| `0x00553520` | R |
| `0x005536F0` | R |
| `0x00553880` | R |
| `0x005538A0` | R, W |
| `0x0055BA20` | R |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?Rva012F4AACLoginScreen@@3PAURva004EE510Login@@A` | 1 |
| `?TheBfmeOnlineLogin@@3PAVBfmeAptScreenOnlineLogin@@A` | 8 |
| `?g_Va012F4AAC@@3HA` | 1 |
| `?g_bfmeObjELB@@3PAVBfmeObjELB@@A` | 1 |
| `?g_s4Guard0055BA20@@3PAXA` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A different constructor publication, a nonzero receiver adjustment or an independently witnessed incompatible receiver class at this cell would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f4aac-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Unresolved for landing. The typed OnlineLogin pointer identity is supported by the retail constructor, destructor and existing pin, and its candidate passed Functions: OK 77/77. The required declared-function gate refuses BfmeThingELAb::bfmeGoELAb in BfmeConv816.cpp and BfmeAptWindowContext::BfmeAptWindowContext in OnlineLoginConstructor.cpp. The restored originals produce those same two failures. Only this address's attempted changes and data row were restored. Resolving those helper declarations against their actual ledger identities, then passing the declaration gate, would allow this correction. Raw logs: `build/rlink/identity-012f49-20261005/012f4aac-declared.log`, `build/rlink/identity-012f49-20261005/012f4aac-declared-restored.log` and `build/rlink/identity-012f49-20261005/012f4aac-build.log`.

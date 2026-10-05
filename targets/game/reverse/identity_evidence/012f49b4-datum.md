# Datum identity at VA 0x012F49B4

The selected storage declaration is `BfmeAptScreenMainMenu *g_rva012F49B4MainMenu`.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

RVA 0x0051F3A0 tests this cell and publishes its unadjusted receiver at VA 0x0091F46A. The same constructor registers AptMainMenu::OnInitialized, AptMainMenu::GoodCampaign, AptMainMenu::EvilCampaign and the rest of the EA AptMainMenu family. It already has the BfmeAptScreenMainMenu constructor identity. Destructor RVA 0x0051D4A0 compares this cell with its receiver and clears it. Download and GameSpy bodies call the object or write the flag at receiver offset 0x259. Their download-state names describe a use of the MainMenu instance, not a separately allocated datum. The new spelling retains the address and uses the independently witnessed MainMenu receiver type.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x004C7470` | R |
| `0x004C78C0` | R |
| `0x0051D4A0` | R, W |
| `0x0051F3A0` | R, W |
| `0x00570170` | R |
| `0x00573000` | R |
| `0x0062E8B0` | R |
| `0x0062EA60` | R |
| `0x0062F760` | R |
| `0x0062F7F0` | R |
| `0x006300B0` | R |

Two additional absolute references at VA 0x008C7801 and VA 0x008C7861 lie outside the current ledger and Ghidra extents. They are retained in the raw reference log and receive separate disassembly probes. They do not establish additional data storage.

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?Data00EF49B4@@3PAVGen004C7470@@A` | 1 |
| `?TheBfmeDownloadState@@3PAVBfmeDownloadState@@A` | 1 |
| `?g_Va012F49B4@@3HA` | 1 |
| `?g_bfmeThingBHG@@3PAUBfmeThingBHG@@A` | 2 |
| `?g_rva012F49B4@@3PAURva012F49B4Thing@@A` | 3 |
| `?g_rva012F49B4@@3PAVRva0051D690@@A` | 1 |
| `?g_rva012F49B4@@3PAVRva012F49B4Thing@@A` | 2 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A MainMenu constructor publication to a different cell, a receiver adjustment at publication, or a distinct object stored by a different retail allocator would refute this choice.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49b4-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

## Final disposition

Corrected. The definition, data row and changed source declarations passed the scoped byte and declaration gates. Existing symbols.csv pins are unchanged. The selected DIR32 spelling was retained where already present and otherwise added beside the existing spellings. The previous TheBfmeDownloadState spelling is replaced by g_rva012F49B4MainMenu. The chosen spelling keeps the proven MainMenu role and the address; it does not claim an original EA global identifier.

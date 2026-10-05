# Datum identity at VA 0x012F49A8

The identity is unresolved. No datum definition or spelling change is authorized by the evidence below.

The retail cell is in `.data`. The tested extent is one four-byte scalar, with initial bytes `00 00 00 00` and no initial pointer relocation. These addresses are not FieldParse or name tables. The scalar pointer publications or string receiver accesses establish the storage shape; the count is one object. The raw operand census confirms the exact direct references into the retail image. The overlap probe finds no other data row overlapping this extent and no DIR32 name strictly inside it. Retail has no PE base-relocation directory, so relocation claims come from operand contracts and byte-verified COFF, not an invented PE relocation table.

RVA 0x0051AB40 stores the result of ILT RVA 0x0000FC4A, reached after duplicating the Apt window load result as two arguments. Startup RVA 0x00C6BC50 calls that same helper with two zero arguments and stores EAX. Every other witnessed use loads the four-byte value, pushes it twice and calls ILT RVA 0x000019F6. The first helper reaches RVA 0x00062EF0 and the second reaches RVA 0x0009B4B0. Both bodies may call an external callback through VA 0x012C233C with addresses of argument carriers. The observed code proves an opaque Apt Living World handle and its four-byte cell. It does not prove whether the helper returns a signed integer, an encoded handle or an opaque pointer. No observed use dereferences this value. The guessed BfmeX pointee types are not established, but the int versus void * choice also remains open.

## Receiver and argument contract

The cell itself is addressed only by the absolute operands listed below. `ADDRESS` means code supplies the address of the object to a constructor, copy operation or cleanup; it does not mean the cell is itself a pointer argument. `R` and `W` are the decoded operand accesses. The pointed-to receiver is supplied in ECX for the member calls shown in the raw disassembly. Local casts preserve the existing receiver layout views and every verified instruction.

| Retail body RVA | Uses of this cell |
|---|---|
| `0x0051AB40` | W |
| `0x0051AF30` | R |
| `0x0051AF70` | R |
| `0x0051AFB0` | R |
| `0x0051B050` | R |
| `0x0051B0C0` | R |
| `0x0051B130` | R |
| `0x0051B1A0` | R |
| `0x0051B270` | R |
| `0x0051B2F0` | R |
| `0x0051B360` | R |
| `0x0051B3D0` | R |
| `0x00C6BC50` | W |

## Competing spellings

The counts below include namespace-scope definitions and expanded factory macro declarations. They are counts before this correction. The raw declarations and source paths are saved in `exact-declaration-counts.log` and `spellings-and-declarations.log`.

| Decorated spelling | Declaring game files |
|---|---:|
| `?g_aptLivingWorldWindowIndex@@3HA` | 3 |
| `?g_aptLivingWorldWindowIndex@@3PAXA` | 2 |
| `?g_bfmeV1064@@3PAVBfmeX1064@@A` | 1 |
| `?g_bfmeV1067@@3PAVBfmeX1067@@A` | 1 |
| `?g_bfmeV1074@@3PAVBfmeX1074@@A` | 1 |
| `?g_bfmeV1077@@3PAVBfmeX1077@@A` | 1 |

## Reference comparison and refutation

The Zero Hour search finds no corresponding Apt singleton global declarations. Its AsciiString and UnicodeString headers support the string buffer shape; its DisplayString and DisplayStringManager headers support the tooltip receiver contract. The BFME-specific Apt identities above are anchored by retail constructor publication, existing pins and EA callback or filename strings, rather than assumed Zero Hour equivalence.

A declaration of the external Apt helper contract, or a retail consumer that performs pointer dereference or signed index arithmetic on this exact cell, would settle its type.

Raw evidence: `build/rlink/identity-012f49-20261005/012f49a8-retail.log`, `build/rlink/identity-012f49-20261005/retail-image.log`, `build/rlink/identity-012f49-20261005/access-contracts.log`, `build/rlink/identity-012f49-20261005/exact-declaration-counts.log`, `build/rlink/identity-012f49-20261005/ilt-chains.log`, `build/rlink/identity-012f49-20261005/relevant-pins.log`, `build/rlink/identity-012f49-20261005/literal-anchors.log`, `build/rlink/identity-012f49-20261005/zh-apt-search.log` and `build/rlink/identity-012f49-20261005/zh-string-types.log`. Per-address add-data and function gate logs, and before and after linkage measurements, are indexed in `build/worker-final.md`.

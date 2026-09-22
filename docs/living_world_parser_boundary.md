# LivingWorldObject parser and adjacent sound-map index

The `LivingWorldObject` block registry identifies the parser at RVA
`0x00614F50` (`docs/ini_schema.md`). Its initial null-manager exception uses
`TheLivingWorldManager==NULL` at VA `0x01116BA0`.

The old `ScriptActions::doTeamUseCommandButtonOnNearestKindof` claim at
`0x00614F8E`, 496 bytes, was a naked byte lift with the wrong boundary and
identity. It began at the `push ecx` inside that exception path, after the
parser's prologue. It extended through the parser's return, alignment padding,
and a separate hash-map index function. Reproducing those bytes did not prove
that ScriptActions identity.

The independently decoded ranges are:

| Start RVA | End (exclusive) | Bytes | Meaning |
|---|---|---:|---|
| `0x00614F50` | `0x0061509C` | 332 | LivingWorldObject parser; return at `0x0061509B` |
| `0x0061509C` | `0x006150F0` | 84 | CC alignment padding |
| `0x006150F0` | `0x0061517E` | 142 | Native AsciiString/LivingWorldSound pointer hash-map `operator[]` |

The parser finds a name key in the manager's map at `+0x27C`. A normal load
reuses an existing object. An override load resolves its final override and
calls the clone at `0x0060F620`. A missing entry allocates 24 bytes, invokes
`0x00618630`, and marks the object as an override only when appropriate. The
parser then loads fields, calls the one-byte method at `0x006185E0`, and inserts
only a newly allocated object.

The constructor independently proves the override link at `+4`, flag at `+8`,
and fields at `+0xC`, `+0x10`, and `+0x14`. The getter at `0x006185F0` returns
FieldParse table VA `0x01116D18`:

| Field | Offset | Parser RVA |
|---|---|---|
| ObjectType | `0xC` | `0x00851050` |
| DefaultFlashValue | `0x10` | `0x00852B20` |
| FlashVariation | `0x14` | `0x00852B20` |

The latter two fields are floats. The neutral `BfmeLivingWorldMapObject` type
comes from the already matched name lookup at `0x006128F0`; no concrete class
name is inferred from the byte match. The inline override lookup preserves the
retail return-value temporary; manually splitting its two paths had dropped
`mov eax,esi` and left a 330-byte reconstruction.

The adjacent 142-byte hash-map index is called by the independently landed
sound lookup at `0x006155E0`. That caller and the `LivingWorldSound` constructor
at `0x0061BF00` establish its key/value types. It was previously retained only
as a dependency because the incorrect 496-byte claim overlapped its body.

Both replacement bodies are authored C++ and receive their own scoped byte
verification. The obsolete naked source and its row are removed together;
`reverse/deleted_rows.csv` records the retirement so a stale merge cannot
resurrect it. The 84 padding bytes receive no replacement claim.

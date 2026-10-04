# FXParticleSystem addresses carry their exported spelling only

`lotrbfme.exe` (unpacked 1.03, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`) exports
every `FXParticleSystem` member by its full decorated name. The export
directory is transcribed in `targets/game/reverse/exports.csv` (`rva` is the
incremental-link thunk, `target_rva` the body it jumps to). It is the
authoritative witness for these names (docs/naming_evidence.md).

Retail was linked without identical-COMDAT folding (`tools/one_identity.py`),
so each body has one identity. Several FX addresses also carried a second
ledger row whose name is the same function spelt differently:

- a different access or virtuality code from the exported one (`MAE` for an
  exported `IAE` destructor, `QAE`/`QBE` for an exported `UAE`/`UBE` member),
  which is the name our TU-local class shapes happen to compile to;
- a name column cut short (an older 255-character COFF limit in a tool), which
  names no symbol at all;
- the `ModuleTag` and `...ModuleTag` spellings of one template instantiation,
  where only one is exported.

None of the retired spellings is exported at any address, and none has a
`symbols.csv` pin (checked with a scan of both files). In every case the
exported row stays, with the same source, size and `object-symbol=` note
pointing at the label the object actually defines, so byte verification is
unchanged. The retired rows are tombstoned in `deleted_rows.csv`.

This does not claim the retired spellings name any other retail address.

## CategoryModuleClass destructors (accessors TU)

The exported protected non-virtual destructors:

| ordinal | ILT | body | export |
|---|---|---|---|
| 340 | 0x0000A916 | 0x005D4A50 | `??1?$CategoryModuleClass@$00@FXParticleSystem@@IAE@XZ` |
| 341 | 0x0001BDFB | 0x005D4AB0 | `??1?$CategoryModuleClass@$01@FXParticleSystem@@IAE@XZ` |
| 342 | 0x000177D8 | 0x005D4A90 | `??1?$CategoryModuleClass@$02@FXParticleSystem@@IAE@XZ` |
| 343 | 0x0002C872 | 0x005D4B10 | `??1?$CategoryModuleClass@$03@FXParticleSystem@@IAE@XZ` |
| 344 | 0x000247B7 | 0x005D4B30 | `??1?$CategoryModuleClass@$04@FXParticleSystem@@IAE@XZ` |
| 345 | 0x00034A04 | 0x005D47D0 | `??1?$CategoryModuleClass@$05@FXParticleSystem@@IAE@XZ` |
| 346 | 0x0000DA3A | 0x005D4AD0 | `??1?$CategoryModuleClass@$06@FXParticleSystem@@IAE@XZ` |
| 347 | 0x00006D3E | 0x005D4AF0 | `??1?$CategoryModuleClass@$07@FXParticleSystem@@IAE@XZ` |
| 348 | 0x0000F010 | 0x005D4A70 | `??1?$CategoryModuleClass@$0A@@FXParticleSystem@@IAE@XZ` |

Each address also carried `...@@MAE@XZ` (protected virtual), the label
`fx_particle_system_category_accessors.cpp` compiles. The exported `IAE` row
keeps `object-symbol=` that label. Retired: the nine `MAE` rows.

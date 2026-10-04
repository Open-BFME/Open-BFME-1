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

## ConcreteModuleTemplate::clone and ConcreteModuleClass::createTemplate (per-member TUs)

Each body below is exported under its full name; the kept row is that name.
The retired row was either a name column cut short (a prefix of the export,
naming no symbol) or the `U...ModuleTag` spelling of the same instantiation,
which is the label the TU compiles and which the kept row maps through
`object-symbol=`.

| ordinal | ILT | body | retired spelling | source |
|---|---|---|---|---|
| 1394 | 0x0004183F | 0x005DAD20 | truncated | `StreakDrawConcreteModuleTemplateCloneThunk.cpp` |
| 1392 | 0x00048D5B | 0x005DAD50 | truncated | `QuadDrawConcreteModuleTemplateCloneThunk.cpp` |
| 1391 | 0x0003ADBE | 0x005DADB0 | truncated | `LightningDrawConcreteModuleTemplateCloneThunk.cpp` |
| 1384 | 0x0002BCFB | 0x005DCD90 | truncated | `SphericalEmissionVelocityConcreteModuleTemplateCloneThunk.cpp` |
| 1382 | 0x00016A40 | 0x005DCDC0 | alternate tag spelling | `HemisphericalEmissionVelocityConcreteModuleTemplateCloneThunk.cpp` |
| 1381 | 0x00006CF3 | 0x005DCDF0 | alternate tag spelling | `CylindricalEmissionVelocityConcreteModuleTemplateCloneThunk.cpp` |
| 1383 | 0x0003BE7B | 0x005DCE20 | alternate tag spelling | `OutwardEmissionVelocityConcreteModuleTemplateCloneThunk.cpp` |
| 1388 | 0x00001825 | 0x005DCE80 | truncated | `LineEmissionVolumeConcreteModuleTemplateCloneThunk.cpp` |
| 1385 | 0x0004622C | 0x005DCED0 | truncated | `BoxEmissionVolumeConcreteModuleTemplateCloneThunk.cpp` |
| 1389 | 0x00045903 | 0x005DCF20 | truncated | `SphereEmissionVolumeConcreteModuleTemplateCloneThunk.cpp` |
| 1386 | 0x0001A019 | 0x005DCF50 | truncated | `CylinderEmissionVolumeConcreteModuleTemplateCloneThunk.cpp` |
| 1387 | 0x00046BAA | 0x005DCFA0 | truncated | `LightningEmissionConcreteModuleTemplateCloneThunk.cpp` |
| 1393 | 0x0000A993 | 0x005DFAB0 | truncated | `RenderObjectDrawModuleTemplateCloneThunk.cpp` |
| 1395 | 0x00008A0D | 0x005E2070 | truncated | `LifeEventModuleTemplateCloneThunk.cpp` |
| 1396 | 0x00023A92 | 0x005E2110 | truncated | `TerrainCollisionModuleTemplateCloneThunk.cpp` |
| 1455 | 0x00001FA5 | 0x005E3E30 | truncated | `ConcreteModuleClassDefaultModuleTag5CreateTemplateThunk.cpp` |
| 1449 | 0x0002BDE1 | 0x005E41B0 | truncated | `ConcreteModuleClassDefaultModuleTag0CreateTemplateThunk.cpp` |
| 1459 | 0x00010564 | 0x005E42E0 | truncated | `ConcreteModuleClassDefaultModuleTag0ACreateTemplateThunk.cpp` |
| 1453 | 0x00041EF2 | 0x005E4400 | truncated | `ConcreteModuleClassDefaultModuleTag2CreateTemplateThunk.cpp` |
| 1451 | 0x00043E46 | 0x005E4520 | truncated | `ConcreteModuleClassDefaultModuleTag1CreateTemplateThunk.cpp` |
| 1457 | 0x000072BB | 0x005E4640 | truncated | `ConcreteModuleClassDefaultModuleTag6CreateTemplateThunk.cpp` |

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

## ConcreteModuleTemplate members in fx_particle_system_bulk.cpp

Retail exports these as virtual members (`UAE`/`UBE`). The bulk TU's shape
declares them non-virtual, so it compiles `QAE`/`QBE` labels, and each
address carried a second row in that spelling. The exported row stays and
keeps `object-symbol=` the compiled label; the `Q` row is retired. Each
retired name differs from its export in that one access/virtuality letter
only.

| ordinal | ILT | body | member | export -> retired |
|---|---|---|---|---|
| 408 | 0x00032C95 | 0x005DAF30 | `??1?$ConcreteModuleTemplate` | U->Q |
| 1488 | 0x000195E2 | 0x005DF000 | `?createTemplate` | U->Q |
| 1489 | 0x0000FF83 | 0x005DF0A0 | `?createTemplate` | U->Q |
| 1484 | 0x0000A2EA | 0x005DF1B0 | `?createTemplate` | U->Q |
| 1485 | 0x0001EF83 | 0x005DF250 | `?createTemplate` | U->Q |
| 1480 | 0x00020F1D | 0x005DF360 | `?createTemplate` | U->Q |
| 1481 | 0x000046C9 | 0x005DF400 | `?createTemplate` | U->Q |
| 1482 | 0x000101B3 | 0x005DF5A0 | `?createTemplate` | U->Q |
| 1483 | 0x0000B2AD | 0x005DF640 | `?createTemplate` | U->Q |
| 1460 | 0x0003200B | 0x005E0940 | `?createTemplate` | U->Q |
| 1461 | 0x00015406 | 0x005E09F0 | `?createTemplate` | U->Q |
| 1444 | 0x00026D5A | 0x005E0B90 | `?createTemplate` | U->Q |
| 1445 | 0x00043626 | 0x005E0C30 | `?createTemplate` | U->Q |
| 1468 | 0x0002A734 | 0x005E0D40 | `?createTemplate` | U->Q |
| 1469 | 0x000051F5 | 0x005E0DE0 | `?createTemplate` | U->Q |
| 1464 | 0x00042050 | 0x005E0EF0 | `?createTemplate` | U->Q |
| 1465 | 0x0001EC63 | 0x005E0F90 | `?createTemplate` | U->Q |
| 1462 | 0x0003DDC5 | 0x005E10A0 | `?createTemplate` | U->Q |
| 1463 | 0x000277D2 | 0x005E1140 | `?createTemplate` | U->Q |
| 1466 | 0x00017A76 | 0x005E1250 | `?createTemplate` | U->Q |
| 1467 | 0x00038C76 | 0x005E12F0 | `?createTemplate` | U->Q |
| 1446 | 0x0000A8B2 | 0x005E1400 | `?createTemplate` | U->Q |
| 1447 | 0x00019B50 | 0x005E14A0 | `?createTemplate` | U->Q |
| 1476 | 0x00012922 | 0x005E1580 | `?createTemplate` | U->Q |
| 1477 | 0x0001F343 | 0x005E1630 | `?createTemplate` | U->Q |
| 1470 | 0x0002D646 | 0x005E1720 | `?createTemplate` | U->Q |
| 1471 | 0x000439AF | 0x005E17D0 | `?createTemplate` | U->Q |
| 1478 | 0x00009D95 | 0x005E18C0 | `?createTemplate` | U->Q |
| 1479 | 0x000113DD | 0x005E1960 | `?createTemplate` | U->Q |
| 1472 | 0x00006F87 | 0x005E1A40 | `?createTemplate` | U->Q |
| 1473 | 0x00016E5A | 0x005E1AF0 | `?createTemplate` | U->Q |
| 1474 | 0x0002F063 | 0x005E1BE0 | `?createTemplate` | U->Q |
| 1475 | 0x00039BB7 | 0x005E1C90 | `?createTemplate` | U->Q |
| 1486 | 0x0002ED02 | 0x005E3EB0 | `?createTemplate` | U->Q |
| 1487 | 0x00005CC2 | 0x005E3F50 | `?createTemplate` | U->Q |
| 1490 | 0x00019CD6 | 0x005E46C0 | `?createTemplate` | U->Q |
| 1491 | 0x00048FD6 | 0x005E4760 | `?createTemplate` | U->Q |
| 1492 | 0x00017571 | 0x005E47E0 | `?createTemplate` | U->Q |
| 1493 | 0x0000A489 | 0x005E4880 | `?createTemplate` | U->Q |
| 1423 | 0x00037C04 | 0x005E8780 | `?createModule` | U->Q |
| 1440 | 0x0001DA7A | 0x005E8810 | `?createModule` | U->Q |
| 1438 | 0x000347BB | 0x005E88A0 | `?createModule` | U->Q |
| 1436 | 0x00009BAB | 0x005E8930 | `?createModule` | U->Q |
| 1439 | 0x00040A89 | 0x005E89C0 | `?createModule` | U->Q |
| 1437 | 0x0002967C | 0x005E8A50 | `?createModule` | U->Q |
| 1425 | 0x000271F1 | 0x005E8AE0 | `?createModule` | U->Q |
| 1422 | 0x00016734 | 0x005E8B80 | `?createModule` | U->Q |
| 1424 | 0x0001A4F1 | 0x005E8C10 | `?createModule` | U->Q |
| 1441 | 0x0000C685 | 0x005E8CA0 | `?createModule` | U->Q |
| 1442 | 0x00019920 | 0x005E8D30 | `?createModule` | U->Q |
| 1418 | 0x0000CE00 | 0x005E8DC0 | `?createModule` | U->Q |
| 1430 | 0x0004407B | 0x005E8E20 | `?createModule` | U->Q |
| 1428 | 0x00007315 | 0x005E8E80 | `?createModule` | U->Q |
| 1427 | 0x00003963 | 0x005E8EE0 | `?createModule` | U->Q |
| 1429 | 0x00005597 | 0x005E8F40 | `?createModule` | U->Q |
| 1419 | 0x0004823E | 0x005E8FA0 | `?createModule` | U->Q |
| 1434 | 0x00033645 | 0x005E9000 | `?createModule` | U->Q |
| 1431 | 0x0002C002 | 0x005E9060 | `?createModule` | U->Q |
| 1435 | 0x0002063A | 0x005E90C0 | `?createModule` | U->Q |
| 1432 | 0x0000CE14 | 0x005E9120 | `?createModule` | U->Q |
| 1433 | 0x00014BE1 | 0x005E9180 | `?createModule` | U->Q |
| 1420 | 0x0003CF5B | 0x005EBF10 | `?createModule` | U->Q |
| 1421 | 0x00030E5E | 0x005EBFB0 | `?createModule` | U->Q |
| 1426 | 0x0001B00E | 0x005EC040 | `?createModule` | U->Q |

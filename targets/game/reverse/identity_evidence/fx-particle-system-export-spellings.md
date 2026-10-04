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

## ConcreteModuleTemplate::getClass: exported name moved off getInstance ILT thunks

Retail exports each `getClass` instantiation as a virtual const member (`UBE`)
whose 5-byte body is `jmp` to the incremental-link thunk of the matching
`ConcreteModuleClass<TAG>::getInstance`. In the ledger the exported `getClass`
name sat in `fx_particle_system.cpp` at that **getInstance** ILT thunk, which
the export directory assigns to `?getInstance@...` (its `rva` column), not at
the `getClass` body. The thunk is `jmp getInstance`, and `getClass` compiles to
`jmp getInstance` as well, so the misplaced row byte-matched by coincidence.
The body itself carried only a non-exported row in `fx_particle_system_bulk.cpp`:
the `QBE` label the bulk shape compiles, or a truncated name with
`object-symbol=` that label.

Each exported name is repointed (`add_match.py --replace-existing`) to its
exported body in `fx_particle_system_bulk.cpp` with `object-symbol=` the `QBE`
label; the non-exported body rows are retired, and add_match tombstones the
name at the ILT thunk. The 25 getInstance ILT thunks are left unclaimed: they
are jump stubs, and a real name there was an over-claim.

| getClass ordinal | getClass ILT | getClass body | thunk it sat on | thunk owner (export) | retired body row |
|---|---|---|---|---|---|
| 1534 | 0x000148B7 | 0x005E21A0 | 0x0000B686 | ordinal 1579, getInstance body 0x005E0B00 | QBE |
| 1535 | 0x00031336 | 0x005E21F0 | 0x000101A9 | ordinal 1580, getInstance body 0x005E1370 | QBE |
| 1536 | 0x0003D087 | 0x005E2020 | 0x00015FB9 | ordinal 1581, getInstance body 0x005DFD50 | QBE |
| 1537 | 0x000376EB | 0x005E2050 | 0x00011F1D | ordinal 1582, getInstance body 0x005E0500 | QBE |
| 1538 | 0x0003C2A4 | 0x005E2040 | 0x00014088 | ordinal 1583, getInstance body 0x005E0270 | QBE |
| 1539 | 0x00003F1C | 0x005DFA70 | 0x0002C34F | ordinal 1584, getInstance body 0x005DEEE0 | QBE |
| 1540 | 0x0002CE6C | 0x005E2060 | 0x00032867 | ordinal 1585, getInstance body 0x005E0790 | QBE |
| 1541 | 0x00009741 | 0x005E2030 | 0x0002969F | ordinal 1586, getInstance body 0x005DFFE0 | QBE |
| 1542 | 0x00047D98 | 0x005E2100 | 0x00016595 | ordinal 1587, getInstance body 0x005E08B0 | truncated |
| 1543 | 0x0001AFB4 | 0x005E21D0 | 0x0003D875 | ordinal 1588, getInstance body 0x005E1010 | truncated |
| 1544 | 0x00014F4C | 0x005E21C0 | 0x0004B0F1 | ordinal 1589, getInstance body 0x005E0E60 | truncated |
| 1545 | 0x00007E0F | 0x005E21E0 | 0x00036458 | ordinal 1590, getInstance body 0x005E11C0 | truncated |
| 1546 | 0x000332FD | 0x005E21B0 | 0x000078A1 | ordinal 1591, getInstance body 0x005E0CB0 | truncated |
| 1547 | 0x0004A331 | 0x005E2210 | 0x0001361F | ordinal 1592, getInstance body 0x005E1690 | truncated |
| 1548 | 0x00009B8D | 0x005E2230 | 0x00033479 | ordinal 1593, getInstance body 0x005E19B0 | truncated |
| 1549 | 0x0002E34D | 0x005E2240 | 0x000340FE | ordinal 1594, getInstance body 0x005E1B50 | truncated |
| 1550 | 0x00012BA2 | 0x005E2200 | 0x00011B76 | ordinal 1595, getInstance body 0x005E14F0 | truncated |
| 1551 | 0x00038FE1 | 0x005E2220 | 0x00026058 | ordinal 1596, getInstance body 0x005E1830 | truncated |
| 1552 | 0x000245C8 | 0x005DFAA0 | 0x00006B4A | ordinal 1597, getInstance body 0x005DF2D0 | truncated |
| 1553 | 0x000088A5 | 0x005DFB40 | 0x0003E130 | ordinal 1598, getInstance body 0x005DF510 | QBE |
| 1554 | 0x00005B5F | 0x005DFA90 | 0x00015CBC | ordinal 1599, getInstance body 0x005DF120 | truncated |
| 1555 | 0x0001F195 | 0x005DFB30 | 0x00026684 | ordinal 1600, getInstance body 0x005DF480 | truncated |
| 1556 | 0x00002DC9 | 0x005DFA80 | 0x00037F4C | ordinal 1601, getInstance body 0x005DEF70 | truncated |
| 1557 | 0x0000625D | 0x005E20F0 | 0x00044BFC | ordinal 1602, getInstance body 0x005E0820 | truncated |
| 1558 | 0x00038E74 | 0x005E2190 | 0x000124AE | ordinal 1603, getInstance body 0x005E0A70 | truncated |

## ConcreteModuleTemplate destructors: exported name moved off ILT thunks

`fx_particle_system_virtual_destructors.cpp` claimed three exported
`ConcreteModuleTemplate<TAG>::~ConcreteModuleTemplate` names (plus a truncated
copy of each) at incremental-link thunks that the export directory assigns to
the base `XModuleTemplate` destructor. Each derived destructor body is `jmp`
to that thunk, so the C++ `jmp base::~` byte-matched the thunk by coincidence.
The real bodies were claimed only by generated `?j_<rva>` placeholders
(`game/gen_small/thunks_037.cpp`, `gen-thunk`). The exported names are
repointed to their bodies with `add_match.py --replace-rva` (which retires the
placeholder), and the six thunk-anchored rows are tombstoned. The three thunks
are left unclaimed.

| ordinal | ILT | body | thunk it sat on | thunk owner (export) |
|---|---|---|---|---|
| 422 | 0x00016DBA | 0x005DF720 | 0x00027656 | ordinal 475 `??1RenderObjectDrawModuleTemplate@FXParticleSystem@@UAE@XZ` (body 0x005DE490) |
| 424 | 0x0003DAAA | 0x005E1E30 | 0x00044E31 | ordinal 455 `??1LifeEventModuleTemplate@FXParticleSystem@@UAE@XZ` (body 0x005DDFE0) |
| 425 | 0x0001BA81 | 0x005E1F40 | 0x00038410 | ordinal 486 `??1TerrainCollisionModuleTemplate@FXParticleSystem@@UAE@XZ` (body 0x005DE870) |

## Two clone bodies that carried only the U...ModuleTag spelling

| ordinal | ILT | body | source |
|---|---|---|---|
| 1380 | 0x00018462 | 0x005DCD30 | `RenderObjectUpdateConcreteModuleTemplateCloneThunk.cpp` |
| 1390 | 0x0002AE87 | 0x005DAD80 | `ButterflyDrawConcreteModuleTemplateCloneThunk.cpp` |

Each body's only row was the `?clone@?$ConcreteModuleTemplate@U...ModuleTag@...`
label the per-member TU compiles; retail exports the same instantiation as the
`V?$ModuleTag<...>` spelling. The row is corrected to the exported name with
`add_match.py --correct-identity`, keeping `object-symbol=` the compiled label.

## Other names sharing an exported FX body (same TU as the export)

These addresses carry an exported FX name plus rows for names retail does not
export anywhere: a truncated copy, the Zero Hour `ParticleSystemTemplate`
spelling of a keyframe parser, a different FX instantiation that only shares
the TU-local label, or an unrelated class whose code happens to be identical.
With no identical-COMDAT folding in retail, the export decides. Each retired
row lives in the same source as the kept exported row, so no file loses
claimed bytes. `?freeZones@ZoneBlock@@IAEXXZ` keeps its `symbols.csv` pin at
0x00012968, which is the ILT thunk the export assigns to
`??1CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ`; that pin is
left for a separate review.

| ordinal | body | retired name | source |
|---|---|---|---|
| 41 | 0x005C18B0 | `??0?$CategoryModuleClassBase@$07$0A@@FXParticleSystem@@QAE@ABV?$CategoryModuleCl` | `obbox.cpp` |
| 41 | 0x005C18B0 | `??0OBBoxClass@@QAE@PBVVector3@@H@Z` | `obbox.cpp` |
| 442 | 0x005D65B0 | `??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ` | `ConcreteModuleTemplateEmissionVolumeDestructor.cpp` |
| 442 | 0x005D65B0 | `?freeZones@ZoneBlock@@IAEXXZ` | `ConcreteModuleTemplateEmissionVolumeDestructor.cpp` |
| 1702 | 0x005EF1F0 | `?parseRGBColorKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z` | `ParticleSys.cpp` |
| 1703 | 0x005EE370 | `?parseRandomKeyframe@ParticleSystemTemplate@@SAXPAVINI@@PAX1PBX@Z` | `ParticleSys.cpp` |

## Byte-identical functions claimed at exported FX bodies (other TUs)

`??0Keyframe@FXParticleSystem@@QAE@XZ` (ordinal 255, body 0x0005C6C0, a
16-byte two-zero-store constructor) and
`?getUV@ParticleSystemTemplate@FXParticleSystem@@QBEPBURegion2D@@XZ` (ordinal
1638, body 0x0005CBA0) are exported. Other TUs claimed the same bodies under
the names of unrelated functions whose code is identical. Retail has no
identical-COMDAT folding, so those functions live at other addresses; their
rows here are retired. `??0ChunkHeader@@QAE@XZ` (chunkio.cpp) is kept for now:
chunkio.cpp links and `fx_particle_system.cpp` does not, so retiring it would
lower LINKED.

| ordinal | body | retired name | source |
|---|---|---|---|
| 255 | 0x0005C6C0 | `??0?$_Bit_iter@U_Bit_reference@_STL@@PAU12@@_STL@@QAE@XZ` | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp` |
| 255 | 0x0005C6C0 | `??0?$pair@VAsciiString@@M@_STL@@QAE@XZ` | `game/GameEngine/Source/Common/Audio/GameAudio.cpp` |
| 255 | 0x0005C6C0 | `??0AssetIterator@@IAE@XZ` | `game/Libraries/Source/WWVegas/WW3D2/assetmgr.cpp` |
| 255 | 0x0005C6C0 | `??0DLINK_TeamBuildQueue@TeamInQueue@@QAE@XZ` | `game/GameEngine/Source/GameLogic/AI/AIPlayer.cpp` |
| 255 | 0x0005C6C0 | `??0DLINK_TeamInstanceList@Team@@QAE@XZ` | `game/GameEngine/Source/Common/RTS/Team.cpp` |
| 255 | 0x0005C6C0 | `??0DLINK_TeamMemberList@Object@@QAE@XZ` | `game/GameEngine/Source/GameLogic/Object/Object.cpp` |
| 255 | 0x0005C6C0 | `??0DLINK_TeamReadyQueue@TeamInQueue@@QAE@XZ` | `game/GameEngine/Source/GameLogic/AI/AIPlayer.cpp` |
| 255 | 0x0005C6C0 | `??0LadderPref@@QAE@XZ` | `game/GameEngine/Source/Common/UserPreferences.cpp` |
| 255 | 0x0005C6C0 | `??0LogicalDecalPoolClass@MultiFixedPoolDecalSystemClass@@QAE@XZ` | `game/Libraries/Source/WWVegas/WW3D2/decalsys.cpp` |
| 255 | 0x0005C6C0 | `??0MemoryCounterClass@@QAE@XZ` | `game/Libraries/Source/WWVegas/WWDebug/wwmemlog.cpp` |
| 255 | 0x0005C6C0 | `??0MemoryPoolFactory@@QAE@XZ` | `game/GameEngine/Source/Common/System/GameMemory.cpp` |
| 255 | 0x0005C6C0 | `??0MorphKeyStruct@TimeCodedMorphKeysClass@@QAE@XZ` | `game/Libraries/Source/WWVegas/WW3D2/hmorphanim.cpp` |
| 255 | 0x0005C6C0 | `??0PrototypeClass@@QAE@XZ` | `game/Libraries/Source/WWVegas/WW3D2/hlod.cpp` |
| 255 | 0x0005C6C0 | `??0TextureLoadTaskListNodeClass@@QAE@XZ` | `game/Libraries/Source/WWVegas/WW3D2/textureloader.cpp` |
| 255 | 0x0005C6C0 | `??0_Bit_iterator_base@_STL@@QAE@XZ` | `game/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp` |
| 1638 | 0x0005CBA0 | `?getName@Object@@QBEABVAsciiString@@XZ` | `game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/ConvertToCarBombCrateCollide.cpp` |

# SiegeEngineContain::exitObjectViaDoor at 0x0022C560 (identity only)

The 1253-byte body at 0x0022C560 is still the generated dump
`?d_0022c560@@YAXXZ`. Earlier sessions saw that it resembles
OpenContain::exitObjectViaDoor. They could not name a receiver because
RiderChangeContain has no such override in Zero Hour (blocker
`identity/open-containment-overlap`). The ExitInterface tables settle it. This
note records the identity for whoever converts the body. No ledger row changes.

## Facts from retail 1.03 (`lotrbfme.exe`, image base 0x400000)

Each contain constructor stores an ExitInterface table at +0x30:

| constructor | base ctor called | +0x30 table | slot 2 (+0x08) ILT | slot 2 body |
|---|---|---|---|---|
| `??0OpenContain` 0x002277A0 | - | 0x010ABFC8 | 0x00047690 | 0x002284D0 `?exitObjectViaDoor@OpenContain@@UAEXPAVObject@@W4ExitDoorType@@@Z` |
| `??0TransportContain` 0x0022D010 | OpenContain (0x0022D01F) | 0x010AD1FC | 0x00047690 | 0x002284D0 (inherited) |
| `??0SiegeEngineContain` 0x0022BC50 | TransportContain (0x0022BC7A) | 0x010ACD98 (at 0x0022BCB1) | **0x0003B674** | **0x0022C560** |
| `??0RiderChangeContain` 0x00229FB0 | SiegeEngineContain (0x00229FBF) | 0x010AC804 (at 0x0022A00E) | 0x0003B674 | 0x0022C560 (inherited) |

- ILT 0x0003B674 jumps to 0x0022C560. Its VA 0x0043B674 appears only in
  slot 2 of 0x010ACD98 and 0x010AC804. So the body is introduced by
  SiegeEngineContain and inherited unchanged by RiderChangeContain, its
  subclass. SiegeEngineContain's destructor 0x0022B870 also stores 0x010ACD98.
- The rest of the table matches ExitInterface: slot 5 is
  `OpenContain::exitObjectInAHurry` (0x002289F0) and slot 9 is
  `OpenContain::getNaturalRallyPoint` (0x002227E0) in all four tables.
  GarrisonContain's own override (0x0021FDC0, `?exitObjectViaDoor@GarrisonContain@...`)
  sits in the same slot of its table. Zero Hour's ExitInterface declares
  `isExitBusy`, `reserveDoorForExit`, `exitObjectViaDoor` as slots 0-2.
- The owner class is named independently of this body: SiegeEngineContain's
  primary table 0x010AD088 (stored at +0 by 0x0022BC50) has the literal getter
  0x0022B970 returning "SiegeEngineContain" in slot 2 and
  `?getModuleNameKey@SiegeEngineContain@@UBE?AW4NameKeyType@@XZ` (0x0022B990) in
  slot 4. RiderChangeContain's primary 0x010ACAF0 slot 2 returns
  "RiderChangeContain".

## Conclusion

0x0022C560 is `SiegeEngineContain::exitObjectViaDoor(Object *, ExitDoorType)`,
mangled `?exitObjectViaDoor@SiegeEngineContain@@UAEXPAVObject@@W4ExitDoorType@@@Z`
like the OpenContain and GarrisonContain rows. It is entered with ECX at the
+0x30 ExitInterface subobject. The BFME body calls the pathfind and obstacle
helpers three times, against once in Zero Hour's OpenContain version, so expect
siege-engine-specific crew handling rather than a copy of OpenContain's body.

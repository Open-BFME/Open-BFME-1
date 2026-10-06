# Drawable::findClientUpdateModule at 0x00415630

| body | old row | identity |
|---|---|---|
| `0x00415630` (55 B) | `?bfmeFindEH@BfmeThingEH@@QAEPAVBfmeItemEH@@H@Z` (placeholder, Common/BfmeOneHundredNinetyOne.cpp) | `?findClientUpdateModule@Drawable@@QAEPAVClientUpdateModule@@W4NameKeyType@@@Z` |

## Callers

`tools/callers_of.py 0x00415630` lists five direct retail callers, every one a
matched row, all reaching the body through the ILT stub `0x00031D2C`
(`jmp 0x00415630`), which symbols.csv already pins as
`?findClientUpdateModule@Drawable@@...`:

- `0x0027FD70` `AssistedTargetingUpdate::makeFeedbackLaser`
- `0x002A7010` `SpecialAbilityUpdate::initLaser`
- `0x004294A0` `LaserFXNugget::doFXObj`
- `0x00429640` `LaserFXNugget::doFXPos`
- `0x00756F00` `W3DLaserDraw::doDrawModule`

Each is a Zero Hour function whose source makes exactly this call:
`(LaserUpdate*)draw->findClientUpdateModule( key_LaserUpdate )`
(AssistedTargetingUpdate.cpp, SpecialAbilityUpdate.cpp, FXList.cpp,
W3DLaserDraw.cpp). The matched sources for LaserFXNuggetEffects.cpp and
SpecialAbilityUpdate_initLaser.cpp already declare and call
`Drawable::findClientUpdateModule`.

## Body

The 55 bytes walk a null-terminated module pointer list at `this+0x154`,
compare each module's vtable slot `+0x10` result against the key and return
the matching module, else 0. That is Zero Hour's
`Drawable::findClientUpdateModule` (`getClientUpdateModules()`, then
`getModuleNameKey() == key`), with the list pointer advanced on each step
(Zero Hour's loop never advances it). `Module::getModuleNameKey` is the fifth
virtual in Zero Hour (Snapshot's crc/xfer/loadPostProcess, `~Module`, then
`getModuleNameKey`), slot `+0x10`.

## Wrong definition removed

`GameClient/Drawable.cpp` carried Zero Hour's body under the same name
(`present-unmatched`). The census kept it, so every caller's reference
resolved to a non-retail body (link queue: wrong_selected, 962 B in
LaserFXNuggetEffects.cpp and SpecialAbilityUpdate_initLaser.cpp). It is
removed; the name now has one definition, retail's.

# Vtable-decided bodies, vtable-decided-1

Retail was linked without identical-COMDAT folding, so each body has one identity. For each body below a vtable decides which row name is right, and the other names were retired. The vtable owners come from `tools/ctor_vtable.py`: a vtable is owned by the class its singly-claimed `??_G` or `getClassMemoryPool` slot names, or by a pinned `??_7` symbol. For a constructor, the vtable is the one it installs last.

| body | kept | evidence | retired |
|---|---|---|---|
| `0x000A71C0` | `??0AnimationSteeringUpdateModuleData@@QAE@XZ` | installs vtable 0x01080EE0, owned through `??_GAnimationSteeringUpdateModuleData` at 0x000A73F0 | `??0PowerPlantUpdateModuleData@@QAE@XZ` |
| `0x000E1540` | `??0Money@@QAE@ABV0@@Z` | installs vtable 0x01083D18, pinned as `??_7Money` and owned through `??_GMoney` at 0x000CD530 | `??0?$SimpleVecClass@M@@QAE@ABV0@@Z`<br>`??0?$SimpleVecClass@VVector4@@@@QAE@ABV0@@Z` |
| `0x001FE190` | `??0HordeUpdateModuleData@@QAE@XZ` | installs vtable 0x010A42E0, owned through `??_GHordeUpdateModuleData` at 0x001FE790; matched C++ callers also call this name | `??0GettingBuiltBehaviorModuleData@@QAE@XZ` |
| `0x005D30E0` | `??0LocomotorStore@@QAE@XZ` | installs vtable 0x01110104, owned through `??_GLocomotorStore` at 0x005D3170 | `??0ImageCollection@@QAE@XZ` |
| `0x0064C840` | `?getRequest@GameSpyPeerMessageQueue@@UAE_NAAVPeerRequest@@@Z` | slot 7 of vtable 0x01119688 (owned through `??_GGameSpyPeerMessageQueue`), and no other vtable holds the body | `?getRequest@GameSpyPSMessageQueue@@UAE_NAAVPSRequest@@@Z` |
| `0x006CF3A0` | `?_bfme_ro_v28@RenderObjClass@@UBEHXZ` | slot 28 of about twenty render-object vtables, including `RenderObjClass`'s own at 0x0113BD88, so it is an inherited `RenderObjClass` virtual | `?xferReal@Xfer@@QAEXPAM@Z` |

`Code/GameEngine/Source/GameLogic/Object/Update/PowerPlantUpdate.cpp` was deleted because its only matched row was retired (`check_csv` refuses a source without one). Restore it from history when one of its functions is matched.

Left for review because the evidence is not independent: `0x006D18A0`, whose owner comes only from the body's own `??_G` name (the rival `??_GCameraShakerClass@CameraShakeSystemClass@@` is nested, so `ctor_vtable.attest` does not count its claim), and `0x0015BEB0`, whose vtable has no owner, only a slot name that mentions `ExitConditions`. Also left: `0x00125CE0`, `0x00217870` and `0x002D5280`, where callers disagree with the vtable or with each other, and `0x0027F130`, where the matching class name belongs to a static `getClassMemoryPool` that cannot sit in a vtable.

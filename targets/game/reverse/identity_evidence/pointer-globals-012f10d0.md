# TheAnimationSoundModuleManager at VA 0x012F10D0

The datum is `AnimationSoundModuleManager *`, 4 bytes in retail .data. Its initial value is 0 (zero-filled virtual tail of .data). This correction changes data declarations and definitions only; every matched function must retain its verified bytes.

RVA 0x00409200 constructs the 40-byte subsystem, installs vtable VA 0x010F0398, and stores its receiver here if the global is null. Game-client initialization at RVA 0x0042F5A0 allocates 0x28 bytes, calls ILT RVA 0x00004E44 (E9 B7 43 40 00) to that constructor, stores the result, invokes init at +4, and assigns the exact EA subsystem-name string TheAnimationSoundModuleManager at VA 0x010F3750 to the name field at receiver+4. This independently resolves the competing spellings. The GameClient destructor deletes through slot 0 and clears the global. GameClient::reset and update invoke slots +0x10 and +0x14. AnimationSoundClientBehavior construction and destruction use this receiver through the register/unregister ILT routes to RVAs 0x004091C0 and 0x00409140. The existing pin and DIR32 rows are retained unchanged.

Every explicit global declaration uses AnimationSoundModuleManager *. Local ABI views are retained through casts at calls and deletion, so neither slot order nor function identities change. The manager constructor TU AnimationSoundModuleManager.cpp owns the definition. The ctor symbol BfmeReg963 is not renamed in this data correction.

The competing spellings and the number of game files that explicitly declare each exact type are measured in `build/rlink/pointer-globals-1791160230/inventory-corrected.log`. Counts do not decide the chosen identity.

| Spelling | Declaring game files |
|---|---:|
| `?g_012F10D0@@3PAVGen_00409040Registry@@A` | 2 |
| `?g_animationSoundClientBehaviorGlobal@@3PAVAnimationSoundClientBehaviorGlobal@@A` | 3 |
| `?g_animationSoundClientBehaviorGlobal@@3PAVBfmeResetSubsystem@@A` | 4 |
| `?g_bfmeReg963@@3PAVBfmeReg963@@A` | 1 |
| `?g_u4Notify@@3PAVU4Notify@@A` | 1 |

Direct retail operand xrefs, with each matched ledger boundary and the raw instructions, are in `build/rlink/pointer-globals-1791160230/retail-012f10d0.log`. The scan found no unmapped direct operand sites. It is a direct-xref census; generic helpers can also access a field through a supplied receiver.

| Retail body RVA | Ledger name |
|---|---|
| `0x00605710` | `??0AnimationSoundClientBehavior@@QAE@ABVRva00605710Source@@@Z` |
| `0x00605380` | `??0AnimationSoundClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z` |
| `0x00409200` | `??0BfmeReg963@@QAE@XZ` |
| `0x00604B40` | `??1AnimationSoundClientBehavior@@UAE@XZ` |
| `0x00431380` | `??1GameClient@@UAE@XZ` |
| `0x006057C0` | `??4U4Assign006057C0@@QAEAAV0@ABV0@@Z` |
| `0x0042F5A0` | `?d_0042f5a0@@YAXXZ` |
| `0x006059F0` | `?d_006059f0@@YAXXZ` |
| `0x00604C00` | `?detach@U4Inner00604C00@@QAEXXZ` |
| `0x00604BE0` | `?n@Gen_00604be0@@QAEXXZ` |
| `0x00604EE0` | `?reactToTransformChange@Rva00604EE0Module@@QAEXPAXPBVCoord3D@@M@Z` |
| `0x00431900` | `?reset@GameClient@@UAEXXZ` |
| `0x004329D0` | `?update@ClientUpdate004329D0@@QAEXXZ` |

Additional raw PE directories, storage bytes, vtable entries, initializer COFF relocations, and registry helpers are in `build/rlink/pointer-globals-1791160230/supplement-complete.log`. The image has no PE base-relocation directory. The portable-map initializers nevertheless reproduce IMAGE_REL_I386_DIR32 relocations to their verified string addresses; those compiler string constants are address mappings, not new data rows. Raw reference excerpts are in `build/rlink/pointer-globals-1791160230/reference-excerpts.log`. Raw EA-string reads are in `build/rlink/pointer-globals-1791160230/extra-retail-strings.log`.

An ILT route ending at another constructor, a subsystem-name assignment to another pointer, or a vtable inconsistent with the registered animation-sound consumers would refute this correction.

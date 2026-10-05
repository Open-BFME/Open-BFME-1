# Retail identity and storage of seventeen scalar candidates

Six addresses have verified data rows and consistent source spellings. Eleven remain unchanged: three shared readonly constants, seven private scalars refused by the data sizing gate, and one timestamp with a conflicting interior DIR32 name. The four Rva classes remain opaque address-derived implementation names; this correction does not claim that EA declared those classes or that its original storage was a class static. No function identity or function extent changes.

## Retail storage and decisions

The authoritative raw extent measurement is `build/rlink/scalar-17/extents-raw.log`. It reads the retail image through the repository Image reader, including loader-zero virtual storage, and checks the pre-change data ledger and every DIR32 address. Every proposed range except the timestamp has no differently addressed DIR32 name inside it and no prior data-row overlap.

| VA | Type | Size | Section | Retail bytes | Initial value | Decision |
| --- | --- | --- | --- | --- | --- | --- |
| 0x010766EC | float constant | 4 | .rdata | `6f12833a` | 0.001f | Unresolved: shared literal; no external datum proved. |
| 0x01090DDC | float constant | 4 | .rdata | `000010c1` | -9.0f | Unresolved: the 0.5f holder is contradicted by retail; external identity unproved. |
| 0x010F0ADC | float constant | 4 | .rdata | `0ad723bc` | -0.01f | Unresolved: shared literal; a shadow-only external identity is unproved. |
| 0x0113BD7C | const float | 4 | .rdata | `ffff7f7f` | FLT_MAX | Corrected: RenderObjClass::AT_MIN_LOD. |
| 0x0113BD80 | const float | 4 | .rdata | `000080bf` | -1.0f | Corrected: RenderObjClass::AT_MAX_LOD. |
| 0x012ACC30 | int | 4 | .data | `00000040` | 0x40000000 | Corrected: existing opaque Rva001A1A30::s_value; next auto waypoint ID. |
| 0x012BA938 | int | 4 | .data | `02000000` | 2 | Corrected: existing opaque Rva006E1BD0::s_value; display mode selector. |
| 0x012BAA2C | int | 4 | .data | `ffffffff` | -1 | Corrected: existing opaque Rva0075B2F0::s_value; prior client time. |
| 0x012D6D74 | bool | 1 | .data | `01` | true | Unresolved registration: private WW3D::IsSortingEnabled is proved; sizing gate refuses it. |
| 0x012D6D84 | bool | 1 | .data | `01` | true | Unresolved registration: private WW3D::ThumbnailEnabled is proved; sizing gate refuses it. |
| 0x012ED8A0 | two 32-bit words used as a 64-bit unsigned timestamp | 8 | .data | `0000000000000000` | 0 | Unresolved: 8-byte extent contains independently named g_bfmeAccDYB at +4. |
| 0x012F12F0 | int | 4 | .data | `00000000` | 0 | Unresolved registration: private Drawable::s_modelLockCount is proved; sizing gate refuses it. |
| 0x01337824 | int storage, unsigned getter result | 4 | .data | `00000000` | 0 | Corrected: existing opaque Rva00892360::s_value; SWF version. |
| 0x0133F429 | bool | 1 | .data | `00` | false | Unresolved registration: private WW3D::IsRendering is proved; sizing gate refuses it. |
| 0x0133F42A | bool | 1 | .data | `00` | false | Unresolved registration: private WW3D::IsCapturing is proved; sizing gate refuses it. |
| 0x0133F42E | bool | 1 | .data | `00` | false | Unresolved registration: private WW3D::MungeSortOnLoad is proved; sizing gate refuses it. |
| 0x0133F434 | int | 4 | .data | `00000000` | 0 | Unresolved registration: private WW3D::FrameCount is proved; sizing gate refuses it. |

## Spellings before the correction

Counts name game files containing a declaration or definition, including game headers, excluding comments. Access mangling is distinguished by the declaring class access section; native definition access follows its header. The raw counts and paths are `build/rlink/scalar-17/counts-before.log` and `counts-before.json`, produced by `counts.py`. The earlier spelling counts in `details-raw.log` do not distinguish access mangling and are superseded by this measurement. Counts are not identity evidence.

| VA | COFF spelling | Game files |
| --- | --- | --- |
| 0x010766EC | `?g_millisecondsToSeconds@@3MA` | 4 |
| 0x010766EC | `?g_msToSec@@3MA` | 1 |
| 0x01090DDC | `?g_bfmeKRW@@3MA` | 0 |
| 0x01090DDC | `?value@BfmeCachedThresholdScaleHolder@@2MB` | 2 |
| 0x010F0ADC | `?BfmeShadowZLimit@@3MB` | 1 |
| 0x010F0ADC | `?g_010F0ADC@@3MA` | 1 |
| 0x0113BD7C | `?AT_MIN_LOD@RenderObjClass@@2MB` | 2 |
| 0x0113BD7C | `?g_Va0113BD7C@@3MA` | 0 |
| 0x0113BD80 | `?AT_MAX_LOD@RenderObjClass@@2MB` | 2 |
| 0x0113BD80 | `?g_Va0113BD80@@3MA` | 1 |
| 0x012ACC30 | `?g_Va012ACC30@@3HA` | 0 |
| 0x012ACC30 | `?s_value@Rva001A1A30@@2HA` | 5 |
| 0x012BA938 | `?g_Va012BA938@@3HA` | 1 |
| 0x012BA938 | `?s_value@Rva006E1BD0@@2HA` | 1 |
| 0x012BAA2C | `?g_bfmeY1058@@3HA` | 1 |
| 0x012BAA2C | `?s_value@Rva0075B2F0@@2HA` | 1 |
| 0x012D6D74 | `?IsSortingEnabled@WW3D@@0_NA` | 2 |
| 0x012D6D74 | `?IsSortingEnabled@WW3D@@2_NA` | 2 |
| 0x012D6D84 | `?Rva012D6D84@WW3D@@0_NA` | 1 |
| 0x012D6D84 | `?g_Va012D6D84@@3EA` | 1 |
| 0x012ED8A0 | `?g_bfmeStartDYB@@3_KA` | 1 |
| 0x012ED8A0 | `?g_bfmeT0DYB@@3HA` | 1 |
| 0x012F12F0 | `?g_bfmeCounter4120@@3HA` | 1 |
| 0x012F12F0 | `?s_modelLockCount@Drawable@@0HA` | 1 |
| 0x01337824 | `?g_Va01337824@@3HA` | 1 |
| 0x01337824 | `?s_value@Rva00892360@@2HA` | 1 |
| 0x0133F429 | `?IsRendering@WW3D@@0_NA` | 5 |
| 0x0133F429 | `?IsRendering@WW3D@@2_NA` | 0 |
| 0x0133F42A | `?IsCapturing@WW3D@@0_NA` | 4 |
| 0x0133F42A | `?IsCapturing@WW3D@@2_NA` | 0 |
| 0x0133F42E | `?IsMungeSortOnLoadEnabled@WW3D@@2_NA` | 0 |
| 0x0133F42E | `?MungeSortOnLoad@WW3D@@0_NA` | 4 |
| 0x0133F434 | `?FrameCount@WW3D@@0HA` | 2 |
| 0x0133F434 | `?FrameCount@WW3D@@2HA` | 1 |

## Access bodies and contracts

The direct absolute-operand scan is `build/rlink/scalar-17/probe-raw.log`, with machine-readable sites, original instruction bytes, access widths and ledger boundaries in `accesses.json`. Raw bodies are `body-<VA>.txt`. Ledger intervals take precedence over Ghidra intervals. A body whose boundary is absent is only an instruction window; its synthetic window start is not a function identity. This is one static scan of the baseline image (n=1); indirect accesses are not exhaustively excluded.

The four scalar setters at RVAs 0x001A1A30, 0x006E1BD0, 0x0075B2F0 and 0x00892360 each load one stack dword at ESP+4, store EAX to their own candidate address and RET without popping an argument. They have no receiver and retain the existing static __cdecl contract. Their getter partners return a single dword in EAX. The Apt getter returns unsigned int and remains so; the preexisting int storage declaration is retained because the verified code only transfers its bits. No new original class identity is inferred from those instructions.

At 0x012ACC30, both Waypoint constructors reset the auto ID to 0x40000000 when their auto-ID branch requires it, copy the current dword into the object ID and increment that same dword. Waypoint::xfer passes its address to the transfer operation; TerrainLogic::xferTerrainState reads and restores it. These BFME branches do not provide an original Zero Hour global name. WaypointConstructor.cpp owns the initialized storage beside its main writers; TinyGlobalStores.cpp retains only the setter declaration and body for this address.

At 0x012BA938, RVA 0x006E1920 returns the dword, RVA 0x006E1BD0 stores its stack argument, and RVA 0x006E2AC0 tests it for zero to disable a display path, then for one to select another display branch. The initial value is two. A more specific original EA name or enum is not proved, so the existing address-derived setter owner is retained.

At 0x012BAA2C, RVA 0x006F3FC0 subtracts this dword from the result of TheGameClient vtable slot 0x68 and stores a fresh result there on the active branch. RVA 0x0075C940 also publishes the same vtable result. Its initial bits are -1 in the current signed storage declaration. The source for the latter writer, BfmeConv1058.cpp, owns the storage. The alternate g_bfmeY1058 spelling supplies no more original identity information than the existing opaque setter owner.

At 0x01337824, RVA 0x00892360 stores its stack argument and RVA 0x00892370 returns the dword. The existing AptGetSwfVersion pin in symbols.csv names the getter and identifies its SWF-version role (`apt-pin.log`); the existing identity evidence is recorded in `apt-prior-evidence.log`. No original name for the storage itself is established. Its sole observed direct writer is in TinyGlobalStores.cpp, which owns its loader-zero definition.

The LOD pair is independently declared and defined as public static const float in the native and Zero Hour RenderObjClass files. Zero Hour rendobj.cpp defines FLT_MAX and -1.0f; native rendobj.cpp already defines those exact symbols. Retail Ring, line, streak, HLod and ParticleBuffer LOD accesses use the corresponding positive minimum sentinel and negative maximum sentinel. The existing rendobj.cpp definitions are kept, two data rows register them, and RingRenderObjPrepareLOD.cpp now reads the reference AT_MAX_LOD spelling. `reference-ww3d.log`, `body-00d19900.txt`, `body-00d78e10.txt` and `body-00d83850.txt` supply the source and retail evidence.

## Unchanged addresses and what settles them

0x010766EC is the readonly 0.001f value used for both time conversion and unrelated tolerance comparisons. The reference mapper uses literals with that value, and neither competing global is declared in Zero Hour. Retail has no observed direct write. A surviving BFME declaration proving independently allocated named storage, rather than compiler-pooled constants, would settle a datum identity. The current role-describing g_millisecondsToSeconds declaration remains unchanged.

0x01090DDC holds -9.0f, and both cached-threshold bodies multiply by that exact address. S3CachedThresholdTest.cpp defines BfmeCachedThresholdScaleHolder::value as 0.5f. Therefore the existing claim that this definition supplies the retail value is false. `rare-spellings.txt`, the existing source and `body-00531b20.txt`/`body-00531b70.txt` allow a reviewer to recheck it. An independently anchored BFME declaration and matching initial bytes would establish a proper external datum; neither current spelling does. The source and ledgers for this address remain unchanged.

0x010F0ADC holds -0.01f and is used by shadow threshold comparison, W3DView, movement scoring and an initialization multiply. The shadow-related pin describes one use but does not establish dedicated externally named storage. A surviving BFME definition or independent address-taking named use would distinguish an external BfmeShadowZLimit from a pooled literal. Its role-describing spelling is retained unchanged.

The private WW3D identities follow both native and Zero Hour declarations and matching retail operations: Enable_Sorting writes 0x012D6D74 and SortingRenderer reads it; display initialization disables thumbnails at 0x012D6D84 and the stack-byte setter writes the same address; Begin_Render sets IsRendering and End_Render clears it; capture start/stop and Shutdown use IsCapturing; mesh post-process and sort-level recomputation read MungeSortOnLoad; End_Render increments FrameCount and particle/rendering bodies read it. The original canonical access digit is private @@0, not public @@2. The thumbnail field is ThumbnailEnabled, and the munge field is MungeSortOnLoad rather than IsMungeSortOnLoadEnabled. Reference facts are in `reference-ww3d.log`; all direct accesses are in `accesses.json`.

The private Drawable::s_modelLockCount identity is supported by the matching Zero Hour lock/unlock logic and the retail decrement body already named friend_unlockDirtyStuffForIteration. The lock body reads zero, optionally traverses the GameClient drawable chain, and increments the same dword; unlock decrements only when positive. `reference-drawable.log`, `body-008120e0.txt` and `body-00812120.txt` establish the receiver-free static contract.

Each of these seven canonical private definitions already exists once in its reference-owned source. add_data_match.py compiled that source but refused the scalar size because private @@0 cannot be named by its external sizeof probe. Raw refusals are `add-private-IsSortingEnabled.log`, `add-private-ThumbnailEnabled.log`, `add-private-IsRendering.log`, `add-private-IsCapturing.log`, `add-private-MungeSortOnLoad.log`, `add-private-FrameCount.log` and `add-private-s_modelLockCount.log`. No row is fabricated and no access is widened. The brief grants the unsized exception only for a private static member table, not these scalars. A supported private-scalar size proof in the repository tool would settle registration; a differing native declaration or retail accessor operand would refute the chosen identities. All seven addresses remain unchanged.

The timer start at RVA 0x00105790 stores timeGetTime into 0x012ED8A0 and zero into 0x012ED8A4. The stop at RVA 0x001057C0 performs SUB on the low word and SBB on the high word, then adds the unsigned 64-bit difference to the accumulator at 0x012ED8A8. This proves use of the pair as an unsigned timestamp, but not whether the original definition was one uint64 or two 32-bit words. The independently named g_bfmeAccDYB at +4 lies inside the proposed 8-byte extent. `body-00505790.txt`, `body-005057c0.txt` and `extents-raw.log` record the contradiction. An original BFME type declaration or another independently named writer/accessor that proves the full extent and resolves that interior name would settle it. No timestamp datum is added.

## Thunks and verification

Five-byte E9 routes are read from retail for the setter/getter, timer and lock/unlock candidates. Every hop, its raw five bytes, final target and final non-E9 bytes are in `details-raw.log`; `thunk-00026e3b.log` is a repository disassembler cross-check. The direct E8/E9 operand scan found no caller through these selected thunks. This absence does not exclude indirect calls or address-taken pointers. The identity decisions therefore use the independently observed data operands and native definitions rather than symbolic thunk labels.

Six add_data_match.py registrations prove each compiled scalar size and initial bytes against retail. Every changed source and rendobj.cpp must pass its scoped Functions gate, CSV integrity, pin consistency and declaration checks. LINKED measurements retain their unrelated blockers. Final raw log paths and every outcome are in build/worker-final.md. Old symbols.csv pins and DIR32 entries are untouched. All chosen spellings already exist in DIR32. No naked body, shared header, generated file, function row, alias or wrapper is changed.

Any different retail initial bytes, an independently proved overlapping datum, a cited accessor addressing another location, a changed verified instruction, or a native definition with different type/access would refute the corresponding correction. For the four opaque scalar owners, an independently anchored original BFME name would supersede the retained address-derived storage spelling.

## Complete directly observed read/write inventory

Each entry below gives the containing retail body RVA and observed access widths. The full original bytes and individual instruction sites remain in accesses.json and the corresponding body log. When the boundary is unavailable, the entry is explicitly a probe window, not a body identity.

### VA 0x010766EC

- RVA 0x0007B8E0, `?update@TimedOperationNode@@QAEIXZ`: 0047B919 d80dec660701 fmul dword ptr [0x10766ec]; 0047B92C d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-0047b8e0.txt`.
- RVA 0x001B4140, `?isNearlyZero@@YA_NM@Z`: 005B4146 d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-005b4140.txt`.
- RVA 0x001B8D30, `?d_001b8d30@@YAXXZ`: 005B909E d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-005b8d30.txt`.
- RVA 0x001BC670, `?maintainCurrentPositionWings@Locomotor@@IAEXPAVObject@@@Z`: 005BC6E2 d81dec660701 fcomp dword ptr [0x10766ec]; 005BC6F3 d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-005bc670.txt`.
- RVA 0x001E43D0, `?computeApproachTarget@Weapon@@QBE_NPBVObject@@0PBUCoord3D@@MAAU3@@Z`: 005E4652 d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-005e43d0.txt`.
- RVA 0x001F5BC0, `?update@BridgeScaffoldBehavior@@UAE?AW4UpdateSleepTime@@XZ`: 005F5CE4 d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-005f5bc0.txt`.
- RVA 0x0040B5A0, `?init@Rva0040B5A0@@QAEXXZ`: 0080B5D0 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-0080b5a0.txt`.
- RVA 0x005B63CA, `boundary-unproved probe window`: 009B63D7 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-009b63ca.txt`.
- RVA 0x006996F0, `?update@Rva006996F0Owner@@QAEXM@Z`: 00A99702 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00a996f0.txt`.
- RVA 0x006E2AC0, `?d_006e2ac0@@YAXXZ`: 00AE54D4 d80dec660701 fmul dword ptr [0x10766ec]; 00AE54E8 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00ae2ac0.txt`.
- RVA 0x006E8E60, `?calculateTerrainLOD@W3DDisplay@@IAEXXZ`: 00AE8EAB d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00ae8e60.txt`.
- RVA 0x006E9210, `?renderLetterBox@W3DDisplay@@IAEXI@Z`: 00AE9250 d80dec660701 fmul dword ptr [0x10766ec]; 00AE9395 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00ae9210.txt`.
- RVA 0x006EE800, `?d_006ee800@@YAXXZ`: 00AEE938 d80dec660701 fmul dword ptr [0x10766ec]; 00AEE9A6 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00aee800.txt`.
- RVA 0x007018A0, `?setCursor@W3DMouse@@UAEXW4MouseCursor@Mouse@@@Z`: 00B019DC d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00b018a0.txt`.
- RVA 0x00725AC0, `?update@W3DSnowManager@@UAEXXZ`: 00B25AE1 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00b25ac0.txt`.
- RVA 0x0075B450, `?rva0075b450@@YAMM@Z`: 00B5B454 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00b5b450.txt`.
- RVA 0x0076C080, `?advanceAnimation@Rva0076C080@@QAEXXZ`: 00B6C402 d80dec660701 fmul dword ptr [0x10766ec]; 00B6C60E d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00b6c080.txt`.
- RVA 0x007A04C0, `?Get_Obj_Space_Bounding_Box@WaterRenderObjClass@@UBEXAAVAABoxClass@@@Z`: 00BA04CA d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00ba04c0.txt`.
- RVA 0x007A7D70, `?update@WaterRenderObjClass@@QAEXXZ`: 00BA7DCF d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00ba7d70.txt`.
- RVA 0x007DCCE0, `?updateNoise1@TerrainShader2Stage@@QAEXPAU_D3DXMATRIX@@0_N@Z`: 00BDCD61 d80dec660701 fmul dword ptr [0x10766ec]; 00BDCD87 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00bdcce0.txt`.
- RVA 0x008C8AC0, `?d_008c8ac0@@YAXXZ`: 00CC957A d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00cc8ac0.txt`.
- RVA 0x008CA3A0, `?d_008ca3a0@@YAXXZ`: 00CCA578 d81dec660701 fcomp dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00cca3a0.txt`.
- RVA 0x00919F20, `?Set_UV_Offset_Rate@SegLineRendererClass@@QAEXABVVector2@@@Z`: 00D19F26 d80dec660701 fmul dword ptr [0x10766ec]; 00D19F2F d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d19f20.txt`.
- RVA 0x0091A570, `?Set_UV_Offset_Rate@StreakLineClass@@QAEXABVVector2@@@Z`: 00D1A576 d80dec660701 fmul dword ptr [0x10766ec]; 00D1A57F d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d1a570.txt`.
- RVA 0x00950C00, `?Set_UV_Offset_Rate@SegmentedLineClass@@QAEXABVVector2@@@Z`: 00D50C06 d80dec660701 fmul dword ptr [0x10766ec]; 00D50C0F d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d50c00.txt`.
- RVA 0x0095C840, `?Set_UV_Offset_Rate@StreakRendererClass@@QAEXABVVector2@@@Z`: 00D5C846 d80dec660701 fmul dword ptr [0x10766ec]; 00D5C84F d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d5c840.txt`.
- RVA 0x0095C8F0, `?Init@StreakRendererClass@@QAEXABUW3dEmitterLinePropertiesStruct@@@Z`: 00D5C9B8 d80dec660701 fmul dword ptr [0x10766ec]; 00D5C9C6 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d5c8f0.txt`.
- RVA 0x0095CE80, `?d_0095ce80@@YAXXZ`: 00D5D622 d805ec660701 fadd dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d5ce80.txt`.
- RVA 0x00960190, `?Init@SegLineRendererClass@@QAEXABUW3dEmitterLinePropertiesStruct@@@Z`: 00D6025B d80dec660701 fmul dword ptr [0x10766ec]; 00D60269 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d60190.txt`.
- RVA 0x00960A30, `?d_00960a30@@YAXXZ`: 00D61236 d805ec660701 fadd dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d60a30.txt`.
- RVA 0x00964A70, `??0RotateTextureMapperClass@@QAE@MABVVector2@@0I@Z`: 00D64A97 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d64a70.txt`.
- RVA 0x00965000, `??0StepLinearOffsetTextureMapperClass@@QAE@ABVVector2@@M_N0I@Z`: 00D65027 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65000.txt`.
- RVA 0x009650A0, `??0StepLinearOffsetTextureMapperClass@@QAE@ABVINIClass@@PBDI@Z`: 00D65122 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d650a0.txt`.
- RVA 0x00965350, `??0ZigZagLinearOffsetTextureMapperClass@@QAE@ABVVector2@@M0I@Z`: 00D6538F d80dec660701 fmul dword ptr [0x10766ec]; 00D65397 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65350.txt`.
- RVA 0x00965420, `??0ZigZagLinearOffsetTextureMapperClass@@QAE@ABVINIClass@@PBDI@Z`: 00D65480 d80dec660701 fmul dword ptr [0x10766ec]; 00D65498 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65420.txt`.
- RVA 0x00965890, `?Calculate_Texture_Matrix@EdgeMapperClass@@UAEXAAVMatrix4@@@Z`: 00D658B2 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65890.txt`.
- RVA 0x00965C00, `??0RandomTextureMapperClass@@QAE@MABVVector2@@I@Z`: 00D65C53 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65c00.txt`.
- RVA 0x00965CE0, `??0RandomTextureMapperClass@@QAE@ABVINIClass@@PBDI@Z`: 00D65D40 d80dec660701 fmul dword ptr [0x10766ec]; 00D65D58 d80dec660701 fmul dword ptr [0x10766ec]; 00D65D70 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d65ce0.txt`.
- RVA 0x00969470, `?Apply@BumpEnvTextureMapperClass@@UAEXH@Z`: 00D694A8 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d69470.txt`.
- RVA 0x00975100, `?d_00975100@@YAXXZ`: 00D75767 d805ec660701 fadd dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d75100.txt`.
- RVA 0x0097DF70, `?Set_Outwards_Velocity@ParticleEmitterClass@@QAEXM@Z`: 00D7DF74 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7df70.txt`.
- RVA 0x0097E040, `?Get_Lifetime@ParticleBufferClass@@QBEMXZ`: 00D7E057 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e040.txt`.
- RVA 0x0097E060, `?Get_Future_Start_Time@ParticleBufferClass@@QBEMXZ`: 00D7E077 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e060.txt`.
- RVA 0x0097E080, `?Get_Fade_Time@ParticleBufferClass@@QBEMXZ`: 00D7E0A0 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e080.txt`.
- RVA 0x0097E260, `?Get_Lifetime@ParticleEmitterClass@@QBEMXZ`: 00D7E27D d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e260.txt`.
- RVA 0x0097E290, `?Get_Future_Start_Time@ParticleEmitterClass@@QBEMXZ`: 00D7E2AD d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e290.txt`.
- RVA 0x0097E2F0, `?Get_Fade_Time@ParticleEmitterClass@@QBEMXZ`: 00D7E316 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e2f0.txt`.
- RVA 0x0097E670, `??0ParticleEmitterClass@@QAE@MIPAVVector3Randomizer@@VVector3@@0MMAAU?$ParticlePropertyStruct@VVector3@@@@AAU?$ParticlePropertyStruct@M@@33M331MMPAVTextureClass@@VShaderClass@@HH_NHHPBUW3dEmitterLinePropertiesStruct@@@Z`: 00D7E6EA d80dec660701 fmul dword ptr [0x10766ec]; 00D7E6FF d80dec660701 fmul dword ptr [0x10766ec]; 00D7E713 d80dec660701 fmul dword ptr [0x10766ec]; 00D7E756 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7e670.txt`.
- RVA 0x0097F140, `?Set_Base_Velocity@ParticleEmitterClass@@QAEXABVVector3@@@Z`: 00D7F149 d80dec660701 fmul dword ptr [0x10766ec]; 00D7F152 d80dec660701 fmul dword ptr [0x10766ec]; 00D7F15B d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7f140.txt`.
- RVA 0x0097FD70, `?Build_Definition@ParticleEmitterClass@@QBEPAVParticleEmitterDefClass@@XZ`: 00D7FE76 d80dec660701 fmul dword ptr [0x10766ec]; 00D7FEA3 d80dec660701 fmul dword ptr [0x10766ec]; 00D7FF17 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d7fd70.txt`.
- RVA 0x00982540, `?Compute_Current_Frame@Animatable3DObjClass@@IBEMPAM@Z`: 00D825C8 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d82540.txt`.
- RVA 0x00983B00, `?Get_Color_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@VVector3@@@@@Z`: 00D83C3D d80dec660701 fmul dword ptr [0x10766ec]; 00D83C97 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d83b00.txt`.
- RVA 0x00983D60, `?Get_Opacity_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@M@@@Z`: 00D83E09 d80dec660701 fmul dword ptr [0x10766ec]; 00D83E47 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d83d60.txt`.
- RVA 0x00983EA0, `?Get_Size_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@M@@@Z`: 00D83F49 d80dec660701 fmul dword ptr [0x10766ec]; 00D83F87 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d83ea0.txt`.
- RVA 0x00983FE0, `?Get_Rotation_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@M@@@Z`: 00D840A9 d80dec660701 fmul dword ptr [0x10766ec]; 00D840EF d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d83fe0.txt`.
- RVA 0x00984150, `?Get_Frame_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@M@@@Z`: 00D841F9 d80dec660701 fmul dword ptr [0x10766ec]; 00D84237 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d84150.txt`.
- RVA 0x00984290, `?Get_Blur_Time_Key_Frames@ParticleBufferClass@@QBEXAAU?$ParticlePropertyStruct@M@@@Z`: 00D84339 d80dec660701 fmul dword ptr [0x10766ec]; 00D84377 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d84290.txt`.
- RVA 0x00986050, `?Reset_Rotations@ParticleBufferClass@@QAEXAAU?$ParticlePropertyStruct@M@@M@Z`: 00D86075 d80dec660701 fmul dword ptr [0x10766ec]; 00D86324 d80dec660701 fmul dword ptr [0x10766ec]; 00D8636B d80dec660701 fmul dword ptr [0x10766ec]; 00D86404 d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d86050.txt`.
- RVA 0x0098D6B0, `?Convert_To_Ver2@ParticleEmitterDefClass@@MAEXXZ`: 00D8D74C d80dec660701 fmul dword ptr [0x10766ec]. Raw `build/rlink/scalar-17/body-00d8d6b0.txt`.

### VA 0x01090DDC

- RVA 0x00131B20, `?bfmeCheckRW@BfmeOwnerRW@@QAEHXZ`: 00531B40 d80ddc0d0901 fmul dword ptr [0x1090ddc]. Raw `build/rlink/scalar-17/body-00531b20.txt`.
- RVA 0x00131B70, `?bfmeExceeds@Gen_00131b70@@QAEHM@Z`: 00531B98 d80ddc0d0901 fmul dword ptr [0x1090ddc]. Raw `build/rlink/scalar-17/body-00531b70.txt`.

### VA 0x010F0ADC

- RVA 0x0040B5A0, `?init@Rva0040B5A0@@QAEXXZ`: 0080B737 d80ddc0a0f01 fmul dword ptr [0x10f0adc]. Raw `build/rlink/scalar-17/body-0080b5a0.txt`.
- RVA 0x007446A0, `?update@W3DView@@UAEXXZ`: 00B44F11 d905dc0a0f01 fld dword ptr [0x10f0adc]; 00B44F75 d905dc0a0f01 fld dword ptr [0x10f0adc]. Raw `build/rlink/scalar-17/body-00b446a0.txt`.
- RVA 0x007C1760, `?updateShadowState@W3DVolumetricShadow@@QAEXXZ`: 00BC189F d81ddc0a0f01 fcomp dword ptr [0x10f0adc]. Raw `build/rlink/scalar-17/body-00bc1760.txt`.
- RVA 0x009A2420, `?getMovementScore@Rva009A2420CollisionNode@@QAEI_N@Z`: 00DA24A4 d80ddc0a0f01 fmul dword ptr [0x10f0adc]. Raw `build/rlink/scalar-17/body-00da2420.txt`.

### VA 0x0113BD7C

- RVA 0x006CF590, `?Rva006CF590GetFloat@@YAMXZ`: 00ACF590 d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00acf590.txt`.
- RVA 0x00919980, `?Get_Value@RingRenderObjClass@@UBEMXZ`: 00D1998E d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00d19980.txt`.
- RVA 0x00950870, `?Get_Value@SegmentedLineClass@@UBEMXZ`: 00D5087E d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00d50870.txt`.
- RVA 0x009558D0, `?rva009558D0@BfmeStreakObject@@QBEMXZ`: 00D558D0 d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00d558d0.txt`.
- RVA 0x00978E10, `?Calculate_Cost_Value_Arrays@HLodClass@@UBEHMPAM0@Z`: 00D78E85 d9057cbd1301 fld dword ptr [0x113bd7c]; 00D78EAC d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00d78e10.txt`.
- RVA 0x00983850, `?Calculate_Cost_Value_Arrays@ParticleBufferClass@@UBEHMPAM0@Z`: 00D8397E a17cbd1301 mov eax, dword ptr [0x113bd7c]; 00D839A2 d9057cbd1301 fld dword ptr [0x113bd7c]. Raw `build/rlink/scalar-17/body-00d83850.txt`.

### VA 0x0113BD80

- RVA 0x006CF5A0, `?Rva006CF5A0GetFloat@@YAMXZ`: 00ACF5A0 d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00acf5a0.txt`.
- RVA 0x009199E0, `?Get_Post_Increment_Value@RingRenderObjClass@@UBEMXZ`: 00D199F2 d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00d199e0.txt`.
- RVA 0x009508D0, `?Get_Post_Increment_Value@SegmentedLineClass@@UBEMXZ`: 00D508E2 d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00d508d0.txt`.
- RVA 0x009558E0, `?Rva009558E0GetFloat@@YAMXZ`: 00D558E0 d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00d558e0.txt`.
- RVA 0x00978E10, `?Calculate_Cost_Value_Arrays@HLodClass@@UBEHMPAM0@Z`: 00D78F03 d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00d78e10.txt`.
- RVA 0x00983850, `?Calculate_Cost_Value_Arrays@ParticleBufferClass@@UBEHMPAM0@Z`: 00D83A0E d90580bd1301 fld dword ptr [0x113bd80]. Raw `build/rlink/scalar-17/body-00d83850.txt`.

### VA 0x012ACC30

- RVA 0x001A1A20, `?Rva001A1A20Get@@YAHXZ`: 005A1A20 a130cc2a01 mov eax, dword ptr [0x12acc30]. Raw `build/rlink/scalar-17/body-005a1a20.txt`.
- RVA 0x001A1A30, `?store@Rva001A1A30@@SAXH@Z`: 005A1A34 a330cc2a01 mov dword ptr [0x12acc30], eax. Raw `build/rlink/scalar-17/body-005a1a30.txt`.
- RVA 0x001A7020, `?xfer@Waypoint@@QAEXPAVXfer@@@Z`: 005A706B 6830cc2a01 push 0x12acc30. Raw `build/rlink/scalar-17/body-005a7020.txt`.
- RVA 0x001AB600, `??0Waypoint@@QAE@HVAsciiString@@PBUCoord3D@@000_NH0@Z`: 005AB752 c70530cc2a0100000040 mov dword ptr [0x12acc30], 0x40000000; 005AB765 8b0d30cc2a01 mov ecx, dword ptr [0x12acc30]; 005AB76E ff0530cc2a01 inc dword ptr [0x12acc30]. Raw `build/rlink/scalar-17/body-005ab600.txt`.
- RVA 0x001AB8B0, `??0Waypoint@@QAE@XZ`: 005AB999 c70530cc2a0100000040 mov dword ptr [0x12acc30], 0x40000000; 005AB9AC 8b0d30cc2a01 mov ecx, dword ptr [0x12acc30]; 005AB9B5 ff0530cc2a01 inc dword ptr [0x12acc30]. Raw `build/rlink/scalar-17/body-005ab8b0.txt`.
- RVA 0x001AD370, `?xferTerrainState@TerrainLogic@@IAEXPAVXfer@@@Z`: 005AD4C5 8b1530cc2a01 mov edx, dword ptr [0x12acc30]; 005AD4DE 890d30cc2a01 mov dword ptr [0x12acc30], ecx. Raw `build/rlink/scalar-17/body-005ad370.txt`.

### VA 0x012BA938

- RVA 0x006E1920, `?Rva006E1920Get@@YAHXZ`: 00AE1920 a138a92b01 mov eax, dword ptr [0x12ba938]. Raw `build/rlink/scalar-17/body-00ae1920.txt`.
- RVA 0x006E1BD0, `?store@Rva006E1BD0@@SAXH@Z`: 00AE1BD4 a338a92b01 mov dword ptr [0x12ba938], eax. Raw `build/rlink/scalar-17/body-00ae1bd0.txt`.
- RVA 0x006E2AC0, `?d_006e2ac0@@YAXXZ`: 00AE2ADB a138a92b01 mov eax, dword ptr [0x12ba938]; 00AE2B68 a138a92b01 mov eax, dword ptr [0x12ba938]. Raw `build/rlink/scalar-17/body-00ae2ac0.txt`.

### VA 0x012BAA2C

- RVA 0x006F3FC0, `?d_006f3fc0@@YAXXZ`: 00AF4053 8b0d2caa2b01 mov ecx, dword ptr [0x12baa2c]; 00AF4070 a32caa2b01 mov dword ptr [0x12baa2c], eax. Raw `build/rlink/scalar-17/body-00af3fc0.txt`.
- RVA 0x0075B2F0, `?store@Rva0075B2F0@@SAXH@Z`: 00B5B2F4 a32caa2b01 mov dword ptr [0x12baa2c], eax. Raw `build/rlink/scalar-17/body-00b5b2f0.txt`.
- RVA 0x0075C940, `?bfmeGo1058E@BfmeE1058@@QAEXXZ`: 00B5C95E a32caa2b01 mov dword ptr [0x12baa2c], eax. Raw `build/rlink/scalar-17/body-00b5c940.txt`.

### VA 0x012D6D74

- RVA 0x008FD510, `?Enable_Sorting@WW3D@@SAX_N@Z`: 00CFD51C a2746d2d01 mov byte ptr [0x12d6d74], al. Raw `build/rlink/scalar-17/body-00cfd510.txt`.
- RVA 0x0090F2F2, `boundary-unproved probe window`: 00D0F300 a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d0f2f2.txt`.
- RVA 0x0090FEE0, `?d_0090fee0@@YAXXZ`: 00D103F6 a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d0fee0.txt`.
- RVA 0x00913AF0, `?rva00913AF0@PointGroupClass@@QAEXH_N@Z`: 00D13FDA a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d13af0.txt`.
- RVA 0x0091A600, `?Render@StreakLineClass@@UAEXAAVRenderInfoClass@@@Z`: 00D1A610 8a0d746d2d01 mov cl, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d1a600.txt`.
- RVA 0x0093B340, `?Insert_Triangles@SortingRendererClass@@SAXABVSphereClass@@GGGG@Z`: 00D3B341 a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d3b340.txt`.
- RVA 0x0093B850, `?Insert_VolumeParticle@SortingRendererClass@@SAXABVSphereClass@@GGGGG@Z`: 00D3B851 a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d3b850.txt`.
- RVA 0x00945980, `?Define_FVF@DX8FVFCategoryContainer@@SAIPAVMeshModelClass@@_N@Z`: 00D4598B a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d45980.txt`.
- RVA 0x009476F0, `?Add_Rigid_Mesh_To_Container@@YAXPAV?$MultiListClass@VDX8FVFCategoryContainer@@@@IPAVMeshModelClass@@@Z`: 00D47718 8a0d746d2d01 mov cl, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d476f0.txt`.
- RVA 0x00947810, `?Register_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z`: 00D4784F a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d47810.txt`.
- RVA 0x00948BD0, `?d_00948bd0@@YAXXZ`: 00D4923A a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d48bd0.txt`.
- RVA 0x00950C90, `?Render@SegmentedLineClass@@UAEXAAVRenderInfoClass@@@Z`: 00D50CA0 8a0d746d2d01 mov cl, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d50c90.txt`.
- RVA 0x00955C40, `?Render@Bitmap2DObjClass@@UAEXAAVRenderInfoClass@@@Z`: 00D55C56 8a0d746d2d01 mov cl, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d55c40.txt`.
- RVA 0x0098BE50, `?Render@ParticleBufferClass@@UAEXAAVRenderInfoClass@@@Z`: 00D8BE54 8a0d746d2d01 mov cl, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d8be50.txt`.
- RVA 0x0098ED30, `?Render@LineGroupClass@@QAEXAAVRenderInfoClass@@@Z`: 00D8EEC2 a0746d2d01 mov al, byte ptr [0x12d6d74]. Raw `build/rlink/scalar-17/body-00d8ed30.txt`.

### VA 0x012D6D84

- RVA 0x006E7020, `?Rva006E7020StoreFlag@@YAXE@Z`: 00AE7024 a2846d2d01 mov byte ptr [0x12d6d84], al. Raw `build/rlink/scalar-17/body-00ae7020.txt`.
- RVA 0x006ED5B0, `?init@W3DDisplay@@UAEXXZ`: 00AED841 c605846d2d0100 mov byte ptr [0x12d6d84], 0. Raw `build/rlink/scalar-17/body-00aed5b0.txt`.

### VA 0x012ED8A0

- RVA 0x00105790, `?bfmeGoDYB@@YAXXZ`: 005057A6 a3a0d82e01 mov dword ptr [0x12ed8a0], eax; 005057AB c705a4d82e0100000000 mov dword ptr [0x12ed8a4], 0. Raw `build/rlink/scalar-17/body-00505790.txt`.
- RVA 0x001057C0, `?Rva001057C0@@YAXXZ`: 005057D6 8b15a0d82e01 mov edx, dword ptr [0x12ed8a0]; 005057E0 1b0da4d82e01 sbb ecx, dword ptr [0x12ed8a4]. Raw `build/rlink/scalar-17/body-005057c0.txt`.

### VA 0x012F12F0

- RVA 0x004120E0, `?bfmeBumpClientGuard@@YAXXZ`: 008120E0 a1f0122f01 mov eax, dword ptr [0x12f12f0]; 0081210A ff05f0122f01 inc dword ptr [0x12f12f0]. Raw `build/rlink/scalar-17/body-008120e0.txt`.
- RVA 0x00412120, `?friend_unlockDirtyStuffForIteration@Drawable@@SAXXZ`: 00812120 a1f0122f01 mov eax, dword ptr [0x12f12f0]; 0081212A a3f0122f01 mov dword ptr [0x12f12f0], eax. Raw `build/rlink/scalar-17/body-00812120.txt`.

### VA 0x01337824

- RVA 0x00892360, `?store@Rva00892360@@SAXH@Z`: 00C92364 a324783301 mov dword ptr [0x1337824], eax. Raw `build/rlink/scalar-17/body-00c92360.txt`.
- RVA 0x00892370, `?AptGetSwfVersion@@YAIXZ`: 00C92370 a124783301 mov eax, dword ptr [0x1337824]. Raw `build/rlink/scalar-17/body-00c92370.txt`.

### VA 0x0133F429

- RVA 0x008FD880, `?End_Render@WW3D@@SA?AW4WW3DErrorType@@_N@Z`: 00CFD893 c60529f4330100 mov byte ptr [0x133f429], 0. Raw `build/rlink/scalar-17/body-00cfd880.txt`.
- RVA 0x008FE280, `?Begin_Render@WW3D@@SA?AW4WW3DErrorType@@_N0ABVVector3@@MP6AXXZ@Z`: 00CFE290 a029f43301 mov al, byte ptr [0x133f429]; 00CFE332 c60529f4330101 mov byte ptr [0x133f429], 1. Raw `build/rlink/scalar-17/body-00cfe280.txt`.

### VA 0x0133F42A

- RVA 0x008FD370, `?Stop_Movie_Capture@WW3D@@SAXXZ`: 00CFD370 a02af43301 mov al, byte ptr [0x133f42a]; 00CFD381 c6052af4330100 mov byte ptr [0x133f42a], 0. Raw `build/rlink/scalar-17/body-00cfd370.txt`.
- RVA 0x008FD6E0, `?Shutdown@WW3D@@SA_NXZ`: 00CFD6F6 a02af43301 mov al, byte ptr [0x133f42a]; 00CFD70A 881d2af43301 mov byte ptr [0x133f42a], bl. Raw `build/rlink/scalar-17/body-00cfd6e0.txt`.
- RVA 0x008FDE90, `?d_008fde90@@YAXXZ`: 00CFDE9E a02af43301 mov al, byte ptr [0x133f42a]; 00CFDEB9 c6052af4330100 mov byte ptr [0x133f42a], 0; 00CFDEE0 c6052af4330101 mov byte ptr [0x133f42a], 1; 00CFDF80 a02af43301 mov al, byte ptr [0x133f42a]; 00CFDF91 c6052af4330100 mov byte ptr [0x133f42a], 0. Raw `build/rlink/scalar-17/body-00cfde90.txt`.
- RVA 0x008FE280, `?Begin_Render@WW3D@@SA?AW4WW3DErrorType@@_N0ABVVector3@@MP6AXXZ@Z`: 00CFE300 a02af43301 mov al, byte ptr [0x133f42a]. Raw `build/rlink/scalar-17/body-00cfe280.txt`.

### VA 0x0133F42E

- RVA 0x0094DE12, `boundary-unproved probe window`: 00D4DE20 a02ef43301 mov al, byte ptr [0x133f42e]. Raw `build/rlink/scalar-17/body-00d4de12.txt`.
- RVA 0x0094E060, `?rva0094E060SetSortLevel@MeshModelClass@@QAEX_N@Z`: 00D4E08B a02ef43301 mov al, byte ptr [0x133f42e]. Raw `build/rlink/scalar-17/body-00d4e060.txt`.
- RVA 0x0096E750, `?post_process@MeshModelClass@@IAEXXZ`: 00D6E7A7 a02ef43301 mov al, byte ptr [0x133f42e]. Raw `build/rlink/scalar-17/body-00d6e750.txt`.

### VA 0x0133F434

- RVA 0x008FD880, `?End_Render@WW3D@@SA?AW4WW3DErrorType@@_N@Z`: 00CFD89F a134f43301 mov eax, dword ptr [0x133f434]; 00CFD8A8 a334f43301 mov dword ptr [0x133f434], eax. Raw `build/rlink/scalar-17/body-00cfd880.txt`.
- RVA 0x00945402, `boundary-unproved probe window`: 00D45410 a134f43301 mov eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d45402.txt`.
- RVA 0x00945F90, `?Request_Log_Statistics@DX8MeshRendererClass@@SAXXZ`: 00D45F90 a134f43301 mov eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d45f90.txt`.
- RVA 0x00947B50, `?Log_Statistics_String@DX8MeshRendererClass@@QAEX_N@Z`: 00D47B59 3b0534f43301 cmp eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d47b50.txt`.
- RVA 0x00986FC0, `?Update_Visual_Particle_State@ParticleBufferClass@@IAEXXZ`: 00D87142 8b0d34f43301 mov ecx, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d86fc0.txt`.
- RVA 0x00987C60, `?Get_New_Particles@ParticleBufferClass@@IAEXXZ`: 00D87C7A a134f43301 mov eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d87c60.txt`.
- RVA 0x00988060, `?Update_Non_New_Particles@ParticleBufferClass@@IAEXI@Z`: 00D880C1 a134f43301 mov eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d88060.txt`.
- RVA 0x0098AD00, `?Render_Line@ParticleBufferClass@@IAEXAAVRenderInfoClass@@@Z`: 00D8AD56 8b3534f43301 mov esi, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d8ad00.txt`.
- RVA 0x0098B460, `?Update_Bounding_Box@ParticleBufferClass@@IAEXXZ`: 00D8B4C3 a134f43301 mov eax, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d8b460.txt`.
- RVA 0x0098B800, `?Render_Particles@ParticleBufferClass@@IAEXAAVRenderInfoClass@@@Z`: 00D8B8DA 8b3d34f43301 mov edi, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d8b800.txt`.
- RVA 0x0098B950, `?Render_Line_Group@ParticleBufferClass@@IAEXAAVRenderInfoClass@@@Z`: 00D8BA02 8b3d34f43301 mov edi, dword ptr [0x133f434]. Raw `build/rlink/scalar-17/body-00d8b950.txt`.

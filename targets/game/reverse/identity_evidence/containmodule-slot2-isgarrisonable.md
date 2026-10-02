# ContainModuleInterface slot 2: isGarrisonable

Binary facts are direct pefile/Capstone reads of retail lotrbfme.exe, SHA-256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.
Addresses are RVAs unless explicitly marked VA.

## A matched BFME call fixes the slot name

Matched Object::getRadarPriority at 001CA4D0 (99 bytes), in
ObjectTemplateQueries.cpp, loads its contain pointer from object +0x1FC at
001CA4F2. At **001CA4FE** it calls `dword ptr [eax+8]`, i.e. contain slot 2,
and tests AL. The matched source names that predicate isGarrisonable.
GeneralsMD ContainModule.h independently places isGarrisonable third, after
asOpenContain and containReactToTransformChange. Thus the mapping rests on
both a direct BFME call and the ZH interface, not on later-slot alignment.

## Introducing owners and the complete inherited-use census

The registered-constructor/first-base-call census is detailed in
`damagemodule-slots0-1-callbacks.md`; the primary literal getter proof for
OpenContain and TunnelContain also appears in `containmodule-slot0-asopencontain.md`.
OpenContain ctor 002277A0 introduces contain table VA 010AC038 at +0x20;
TunnelContain ctor 0022EE70 first calls it, then replaces that table with
VA 010ADB38. Their primary slot-2 getters return OpenContain and TunnelContain.

GarrisonContain's registered factory 00116040 calls ILT 0001934E at
0011607E -> constructor 0021D820. That constructor calls OpenContain at
0021D84A, then installs primary VA 010AB818 at 0021D86A and contain
VA 010AB598 at +0x20 at 0021D87E. Its primary slot-2 ILT 000085D5 ->
getter 0021D9B0 returns literal VA 01090AC0, `GarrisonContain`.

| Owner | Constructor RVA | Contain table VA | Slot-2 body RVA |
|---|---|---|---|
| AODHordeContain | 0x00230580 | 010AE520 | 00220210 |
| ContestableContain | 0x0021BEE0 | 010AB140 | 0021B860 |
| GarrisonContain | 0x0021D820 | 010AB598 | 0021B860 |
| HealContain | 0x00220190 | 010AB9F8 | 00220210 |
| HordeContain | 0x0023EAF0 | 010AF048 | 00220210 |
| HordeGarrisonContain | 0x00248F90 | 010AFB40 | 0021B860 |
| HordeSiegeEngineContain | 0x0024A560 | 010B0028 | 00220210 |
| HordeTransportContain | 0x0024B6F0 | 010B0408 | 00220210 |
| HorseHordeContain | 0x0024D220 | 010B0AD0 | 00220210 |
| OpenContain | 0x002277A0 | 010AC038 | 00220210 |
| RiderChangeContain | 0x00229FB0 | 010AC870 | 00220210 |
| SiegeEngineContain | 0x0022BC50 | 010ACE08 | 00220210 |
| SlaughterHordeContain | 0x0024E7A0 | 010B0F40 | 0021B860 |
| TransportContain | 0x0022D010 | 010AD268 | 00220210 |
| TunnelContain | 0x0022EE70 | 010ADB38 | 0022EF30 |

Whole-image stub-VA searches find exactly ten references to 00417B16
(OpenContain), four to 00432D5D (GarrisonContain), and one to 00425E50
(TunnelContain). Each occurs once in slot 2 of precisely the tables above.
CaveContain has a different override and is outside this claim. The base-call
chains establish that the ten-use body is introduced by OpenContain, and
that GarrisonContain introduces the four-use true body inherited by its
three descendants. TunnelContain explicitly replaces its inherited slot.
These are three identities, not fifteen separate inherited-method claims.

## Class-specific ZH twins and exact extents

GeneralsMD OpenContain.h:202, GarrisonContain.h:114 and TunnelContain.h:93
explicitly define public const virtual `Bool isGarrisonable() const` in
each of these classes, returning false, true and false respectively.

| Owner | ILT RVA | Body RVA | Complete bytes | Decorated suffix |
|---|---|---|---|---|
| OpenContain | 00017B16 | 00220210 | 32 C0 C3 | UBE_NXZ |
| GarrisonContain | 00032D5D | 0021B860 | B0 01 C3 | UBE_NXZ |
| TunnelContain | 00025E50 | 0022EF30 | 32 C0 C3 | UBE_NXZ |

Each ILT is E9 directly to its listed body. INT3 immediately follows each
three-byte return body; AL return width, no stack arguments and the const
virtual mangling agree with the explicit ZH declarations. Use the existing
OpenContain.cpp/GarrisonContain.cpp TUs and the untouched full vendored
TunnelContain.cpp (which emits its inline virtuals). Retire the two free
function placeholders. Repoint the generated TunnelContain row without
editing its gen_small source.

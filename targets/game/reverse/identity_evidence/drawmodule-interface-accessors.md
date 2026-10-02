# DrawModule interface-acquisition slots

All BFME1 addresses below are RVAs unless explicitly called VAs. Evidence was
read with pefile and capstone from
`inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`, image base
`0x00400000`. Byte equality alone is not the identity argument. Image SHA-256:
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

## W3DDebrisDraw: slots 40 and 41

`module_registry.tsv` independently registers the literal `W3DDebrisDraw` at
`0x006C0046`, instance factory `0x006BEF40`, constructor `0x007505C0`, object
size `0x48`. The constructor calls DrawableModule at RVA `0x00113DA0` through ILT `0x00002874` at
`0x007505CF` and makes these stores:

| Instruction | Destination | Table VA |
|---|---|---|
| `0x007505D4` | `[esi+0x0C]` | `0x01121EA4` (base interface) |
| `0x007505DD` | `[esi]` | `0x01121EC0` (derived primary) |
| `0x007505E3` | `[esi+0x0C]` | `0x01121EB0` (derived interface) |

The secondary table has exactly the two DebrisDrawInterface operations from
Zero Hour: slot 0 goes through ILT `0x0000FA74` to `0x00750CC0`, the independently
reconstructed `W3DDebrisDraw::setModelName`; slot 1 goes through `0x000302C4` to
`0x00750F10`, `W3DDebrisDraw::setAnimNames`. This names the interface at +0x0C.

| Primary slot | Pointer RVA | ILT RVA | Body RVA | Identity |
|---|---|---|---|---|
| 40 | `0x00D21F60` | `0x0004143E` | `0x00750690` | const `getDebrisDrawInterface` |
| 41 | `0x00D21F64` | `0x0000171C` | `0x00750680` | non-const `getDebrisDrawInterface` |

An executable-section E9 scan finds exactly one stub targeting each body. A
bytewise whole-image scan finds exactly one occurrence of each stub VA as a
little-endian dword: the listed primary-table entry. Both bodies are the complete
11-byte sequence `85 C9 74 04 8D 41 0C C3 33 C0 C3`, ending in returns on both
paths and followed by INT3 padding. Both perform the null-preserving derived-to-
base pointer conversion to the constructor-proven secondary interface.

The lexical and type witnesses are Zero Hour's unmodified
`GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DDebrisDraw.h`
(lines 47, 73-74): public inheritance from `DrawModule, DebrisDrawInterface`, then
public virtual `DebrisDrawInterface* getDebrisDrawInterface() { return this; }`
and `const DebrisDrawInterface* getDebrisDrawInterface() const { return this; }`.
The two upstream bodies compile to the exact BFME1 bytes with the existing
`BFME_MODULE_NO_MPO` shim configuration, which makes the primary base 12 bytes.
MSVC 7.1 groups overloaded virtuals in reverse declaration order (also documented
in `docs/matching.md`), so the const overload is slot 40 and non-const slot 41.
They return pointers in EAX, have no stack arguments, and are public virtuals:

- `?getDebrisDrawInterface@W3DDebrisDraw@@UBEPBVDebrisDrawInterface@@XZ`.
- `?getDebrisDrawInterface@W3DDebrisDraw@@UAEPAVDebrisDrawInterface@@XZ`.

## Family cross-check

The registered constructors establish independent primary tables:

| Owner | Constructor | Primary table VA | Slots 40 / 41 bodies |
|---|---|---|---|
| W3DDebrisDraw | `0x007505C0` | `0x01121EC0` | `00750690 / 00750680` |
| W3DRopeDraw | `0x0075A490` | `0x011234E8` | `00750110 / 00750100` |
| W3DLaserDraw | `0x00757E70` | `0x01122A00` | `00750110 / 00750100` |
| W3DScriptedModelDraw | `0x00773360` | `0x01123D38` | `00750110 / 00750100` |

In the other tables these slots inherit DrawModule's null default. W3DRopeDraw
instead overrides slots 42/43 (`0075A5C0 / 0075A5B0`), W3DLaserDraw slots 44/45
(`00757BD0 / 00757BC0`), and the model family slots 38/39
(`00751DA0 / 00751D90`). The distinct override pairs agree with the independently
registered owners and their Zero Hour interface inheritance. BFME omits the
ZH TracerDrawInterface pair in this region; no global ZH slot-number identity
is assumed.

## Correction

The previous `?dup_00750680@@YAXXZ` and `?dup_00750690@@YAXXZ` ledger rows use
`gen-alias;object-symbol=?getRopeDrawInterface@W3DRopeDraw@@UAEPAVRopeDrawInterface@@XZ`
and `W3DRopeDraw.cpp`. Identical conversion bytes do not justify that owner or
interface. The unique retail routes above prove W3DDebrisDraw. Replace the two
rows at their unchanged 11-byte extents, tombstone their old claims, and use a
small TU that includes the upstream W3DDebrisDraw header and forces both inline
overloads to be emitted. The unrelated W3DRopeDraw source remains in use.

## Mechanical registered-table census

For each module_registry row ending in Draw, disassemble the registered
constructor, select its final primary-vptr store, read slots 38 through 45,
and resolve each pointer through its E9 stub. This yields all 16 registered
Draw owners (the rest of this note uses the Debris pair only):

| Registered owner | Primary table RVA | Store instruction RVA | Slot 40 body | Slot 41 body |
|---|---|---|---|---|
| W3DBuffDraw | `0xd21cd8` | `0x750254` | `0x750110` | `0x750100` |
| W3DDebrisDraw | `0xd21ec0` | `0x7505dd` | `0x750690` | `0x750680` |
| W3DDefaultDraw | `0xd21ff0` | `0x7513fc` | `0x750110` | `0x750100` |
| W3DFloorDraw | `0xd22220` | `0x7517b7` | `0x750110` | `0x750100` |
| W3DHordeModelDraw | `0xd22470` | `0x751d18` | `0x750110` | `0x750100` |
| W3DLaserDraw | `0xd22a00` | `0x757eac` | `0x750110` | `0x750100` |
| W3DLightDraw | `0xd22b20` | `0x7583d6` | `0x750110` | `0x750100` |
| W3DPropDraw | `0xd23068` | `0x7592d4` | `0x750110` | `0x750100` |
| W3DQuadrupedDraw | `0xd23390` | `0x759744` | `0x750110` | `0x750100` |
| W3DRopeDraw | `0xd234e8` | `0x75a4ae` | `0x750110` | `0x750100` |
| W3DScriptedModelDraw | `0xd23d38` | `0x773398` | `0x750110` | `0x750100` |
| W3DStreakDraw | `0xd254a8` | `0x77d968` | `0x750110` | `0x750100` |
| W3DSupplyDraw | `0xd256d0` | `0x77db84` | `0x750110` | `0x750100` |
| W3DTankDraw | `0xd25ab0` | `0x77f081` | `0x750110` | `0x750100` |
| W3DTreeDraw | `0xd25be8` | `0x77f1d4` | `0x750110` | `0x750100` |
| W3DTruckDraw | `0xd265b0` | `0x77fb51` | `0x750110` | `0x750100` |

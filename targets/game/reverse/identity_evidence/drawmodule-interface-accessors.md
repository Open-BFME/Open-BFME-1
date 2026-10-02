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
Draw owners. The census columns below show the Debris pair:

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

## DrawModule's inherited null getters

The primary base table at VA `0x01121BA8` contains the default entries in all
four interface pairs. RVA `0x00750230` seats that table and tail-jumps through
ILT `0x0002B8C8` to the next base destructor at `0x00113E60`. Concrete draw
module destruction has the same transition: the independently reconstructed
W3DLightDraw destructor seats `0x01121BA8` at instruction RVA `0x007585E8`
before destroying DrawableModule. Its partial declaration reproduces the full
59-slot table. Zero Hour's `DrawModule : public DrawableModule` and empty inline
DrawModule destructor supply the introducing-class witness. These shared
bodies belong to DrawModule, not to any of the 16 registered concrete owners.

The same `Common/DrawModule.h` declares the eight public virtual const/non-const
getters below, returning typed null pointers. Its exact unmodified inline
bodies are compiled in `DrawModuleInterfaceAccessors.cpp`; no layout fields
are needed by a null getter. The table pairs use the same reversed overload
ordering as the proven W3DDebrisDraw pair.

| Slot | ILT RVA | Body RVA | Exact public virtual declaration |
|---|---|---|---|
| 38 | `0003B47B` | `007500F0` | `const ObjectDrawInterface* getObjectDrawInterface() const` |
| 39 | `0001D8DB` | `007500E0` | `ObjectDrawInterface* getObjectDrawInterface()` |
| 40 | `00040449` | `00750110` | `const DebrisDrawInterface* getDebrisDrawInterface() const` |
| 41 | `00011C39` | `00750100` | `DebrisDrawInterface* getDebrisDrawInterface()` |
| 42 | `00008819` | `00750130` | `const RopeDrawInterface* getRopeDrawInterface() const` |
| 43 | `0003C6AA` | `00750120` | `RopeDrawInterface* getRopeDrawInterface()` |
| 44 | `00031408` | `00750150` | `const LaserDrawInterface* getLaserDrawInterface() const` |
| 45 | `00001951` | `00750140` | `LaserDrawInterface* getLaserDrawInterface()` |

Each body is `33 C0 C3` (`xor eax,eax; ret`), followed by INT3 padding. No calls,
stack arguments, or pointer adjustment occur. Every inherited table uses the
same respective ILT entry; those repetitions are inheritance, not independent
class-specific bodies.

Further slot witnesses independently distinguish the interface pairs:

- Object: the matched Zero Hour twin
  `AnimatedParticleSysBoneClientUpdate::clientUpdate`, RVA `0x00603020` (61 B),
  calls primary slot 39 and then `updateBonesForClientParticleSystems` on the
  returned ObjectDrawInterface. The model secondary table VA `0x01123C68`
  begins with the matched `clientOnly_getRenderObjInfo` (`0075C390`),
  `clientOnly_getRenderObjBoundBox` (`0075C470`) and
  `clientOnly_getRenderObjBoneTransform` (`00763520`), agreeing with the three
  initial ObjectDrawInterface declarations in Zero Hour. This corroborates
  the model-family override of slots 38/39.
- Debris: the unique registered W3DDebrisDraw pair proven above.
- Rope: registered constructor `0075A490` seats secondary VA `011234D4` at
  +0x0C. That table's ILTs `00030BAC`, `00006B81`, `0004A525` reach matched
  `initRopeParms` (`0075AC70`), `setRopeCurLen` (`00759EA0`) and `setRopeSpeed`
  (`00759EB0`). Zero Hour `W3DRopeDraw.h:65-66` explicitly supplies both named
  getters, and its primary slots 42/43 are the +0x0C conversion pair.
- Laser: registered constructor `00757E70` seats secondary VA `011229FC` at
  +0x0C. Its only entry, ILT `00012CE2`, reaches the matched const float getter
  `getLaserTemplateWidth` (`00756E40`). Zero Hour `W3DLaserDraw.h:91-92`
  supplies both interface-getter twins; its primary slots 44/45 return +0x0C.

The eight previous `rva...@DrawModule` identities are replaced at unchanged
three-byte extents. This corrects the old untyped pointer and non-const
placeholders, including the nonvirtual claim at `00750130`. The partial
W3DLightDraw destructor declaration is updated to the same typed overloads,
with non-const declared first so MSVC emits const first. Unproven DrawModule
slots outside this getter block remain opaque.

### Retiring the old ICF misanchors

Before this correction, each of the eight real getter names was also claimed
at `0x006CF680`, size 3, source `W3DDefaultDraw.cpp`, with
`icf-owner=?Get_Sort_Level@RenderObjClass@@UBEHXZ`. Those are erroneous aliases:
retail did not fold identical COMDATs, and the DrawModule introducing table
and independently registered derived tables route these methods to the eight
distinct bodies listed above, never to `006CF680`. The zero-return bytes alone
cannot identify a method. Delete and tombstone precisely those eight name/RVA
pairs at `006CF680`, preserving all other claims there; no conclusion about
that address's correct identity is needed for this narrowly scoped repair.
The named methods survive at their proven retail addresses, so this is not a
descriptive-to-opaque downgrade and requires no name_corrections exemption.

An executable-section E9 scan finds exactly one ILT for each of these eight
default bodies. A whole-image pointer scan finds 11 occurrences apiece for
the Object pair and 17 apiece for the Debris/Rope/Laser pairs, all in the
corresponding inherited table slots. In particular the base table's slot
39 pointer lives at RVA `00D21C44`, and slots 38 through 45 occupy
`00D21C40` through `00D21C5C`. The matched Object getter caller's indirect
call is physically at `0060303A`, operand `[eax+0x9C]` (slot 39).

The compiled W3DLightDrawDestructor object was also inspected directly: its
`??_7DrawModule@@6B@` COFF relocations at offsets 38*4 through 45*4 name exactly
the eight typed methods above, const first in each pair. Its six ledger rows
remain byte-exact. Retiring the eight misanchors reduces the measured
`one_identity.surplus` baseline from 2516 to 2508.


## W3DLaserDraw: slots 44 and 45

The same census resolves the laser-specific pair independently. Registry site
`006C0112` names W3DLaserDraw, factory `006BF150`, constructor `00757E70`,
size `0x5C`. The factory pushes `0x5C` at `006BF166` and calls ILT `0000E61A`
at `006BF18B`, resolving to that constructor. Constructor instruction
`00757EA5` installs base LaserDrawInterface table VA `011229A0` at +0x0C,
`00757EAC` installs the derived primary VA `01122A00`, and `00757EB3`
installs derived secondary VA `011229FC` at +0x0C. Its single secondary
operation is the matched getLaserTemplateWidth described above.

| Slot | Pointer RVA | ILT RVA | Body RVA | Identity |
|---|---|---|---|---|
| 44 | `00D22AB0` | `0000F64B` | `00757BD0` | const getLaserDrawInterface |
| 45 | `00D22AB4` | `0002C13D` | `00757BC0` | non-const getLaserDrawInterface |

Whole-image bytewise dword scans find each stub VA exactly once, at its listed
primary-table entry. Both 11-byte bodies are `85 C9 74 04 8D 41 0C C3 33 C0 C3`,
with INT3 immediately after the final RET. Their null-preserving +0x0C
adjustment agrees with the independently proven secondary interface.
Zero Hour W3DLaserDraw.h:70 supplies DrawModule/LaserDrawInterface inheritance;
lines 91-92 explicitly define both public virtual overloads returning this.
The const overload occupies slot 44 under the same MSVC reverse-overload
rule proven above. The exact pointer-returning manglings are
`?getLaserDrawInterface@W3DLaserDraw@@UBEPBVLaserDrawInterface@@XZ` and
`?getLaserDrawInterface@W3DLaserDraw@@UAEPAVLaserDrawInterface@@XZ`.

Replace the two `?dup_00757bc0/00757bd0` aliases that falsely use the Rope
getter's object symbol. The upstream Laser header emits each real body in
W3DLaserDrawInterfaceAccessors.cpp; its wrappers are emission anchors only.
The existing Rope TU remains needed by its other rows. This is an identity
correction at unchanged extents, with no new pin or inferred member name.

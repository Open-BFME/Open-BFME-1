# TheRadar pointer at VA 0x012EF0E4

The selected datum is `class Radar *TheRadar`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheRadar@@3PAVRadar@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF0E4-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheRadar. Retail readers invoke radar object/event operations and its subsystem update. The reference declares Radar *TheRadar. The RadarSubsystem and BfmeThingAOA views access the same singleton at the same absolute operand address. The view casts preserve the receiver contract and do not assert new inheritance.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h:155: class Radar : public Snapshot,`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h:294: extern Radar *TheRadar;  ///< the radar singleton extern`

The pointer is defined once in `game/GameEngine/Source/Common/System/Radar.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?Radar00598950@@3PAVBfmeThingAOA@@A` | 1 |
| `?TheRadar@@3PAVRadar@@A` | 29 |
| `?TheRadarClientUpdate@@3PAVRadarSubsystem@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF0E4-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF0E4-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF0E4-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x0006B910 | 0x0046B9AC | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00079060 | 0x0047A095 | `push 0x12ef0e4` |
| 0x000D77B0 | 0x004D7886 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x000D77B0 | 0x004D7892 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x000D77B0 | 0x004D7A1A | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x000D77B0 | 0x004D7A26 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001072A0 | 0x005072C4 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001072F0 | 0x00507314 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001112D0 | 0x0051146D | `mov edx, dword ptr [0x12ef0e4]` |
| 0x001A8080 | 0x005A80CC | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001BED80 | 0x005BED86 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001C6F10 | 0x005C7040 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001C7E60 | 0x005C7EA5 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001C7E60 | 0x005C7F79 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001CE530 | 0x005CE59E | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001CE640 | 0x005CE661 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001CEFC0 | 0x005CF093 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001CEFC0 | 0x005CF49A | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D22C0 | 0x005D2374 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D29A0 | 0x005D39C6 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D4010 | 0x005D4162 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D4530 | 0x005D4709 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D4530 | 0x005D4715 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001D48A0 | 0x005D4DBE | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x001F2E80 | 0x005F302D | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00286440 | 0x006865ED | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x0029E330 | 0x0069E9AD | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002AB690 | 0x006AB8CA | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002AB690 | 0x006AB9A1 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002AC620 | 0x006ACA28 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002AC620 | 0x006ACA34 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002B8FF0 | 0x006B96FD | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002ED760 | 0x006ED769 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002EEC70 | 0x006EEC7F | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002EECA0 | 0x006EECC3 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002EF9F0 | 0x006EF9F0 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002EFD50 | 0x006EFD50 | `mov eax, dword ptr [0x12ef0e4]` |
| 0x002EFD60 | 0x006EFD60 | `mov eax, dword ptr [0x12ef0e4]` |
| 0x002F4140 | 0x006F4189 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x002FD790 | 0x006FD8A8 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00303BF0 | 0x00709C62 | `mov edx, dword ptr [0x12ef0e4]` |
| 0x00303BF0 | 0x00709C81 | `mov eax, dword ptr [0x12ef0e4]` |
| 0x0035F4E0 | 0x0075F5B3 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x0036F4D0 | 0x0076F5E2 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00370730 | 0x0077080A | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00394260 | 0x00794A29 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00394260 | 0x00794BD6 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00394260 | 0x00795AC1 | `mov eax, dword ptr [0x12ef0e4]` |
| 0x00397540 | 0x007999AC | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00419F00 | 0x0081A014 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00419F00 | 0x0081A0E5 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x0041EBD0 | 0x0081EE95 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x0043AAF0 | 0x0083AB04 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x0043AAF0 | 0x0083AB3A | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00445080 | 0x00845647 | `mov edi, dword ptr [0x12ef0e4]` |
| 0x004BFFE0 | 0x008BFFE8 | `mov eax, dword ptr [0x12ef0e4]` |
| 0x004BFFE0 | 0x008C0109 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x004BFFE0 | 0x008C023E | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x004BFFE0 | 0x008C0277 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00589490 | 0x00989541 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00589490 | 0x0098955C | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00589490 | 0x0098956C | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00589490 | 0x0098957D | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00592CD0 | 0x00992D10 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00598950 | 0x00998A39 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x005AFFB0 | 0x009B018F | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00603640 | 0x00A036E3 | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x006C4A50 | 0x00AC4A7C | `mov ecx, dword ptr [0x12ef0e4]` |
| 0x00799DC0 | 0x00B99E5C | `mov eax, dword ptr [0x12ef0e4]` |
| 0x00799DC0 | 0x00B99EA4 | `mov ecx, dword ptr [0x12ef0e4]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

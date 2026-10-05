# TheSidesList pointer at VA 0x012EF428

The selected datum is `class SidesList *TheSidesList`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheSidesList@@3PAVSidesList@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF428-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheSidesList, and snapshot registration uses CHUNK_SidesList. The retail users index sides and teams through this singleton; GameLogic init loads it before the two initialization calls. The reference declares SidesList *TheSidesList. BfmeSidesList and BfmeTableERJ are local views of this singleton, including the skirmish-side lookup and script-map setup.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h:135: class SidesList : public SubsystemInterface,`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h:243: extern SidesList *TheSidesList;	 ///< singleton instance of SidesList`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h:256: //friend class SidesList;  // This is essentially a component of the SidesInfo data structure.`

The pointer is defined once in `game/GameEngine/Source/GameLogic/Map/SidesList.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheSidesList@@3PAVBfmeSidesList@@A` | 1 |
| `?TheSidesList@@3PAVSidesList@@A` | 15 |
| `?g_bfmeTableERJ@@3PAVBfmeTableERJ@@A` | 2 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF428-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF428-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF428-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479796 | `push 0x12ef428` |
| 0x000889A0 | 0x004889FB | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1A90 | 0x004D1AA8 | `mov eax, dword ptr [0x12ef428]` |
| 0x000D1A90 | 0x004D1AEA | `mov eax, dword ptr [0x12ef428]` |
| 0x000D1C30 | 0x004D1C48 | `mov eax, dword ptr [0x12ef428]` |
| 0x000D1C30 | 0x004D1C88 | `mov eax, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D1E66 | `mov esi, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D1E96 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D1ECD | `mov esi, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D1F04 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D1FB5 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D20D0 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D20E6 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D20F8 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000D1E30 | 0x004D212A | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB152 | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB1EE | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB2EB | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB382 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB3F8 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB461 | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB527 | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB549 | `mov edx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB5B0 | `mov esi, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB5E3 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB68E | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB7B8 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB7EA | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB8AA | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB8FB | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB91B | `mov edx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB947 | `mov edx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DB967 | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBA17 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBA2F | `mov eax, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBA6F | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBB1A | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBC44 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000DB020 | 0x004DBC76 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E0090 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E0172 | `mov eax, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E0196 | `mov eax, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E01C7 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E0280 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E0292 | `mov eax, dword ptr [0x12ef428]` |
| 0x000E0060 | 0x004E04E4 | `mov eax, dword ptr [0x12ef428]` |
| 0x000E0640 | 0x004E0729 | `mov eax, dword ptr [0x12ef428]` |
| 0x000E0640 | 0x004E0804 | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0640 | 0x004E08BE | `mov ecx, dword ptr [0x12ef428]` |
| 0x000E0640 | 0x004E090E | `mov eax, dword ptr [0x12ef428]` |
| 0x001112D0 | 0x005114B9 | `mov eax, dword ptr [0x12ef428]` |
| 0x001112D0 | 0x00511775 | `mov eax, dword ptr [0x12ef428]` |
| 0x00337200 | 0x00737254 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0033C290 | 0x0073C2B2 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0033C290 | 0x0073C2D8 | `mov edx, dword ptr [0x12ef428]` |
| 0x0033C290 | 0x0073C2F1 | `mov eax, dword ptr [0x12ef428]` |
| 0x0033CA50 | 0x0073CA53 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0033CA50 | 0x0073CABC | `mov ecx, dword ptr [0x12ef428]` |
| 0x00342E40 | 0x007430D1 | `mov eax, dword ptr [0x12ef428]` |
| 0x00342E40 | 0x00743168 | `mov eax, dword ptr [0x12ef428]` |
| 0x00342E40 | 0x007431F2 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0034B9A0 | 0x0074BA87 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0034B9A0 | 0x0074BB0B | `mov ecx, dword ptr [0x12ef428]` |
| 0x0034B9A0 | 0x0074BB7D | `mov ecx, dword ptr [0x12ef428]` |
| 0x0034B9A0 | 0x0074BC6A | `mov edx, dword ptr [0x12ef428]` |
| 0x0034F950 | 0x0074F950 | `mov edx, dword ptr [0x12ef428]` |
| 0x0034F950 | 0x0074F99B | `mov edx, dword ptr [0x12ef428]` |
| 0x0035C8A0 | 0x0075C8A0 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0035C8A0 | 0x0075C927 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0035C8A0 | 0x0075C93D | `mov ecx, dword ptr [0x12ef428]` |
| 0x0036E650 | 0x0076E6AD | `mov ecx, dword ptr [0x12ef428]` |
| 0x0036E650 | 0x0076E722 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00374CF0 | 0x00774E3D | `mov ecx, dword ptr [0x12ef428]` |
| 0x00374F20 | 0x00774F52 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00374F20 | 0x00774F8D | `mov ecx, dword ptr [0x12ef428]` |
| 0x00375590 | 0x007755DB | `mov ecx, dword ptr [0x12ef428]` |
| 0x003865B0 | 0x0078675C | `mov ecx, dword ptr [0x12ef428]` |
| 0x003865B0 | 0x007867FD | `mov ecx, dword ptr [0x12ef428]` |
| 0x003865B0 | 0x00786813 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0038A1F0 | 0x0078A4EA | `mov ecx, dword ptr [0x12ef428]` |
| 0x0038A1F0 | 0x0078A4F5 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00392D00 | 0x00792E19 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00392D00 | 0x00793426 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00392D00 | 0x00793436 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00392D00 | 0x007934D5 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00392D00 | 0x00793589 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00394260 | 0x00794868 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00394260 | 0x007948C8 | `mov ebp, dword ptr [0x12ef428]` |
| 0x00394260 | 0x00794903 | `mov ebp, dword ptr [0x12ef428]` |
| 0x00394260 | 0x00794930 | `mov ecx, dword ptr [0x12ef428]` |
| 0x00394260 | 0x00794968 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4ADAA | `mov ecx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4ADCB | `mov ecx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4AE39 | `mov edx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4AE65 | `mov eax, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4AEDB | `mov ecx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4AF67 | `mov ecx, dword ptr [0x12ef428]` |
| 0x0074ACB0 | 0x00B4B26C | `mov ecx, dword ptr [0x12ef428]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

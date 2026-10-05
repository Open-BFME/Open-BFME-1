# TheLightPointSystem pointer at VA 0x012F0FF8

The selected datum is `class LightPointSystem *TheLightPointSystem`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheLightPointSystem@@3PAVLightPointSystem@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012F0FF8-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration constructs TheLightPointSystem from VA 0x01076348. INI::parseLightPointLevel at RVA 0x0039CCF0 loads this pointer, passes the address of its level vector at offset 8 and the parsed name through ILT RVA 0x00028AF6 to the lookup body at RVA 0x0039C1A0, then passes the level pointer through ILT RVA 0x0001FE88 to LightPointSystem::addLevel at RVA 0x0039CAB0. The existing class-qualified find, addLevel and rva0039C260 pins and matched bodies establish the pointee view. Player callers use their own integer-index store at offset 0x274 as an argument to this same system. This is not a separate special-power allowance store; the light-point lookup supplies that allowance behavior.

The reference facts that can be checked independently are:

The class-qualified pins and the exact routed retail calls above provide the independent identity facts; Zero Hour does not define this BFME-specific singleton.

The pointer is defined once in `game/GameEngine/Source/Common/GameEngine.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheBfmeSpecialPowerAllowanceStore@@3PAVBfmeSpecialPowerAllowanceStore@@A` | 1 |
| `?g_bfmeSinkBRB@@3PAVBfmeSinkBRB@@A` | 1 |
| `?g_bfmeSinkBRB@@3PAVLightPointSystem@@A` | 2 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012F0FF8-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012F0FF8-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012F0FF8-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479BFF | `push 0x12f0ff8` |
| 0x000C9890 | 0x004C9892 | `mov ecx, dword ptr [0x12f0ff8]` |
| 0x000C9900 | 0x004C9902 | `mov ecx, dword ptr [0x12f0ff8]` |
| 0x000C9930 | 0x004C9932 | `mov ecx, dword ptr [0x12f0ff8]` |
| 0x002A9850 | 0x006A9929 | `mov eax, dword ptr [0x12f0ff8]` |
| 0x0039CCF0 | 0x0079CCFE | `mov eax, dword ptr [0x12f0ff8]` |
| 0x0039CCF0 | 0x0079CD3E | `mov ecx, dword ptr [0x12f0ff8]` |
| 0x0039CCF0 | 0x0079CE30 | `mov ecx, dword ptr [0x12f0ff8]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

# TheBuildAssistant pointer at VA 0x012ED83C

The selected datum is `class BuildAssistant *TheBuildAssistant`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheBuildAssistant@@3PAVBuildAssistant@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED83C-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheBuildAssistant. Retail uses it for building, selling and the subsystem update slot. The reference declares BuildAssistant *TheBuildAssistant. The Rva0038DA10System view in GameLogic.cpp dispatches the update slot of this same pointer.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h:103: class BuildAssistant : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BuildAssistant.h:217: extern BuildAssistant *TheBuildAssistant;`

The pointer is defined once in `game/GameEngine/Source/Common/System/BuildAssistant.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheBuildAssistant@@3PAVBuildAssistant@@A` | 8 |
| `?TheBuildAssistant@@3PAVRva002B7C80BuildAssistant@@A` | 0 |
| `?g012ED83C@@3PAURva0038DA10System@@A` | 1 |
| `?g_bfmeOut982@@3PAVBfmeOut982@@A` | 0 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED83C-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED83C-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED83C-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479B44 | `push 0x12ed83c` |
| 0x000CE260 | 0x004CE2BD | `mov ecx, dword ptr [0x12ed83c]` |
| 0x00150E90 | 0x00550EA0 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x001643B0 | 0x00564488 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x001FECD0 | 0x005FEDA5 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x0029D790 | 0x0069D7BE | `mov ecx, dword ptr [0x12ed83c]` |
| 0x002B7C80 | 0x006B7CDF | `mov ecx, dword ptr [0x12ed83c]` |
| 0x002B7C80 | 0x006B7CFC | `mov ecx, dword ptr [0x12ed83c]` |
| 0x002C96D0 | 0x006C971A | `mov ecx, dword ptr [0x12ed83c]` |
| 0x002C96D0 | 0x006C9760 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x002F0CB0 | 0x006F0CD6 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x0038DA10 | 0x0078E12C | `mov ecx, dword ptr [0x12ed83c]` |
| 0x00397540 | 0x007985F2 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x004A4240 | 0x008A4A23 | `mov ecx, dword ptr [0x12ed83c]` |
| 0x004A747F | 0x008A74C3 | `mov ecx, dword ptr [0x12ed83c]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

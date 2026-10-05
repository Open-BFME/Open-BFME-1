# TheLocomotorStore pointer at VA 0x012EF504

The selected datum is `class LocomotorStore *TheLocomotorStore`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheLocomotorStore@@3PAVLocomotorStore@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF504-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheLocomotorStore. The parser additionally contains the assertion string TheLocomotorStore==NULL. Lookup callers resolve LocomotorTemplate entries by name and create locomotors; GameLogic updates the same singleton. The reference declares LocomotorStore *TheLocomotorStore. The Rva0038DA10System update view refers to the same receiver.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h:225: friend class LocomotorStore;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h:468: class LocomotorStore : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h:507: extern LocomotorStore *TheLocomotorStore;`

The pointer is defined once in `game/GameEngine/Source/GameLogic/Object/Locomotor.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheLocomotorStore@@3PAVLocomotorStore@@A` | 5 |
| `?TheRva001B70E0LocomotorStore@@3PAVRva001B70E0LocomotorStore@@A` | 0 |
| `?g012EF504@@3PAURva0038DA10System@@A` | 1 |
| `?g_bfmeOwnerERA@@3PAVBfmeOwnerERA@@A` | 0 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF504-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF504-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF504-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479A23 | `push 0x12ef504` |
| 0x001B70E0 | 0x005B7110 | `mov esi, dword ptr [0x12ef504]` |
| 0x001BAAA0 | 0x005BABF6 | `mov ebp, dword ptr [0x12ef504]` |
| 0x001BAD80 | 0x005BAD88 | `mov ecx, dword ptr [0x12ef504]` |
| 0x001BAEC0 | 0x005BAECE | `mov eax, dword ptr [0x12ef504]` |
| 0x001BAEC0 | 0x005BAF33 | `mov ebp, dword ptr [0x12ef504]` |
| 0x001BAEC0 | 0x005BB002 | `mov ecx, dword ptr [0x12ef504]` |
| 0x001BD0D0 | 0x005BD13B | `mov ecx, dword ptr [0x12ef504]` |
| 0x0027EC80 | 0x0067ED95 | `mov ecx, dword ptr [0x12ef504]` |
| 0x0038DA10 | 0x0078E154 | `mov ecx, dword ptr [0x12ef504]` |
| 0x00396D40 | 0x00796D9B | `mov ecx, dword ptr [0x12ef504]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

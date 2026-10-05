# TheObjectCreationListStore pointer at VA 0x012EF70C

The selected datum is `class ObjectCreationListStore *TheObjectCreationListStore`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheObjectCreationListStore@@3PAVObjectCreationListStore@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF70C-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheObjectCreationListStore. Retail consumers perform object-creation-list name lookup and parsing through this pointer. The reference declares ObjectCreationListStore *TheObjectCreationListStore. BfmeS1061 is a local lookup receiver view on that singleton.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h:44: class ObjectCreationListStore;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h:187: class ObjectCreationListStore : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h:221: extern ObjectCreationListStore *TheObjectCreationListStore;`

The pointer is defined once in `game/GameEngine/Source/GameLogic/Object/ObjectCreationList.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheObjectCreationListStore@@3PAVObjectCreationListStore@@A` | 7 |
| `?g_bfmeS1061@@3PAVBfmeS1061@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF70C-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF70C-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF70C-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x004799DA | `push 0x12ef70c` |
| 0x000B8F10 | 0x004B8F1B | `mov ecx, dword ptr [0x12ef70c]` |
| 0x001D82E0 | 0x005D830D | `mov ecx, dword ptr [0x12ef70c]` |
| 0x001DB050 | 0x005DB06C | `mov ecx, dword ptr [0x12ef70c]` |
| 0x001F2AF0 | 0x005F2BC0 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x001F2AF0 | 0x005F2C57 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002016E0 | 0x00601700 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002097E0 | 0x00609820 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x0028BB10 | 0x0068BB30 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002A40E0 | 0x006A4120 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002AEEA0 | 0x006AEEE0 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002B0890 | 0x006B08D0 | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002DF5A0 | 0x006DF5AF | `mov ecx, dword ptr [0x12ef70c]` |
| 0x002DF5A0 | 0x006DF5C3 | `mov ecx, dword ptr [0x12ef70c]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

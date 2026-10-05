# TheScienceStore pointer at VA 0x012ED7AC

The selected datum is `class ScienceStore *TheScienceStore`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheScienceStore@@3PAVScienceStore@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED7AC-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheScienceStore. The Science definition parser receives this pointer, and callers use its collection at offset 8 to resolve science names and prerequisites. The reference declares ScienceStore *TheScienceStore. Both BfmeC1087 and BfmeC1091 are receiver views used for science lookup on this singleton.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h:56: friend class ScienceStore;`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h:79: class ScienceStore : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Science.h:136: extern ScienceStore* TheScienceStore;`

The pointer is defined once in `game/GameEngine/Source/Common/RTS/Science.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheScienceStore@@3PAVScienceStore@@A` | 11 |
| `?g_bfmeC1087@@3PAVBfmeC1087@@A` | 1 |
| `?g_bfmeC1091@@3PAVBfmeC1091@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED7AC-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED7AC-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED7AC-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x0047953E | `push 0x12ed7ac` |
| 0x0009A580 | 0x0049A8BD | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000B8F40 | 0x004B8F44 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000B9BE0 | 0x004B9BEC | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000BCD80 | 0x004BCDD4 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000BE440 | 0x004BE546 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000C9850 | 0x004C9856 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000CFDF0 | 0x004CFE27 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000CFDF0 | 0x004CFE38 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000D55B0 | 0x004D55C7 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000D5600 | 0x004D5608 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000E8630 | 0x004E8650 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000E8630 | 0x004E86D8 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000E8630 | 0x004E879A | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000FA610 | 0x004FA6E0 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000FAB10 | 0x004FAD10 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x000FAB10 | 0x004FADA5 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x0010C5E0 | 0x0050C63E | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x0010C5E0 | 0x0050C689 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x0014A0A0 | 0x0054A0D6 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x001628F0 | 0x00562B33 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x002F00C0 | 0x006F00C4 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x002F0140 | 0x006F0144 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x002F01C0 | 0x006F0215 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x00322C70 | 0x00722C74 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x00322D10 | 0x00722D14 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x004A09D0 | 0x008A0A7F | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x004A09D0 | 0x008A0AA0 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x004A09D0 | 0x008A0AB1 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x004C1C30 | 0x008C1F01 | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x004C1C30 | 0x008C26CA | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x005996F0 | 0x009997DD | `mov ecx, dword ptr [0x12ed7ac]` |
| 0x005999B0 | 0x00999C80 | `mov ecx, dword ptr [0x12ed7ac]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

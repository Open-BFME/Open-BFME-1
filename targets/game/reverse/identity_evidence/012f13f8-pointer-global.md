# TheDrawGroupInfo pointer at VA 0x012F13F8

The selected datum is `struct DrawGroupInfo *TheDrawGroupInfo`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheDrawGroupInfo@@3PAUDrawGroupInfo@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012F13F8-retail.log`. A null initial value contains no initialized target relocation to resolve. The direct constructor and destructor stores prove this is a writable datum rather than a compiler constant.

GameClient construction at RVA 0x00433340 allocates and constructs the object through ILT RVA 0x000119DC, whose E9 reaches RVA 0x00421B80, and stores the result into this global. GameClient destruction at RVA 0x00431380 deletes the pointee and writes zero. The INI parser at RVA 0x000B8200 contains TheDrawGroupInfo==NULL; GameClient loads Data\INI\DrawGroupInfo.ini. Display-string post-load reads font name, size and bold at offsets 0, 4 and 8. The group-number draw body at RVA 0x00410F90 reads player-color control at offset 9, colors at 0x0C and 0x10, shadow offsets at 0x14 and 0x18, and the X/Y position and mode fields at 0x1C, 0x20, 0x24 and 0x28. These match the reference struct DrawGroupInfo, so the canonical decorated spelling uses PAU, not PAV.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h:33: struct DrawGroupInfo`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h:66: extern DrawGroupInfo *TheDrawGroupInfo;`

The pointer is defined once in `game/GameEngine/Source/GameClient/GameClientConstructor00433340.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheDrawGroupInfo@@3PAUDrawGroupInfo@@A` | 3 |
| `?TheDrawGroupInfo@@3PAVDrawGroupInfo@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012F13F8-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012F13F8-direct-writers-fields.log` preserves the complete constructor, destructor, parser and drawing bodies, with their direct stores, field reads and E9 chains. This cell is written directly rather than through the subsystem registration helper. `build/rlink/pointer-globals-1791178372/012F13F8-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x000B8200 | 0x004B8200 | `mov eax, dword ptr [0x12f13f8]` |
| 0x00410F90 | 0x00810FAF | `mov edi, dword ptr [0x12f13f8]` |
| 0x00410F90 | 0x0081106E | `mov ecx, dword ptr [0x12f13f8]` |
| 0x00410F90 | 0x00811086 | `mov eax, dword ptr [0x12f13f8]` |
| 0x0042F5A0 | 0x0082F617 | `mov ecx, dword ptr [0x12f13f8]` |
| 0x0042F5A0 | 0x0082F62E | `mov eax, dword ptr [0x12f13f8]` |
| 0x0042F5A0 | 0x0082F642 | `mov eax, dword ptr [0x12f13f8]` |
| 0x00431380 | 0x008313BB | `mov ecx, dword ptr [0x12f13f8]` |
| 0x00431380 | 0x008313DD | `mov dword ptr [0x12f13f8], ebp` |
| 0x00433340 | 0x00833572 | `mov dword ptr [0x12f13f8], eax` |
| 0x00433340 | 0x00833592 | `mov dword ptr [0x12f13f8], ebx` |
| 0x006F5890 | 0x00AF58A8 | `mov eax, dword ptr [0x12f13f8]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

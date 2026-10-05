# TheFunctionLexicon pointer at VA 0x012ED88C

The selected datum is `class FunctionLexicon *TheFunctionLexicon`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheFunctionLexicon@@3PAVFunctionLexicon@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED88C-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheFunctionLexicon. The input callback parser at RVA 0x00486900 loads this singleton into ECX, pushes the table index 1 and the name key, and calls ILT RVA 0x00025CD4, whose five-byte E9 reaches RVA 0x001056E0. Other readers use that same routed lookup for callback table indices 8, 9 and 11. The reference declares FunctionLexicon *TheFunctionLexicon and uses its indexed function tables for the corresponding window callbacks. WindowLookupShim is a local view of that receiver.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/FunctionLexicon.h:45: class FunctionLexicon : public SubsystemInterface`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/FunctionLexicon.h:128: };  // end class FunctionLexicon`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/FunctionLexicon.h:151: extern FunctionLexicon *TheFunctionLexicon;  ///< function dictionary external`

The pointer is defined once in `game/GameEngine/Source/Common/System/FunctionLexicon.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheFunctionLexicon@@3PAVFunctionLexicon@@A` | 4 |
| `?TheWindowLookupShim@@3PAVWindowLookupShim@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED88C-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED88C-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED88C-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x004796FB | `push 0x12ed88c` |
| 0x0046A870 | 0x0086A8E7 | `mov ecx, dword ptr [0x12ed88c]` |
| 0x0046A870 | 0x0086A9DC | `mov ecx, dword ptr [0x12ed88c]` |
| 0x004867A0 | 0x0088680C | `mov ecx, dword ptr [0x12ed88c]` |
| 0x00486850 | 0x008868BC | `mov ecx, dword ptr [0x12ed88c]` |
| 0x00486900 | 0x0088696C | `mov ecx, dword ptr [0x12ed88c]` |
| 0x004869B0 | 0x00886A1C | `mov ecx, dword ptr [0x12ed88c]` |
| 0x00486A60 | 0x00886ACC | `mov ecx, dword ptr [0x12ed88c]` |
| 0x00487630 | 0x0088768B | `mov ecx, dword ptr [0x12ed88c]` |
| 0x004876C0 | 0x00887719 | `mov ecx, dword ptr [0x12ed88c]` |
| 0x00487750 | 0x008877A9 | `mov ecx, dword ptr [0x12ed88c]` |
| 0x004877E0 | 0x00887839 | `mov ecx, dword ptr [0x12ed88c]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

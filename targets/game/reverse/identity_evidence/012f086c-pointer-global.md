# TheCaveSystem pointer at VA 0x012F086C

The identity facts support the proposed datum `class CaveSystem *TheCaveSystem`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheCaveSystem@@3PAVCaveSystem@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012F086C-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheCaveSystem. Retail users look up tunnel trackers by cave index and serialize or mutate the cave system. The reference declares CaveSystem *TheCaveSystem. BfmeJ1101 accesses this same pointer as a local receiver view.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CaveSystem.h:45: class CaveSystem : public SubsystemInterface,`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CaveSystem.h:75: extern CaveSystem *TheCaveSystem;`

The proposed owner is `game/GameEngine/Source/GameLogic/System/CaveSystem.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The attempted declaration correction was restored because find_declared_unmatched.py --fail reports the existing BfmeW1101::bfmeGo1101B definition in BfmeConv1101.cpp. The data row was removed. The address is unresolved for landing despite the established CaveSystem identity. The raw refusal is build/rlink/pointer-globals-1791178372/declared-unmatched-after.log. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheBfmeChainOwner@@3PAVBfmeChainOwner@@A` | 0 |
| `?TheCaveSystem@@3PAVCaveSystem@@A` | 6 |
| `?g_bfmeJ1101@@3PAVBfmeJ1101@@A` | 1 |
| `?g_bfmeMgrTJA@@3PAVBfmeMgrTJA@@A` | 0 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012F086C-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012F086C-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012F086C-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x004797DC | `push 0x12f086c` |
| 0x002197E0 | 0x006197E6 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219800 | 0x00619810 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219890 | 0x00619896 | `mov ecx, dword ptr [0x12f086c]` |
| 0x002198B0 | 0x006198B6 | `mov ecx, dword ptr [0x12f086c]` |
| 0x002198D0 | 0x006198D6 | `mov ecx, dword ptr [0x12f086c]` |
| 0x002198F0 | 0x006198F6 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219C70 | 0x00619C82 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D10 | 0x00619D2A | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D10 | 0x00619D3B | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D70 | 0x00619D7B | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D70 | 0x00619D91 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D70 | 0x00619D9F | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D70 | 0x00619DBE | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219D70 | 0x00619DCE | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219E20 | 0x00619E2B | `mov ecx, dword ptr [0x12f086c]` |
| 0x00219E80 | 0x00619E87 | `mov ecx, dword ptr [0x12f086c]` |
| 0x0021A080 | 0x0061A0AF | `mov ecx, dword ptr [0x12f086c]` |
| 0x0021A080 | 0x0061A0C0 | `mov ecx, dword ptr [0x12f086c]` |
| 0x00391C40 | 0x00791EEC | `mov eax, dword ptr [0x12f086c]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

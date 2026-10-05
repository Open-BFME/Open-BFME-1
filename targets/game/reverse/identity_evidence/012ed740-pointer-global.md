# ThePlayerAITypeSet pointer at VA 0x012ED740

The selected datum is `class PlayerAITypeSet *ThePlayerAITypeSet`, a single mutable singleton pointer. Its canonical decorated spelling is `?ThePlayerAITypeSet@@3PAVPlayerAITypeSet@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012ED740-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The subsystem registration constructs the name from VA 0x0107647C. RVA 0x000DF1A0 passes an INI pointer with this singleton in ECX to ILT RVA 0x0003EBD5, whose E9 reaches RVA 0x000DEEC0. RVA 0x0019FD00 passes an AsciiString pointer with this singleton in ECX through ILT RVA 0x0000336E to PlayerAITypeSet::find at RVA 0x000DE1B0, then indexes 16-byte entries via the pointer at pointee offset 8. The existing class-qualified find pin and matched implementation establish the pointee view. BfmePlayerAITypeSet is a second view of the same receiver.

The reference facts that can be checked independently are:

The class-qualified pins and the exact routed retail calls above provide the independent identity facts; Zero Hour does not define this BFME-specific singleton.

The pointer is defined once in `game/GameEngine/Source/Common/GameEngine.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?ThePlayerAITypeSet@@3PAVBfmePlayerAITypeSet@@A` | 1 |
| `?ThePlayerAITypeSet@@3PAVPlayerAITypeSet@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012ED740-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012ED740-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012ED740-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x0047988D | `push 0x12ed740` |
| 0x000DF1A0 | 0x004DF1A4 | `mov ecx, dword ptr [0x12ed740]` |
| 0x0019FD00 | 0x0059FDC2 | `mov ecx, dword ptr [0x12ed740]` |
| 0x0019FD00 | 0x0059FDD2 | `mov edx, dword ptr [0x12ed740]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

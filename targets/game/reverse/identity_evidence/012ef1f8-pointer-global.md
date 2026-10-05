# TheAerialPathfinder pointer at VA 0x012EF1F8

The selected datum is `class AerialPathfinder *TheAerialPathfinder`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheAerialPathfinder@@3PAVAerialPathfinder@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF1F8-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration constructs TheAerialPathfinder from VA 0x010762CC. The NoFlyZone parser at RVA 0x000B7E70 passes a polygon pointer and a height with this singleton in ECX to ILT RVA 0x0003DF82, whose E9 reaches AerialPathfinder::addNoFlyZone at RVA 0x00148C10. The matched addNoFlyZone class-qualified implementation and existing pins supply the type spelling independently of the declaration count. Goal setup at RVA 0x002BC260 loads this identical pointer and routes its six-argument member call through ILT RVA 0x0000A795. Its Rva002BC260Global view is preserved as a use-site cast.

The reference facts that can be checked independently are:

The class-qualified pins and the exact routed retail calls above provide the independent identity facts; Zero Hour does not define this BFME-specific singleton.

The pointer is defined once in `game/GameEngine/Source/Common/GameEngine.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheAerialPathfinder@@3PAVAerialPathfinder@@A` | 2 |
| `?g_rva002bc260@@3PAVRva002BC260Global@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF1F8-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF1F8-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF1F8-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x00479D75 | `push 0x12ef1f8` |
| 0x000B7E70 | 0x004B7EEE | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x00149010 | 0x00549094 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x001BBC50 | 0x005BBD71 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x001BBC50 | 0x005BBE63 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x001BBC50 | 0x005BBED0 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x001BBC50 | 0x005BC29B | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x002BC260 | 0x006BC283 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x002BC9C0 | 0x006BCA23 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x002BC9C0 | 0x006BCA51 | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x002BC9C0 | 0x006BCA7D | `mov ecx, dword ptr [0x12ef1f8]` |
| 0x002BC9C0 | 0x006BCAAD | `mov ecx, dword ptr [0x12ef1f8]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

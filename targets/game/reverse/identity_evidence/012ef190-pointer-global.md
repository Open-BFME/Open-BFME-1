# TheGameState pointer at VA 0x012EF190

The selected datum is `class GameState *TheGameState`, a single mutable singleton pointer. Its canonical decorated spelling is `?TheGameState@@3PAVGameState@@A`. The pointer has size 4, section `.data`, and initial bytes `00000000` (null). The surrounding bytes, PE extent, every absolute operand found by the byte search, and the absence of a data-row overlap or an interior DIR32 name are recorded in `build/rlink/pointer-globals-1791178372/012EF190-retail.log`. A null initial value contains no initialized target relocation to resolve. Its mutation and address passed to the subsystem registration prove this is a writable datum rather than a compiler constant.

The registration names TheGameState, and snapshot registration uses CHUNK_GameState. Retail readers perform save-game and state dispatch operations with this pointer as their receiver. The reference declares GameState *TheGameState. TheRva005121A0Service is another receiver view on this singleton.

The reference facts that can be checked independently are:

- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h:151: class GameState : public SubsystemInterface,`
- `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameState.h:240: extern GameState *TheGameState;`

The pointer is defined once in `game/GameEngine/Source/Common/System/SaveGame/GameState.cpp`, the reference owner or the source that contains the main initialization writer. Existing competing DIR32 rows are retained. The users now declare the canonical pointer type. Where a recovered caller needs a narrower layout or a different member signature, its existing view is reached by a cast at the use site; no inheritance, wrapper, forwarder or alias identity is added. Function definitions and ledger function identities remain unchanged.

Before correction, the direct declarations in game sources (including GLOBAL macro declarations and pointer declarator lists) were:

| Decorated spelling | Files declaring it |
|---|---:|
| `?TheGameState@@3PAURva0075B660State@@A` | 0 |
| `?TheGameState@@3PAVGameState@@A` | 32 |
| `?TheRva005121A0Service@@3PAVRva005121A0Service@@A` | 1 |

Counts do not decide identity. Includes may bring in additional reference declarations; the direct source declaration inventory is in `012EF190-game-uses.log` under the raw-log folder. The authoritative reference type and witnessed retail receiver contract decide the choice.

All decoded absolute references to the cell are listed below. A `push` of the cell address supplies a writer by reference; a `mov` whose destination names the absolute cell is a direct store; other absolute-cell operands are reads. `build/rlink/pointer-globals-1791178372/012EF190-writer.log` preserves the full registration helper and the pointer store through its address. `build/rlink/pointer-globals-1791178372/012EF190-contracts.log` preserves nearby strings and every five-byte E9 chain for the calls surrounding these references, including their final targets and ledger labels.

| Retail body RVA | Instruction VA | Access |
|---|---|---|
| 0x00079060 | 0x0047A324 | `push 0x12ef190` |
| 0x0010C7E0 | 0x0050C80B | `mov ecx, dword ptr [0x12ef190]` |
| 0x0010C7E0 | 0x0050C85D | `mov ecx, dword ptr [0x12ef190]` |
| 0x00110600 | 0x005106F3 | `mov ecx, dword ptr [0x12ef190]` |
| 0x001112D0 | 0x0051132A | `mov eax, dword ptr [0x12ef190]` |
| 0x00111C40 | 0x00511C85 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00112FF0 | 0x00513023 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x005132CB | `mov ebp, dword ptr [0x12ef190]` |
| 0x00113280 | 0x005132F6 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x00513301 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x0051333F | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x00513373 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x00513398 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x00513411 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x0051343C | `mov ecx, dword ptr [0x12ef190]` |
| 0x00113280 | 0x00513486 | `mov ecx, dword ptr [0x12ef190]` |
| 0x002ECF40 | 0x006ECFAA | `mov eax, dword ptr [0x12ef190]` |
| 0x002ECF40 | 0x006ECFC1 | `mov ecx, dword ptr [0x12ef190]` |
| 0x002ECF40 | 0x006ED00D | `mov eax, dword ptr [0x12ef190]` |
| 0x00386A30 | 0x00786AC1 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00386A30 | 0x00786AF0 | `mov eax, dword ptr [0x12ef190]` |
| 0x00386DE0 | 0x00786E6F | `mov ecx, dword ptr [0x12ef190]` |
| 0x00386DE0 | 0x00786E9E | `mov eax, dword ptr [0x12ef190]` |
| 0x00394260 | 0x0079442F | `mov ecx, dword ptr [0x12ef190]` |
| 0x00394260 | 0x00794440 | `mov ecx, dword ptr [0x12ef190]` |
| 0x003BDB80 | 0x007BDBC8 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00418DA0 | 0x008196A9 | `mov eax, dword ptr [0x12ef190]` |
| 0x004516E0 | 0x008517C5 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00491FA0 | 0x00891FE3 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DF130 | 0x008DF41A | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DF520 | 0x008DF7F8 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DFD10 | 0x008DFDAA | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DFEF0 | 0x008E016F | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DFEF0 | 0x008E0323 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DFEF0 | 0x008E03BF | `mov ecx, dword ptr [0x12ef190]` |
| 0x004DFEF0 | 0x008E0401 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004E4790 | 0x008E4A37 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004F6B60 | 0x008F7E76 | `mov ecx, dword ptr [0x12ef190]` |
| 0x004FD9B0 | 0x008FE786 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0051D700 | 0x0091D74E | `mov ecx, dword ptr [0x12ef190]` |
| 0x0051D9D0 | 0x0091D9E5 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0051E900 | 0x0091E92F | `mov ecx, dword ptr [0x12ef190]` |
| 0x0051E9B0 | 0x0091EA16 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00569E10 | 0x00969E92 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00569E10 | 0x00969EA9 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056D070 | 0x0096D2B9 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056D430 | 0x0096D4B3 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056DB70 | 0x0096DBA1 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056DB70 | 0x0096DBEF | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056E230 | 0x0096E38A | `mov ecx, dword ptr [0x12ef190]` |
| 0x0056FD30 | 0x0096FD66 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00621170 | 0x00A2119A | `mov ecx, dword ptr [0x12ef190]` |
| 0x00621170 | 0x00A211B3 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00621350 | 0x00A21392 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00621350 | 0x00A214F5 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00628BA0 | 0x00A29573 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00628BA0 | 0x00A2958E | `mov ecx, dword ptr [0x12ef190]` |
| 0x0062AD50 | 0x00A2B501 | `mov ecx, dword ptr [0x12ef190]` |
| 0x0062AD50 | 0x00A2B50C | `mov ecx, dword ptr [0x12ef190]` |
| 0x00635D90 | 0x00A35E49 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00639190 | 0x00A392DF | `mov ecx, dword ptr [0x12ef190]` |
| 0x00675450 | 0x00A7545A | `mov ecx, dword ptr [0x12ef190]` |
| 0x00675480 | 0x00A754A3 | `mov ecx, dword ptr [0x12ef190]` |
| 0x00675610 | 0x00A7561A | `mov ecx, dword ptr [0x12ef190]` |
| 0x00675640 | 0x00A75663 | `mov ecx, dword ptr [0x12ef190]` |
| 0x006861C0 | 0x00A86276 | `mov ecx, dword ptr [0x12ef190]` |
| 0x006861C0 | 0x00A8636D | `mov ecx, dword ptr [0x12ef190]` |
| 0x0068B540 | 0x00A8B581 | `mov ecx, dword ptr [0x12ef190]` |
| 0x006C39D0 | 0x00AC39FE | `mov ecx, dword ptr [0x12ef190]` |
| 0x0075B660 | 0x00B5B670 | `mov eax, dword ptr [0x12ef190]` |
| 0x00769370 | 0x00B693BE | `mov eax, dword ptr [0x12ef190]` |
| 0x0076DCC0 | 0x00B6DD17 | `mov eax, dword ptr [0x12ef190]` |
| 0x0076F9E0 | 0x00B6FA06 | `mov eax, dword ptr [0x12ef190]` |
| 0x00774AA0 | 0x00B74AC5 | `mov eax, dword ptr [0x12ef190]` |

The receiver is the value loaded from this one four-byte cell, passed unchanged in ECX for the witnessed thiscall operations (or through the explicit subobject adjustments already present in the existing caller). The argument contracts are the observed pushes and callee returns in the raw retail logs, checked against the reference operations or the existing class-qualified pins. This correction would be refuted by a routed call ending at a different body, a reference declaration with a different real type whose retail accesses agree instead, a non-pointer-width access to this cell, a datum or name inside its four-byte range, or any changed instruction or failed byte gate after the declaration correction.

# Data identity at VA 0x012F9CFC

The datum is the four-byte enum `FilterTypes W3DShaderManager::m_currentFilter`. The Zero Hour declaration is W3DShaderManager.h:125 and definition W3DShaderManager.cpp:112. The current donor defines the same member initialized to FT_NULL_FILTER.

Retail constructor RVA 0x007165C0 clears VA 0x012F9CFC. Filter pre/post-render bodies RVAs 0x00716A10 and 0x00716A50 record or clear the filter selector. Start-render-to-texture RVA 0x007171F0 reads it for filter-specific behavior; shutdown RVA 0x00717DA0 clears it. The older int spelling describes the width but loses the reference enum contract.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`.

A non-selector use that establishes an incompatible type, or a different cell used for the same reference state, refutes this enum identity.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?m_currentFilter@W3DShaderManager@@1HA` | 1 |
| `?m_currentFilter@W3DShaderManager@@1W4FilterTypes@@A` | 2 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

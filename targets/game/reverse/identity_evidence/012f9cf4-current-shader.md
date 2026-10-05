# Data identity at VA 0x012F9CF4

The datum is the four-byte enum `W3DShaderManager::ShaderTypes W3DShaderManager::m_currentShader`. The Zero Hour declaration is W3DShaderManager.h:122 and definition W3DShaderManager.cpp:111. The current donor defines this enum member.

Retail manager construction RVA 0x007165C0 stores -1 at VA 0x012F9CF4 after clearing manager state. Set/reset shader RVAs 0x00716980 and 0x007169D0 compare or assign the current shader selector. Shutdown RVA 0x00717DA0 clears it to the invalid enum value 0. The getter RVA 0x007C5560 returns the dword. The corrected getter retains its existing int return ABI; only the stored datum type and spelling change.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`.

Use of this cell as an object pointer, or a shader-selector contract bound to another address, refutes the enum identity.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?g_Va012F9CF4@@3HA` | 1 |
| `?m_currentShader@W3DShaderManager@@1HA` | 1 |
| `?m_currentShader@W3DShaderManager@@1W4ShaderTypes@1@A` | 1 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

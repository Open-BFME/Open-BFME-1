# Data identity at VA 0x012F9D00

The datum is the one-byte boolean `W3DShaderManager::m_renderingToTexture`. The Zero Hour declaration is protected in W3DShaderManager.h:127 and definition is W3DShaderManager.cpp:118. The current donor defines this protected boolean.

Retail constructor RVA 0x007165C0 stores a byte zero at VA 0x012F9D00. Start-render-to-texture RVA 0x007171F0 reads this flag and writes true after changing the render target; end-render-to-texture RVA 0x00717420 reads it and writes a byte zero. RVA 0x00722110 returns its low byte. The aggregate spelling g_bfmeShaderManager was a view anchored at this flag and used only to reach other resource cells at fixed offsets. Its external object declaration is removed; the existing field view is explicitly based on the real flag address. Public boolean declarations in the two smudge TUs are corrected to the reference protected spelling, using the reference inline accessor.

The registered object has 1 byte in retail `.data`, one object, and initial bytes `00`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`. The smudge accessors use the existing reference method W3DShaderManager::isRenderingToTexture declared at reference W3DShaderManager.h:113.

A multi-byte access to this cell that proves a larger object beginning here, or a render-state flag stored at another address, refutes the boolean extent and ownership.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?g_00722110@@3EA` | 1 |
| `?g_bfmeShaderManager@@3UBfmeShaderManagerStatics@@A` | 1 |
| `?m_renderingToTexture@W3DShaderManager@@1_NA` | 2 |
| `?m_renderingToTexture@W3DShaderManager@@2_NA` | 2 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

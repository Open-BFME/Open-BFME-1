# Data identity at VA 0x012F7730

The datum is `LANAPI *TheLAN`, one four-byte singleton pointer. The Zero Hour definition is `GameEngine/Source/GameNetwork/LANAPICallbacks.cpp:50`, and the current donor defines it in the corresponding file.

The retail readers use ECX loaded from VA 0x012F7730 for LAN dispatch. The matched update helper RVA 0x004CAF70 calls vtable slot +0xC0 to obtain the LAN game, as independently documented in identity_evidence/004caf70.md. The matched score-screen initializers store the chat listbox at receiver +0x5C. LAN create/reset, game-info and direct-connect bodies in references.json read or publish this singleton. Four remaining invented global declarations are respelled to TheLAN with their existing dispatch views retained at use sites.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp`.

A GetMyGame dispatch using a different global, or a constructor publishing another subsystem at this VA, refutes this LAN identity.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?TheLAN@@3PAVLANAPI@@A` | 45 |
| `?g_Va012F7730@@3PAVGen00024B7C@@A` | 0 |
| `?g_bfmeG1061@@3PAVBfmeG1061@@A` | 1 |
| `?g_bfmeG1070@@3PAVBfmeG1070@@A` | 1 |
| `?g_bfmeG1078@@3PAUBfmeG1078@@A` | 0 |
| `?g_bfmeG1102@@3PAVBfmeG1102@@A` | 1 |
| `?g_bfmeGlobLE@@3PAVBfmeGlobLE@@A` | 1 |
| `?g_bfmeK1023@@3PAVBfmeK1023@@A` | 0 |
| `?g_bfmeObjECI@@3PAVBfmeObjECI@@A` | 0 |
| `?g_rva004CAF70_g@@3PAXA` | 0 |
| `?s_chatHolder@@3PAVChatHolder@@A` | 0 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

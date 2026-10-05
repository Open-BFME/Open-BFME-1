# Data identity at VA 0x012F7194

The datum is `GameSpyInfoInterface *TheGameSpyInfo`, one four-byte singleton pointer. The Zero Hour definition is `GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp:55`, and its setup code calls the interface factory. The current game donor defines the same interface pointer in PeerDefs.cpp.

Matched SetUpGameSpy RVA 0x006377D0 calls ILT RVA 0x0001AF0F and stores EAX to VA 0x012F7194 at retail VA 0x00A3794E. It then reloads the pointer into ECX and calls its interface slots, including 0x100 and 0x108 for ASCII-string inputs. The matched GameSpyInfo::addChat RVA 0x00625AF0 loads this pointer as its receiver. The class-pointer spellings confuse the stored interface contract with implementation or partial dispatch views. Raw readers and writers are enumerated in references.json, with their complete bodies in body-*.txt.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngine/Source/GameNetwork/GameSpy/PeerDefs.cpp`.

A setup factory that returns a different subsystem interface, or a non-pointer retail access governing this four-byte cell, refutes the interface ownership.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?Rva012F7194@@3PAVRva012F7194Slots@@A` | 0 |
| `?TheBfmeSpyXE@@3PAVBfmeSpyXE@@A` | 0 |
| `?TheGameSpyInfo@@3PAUGameSpyInfo@@A` | 0 |
| `?TheGameSpyInfo@@3PAVBfmeGameSpyInfoView@@A` | 0 |
| `?TheGameSpyInfo@@3PAVGameSpyInfo@@A` | 2 |
| `?TheGameSpyInfo@@3PAVGameSpyInfoInterface@@A` | 125 |
| `?TheGameSpyInfo@@3PAVRva004E5DF0GameSpyInfo@@A` | 0 |
| `?TheGameSpyInfo@@3PAVRva0055CD80GameSpyInfo@@A` | 0 |
| `?TheGameSpyInfo@@3PAXA` | 0 |
| `?g_bfmeB1025@@3PAVBfmeB1025@@A` | 0 |
| `?g_bfmeInfoETA@@3PAVBfmeInfoETA@@A` | 0 |
| `?g_bfmeP1079@@3PAVBfmeP1079@@A` | 0 |
| `?g_bfmeUiDZD@@3PAVBfmeUiDZD@@A` | 0 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

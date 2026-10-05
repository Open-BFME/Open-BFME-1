# Data identity at VA 0x012F71B4

The datum is `GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue`, one four-byte interface pointer. The Zero Hour definition is `GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp:90`; its setup use is in PeerDefs.cpp:627. The current donor defines this pointer in BuddyThread.cpp.

Matched SetUpGameSpy RVA 0x006377D0 calls ILT RVA 0x0000EB1F and stores EAX to VA 0x012F71B4 at retail VA 0x00A37916. It then loads the returned vptr and calls slot +4 with ECX holding the queue. Persistent-storage login RVA 0x006549C0 loads the queue into ECX before calls to slots +0x2C and +0x30. The request helper RVA 0x00627AA0 supplies its request structure to queue slot +0x18. These are interface dispatch views of one pointer, not independent singleton objects.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp`.

A setup factory returning a different queue, or a witnessed object stored inline rather than through a four-byte pointer, refutes this identity.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?Rva012F71B4Buddy@@3PAVRva006549C0BuddyView@@A` | 1 |
| `?TheGameSpyBuddyMessageQueue@@3PAVGameSpyBuddyMessageQueueInterface@@A` | 24 |
| `?TheGameSpyBuddyMessageQueue@@3PAVRva0050D030ReferenceBuddyMessageQueueInterface@@A` | 0 |
| `?g_rva00627AA0@@3PAURva00627AA0Obj@@A` | 1 |
| `?g_va012F71B4@@3PAXA` | 2 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

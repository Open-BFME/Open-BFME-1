# Data identity at VA 0x012F7180

The datum is the single STLport `std::list<QueuedDownload> queuedDownloads` object. The Zero Hour definition is in `GameEngine/Source/GameNetwork/GameSpy/MainMenuUtils.cpp:70`; the current game donor has the corresponding definition. This is a list object, not an inline array of download records. Its sentinel pointer is allocated at dynamic initialization.

The initializer RVA 0x00C6C3F0 supplies ECX=0x012F7180 and an allocator argument to ILT RVA 0x00049C4C. Its five bytes `e9cfd85d00` jump to RVA 0x00627520. The initializer registers RVA 0x00C708D0 for teardown. That forwarder supplies the same ECX and jumps through ILT RVA 0x00011D5B to the list destructor. Reset RVA 0x0062E8B0 and cancellation RVA 0x0062F760 use this object as the receiver of list cleanup. Start-online RVA 0x0062EA60 checks the list contents. The receiver views are retained only at uses; their former globals are removed.

The registered object has 4 bytes in retail `.data`, one object, and initial bytes `00000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngine/Source/GameNetwork/GameSpy/MainMenuUtils.cpp`.

A list constructor or cleanup thunk routing to a different receiver address, or a compiled sizeof different from the registered extent, refutes the proposed ownership.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeObject_00C708D0@@3VGen_00C708D0Target@@A` | 1 |
| `?g_rva012F7180DownloadQueue@@3VGen00627270Owner@@A` | 1 |
| `?queuedDownloads@@3V?$list@VQueuedDownload@@V?$allocator@VQueuedDownload@@@_STL@@@_STL@@A` | 3 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

# Data identity at VA 0x012F9800

The datum is an eight-byte `MutexClass g_w3dMouseThreadRunLock`. The existing role name is retained and its one-byte declaration is corrected. It is not an unsigned-char flag. The reference MutexClass contains a handle and an unsigned lock count; no inheritance is introduced.

Dynamic initializer RVA 0x00C6C4D0 supplies ECX=0x012F9800 and a null name to the MutexClass constructor at RVA 0x009DB320. The constructor clears receiver +0 and +4, invokes CreateMutex, and stores the returned handle at +0. The atexit body RVA 0x00C709B0 supplies the same ECX to RVA 0x009DB350, whose body calls CloseHandle with the value at +0. Retail mouse bodies pass the address to lock guards. The next named object begins at VA 0x012F9808, so an eight-byte object fits without overlap.

The registered object has 8 bytes in retail `.data`, one object, and initial bytes `0000000000000000`. It lies in the virtual zero-filled tail of `.data`. It is mutable storage, not a compiler constant. There are no nonzero initial pointer fields, and the retail PE base-relocation directory is empty. The raw address-boundary and data-row probe in `build/rlink/retail-probe.log` establishes no other datum or DIR32 name strictly inside this extent. Existing competing rows at the same start address remain additive; no symbols.csv pin is removed or rewritten.

The receiver and argument contract is given above. This correction creates no wrapper, inheritance or second datum. Function identities, ledger order and verified instructions are retained. The owning definition is `game/GameEngine/Source/Common/StaticInit/Rva00C6C4D0Init.cpp`.

A constructor touching a field beyond +7, a teardown that does not close the handle at +0, or a guard bound to a different address refutes this mutex type and extent.

Direct typed declarations and definitions in game files before this change are counted below. Included reference headers are not counted as separate game files. Counts are subordinate to the retail and reference evidence; they do not decide identity. The declaration probe and its per-file results are saved in `build/rlink/declaration-counts-final.log` and `build/rlink/declaration-counts.json`.

| Existing decorated spelling | Declaring game files |
|---|---:|
| `?TheBfmeObject_00C709B0@@3VGen_00C709B0Target@@A` | 1 |
| `?g_w3dMouseThreadRunLock@@3EA` | 1 |

Raw evidence is in `build/rlink/retail-probe.log`, `build/rlink/references.json`, the `body-<RVA>.txt` files, `build/rlink/extra-retail.log`, `build/rlink/supplement.log`, `build/rlink/setup-disassembly.log`, `build/rlink/reference-shader.txt` and `build/rlink/reference-network-mouse.txt`. Supplement.log records each five-byte thunk and final target for the queue factories and list cleanup, plus the imported CreateMutexA and CloseHandle addresses used by the mutex bodies. Data registration and final gate paths are listed in `build/worker-final.md`.

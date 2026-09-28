# 0x00882BA0 MemoryPool::_Free: tracker callee is 0x008839B0, not isValidBlock

name_regression paired `memory_pool.cpp` with the new `MemoryPoolFree.cpp`
and read `Rva008838F0Owner::isValidBlock -> rva008839B0` as a rename. It is
not one: the two TUs call two different methods of the same owner object.

- `isValidBlock` is `?isValidBlock@Rva008838F0Owner@@QAE_NHPAX@Z` at
  0x00883AD0 (153 B, matched in `memorypool_tracker.cpp`). Its callers are
  `MemoryPool::_IsValidBlock` and `_VerifyIntegrity`, both still in
  `memory_pool.cpp` and unchanged by this seat.
- `tools/callees.py 0x00882BA0 358` resolves both tracker calls in the
  `_Free` body to 0x008839B0, the matched
  `?rva008839B0@Rva008838F0Owner@@QAEXHPAX@Z` (284 B,
  `memorypool_tracker_free.cpp`). That method returns `void`, where
  `isValidBlock` returns `bool`, so the two declarations mangle differently.

No name was dropped. `isValidBlock` keeps its spelling everywhere it
occurs, and the `_Free` body uses the ledger's existing address-derived
name for a different address.

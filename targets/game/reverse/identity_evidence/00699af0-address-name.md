# RVA 0x00699AF0 keeps its address-derived name

The deleted attempt named the loop `sweep_Rva00699AF0`. That name described the loop behavior, but it did not identify a game method.

The file `Rva00699B40RefreshChannel.cpp` already contained `rva00699B40RefreshChannel`, whose ledger row owns RVA 0x00699B40. The new `rva00699AF0` body owns RVA 0x00699AF0 in the same file. The name checker paired the deleted attempt with the existing sibling because both bodies use that file.

Five callers in `AudioManagerInit` reach RVA 0x00699AF0 through ILT 0x00047F3C. The symbol pin proves a `void(int)` ABI, but it does not prove a method name. The ledger therefore keeps `?rva00699AF0@@YAXH@Z`, which identifies the body by its address.

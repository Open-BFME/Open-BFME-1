# RVA 0x006FCC10 member ABI correction

The prior `?Rva006FCC10@@YGHMMMPAM@Z` declaration treated this address-derived normalized-range helper as a standalone stdcall function because its body ignores ECX. The retail caller at RVA 0x006FCCC0 independently proves the member-call context: instructions +0x006B and +0x009C load ECX from ESI (the caller's owner) immediately before calling ILT RVA 0x00031D0E, whose destination is 0x006FCC10. Both calls push four arguments: value, lower, upper, and fractional-result pointer.

An unused-this thiscall member has the same stack ABI and emitted body as stdcall here. The single canonical definition is corrected to `Rva006FCCC0Owner::rva006FCC10(float, float, float, float *)`; no second alias, alternate ABI declaration, or new symbol pin is introduced. The owner remains address-derived because no semantic class identity is proven.

Scoped probe observations: the corrected helper is EXACT at 131 bytes; the caller using normal member calls is EXACT at 240 bytes. Searching game source and banked attempts for Rva006FCC10, rva006FCC10, and j_00031d0e finds no other typed C++ caller. The generated ILT wrapper remains unchanged.

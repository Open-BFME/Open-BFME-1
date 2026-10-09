# Slot arrays at VA 01346C50 and 01346CF0

The two complete matched 109-byte selectors at RVA 00920AE0 and
00920B50 independently emit eight DWORD loads and stores on these
two arrays. Load bases advance by 20 bytes per slot; the argument
selects an option at scale four, and each store is to slot+16.
The first selector's last store is VA 01346CEC; the second selector's
last store is VA 01346D8C. Their final RET instructions occur at
00920B4C and 00920BBC, followed by INT3 padding.

Both complete arrays therefore span eight 20-byte entries (160 bytes).
Array B begins exactly 160 bytes after array A. The separately recorded
VertexMaterialClass::Presets pointer array begins at VA 01346D90,
exactly after array B, and has its own definition and accesses in
vertmaterial.cpp and VertexMaterialClass_Init_Thunk.cpp.

Retail loader-mapped .data holds 160 zero bytes at each array base.
The existing Rva00920AE0Slot view and all field names stay unchanged;
its sizeof is 20, with four option DWORDs followed by one selected
DWORD. Compiler array sizeof probes must report 160. Define only the
two existing symbols; no pin, alias, address global, or DIR32 record
change is required.

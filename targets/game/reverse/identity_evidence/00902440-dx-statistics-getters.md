# Eleven native DX8Wrapper statistics getters

The existing native `dxwrapper.cpp` already contains these complete clean
C++ definitions. The Zero Hour twin `WW3D2/dx8wrapper.h` lines435..446
declares ten static no-argument unsigned getters and one static no-argument
unsigned-long Get_FrameCount. Its cpp defines the same getters beside
End_Statistics. No incoming ECX or hidden stack arguments are inferred from
the short machine bodies: the native declaration supplies the contract.

Retail RVAs00902440 through009024E0, step16, each contain exactly
`mov eax,[absolute]; ret` followed by ten INT3 bytes. Ghidra read_memory
at VA00D02440 independently agrees with all176 baseline bytes. The ten
named last-frame fields follow the independently matched113B
End_Statistics at009023C0, whose final RET is00902430. These are complete
native getter bodies separated by actual padding, not interior suffixes.
No raw direct E8/E9 entry references were found; the source twin,
independently bound producer and separate RET/INT3 extents are the evidence.

Before changing the ledger, the existing TU passed109/109 strict checks,
including230 literals,24 float constants,443 DIR32 references and its data
row. The compiled End_Statistics relocations independently bind every
getter's private static to the same retail destination:

| Getter RVA | Native suffix after Get_Last_Frame_ | Global VA | Producer DIR32 offset |
| --- | --- | --- | --- |
| 00902440 | Matrix_Changes | 01340598 | 12 |
| 00902450 | Material_Changes | 0134059C | 1D |
| 00902460 | Vertex_Buffer_Changes | 013405A0 | 29 |
| 00902470 | Index_Buffer_Changes | 013405A4 | 34 |
| 00902480 | Light_Changes | 013405A8 | 3F |
| 00902490 | Texture_Changes | 013405AC | 4B |
| 009024A0 | Render_State_Changes | 013405B0 | 56 |
| 009024B0 | Texture_Stage_State_Changes | 013405B4 | 61 |
| 009024C0 | DX8_Calls | 013405B8 | 67 |
| 009024D0 | Draw_Calls | 013405BC | 6C |

009024E0 is Get_FrameCount, returning the native private static
DX8Wrapper::FrameCount at VA01340580. Its unsigned-long declaration and
existing DIR32 binding independently agree. The private last-frame
variables remain in the producer's TU; no duplicate externs or pins are
introduced. Only stale present-unmatched comments are removed from source.
The transactional add_match_batch gate verifies every new six-byte getter
and all existing TU rows together; each manifest row records
model=gpt-6-astra. This is one same-pattern native getter batch.

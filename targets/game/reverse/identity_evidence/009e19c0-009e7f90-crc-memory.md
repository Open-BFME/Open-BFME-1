# CRC_Memory at 0x009E19C0 and CRC::Memory at 0x009E7F90

| body | old row | identity |
|---|---|---|
| `0x009E19C0` (53 B) | `?Memory@CRC@@SAKPAEKK@Z` (crc.cpp) | `?CRC_Memory@@YAKPBEKK@Z` (realcrc.cpp) |
| `0x009E7F90` (53 B) | `?CRC_Memory@@YAKPBEKK@Z` (realcrc.cpp) | `?Memory@CRC@@SAKPAEKK@Z` (crc.cpp) |

The two rows were swapped. Both bodies are the same CRC32 memory loop
(`not eax; ... mov edi,[edx*4+TABLE]; shr eax,8; xor eax,edi; inc ecx;
dec esi; jne; not eax; ret`) and the byte check masks the table address, so
either name byte-matches either body. Only the table, the neighbours and the
callers separate them.

## Tables and neighbours

Zero Hour has two CRC32 translation units with different tables:

- `WWLib/realcrc.cpp`: `CRC32_Table` and, in this order, `CRC_Memory`,
  `CRC_String`, `CRC_Stringi`.
- `WWLib/crc.cpp`: `CRC::_Table` and, in this order, `CRC::Memory`,
  `CRC::String`.

Every code reference to either table in retail `.text`:

| table | referencing bodies |
|---|---|
| `0x012D9930` | `0x009E19C0` (+0x23), `0x009E1A00` (+0x2B), `0x009E1A40` (+0x30) |
| `0x012D9DF0` | `0x009E7F90` (+0x23), `0x009E7FD0` (+0x2B) |

`0x009E19C0`, `0x009E1A00` and `0x009E1A40` are contiguous, share table
`0x012D9930`, and the third is the case-insensitive `CRC_Stringi`
(`call ebx` through the `toupper` import slot at 0x01359500), which exists only in realcrc.cpp. That is
realcrc.cpp's three functions in source order. `0x009E7F90` and
`0x009E7FD0` are contiguous, share `0x012D9DF0`, and `0x009E7FD0` is
`CRC::String` (fedaea8fd1; called by `INIClass::CRC`, `INIEntry::Index_ID`,
`INISection::Index_ID` and `INIClass::Find_Section`, all of which call
`CRC::String` in Zero Hour's ini.cpp/inisup.h). That is crc.cpp's pair in
source order. The old ledger mixed the two units: `CRC::Memory` sat with
realcrc's table and neighbours, the free `CRC_Memory` with crc.cpp's.

## Callers

The only direct retail callers of either body (E8 scan, no ILT thunks exist
for either):

- `0x009E19C0`: nine sites in `VertexMaterialClass::Compute_CRC`
  (0x00920EFC..0x00920F6C), one in `UVBufferClass::Update_CRC` (0x009292D0)
  and two in `MeshMatDescClass::Install_UV_Array` (0x0092A591, 0x0092A694).
  Zero Hour's vertmaterial.cpp and meshmatdesc.cpp make every one of these
  calls as `CRC_Memory(...)` and include realcrc.h.
- `0x009E7F90`: none.

The game sources had been changed to call `CRC::Memory` through a TU-local
class declaration so they would resolve to the old row; they now call
`CRC_Memory` as Zero Hour does.

The DIR32 whitelist entries `?CRC32_Table@@3PAKA` and `?_Table@CRC@@0PAKA`
existed only because of the swap ("realcrc.cpp is linked twice"): after it
each table has one address.

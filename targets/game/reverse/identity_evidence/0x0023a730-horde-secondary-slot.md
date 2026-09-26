# 0x0023A730 secondary-interface slot

The retail body is 191 bytes, ends in a plain `ret`, and receives its object in
ECX. ILT `0x00043A7C` jumps to this body. Three independently installed
secondary vtables place that ILT in slot 3 (`+0x0C`):

| Vtable | Constructor and store | Physical family |
| --- | --- | --- |
| `0x010AE230` | `0x00230580+0x79`, `[esi+0xE4]` | AODHordeContain |
| `0x010AED58` | `0x0023EAF0+0x81`, `[esi+0xE4]` | HordeContain |
| `0x010B07E0` | `0x0024D220+0x5C`, `[esi+0xE4]` | HorseHordeContain |

The receiver is therefore the `+0xE4` subobject. Its load at
`0x0023A730+0x19`, `[esi-0xDC]`, reads the enclosing object's `+8` pointer.
The body calls ILT `0x0000325B` twice with that pointer and later with a list
element pointer in ECX. That ILT jumps to the existing matched 22-byte
`Rva001BF100::run` body at `0x001BF100`, which has no stack arguments and
returns with a plain `ret`. The other direct calls are the matched STLport
allocator at `0x0082E540` and node deallocator at `0x0082E5F0`. A virtual
call at receiver slot 60 (`+0xF0`) receives the local list pointer.

`Rva0023A730Receiver::slot03` preserves the address and structural slot
without claiming an unproved semantic method or pointee type. The clean
STLport source probes at 191/191 bytes with nine aligned relocations, and
the strict scoped `add_match`/`build.sh` gate accepts it without a new pin.

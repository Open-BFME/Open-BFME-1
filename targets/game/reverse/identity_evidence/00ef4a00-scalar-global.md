# Scalar identity at VA 0x012F4A00

The chosen reconstruction spelling is `?g_rva005380a0_id@@3IA`. It represents `unsigned int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The four-byte narrow num_get facet identifier. RVA 0x00831F90 writes 12; RVA 0x0053CA40 passes its address to locale::_M_use_facet and invokes num_get do_get slot 0x28 for long extraction. RVA 0x005380A0 also passes its address to _M_use_facet. The latter reads a dword from its id argument at RVA 0x008321D6.

inputs/vendor/stlport/stl/_locale.h declares locale::id::_M_index as size_t; _num_get.h initializes num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index to 12. The existing address-qualified role name is retained with a four-byte unsigned storage view; it is not an assertion of the original template COFF spelling.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_bfmeSlot04VA@@3HA` occurs in 1 game file(s).
- `?g_rva005380a0_id@@3DA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x005380A0`, instruction VA `0x009380A4`: `push 0x12f4a00`; width 0, access 0.
- RVA `0x0053CA40`, instruction VA `0x0093CAAE`: `push 0x12f4a00`; width 0, access 0.
- RVA `0x00831F90`, instruction VA `0x00C31FB8`: `mov dword ptr [0x12f4a00], 0xc`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/Common/BfmeOneHundredTwentyTwo.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F4A00-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

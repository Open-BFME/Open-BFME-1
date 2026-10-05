# Scalar identity at VA 0x01346E50

The chosen reconstruction spelling is `?last_frame_sorting_vertices@Debug_Statistics@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

Snapshot of sorting vertex count at VA 0x01346E6C, which RVA 0x00937280 increases by argument 2. Its verified SortingRendererClass callers and the Zero Hour Record_Sorting_Polys_And_Vertices contract establish the role.

Zero Hour Libraries/Source/WWVegas/WW3D2/statistics.cpp declares the named last-frame counters as static int and copies accumulator values in End_Statistics. The reconstructed namespace provides external linkage; it does not claim that upstream file-static variables had exported COFF names.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_Va01346E50@@3HA` occurs in 1 game file(s).
- `?last_frame_draw_calls@Debug_Statistics@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x009372C0`, instruction VA `0x00D372C0`: `mov eax, dword ptr [0x1346e50]`; width 4, access 1.
- RVA `0x00937EF0`, instruction VA `0x00D37F4F`: `mov dword ptr [0x1346e50], ecx`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/Libraries/Source/WWVegas/WW3D2/statistics.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/01346E50-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

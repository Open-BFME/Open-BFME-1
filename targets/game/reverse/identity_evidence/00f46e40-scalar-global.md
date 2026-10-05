# Scalar identity at VA 0x01346E40

The chosen reconstruction spelling is `?last_frame_dx8_renders@Debug_Statistics@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

Snapshot of DX8 render count at VA 0x01346E68. The shader-aware DX8 recorder RVA 0x009373A0 and the sorting insertion recorder RVA 0x00937280 increment that source once per record. This is a BFME extension absent from the Zero Hour counter declarations.

Zero Hour Libraries/Source/WWVegas/WW3D2/statistics.cpp declares the named last-frame counters as static int and copies accumulator values in End_Statistics. The reconstructed namespace provides external linkage; it does not claim that upstream file-static variables had exported COFF names.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_Va01346E40@@3HA` occurs in 1 game file(s).
- `?last_frame_dx8_renders@Debug_Statistics@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x009372D0`, instruction VA `0x00D372D0`: `mov eax, dword ptr [0x1346e40]`; width 4, access 1.
- RVA `0x00937EF0`, instruction VA `0x00D37F55`: `mov dword ptr [0x1346e40], edx`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/Libraries/Source/WWVegas/WW3D2/statistics.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/01346E40-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

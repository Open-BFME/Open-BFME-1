# Scalar identity at VA 0x01346E48

The chosen reconstruction spelling is `?g_Va01346E48@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

Snapshot of the standalone counter at VA 0x01346E18, whose only direct writer increments it in RVA 0x009371E0. End_Statistics copies that source here and RVA 0x00937220 returns it. The competing last_frame_dx8_polygons spelling is disproven by the shader-aware polygon accumulator and snapshot at VA 0x01346E04. The original semantic name of this standalone counter remains unresolved; the existing address spelling makes no claim about it.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_Va01346E48@@3HA` occurs in 1 game file(s).
- `?last_frame_dx8_polygons@Debug_Statistics@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x00937220`, instruction VA `0x00D37220`: `mov eax, dword ptr [0x1346e48]`; width 4, access 1.
- RVA `0x00937EF0`, instruction VA `0x00D37F28`: `mov dword ptr [0x1346e48], eax`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The semantic identity of the standalone accumulator at VA 0x01346E18 is unresolved. Its pre-change last_frame_dx8_polygons label is wrong because the proven polygon snapshot is at VA 0x01346E04. The address-qualified spelling is retained here. This is one descriptive-to-address name regression for the coordinator to document. A retail caller or EA string identifying the standalone increment routine would settle its original semantic name.

The definition owner is `game/Libraries/Source/WWVegas/WW3D2/statistics.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/01346E48-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

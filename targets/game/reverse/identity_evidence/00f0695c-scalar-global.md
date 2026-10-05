# Scalar identity at VA 0x0130695C

The chosen reconstruction spelling is `?g_open2SyncB@@3IA`. It represents `unsigned int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

A saved synchronization value copied from VA 0x0133F420 by RVA 0x00782ED0 and supplied to WW3D::Sync by RVA 0x00783010.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_open2SyncB@@3IA` occurs in 1 game file(s).
- `?rva0130695C@@3IA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x00782ED0`, instruction VA `0x00B82F56`: `mov dword ptr [0x130695c], eax`; width 4, access 2.
- RVA `0x00783010`, instruction VA `0x00B83043`: `mov ecx, dword ptr [0x130695c]`; width 4, access 1.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/Libraries/Source/WWVegas/WW3D2/RendererInitialize00782ED0.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/0130695C-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

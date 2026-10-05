# Scalar identity at VA 0x01352810

The chosen reconstruction spelling is `?AllocateCount@@3IA`. It represents `unsigned int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

Allocation-operation counter: WWMemoryLogClass::Allocate_Memory at RVA 0x00AFF2D0 increments it before allocating; RVA 0x00AFE940 resets it and RVA 0x00AFE950 returns it.

Zero Hour Libraries/Source/WWVegas/WWDebug/wwmemlog.cpp defines static unsigned AllocateCount and FreeCount and has the same allocate, release, reset and getter operations. Their game definitions are changed to external linkage only.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_Glo00F52810@@3HA` occurs in 1 game file(s).
- `?g_Va01352810@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x00AFE940`, instruction VA `0x00EFE942`: `mov dword ptr [0x1352810], eax`; width 4, access 2.
- RVA `0x00AFE950`, instruction VA `0x00EFE950`: `mov eax, dword ptr [0x1352810]`; width 4, access 1.
- RVA `0x00AFF2D0`, instruction VA `0x00EFF2D0`: `mov edx, dword ptr [0x1352810]`; width 4, access 1.
- RVA `0x00AFF2D0`, instruction VA `0x00EFF2DC`: `mov dword ptr [0x1352810], edx`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/Libraries/Source/WWVegas/WWDebug/wwmemlog.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/01352810-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

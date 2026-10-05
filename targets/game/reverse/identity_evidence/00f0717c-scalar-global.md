# Scalar identity at VA 0x0130717C

The chosen reconstruction spelling is `?g_bfme5MatPassCount@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The live material-pass count: constructor RVA 0x007CBB30 increments it and installs vtable VA 0x01128880; destructor RVA 0x007CBCE0 installs the same vtable, decrements it and releases two resources when it reaches zero. This confirms the existing material-pass role name over the opaque EAX label.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_bfme5MatPassCount@@3HA` occurs in 1 game file(s).
- `?g_bfmeCountEAX@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x007CBB30`, instruction VA `0x00BCBB54`: `inc dword ptr [0x130717c]`; width 4, access 3.
- RVA `0x007CBCE0`, instruction VA `0x00BCBD03`: `mov eax, dword ptr [0x130717c]`; width 4, access 1.
- RVA `0x007CBCE0`, instruction VA `0x00BCBD11`: `mov dword ptr [0x130717c], eax`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/Common/Bfme5MatPassCtors.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/0130717C-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

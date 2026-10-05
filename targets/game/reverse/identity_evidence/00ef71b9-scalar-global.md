# Scalar identity at VA 0x012F71B9

The chosen reconstruction spelling is `?g_bfmeFlagBGA@@3EA`. It represents `unsigned char`, 1 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The callback error byte: callback RVA 0x0063B090 sets it for error -204; the thread at RVA 0x0063EB00 tests and clears it.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_Rva012F71B9@@3EA` occurs in 1 game file(s).
- `?g_bfmeFlagBGA@@3EA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x0063B090`, instruction VA `0x00A3B0D7`: `mov byte ptr [0x12f71b9], cl`; width 1, access 2.
- RVA `0x0063EB00`, instruction VA `0x00A3ED1D`: `mov byte ptr [0x12f71b9], 0`; width 1, access 2.
- RVA `0x0063EB00`, instruction VA `0x00A3ED1D`: `mov byte ptr [0x12f71b9], 0`; width 1, access 2.
- RVA `0x0063EB00`, instruction VA `0x00A3EEB7`: `mov al, byte ptr [0x12f71b9]`; width 1, access 1.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0063B090GameSpyBuddyCallback.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F71B9-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

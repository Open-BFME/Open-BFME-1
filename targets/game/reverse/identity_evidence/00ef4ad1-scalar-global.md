# Scalar identity at VA 0x012F4AD1

The chosen reconstruction spelling is `?g_optByte12F4AD1@@3EA`. It represents `unsigned char`, 1 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The options byte written from the ShowOptions argument at RVA 0x0055E290 and tested for zero by RVAs 0x0055DC00, 0x0055DCB0 and 0x0055E120. All accesses are one byte; no signed numeric operation exists.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_bfmeD1072@@3DA` occurs in 4 game file(s).
- `?g_optByte12F4AD1@@3EA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x0055DC00`, instruction VA `0x0095DC0C`: `mov al, byte ptr [0x12f4ad1]`; width 1, access 1.
- RVA `0x0055DCB0`, instruction VA `0x0095DD01`: `mov al, byte ptr [0x12f4ad1]`; width 1, access 1.
- RVA `0x0055E120`, instruction VA `0x0095E150`: `mov al, byte ptr [0x12f4ad1]`; width 1, access 1.
- RVA `0x0055E290`, instruction VA `0x0095E2D8`: `mov byte ptr [0x12f4ad1], cl`; width 1, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/GameClient/GUI/ShowOptions.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F4AD1-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

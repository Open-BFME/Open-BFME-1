# Scalar identity at VA 0x012F4980

The chosen reconstruction spelling is `?Rva00510DC0DisplayHeight@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The display-string height out-parameter supplied to vtable slot 0x3C by RVA 0x00510DC0; RVA 0x00510D10 loads it with signed fild for vertical tooltip placement.

GameEngine/Include/GameClient/DisplayString.h declares getSize(Int *width, Int *height); the display-string allocation, font, text and size calls in the raw body establish this receiver.

The competing pre-change spellings and the numbers of game files containing each are:

- `?Rva00510DC0DisplayHeight@@3HA` occurs in 1 game file(s).
- `?g_bfmeCy1264@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x00510D10`, instruction VA `0x00910D43`: `fild dword ptr [0x12f4980]`; width 4, access 1.
- RVA `0x00510DC0`, instruction VA `0x00910E8A`: `push 0x12f4980`; width 0, access 0.
- RVA `0x00510DC0`, instruction VA `0x00910EE5`: `mov edx, dword ptr [0x12f4980]`; width 4, access 1.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptGuiFX.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F4980-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

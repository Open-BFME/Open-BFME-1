# Scalar identity at VA 0x012F4B9C

The chosen reconstruction spelling is `?g_rva0058BED0NextId@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The next wrapping identifier, read into receiver+0x0C, incremented, compared with signed jl against 0xFFFF, reset to zero on overflow, and passed as the first argument to the registration body at RVA 0x00565C90. All accesses are in constructor RVA 0x0058BED0.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_rva0058BED0NextId@@3HA` occurs in 1 game file(s).
- `?g_rva0058BED0ReadId@@3HA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x0058BED0`, instruction VA `0x0098BEFB`: `mov ecx, dword ptr [0x12f4b9c]`; width 4, access 1.
- RVA `0x0058BED0`, instruction VA `0x0098BF04`: `inc dword ptr [0x12f4b9c]`; width 4, access 3.
- RVA `0x0058BED0`, instruction VA `0x0098BF10`: `cmp dword ptr [0x12f4b9c], 0xffff`; width 4, access 1.
- RVA `0x0058BED0`, instruction VA `0x0098BF20`: `mov dword ptr [0x12f4b9c], eax`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngine/Source/Common/Rva0058BF70Destructor.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F4B9C-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

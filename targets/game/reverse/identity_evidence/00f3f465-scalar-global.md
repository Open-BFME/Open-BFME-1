# Scalar identity at VA 0x0133F465

The chosen reconstruction spelling is `?Lite@WW3D@@0_NA`. It represents `bool`, 1 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

WW3D::Lite. WW3D::Init at RVA 0x008FD640 copies its lite argument into this byte, and WW3D::Shutdown at RVA 0x008FD6E0 tests it before DX8Wrapper::Shutdown.

Zero Hour Libraries/Source/WWVegas/WW3D2/ww3d.cpp defines bool WW3D::Lite = false and uses the same Init store and Shutdown test; ww3d.h declares the private static bool. The corresponding game source already owns this definition.

The competing pre-change spellings and the numbers of game files containing each are:

- `?g_WW3D_Lite@@3EA` occurs in 1 game file(s).
- `?g_WW3D_SkipDeviceShutdown@@3EA` occurs in 1 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x008FD640`, instruction VA `0x00CFD665`: `mov byte ptr [0x133f465], bl`; width 1, access 2.
- RVA `0x008FD6E0`, instruction VA `0x00CFD726`: `cmp byte ptr [0x133f465], bl`; width 1, access 1.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

This private static bool is already defined in the reference-owning game source. The data tool refuses private static members because its sizeof probe cannot name them. Per the private-static exception in the worker brief, its one zero byte is verified directly and its DIR32 spelling is added without a data row. The redundant free-byte definition is removed; both callers use the existing private static member.

The definition owner is `game/Libraries/Source/WWVegas/WW3D2/ww3d.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/0133F465-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

The owner COFF object independently defines exactly one `?Lite@WW3D@@0_NA` at offset 100 of its 101-byte `.bss` section. Its final byte is zero, matching retail VA 0x0133F465. The raw symbol, section, and initial byte proof is in `build/rlink/private-scalar.log`; the expected private-access sizing refusal is in `build/rlink/0133F465-add-data.log`.

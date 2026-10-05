# Scalar identity at VA 0x012F9D20

The chosen reconstruction spelling is `?ShaderQuadIndex@@3HA`. It represents `int`, 4 byte(s), in retail `.data`, with initial value zero. The extent contains no other datum or interior DIR32 name. These are mutable storage cells, not compiler constants.

The quad-ring cursor. Shader viewport bodies RVAs 0x00716AD0 and 0x00716F50 multiply it by four for vertex offsets, increment it, and use a signed threshold of 50 to reset it. Resource bodies RVAs 0x007165C0, 0x00716770 and 0x00717C90 reset it to zero.

The competing pre-change spellings and the numbers of game files containing each are:

- `?ShaderQuadIndex@@3HA` occurs in 1 game file(s).
- `?rva012F9D20@@3IA` occurs in 3 game file(s).

Retail reads and writes, with instruction-level widths and access flags, are recorded below. Access 1 is read, 2 is write, and 3 is read and write; an address immediate passes storage to another body.

- RVA `0x007165C0`, instruction VA `0x00B166C2`: `mov dword ptr [0x12f9d20], edx`; width 4, access 2.
- RVA `0x00716770`, instruction VA `0x00B167EE`: `mov dword ptr [0x12f9d20], esi`; width 4, access 2.
- RVA `0x00716AD0`, instruction VA `0x00B16B86`: `mov eax, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716AD0`, instruction VA `0x00B16E01`: `mov edx, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716AD0`, instruction VA `0x00B16E46`: `mov eax, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716AD0`, instruction VA `0x00B16E4F`: `mov dword ptr [0x12f9d20], eax`; width 4, access 2.
- RVA `0x00716AD0`, instruction VA `0x00B16E56`: `mov dword ptr [0x12f9d20], ebx`; width 4, access 2.
- RVA `0x00716F50`, instruction VA `0x00B16F64`: `mov eax, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716F50`, instruction VA `0x00B17106`: `mov edx, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716F50`, instruction VA `0x00B17149`: `mov eax, dword ptr [0x12f9d20]`; width 4, access 1.
- RVA `0x00716F50`, instruction VA `0x00B17152`: `mov dword ptr [0x12f9d20], eax`; width 4, access 2.
- RVA `0x00716F50`, instruction VA `0x00B17159`: `mov dword ptr [0x12f9d20], edi`; width 4, access 2.
- RVA `0x00717C90`, instruction VA `0x00B17CD5`: `mov dword ptr [0x12f9d20], edi`; width 4, access 2.

The receiver and argument contracts are the raw instruction contracts described above. No inheritance, wrapper, forwarder, or additional function identity is introduced. Existing function bytes and extents must remain unchanged.

The definition owner is `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderViewport.cpp`. A different retail access width, an interior datum or DIR32 name, a reader or writer inconsistent with the stated role, or any changed instruction under the chosen spelling would refute the correction. For the statistics snapshots, a counter writer or verified caller showing a different polygon/vertex argument order would also refute it.

Raw evidence: `build/rlink/012F9D20-retail.log`, `build/rlink/spelling-counts.log`, `build/rlink/retail-callers.log`, and `build/rlink/reference-excerpts.log`. Additional counter probes are in `build/rlink/counter-probe.log` and their address-specific retail logs. Gate receipts and LINKED measurements are listed in `build/worker-final.md`.

# Disabled-name address cells at VA 0x012A9200

Retail `retail-1.03-unpacked/files/lotrbfme.exe`, SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`,
contains eleven string pointers followed by a null DWORD at VA
0x012A9200..0x012A922F. This is 48 bytes of initialized writable `.data`.
The eleven pointed-to strings occupy 208 bytes including their NULs;
their individual definitions and data rows exclude alignment padding.

The masked lookup at RVA 0x001C3F80 (39 bytes) returns a DWORD from this
table. The xfer body at RVA 0x001C4CC0 (460 bytes) reads its first eleven
cells and passes their values as string pointers. The parser at RVA
0x0029C7B0 passes the same table to `INI::scanIndexList` at RVA 0x008509E0.
That scanner advances four bytes per cell and stops at the first null,
independently establishing the consumed twelve-cell interval. Bytes at
0x012A9230..0x012A923F are excluded; original allocation padding is unknown.

Both existing source consumers declare `extern int g_bfmeTableDJa[]`.
The physical definition preserves this PE32/MSVC 7.1 address-storage
interface. Its eleven pointer-to-int casts must emit genuine static DIR32
relocations to the named string providers, followed by one zero cell.
This is a target-specific storage view, not a recovery of the original
C++ element type. The original table is semantically a string-pointer list.
All caller bodies, signatures, and relocation names remain unchanged.
No dynamic initializer, helper, alias, or shared-header change is added.

The strings begin with `DEFAULT`, followed by ten `DISABLED_` names through
`DISABLED_SCRIPT_UNDERPOWERED`. Exactly these eleven entries are witnessed;
their count does not establish a BitFlags template width or class identity.
In particular, this change does not claim `BitFlags<11>` or `BitFlags<67>`
as the original owner and does not infer ArmorSet from an existing filename.

The separate historical `BitFlags<67>::s_bitNameList` spelling remains
actively referenced by `Object.cpp`, including the matched getter at RVA
0x001C0870. The address-derived parser also retains its existing static
table spelling. Their records and source remain untouched; their unresolved
bindings are separate work. This definition serves the two existing
`g_bfmeTableDJa` consumers and does not claim whole-program table selection.

The data gate must prove all twelve data extents and all eleven pointer
relocations. Independent COFF review must preserve every existing code,
COMDAT and EH section, with current dependency receipts and no initializer
code. This is 256 bytes of physical data ownership, not new function
conversion or measured whole-program LINKED progress.

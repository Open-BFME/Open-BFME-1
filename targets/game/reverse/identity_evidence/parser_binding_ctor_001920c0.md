# Parser binding constructor at 0x001920C0: parameter types

The 73-byte body at `0x001920C0` was claimed as
`??0BfmeParserBindingVE@@QAE@HHHPAVBfmeParserRegistryVE@@PAX1@Z`, a
placeholder signature of three ints, a registry pointer and two `void *`. The
class name `BfmeParserBindingVE` is kept. The parameter types are corrected to
`(SidesList *owner, bool (SidesList::*)(DataChunkInput &, DataChunkInfo *),
DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel)`.
The new decorated name is
`??0BfmeParserBindingVE@@QAE@PAVSidesList@@P81@AE_NAAVDataChunkInput@@PAUDataChunkInfo@@@ZPAV2@ABVAsciiString@@5@Z`.

## Evidence

1. **The only retail out-of-line caller passes an 8-byte member pointer by
   value.** At `0x0019B030+0x1CD` retail builds the second and third arguments
   in registers: `xor ecx,ecx; push ecx; mov eax,0x413C6E; push eax`. It then
   pushes `esi` (`this`) and calls ILT `0x0002B09E`, which jumps to
   `0x001920C0`. That register sequence is how MSVC 7.1 copies an 8-byte
   aggregate argument. Three separate `int` arguments compile to
   `push 0; push 0x413C6E` instead, which measured 139 differing bytes in that
   caller.
2. **The owner type is SidesList.** The body installs binding vtable
   `0x0109BFD4` (base `0x0107C7D0`). The same vtable is installed inline by the
   landed `CachedSidesLoader0019EC80::load` (0x0019EC80), where the owner is a
   `new SidesList` and the callbacks are SidesList member callbacks, and by
   `WorldHeightMap::Rva0074ACB0Load` (0x0074ACB0), which binds `TheSidesList`.
   The out-of-line caller 0x0019B030 binds `g_bfmeTableERJ`. That global is
   pinned at VA `0x012EF428`, which is `TheSidesList` in
   `dir32_addresses.csv`. One vtable means one binding class, so its owner is
   SidesList.
3. **The layout is unchanged.** The body stores the owner, the member-pointer
   entry and the zero this-adjustment into the three derived fields after the
   base constructor. It cleans six stack dwords (`ret 0x18`), which fits one
   pointer, one 8-byte member pointer and three pointer/reference arguments.
   The corrected source byte-matches retail 0x001920C0 (73 B, exact modulo
   relocations).

No other matched C++ caller names the old decorated symbol. The two other
users of this binding (0x0019EC80 and 0x0074ACB0) inline their own copies.

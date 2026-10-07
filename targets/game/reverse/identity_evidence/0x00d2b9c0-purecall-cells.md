# Readonly purecall cells at VA 0x0112B9C0

Retail `retail-1.03-unpacked/files/lotrbfme.exe`, SHA256
`1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`,
contains four consecutive pointer cells at VA 0x0112B9C0..0x0112B9CC in
`.rdata`. Each contains VA 0x00C8C500, directly naming the already matched
60-byte CRT `_purecall` override at RVA 0x0088C500. Its existing provider is
`game/Libraries/Source/debug/debug_purecall.cpp`, with the contract
`extern "C" int __cdecl _purecall(void)`. There is no intervening ILT or IAT.

The matched constructors at RVA 0x007F9B80 (208 bytes) and 0x00803820
(104 bytes) independently install exactly VA 0x0112B9C0 into receiver+4
before replacing that base table with their final tables. Both previously
referenced the undefined array `g_0112B9C0`. The physical provider now owns
these four cells, and both declarations use an externally linked array of
const pointers to const void, preserving the readonly storage contract.

The independently referenced string `conn made\n` begins at VA 0x0112B9D0,
immediately after the four cells. The preceding word at VA 0x0112B9BC is
also `_purecall`, not an RTTI locator. This claim is limited to the sixteen
physical bytes beginning at the constructor-proven address: it does not
recover the original base-class identity or exclude possible sharing with
neighboring table storage. No neighboring bytes are claimed.

There is no overlapping current data-ledger owner. The two constructor
extents, their other relocation targets, and EH/COMDAT material must remain
unchanged apart from the table's const-correct symbol binding. Dependency
receipts must be current. The data gate verifies all sixteen bytes and all
four `_purecall` relocations. No helper body, alias, pin, shared header, or
link order changes.

Both source users now emit `?g_0112B9C0@@3QBQBXB`. The sole old DIR32 record,
`?g_0112B9C0@@3PAPBXA,0x0112B9C0`, described the obsolete mutable spelling
and is retired without rewriting its address or adding a replacement record.
This is the deletion route supported by `tools/dir32_record_guard.py`.
The verified data row backs the new readonly spelling at the same VA, and
the normal DIR32 identity and cross-reference checks remain active. No source
still declares the old spelling, and it has no pin or physical data owner.

`UnclaimedVfptrCtors.cpp` also contains the existing 9-byte constructor at
RVA 0x007F9130. Its fabricated one-slot compiler vftable is already recorded
as DIR32 debt in `body_guard_baseline.csv`; it is not a verified sixteen-byte
data owner. That source and baseline remain untouched, and the normal check
continues rejecting that vftable identity. This contribution does not claim
unique whole-program vtable selection or repair that preexisting debt.

This is a data/provider contribution, not new C++ function conversion or
measured whole-program LINKED progress.

# 0x0074C350: four-argument alpha-byte body

The generated dump `Code/gen_asm/d_00745b10.asm` fixes this body at
0x0074C350 for 327 bytes. It ends at +0x144 with `ret 0x10`, and the next
function starts at 0x0074C4F0. The only observed caller is the carved
0x0072D210 body: at +0x3CE through +0x3E1 it pushes a pointer to a local
byte, a pointer to a four-byte alpha buffer, y, and x, then calls ILT
0x0001D494. That ILT jumps to physical 0x0074C350. Retail passes four stack
words and the callee cleans all four. The fourth pointer is never read or
written in the callee, so the C++ declaration keeps it opaque.

The body indexes a height-map-sized array with origin X/Y (+0x120E0/+0x120E4),
width (+0x08), and data size (+0x20), checks the pointer at +0x8C, reads the
index table at +0x90, and fills four alpha bytes using the 16-byte blend records
reached through +0x80A4. It has no direct calls or relocation sites. These
fields and behavior support a height-map relationship, but the caller does not
name an owner or method. The existing seven-argument
`WorldHeightMap::getExtraAlphaUVData` body is a different physical function at
0x0074C140 and cannot name this four-argument body.

`Rva0074C350Owner::rva0074C350` compiled with the repository's MSVC 7.1
settings matches all 327 retail bytes after explicitly ordering the four-byte
initialization and diagonal writes. The first same-size probe differed only in
the order of those independent byte stores (25 bytes); the final probe has zero
non-relocation differences and zero relocation sites. The strict replacement
gate and affected source/thunk/dump checks validate the live ledger claim.

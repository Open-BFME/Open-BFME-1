# RVA 0x001CD160 exact set-mask propagation bank

This body is independently bounded by RET4 at RVA 0x001CD2A9 (+0x149)
and INT3 at 0x001CD2AC (+0x14C), hence 332 bytes. ILT0xBE6A reaches it.
Ghidra created and decompiled the same 332-byte function; native bytes were
independently decoded with pefile/capstone. No caller or name witness is
known, so the saved reconstruction uses an opaque address-qualified owner.

The receiver offsets, template/parent selection, interface slots, copied
12-byte-node list and cleanup contracts match the independently investigated
0x001CCFC0 sibling. See 001ccfc0-exact-mask-propagation-bank.md for the
list-copy 0x1CB160 conflicting generated identities and canonical-type work
still required before either bank can be integrated into production.

This body SETS the caller mask: in the item loop it pushes EDI (caller mask)
at +0xD5, then LEAs the local zero mask at ESP+0x14 and pushes it at +0xDE.
The final receiver call repeats this at +0x112/+0x11B. That is the opposite
of 0x001CCFC0, which pushes local zero mask first then EDI. Do not resurrect
the old shared clearModelConditionFlags semantic spelling.

Its separate handler is RVA 0x00C09258, FuncInfo 0x00DF7BD8: one state,
0 -> -1, cleanup 0x00C09250 LEA ECX,[EBP-0x38] then jump through0x418949
and0xD0020 to the native list base destructor0xCEBD0.

The source preloads each list item before scoped bitset-backed forty-byte
zero-mask construction, then passes (zero,caller). Probe independently
reports 332 bytes EXACT modulo10 relocation slots. Its zero-storage view
asserts no semantic model-condition count. All game views are opaque;
no new helper pin, canonical-class redeclaration, or production row is added.
This is a saved instruction match, not a strict linked conversion.

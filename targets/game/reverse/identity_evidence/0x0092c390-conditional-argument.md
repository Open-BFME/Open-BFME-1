The false arm is not an `if/else` with two statements. Retail pushes zero
with `xor eax,eax; push eax` and reuses the same register that carries the
`Get_HTree` result in the true arm, which is the register-allocated residue of
a value living in a register, not a literal `push 0` (6A 00). Writing the body
as one conditional argument,

    ((Rva00925860 *)m_model)->method(
        dst,
        m_field84 ? (void *)((RenderObjClass *)m_field84)->Get_HTree() : (void *)0);

keeps the value in a register, tail-duplicates the helper call, and emits
`xor eax,eax` in the false arm. probe: 67 bytes, EXACT modulo relocation slots.
Any `if (m_field84) {...} else { method(dst, 0); }` shape compiles to 66 bytes
with 14 non-relocation differences (0.870), because MSVC hoists the `push 0`
and the `m_model` load ahead of the argument setup.

`Get_Deformed_Vertices` is defined in the same translation unit as its matched
caller `BfmeShadowBufferEntry::update`, so the declaration carries
`__declspec(noinline)`. Without it MSVC expands the 67-byte body into
`update` at retail's call site 0x007C1DC0 and `update` stops matching
(338 bytes against retail's 289).

The `Rva00925860` shim is address-keyed: the helper body at 0x00925860 is
still a `gen-dump`, so the name and the two-pointer thiscall ABI come from the
symbols.csv pin `?method@Rva00925860@@QAEXPAX0@Z` (8-byte stack cleanup).

# 0x003C7F40 is a __thiscall member of the 0x003C8030 owner

The only caller, 0x003C8030 (64 bytes, `ret 0x10`), calls ILT 0x00029B31
(`jmp 0x003C7F40`) at +0x10. From entry to that call it never writes ECX: the
three stack arguments are staged through EAX and EDX only (+0x00..+0x0f), and
no `mov ecx` precedes the call. That is the codegen of a `__thiscall` member
passing its incoming `this` straight through to another member of the same
object. Declared as free `__stdcall` functions (and with struct/ref/inline
variants plus /O1 /Ox /Og /Oa /Ow /G5-/G7 /Oy- sweeps) the caller stayed at 18
byte diffs; declared as two members of one owner it compiles EXACT 64/64.

The callee body never reads incoming ECX (first ECX write at +0x21, from the
SEH frame) and returns with `ret 0x0c`, so a `__thiscall` member with an unused
`this` and three stack arguments compiles to the same 184 bytes as the previous
`__stdcall` spelling: probe EXACT 184/184 with 11 relocations.

The previous name `Rva003C7F40ComposeAndDispatch` was already opaque and
address-qualified; the new one, `Rva003C7F40Owner::rva003C7F40`, keeps the
address token and claims no semantic owner. Only the ABI changes. The
pointer-return correction in `0x003c7f40-return-pointer.md` still applies.

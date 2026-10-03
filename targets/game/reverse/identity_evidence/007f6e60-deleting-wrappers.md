# Two table-backed deleting wrappers

These are distinct31B bodies, each ending with RET4 at start+1C and one
INT3 after start+1F. Ghidra reads at00BF6E60 and00C01650 independently
confirm the full32-byte windows. Neither32-byte aligned span is claimed
as32 bytes: the padding is excluded.

- RVA007F6E60 is slot0 of table VA0112B5F0, independently installed by
  matched007F56C0 and007F56E0. Its restored operand uses the very same
  Rva0112B5F0 external already used by those two bodies in this TU.
- RVA00801650 is slot0 of table VA0112C358, independently installed by
  matched constructor008011C0 and teardown00801C40. It uses the existing
  g_bfmeVftBVHW data binding from that teardown, not a new table alias.

Both bodies have the MSVC scalar-deleting contract: ECX is the receiver;
one unsigned flags word is popped by RET4; bit0 requests deletion; EAX
returns the original receiver. Each unconditionally installs its witnessed
table at offset00 before the optional call to the existing canonical
`operator delete(void*)` at00881EB0. The callee inventories independently
name that same function. No remaining member/base cleanup exists in
either complete body.

The original owner spellings are not independently established, so both
ordinary C++ methods retain fully address-qualified owner names. Their
explicit pointer-store/conditional-delete/return code reproduces all31B
and both relocations. No compiler ABI is disguised as a no-argument leaf;
no table definition, purecall binding, destructor alias or new pin is
introduced. All three earlier table-store claims remain in the scoped TU.

# 0x003C83E0 manager gate and reset

The retail body is 174 bytes, enters with `this` in ECX and one stack word,
and ends both arms with `ret 4`. The matched
`LivingWorldRegionManager::rva003CB290` calls it through ILT 0x00016248
at +0x2CD with ECX still holding the manager and a 0 or 1 argument. This
supports the manager receiver; it does not establish the lexical method name.

The body calls seven physical ILTs in order: 0x00048C4D to 0x00609320,
0x0000EA7F to 0x003BD830, 0x000485D1 to 0x0060D480, 0x00025A77 to
0x003BED00, 0x00039801 to the matched manager method at 0x003C8300,
0x0001C3BE to the matched update body at 0x003C6200, and 0x0004669B
to the +0x154 receiver-adjusting thunk at 0x00594000. The last call has
one pushed word here and in the independently matched 0x003C6200 caller;
the thunk's current no-argument source declaration therefore does not
define this call site's ABI. The C++ uses typed views of address-only ILTs,
without adding semantic pins or changing the thunk claim.

The first two predicate failures return directly. The next two gates fail
into a cleanup arm that calls 0x0004669B with zero and clears manager fields
+0x40 and +0x44 if +0x40 is nonzero. A clear byte at global 0x012F1028
+0x1C also returns directly. On success, the body copies two words at
that global's +0x20/+0x24 into a local pair, passes the pair to 0x003C8300,
and passes its returned pointer plus the original stack word to 0x003C6200.
The pair, field, and other owner names remain address-derived because their
precise semantics are not independently established.

The scratch C++ first compiled to 170 bytes because its early gate failures
incorrectly reached cleanup and its nested-call arguments were evaluated in
the wrong order. Restoring the distinct retail exits and passing the stack
word before the nested lookup produced 174/174 bytes modulo relocation
slots. The scoped strict gate must verify every physical ILT and global
reference before replacing the generated row.

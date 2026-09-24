# STLport AsciiString-set copy at 0x000C11D0

The 82-byte body at 0x000C11D0 is the random-access `__copy` overload in
`vendor/stlport/stl/_algobase.h:136-143`, instantiated for
`AsciiString *` and `insert_iterator<set<AsciiString>>`. It subtracts the
two input pointers and divides by four, loops over the range, calls the
matched hinted `set<AsciiString>` insertion at 0x000C05C0 through ILT
0x00039838, increments the returned tree node through the matched STLport
helper at 0x0082B870, and returns the two-word insertion iterator. Explicit
instantiation from the vendored header compiles to all 82 retail bytes with
two aligned relocations. The initial stack word is the hidden return pointer;
the following words are first, last, the two-word output iterator, an unused
random-access tag reference, and an unused distance-type pointer. The body
ends in `ret`, so the caller cleans up those seven stack words.

Both 45-byte wrappers at 0x000C13E0 and 0x000C1500 call that body through
ILT 0x00019C45 and then return their hidden result pointer. Their seven
pushed words match the ABI above, including the tag and null distance
pointer. Each wrapper compiles byte-exactly from the `__copy_aux` forwarding
expression in `vendor/stlport/stl/_algobase.h:204-210` with the native
insertion-iterator return type. Because retail has two bodies for the same
template specialization and the function ledger permits one address per
symbol, their exported names retain separate RVA tokens.

The old `bfmeDoSevenRL(void *, ...)` pin at ILT 0x00019C45 was an opaque
seven-argument guess. Its `void` return and untyped arguments hid the STLport
return convention. The route-qualified pin for the native `__copy` symbol
replaces it; the old matched wrapper rows are replaced by typed versions at
the same addresses and sizes. No identity is inferred from byte shape alone:
the vendored algorithm, specific matched insertion/increment callees, and
the two independent caller stacks agree on the specialization and ABI.

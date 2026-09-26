# 0x00594000: one-argument offset tail thunk

The live 0x00594000/11 row and its `MemberOffsetTailThunks.cpp` macro formerly
declared `Rva00594000::invoke()` and `Gen00593A30::handle()` with no stack
arguments. Retail proves one argument. This note records the ABI correction;
the class and method labels remain address-derived because their original
lexical identity is unknown.

Retail 0x00594000 is exactly `add ecx,0x154; jmp 0x0001F90B`.
ILT 0x0001F90B jumps to the physical 850-byte callee at 0x00593A30. The
tail jump does not modify the stack; the callee inherits the return address
and any arguments from the thunk's caller.

Two independent matched callers use ILT 0x0004669B, which jumps to this
thunk:

* `Rva003C6200Owner::update` at 0x003C6200 executes `push edi; call
  0x0004669B` at offsets +0x19/+0x1A and +0x5A/+0x5B, with no caller-side
  `add esp` after either call. EDI is its item pointer, possibly null. Its
  matched source calls the ILT through a one-argument member-function view.
* `LivingWorldRegionManager::rva003C83E0` at 0x003C83E0 executes `push 0;
  call 0x0004669B` at +0x92/+0x94, again without caller cleanup. Its matched
  source also calls the ILT through a one-argument member-function view.

Physical 0x00593A30 reads `[esp+0x30]` into EBX at offset +0x19. Its
preceding three pushes, 0x1C-byte stack allocation, and EBX push mean that
address is entry-ESP+4, the first stack argument. It compares EBX with a
receiver field at +8 and ends in `ret 4` at +0x34F. Thus it consumes exactly
one stack word. `tools/callers_of.py 0x00594000` lists only the first caller;
raw disassembly and `tools/callees.py 0x003C83E0 174` independently show the
second.

The old `?handle@Gen00593A30@@QAEXXZ` pin was address-consistent but had the
wrong zero-argument ABI. Only this source TU used that symbol. The corrected
pin is `?handle@Gen00593A30@@QAEXPAX@Z -> 0x00593A30`, retaining the
address-derived owner and generic method spelling. The body row changes from
`?invoke@Rva00594000@@QAEXXZ` to
`?invoke@Rva00594000@@QAEXPAX@Z` at the same 11-byte extent. The two ILT
rows and address pin `?b_00593a30@@YAXXZ` stay unchanged.

An ignored ordinary-C++ scratch probe forwarded one `void*` from the thunk to
the +0x154 receiver. MSVC 7.1 emitted 11 bytes with the exact retail
non-relocation instruction shape and one REL32 relocation at +7 to
`?handle@Gen00593A30@@QAEXPAX@Z`. That masked shape is not a landing by
itself; the scoped build must prove that this relocation resolves to the
physical retail ILT 0x0001F90B and all other rows in the shared TU remain
matched. This identity repair adds zero native C++ bytes.

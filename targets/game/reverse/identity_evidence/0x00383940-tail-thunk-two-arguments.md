# 0x00383940: the tail thunk forwards two stack arguments

`?invoke@Rva00383940@@QAEXXZ` declared the 9-byte offset tail thunk with no
arguments. Its bytes cannot show arguments, so the ABI comes from both ends:

- 0x00383940: `add ecx, 0x170; jmp 0x00362760`. The target inherits this frame
  and its `ret` returns to our caller.
- 0x00362760 is the matched `?handle@Gen00362760@@QAEXHPAX@Z`
  (`Gen00362760ElemHandle.cpp`, 62 B): `handle(int index, void *visitor)`,
  bounds-checking `index` against a vector at +0x18 and ending in `ret 8`.
- The caller 0x0049A540 +0x7B..+0x8F: `mov edx,[esi+8]; lea ecx,[esp+0x10];
  push ecx; mov ecx,[TheGameLogic]; push edx; call 0x00408AA8` (ILT 0x00008AA8,
  `jmp 0x00383940`), i.e. an int and a pointer pushed, `this` = TheGameLogic.

So the thunk is `void invoke(int index, void *item)` forwarding both words:
`?invoke@Rva00383940@@QAEXHPAX@Z`. The name stays address-derived; only the
parameter list (and so the mangling) changes. `MemberOffsetTailThunks.cpp`
gains a BFME_OFFSET_TAIL_THUNK_ARG2 shape beside the existing ARG1 one, and
declares Gen00362760 with the matched two-argument handle, so the thunk's jmp
now resolves to the matched body's own name. The bytes are unchanged.

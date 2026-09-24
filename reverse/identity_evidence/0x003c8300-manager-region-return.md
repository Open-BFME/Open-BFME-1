# 0x003C8300 manager wrapper: pre-edit ABI and identity review

Retail 0x003C8300 is 46 bytes. It takes `this` in ECX, reads one stack
argument after its local frame, and ends with `ret 4` at +0x2B. It saves ECX
in ESI, passes that argument plus an address of a local three-word result to
vslot +0x20 of the global at 0x012F7048, then calls ILT 0x00046150.
That ILT jumps to the matched physical body 0x003C8160,
`LivingWorldRegionManager::rva003C8160(Coord3D *)`, which returns a
`LivingWorldRegion *`. The wrapper restores ESI and ESP after that call,
without writing EAX, so it propagates the region pointer. The current
`void BfmeJ1052::bfmeGo1052J(int)` declaration loses both the pointer return
and the established receiver identity even though its 46 bytes match.

On the caller side, matched `LivingWorldRegionManager::rva003CB290` at
0x003CB290 calls ILT 0x00016248 at +0x2CD with ECX=`this` and one stack
word. That thunk reaches 0x003C83E0, which saves ECX in ESI. Its call at
+0x6F to ILT 0x00039801 (physical 0x003C8300) sets ECX=ESI, pushes a
pointer to the two-word global-position copy, and leaves a separate flag
word on the stack. It immediately pushes the returned EAX and calls the
matched 0x003C6200 `update(item, force)` body, which consumes both EAX and
the flag (`ret 8`). The matched caller, forwarded receiver, matched callee,
and consumed result independently agree on a manager thiscall that returns
a region pointer.

The precise method spelling is not known. The proposed claim is the
address-qualified `LivingWorldRegionManager::rva003C8300`, taking a pointer
to the two-word input and returning `LivingWorldRegion *`. The input's
semantic type is not established, so its type remains address-qualified.
No new callee pin is justified: 0x00046150 is an existing ILT and
0x003C8160 is already matched. The source uses a typed member-pointer view
of the address-only `j_00046150` thunk, so the relocation must land on the
retail ILT without asserting its old lexical name. The old `bfmeUse1052` pin at that ILT may
serve unrelated matched code and must be audited separately before removal.

Adversarial checks before publication: verify the new 46-byte body with
the strict relocation gate, including the global and 0x00046150 route;
verify all five remaining `BfmeConv1052.cpp` claims after removing the old
definition; run the function-candidate loss and name-regression guards; and
keep the 0x003C83E0 caller in its generated row until its own C++ body is
exact. A masked-byte match alone does not establish the return or owner.

The name guard also aligns two unrelated tokens across the moved source:
`BfmeD1052` remains in `BfmeConv1052.cpp` for its separate 0x00221870
claim; `Rva003C8300Pair` is the new wrapper's two-word argument, not a
rename of that class. `j_00046150` is the existing address-only ILT called
inside the new wrapper, not the wrapper's replacement name. The actual row
correction is `bfmeGo1052J` to `rva003C8300` and is limited to 0x003C8300.

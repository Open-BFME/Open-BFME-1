# Unresolved Apt sized-delete ownership at RVA 00891650

This is an evidence correction, not an EH repair or new byte/linkage credit.
The five existing parent/constructor rows in three TUs still byte-match, but
their emitted allocation-failure cleanup is not the native cleanup. In
particular, the prior comment in `game/Libraries/Source/Apt/AptDisplayList.cpp`
inferred global delete from a scan restricted to eleven-byte actions. The
actual parent-to-handler-to-FuncInfo chain disproves that inference.

## Native cleanup identity and dimensions

The following are RVAs except for FuncInfo and unwind-map pointers, which are
VAs in the retail image (image base 00400000):

| Parent | Handler | FuncInfo VA | Unwind-map VA | State | Action |
| --- | --- | --- | --- | --- | --- |
| 008930C0 | 00C56D0F | 0124615C | 01246154 | 0, previous -1 | 00C56D00 |
| 008BE3B0 | 00C5929F | 012483E0 | 012483D8 | 0, previous -1 | 00C59290 |
| 008BE5A0 | 00C592EF | 01248438 | 01248430 | 0, previous -1 | 00C592E0 |

Each action is **15 bytes**, with this instruction shape:

```
push 64h
mov eax,[ebp-10h]
push eax
call 00891650
add esp,8
ret
```

The call instructions are at 00C56D06, 00C59296 and 00C592E6. An independent
fourth witness is parent 00896AF0, handler 00C57345, FuncInfo VA 012467E8,
unwind-map VA 01246798, state 5 action 00C57308. Its fifteen-byte action uses
the saved pointer at EBP+4 and calls the same provider at instruction 00C5730E.
All four parents call constructor 00892DA0, at instructions 00893139,
008BE3F9, 008BE5EE and 00896D34 respectively.

The provider at **00891650 is 34 bytes**, not fifteen. Its sole real ledger
identity is `??3Rva00891650HeaderedDelete@@SAXPAXI@Z`, in
`game/GameEngine/Source/Common/HeaderedDeleteOperators.cpp`. Its ABI is
`void __cdecl(void *, unsigned int)`. It calls bookkeeping removal 00897330
on the object, then the callback at VA 01337830 with `(object - 8, size + 8)`.
There are fifteen distinct 34-byte providers in that TU; equal bytes at other
addresses do not justify merging their identities.

## Current source and bounded failed probes

The three reconstructed views are in `BfmeThingBEConstructor.cpp`,
`Rva008930C0AptLookup.cpp` and `AptDisplayList.cpp`. The first two declare an
undefined unsized class delete. The third declares no class delete. Original
MSVC compilation emits eleven-byte cleanup actions calling that unsized
class member in the first two TUs and global delete 00881EB0 in the third.
The five main rows, totaling 848 bytes, remain exact; their gates do not
claim these cleanup actions as natural children of these authored parents.

Two scratch-only probes replaced that setup with a same-class sized-delete
body forwarding to the existing 00891650 provider: ordinary inline and
`__forceinline`. Both retain all five exact parent rows and grow the three
actions to fifteen bytes, but both leave a call to an emitted
`??3BfmeNestedBE@@SAXPAXI@Z` wrapper. The native actions directly call
00891650. Neither probe is accepted; neither was integrated. Matching the
action's length alone is insufficient.

This defect predates allocator-name commit
`2465f1b38c5e13b5815ce6192fe1acd27665219c`. Replacing only `WideAllocPtr` with
`Rva008C5D70Alloc` in each parent-of-commit source reproduces the corresponding
post-commit source exactly. The deallocation declarations, false comment and
virtual views were unchanged by that commit. Its 185-byte DisplayList
LINKED increase is a scoped linker metric, not proof of these unclaimed EH
bytes or the complete C++ virtual model.

## Why provider rehoming is not yet justified

Constructor 00892DA0 installs vtable VA 01135DB0. Slot 0 is the retain-like
body 008C3E90; slot 13 is scalar deleting destructor 00892ED0. That destructor
calls complete destructor 008C4270 and, when deleting, inlines bookkeeping
removal and free of `(this - 8, 108)`. This corroborates size 100 and the
eight-byte header, but does not identify the static delete's declaring class.

The constructor's own handler 00C56CB3 reaches FuncInfo VA 012460F0 and
unwind map VA 012460E0. State 0 action 00C56CA0 destroys the unchanged
`this` through 00891800, whose seven bytes install vtable VA 01135D68.
Complete destructor 008C4270 also ends with this table. Thus an offset-zero
polymorphic base is independently supported. However, that base table's
slot-13 destructor 008928B0 uses global delete on the unadjusted pointer,
not the headered policy. Assigning headered delete to that known base would
contradict its own deletion path.

Both table predecessor dwords are zero, so neither supplies an RTTI
complete-object locator or base hierarchy. No authoritative local Apt class
header or named relocation distinguishes a direct class declaration from an
unobserved allocation-policy base. Current reconstructed `HeaderedDeleteBase`
and `BfmeBaseAAA` spellings are not independent evidence. The latter's
generated destructor-at-slot-zero model also differs from the native
sixteen-slot table. Rehoming the provider to `BfmeNestedBE` merely because
these allocations use it would choose an unproved declaring owner.

## Acceptance conditions for an eventual repair

Recover independent declaring-owner/ABI evidence before renaming the sole
00891650 provider or adding an inheritance relationship. Preserve all fifteen
provider rows and all five parent rows, and verify the complete handler,
FuncInfo, unwind-map and action graphs, including constructor 00892DA0's own
unwind states and any emitted deleting destructors/vtables. All three shared
33-byte operator-new COMDAT copies must remain coherent. The fourth native
cleanup witness must still resolve to the same provider. Do not add an alias,
a forwarding wrapper, a duplicate identity or a guessed base to make a gate
green. A fresh link preview supplements, but cannot replace, these checks.

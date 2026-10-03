# C54BC9 and native locale-comparison parent 008365B0

The retail parent at RVA 008365B0 pushes handler C54BE2 at 008365B2.
The handler selects FuncInfo E43FCC, unwind map E43FBC. State 1 -> 0
selects C54BC9, independently of the neighboring state-0 action C54BB0.
The complete 25-byte action tests bit 2 at EBP-34, clears that bit,
and destroys EBP-24 through ILT 1642D -> A5120. Its conditional RET
is at C54BE1, immediately before the handler. Ghidra read_memory agrees.

The parent ends in RET 4 at 8366AE, followed by INT3 at 8366B1 (257 bytes).
Its receiver comparison and three 12-byte temporaries reproduce native
STLport locale equality, rather than the vector-shaped interpretations in
older records. The existing STLport header stl/_locale.h declares the
const member name()/operator==() ABI. The independent upstream source
at https://android.googlesource.com/platform/external/stlport/+/e46c9386c4f79aa40185f79a19fc5b2a7ef528b3/src/locale.cpp
contains the same implementation-pointer test and three name() temporaries.
This is a later upstream source witness, not a claim that this external
snapshot is the exact 4.5.3 release shipped in BFME.

Retail getter 836580 loads the implementation pointer, addresses +C, and
calls the canonical narrow-string copy constructor through ILT 1CB11 ->
4FB1B0. At C6D8B0, the global initializer constructs VA 130BCB4 from the
literal "*" at VA10892DC and registers C70CC0 for destruction. That
independently establishes the third comparison's string constant.

Native string destructor specialization is declared before <locale> to
avoid an already-instantiated specialization. Its nonthrowing contract is
supported by the full A5120 body: null guard and either CRT deallocation or
node-pool deallocation, then return, with no throwing operation. Declaring
it without throw() produced 271 bytes (171 differing bytes); throw()
produced all 257 instruction bytes with all 12 relocation sites aligned.
Four standard EH-choice trials were unchanged before this lifetime fix;
the unused remainder was canceled after the exact source was found.

The initial relocation-masked result alone did not establish the typed
callee bindings. Strict verification reported the getter and comparison
symbols unresolved. The dependency corrections below resolve them by
replacing the existing synthetic claims, not by adding alias pins. The
A5120 native-string binding is retained unchanged; its shared machine
shape alone does not justify another destructor alias.

## Dependency identity corrections

The 34-byte getter at 836580 ends RET4 at 83659F before INT3. Its native
locale::name emission matches every instruction and the one relocation to
canonical basic_string<char>'s copy constructor at 4FB1B0. The old
BfmeThingDPF::bfmeGoDPF declaration instead fabricated an explicit result
pointer and a volatile bookkeeping integer. The real nontrivial result
lifetime is independently witnessed by the parent and both cleanup states.
The native locale receiver shape is also witnessed by its already-matched
constructor/destructor at 832120/832170 and the _Locale_impl RTTI evidence
in game/stlport/LocaleImplDeletingDestructor.cpp.

The 65-byte body at 832790 is the native string inequality template declared
and defined in the local vendor stl/_string.h: size equality, char_traits
comparison, then negation. It matches all 65 bytes without any relocations;
returns occur at 8327C2 and 8327D0, then INT3 at 8327D1. Its actual callers
here pass native locale-name results and the independently initialized
"*" string. This refutes the invented BfmeStrIF owner view. The old
bfmeTextDiffers and bfmeGoDPF definitions have no other source callers.
Their narrow identity corrections replace those definitions; no alias pin
is added. These 99 already-native bytes receive no new conversion credit.

Initial strict parent verification failed on precisely the two typed
helper bindings above. The dependency corrections and final parent/action claims are verified
together through the normal strict source gate. The parent ledger keeps
its address-based dup_008365B0 name; the actual emitted native member
symbol is recorded as object-symbol. The action uses $L13973 from that
member, selected by the independent retail unwind map above.

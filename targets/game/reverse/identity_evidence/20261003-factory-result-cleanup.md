# Factory result cleanup at C5AC60

Retail image: BFME1 1.03 unpacked baseline, image base 00400000.
All addresses below are RVAs. Raw retail bytes and Ghidra memory agree.

The already matched factory `bfmeMakeXW` at 008FF200 constructs the
address-named `Gen008FF1B0` return object through the independently matched
constructor at 008FF1B0. The constructor and initializer at 008FEC90 in
`P8ZeroingCtors.cpp` own a single reference pointer at offset zero. No semantic
class name is asserted by this repair.

The factory pushes handler C5AC81 at 008FF202. That handler selects FuncInfo
E49CE0 and unwind map E49CD0. State 0 -> -1 selects C5AC60, which tests mask 1
at EBP-10 and passes the hidden return object's address from EBP+4 to 008FEB80.
The complete action is 25 bytes: its conditional RET is C5AC78, before the
separate temporary cleanup at C5AC79. Ghidra creation of the factory function
also recovers its full 141-byte body and return-object construction.

The destructor at 008FEB80 is exactly 12 bytes:

    mov ecx, [ecx]
    test ecx, ecx
    je 008FEB8B
    jmp 009EB7A0
    ret

INT3 padding starts at 008FEB8C. Its tail target is the existing
`TextureClass::Release_Ref` binding used by the same factory and initializer.
The old row was an opaque `dup_008feb80` with `gen-alias` notes pointing to
`NetCommandRef::~NetCommandRef`, whose own native retail target is 00676280
and whose final callee is `NetCommandMsg::detach`. That is not this owner or
callee. Replace only that alias row with the result owner's native destructor;
retain the real network source and its other claims unchanged.

The parent is reverified after adding the noinline destructor, then its native
compiler-emitted cleanup is selected by object label and checked with the real
destructor relocation. No destructor alias pins or synthetic parent wrappers
are introduced. The existing address-named owner and member spellings are
preserved; no new field identity is claimed.

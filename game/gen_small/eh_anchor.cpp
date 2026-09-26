// cl: /EHsc
// The EH anchor. Beside every /EHsc function that owns an object needing
// unwind, MSVC 7.1 emits a ten-byte `__ehhandler$` stub: `mov eax, <funcinfo>;
// jmp ___CxxFrameHandler`. The retail image carries thousands of them, and they
// differ only in the funcinfo pointer -- a DIR32 site the gate copies from the
// target -- and in the jmp displacement, which is a function of the stub's own
// address. So one stub compiled here reproduces every one of them, and each
// eh_<rva> row in targets/game/reverse/functions.csv binds one retail stub to this obj's
// __ehhandler$ symbol via its `object-symbol=` note.
//
// Nothing here claims eh_anchor itself: the function exists only to make the
// compiler emit the handler stub. The dtor and the callee are declared and
// never defined on purpose -- an extern dtor is an unwind action the compiler
// cannot elide, and the extern call between construction and scope end is what
// makes the EH state machine real rather than optimised away.
struct EhAnchorGuard {
    ~EhAnchorGuard();
};

void eh_anchor_callee();

void eh_anchor() {
    EhAnchorGuard guard;
    eh_anchor_callee();
}

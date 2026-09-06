// ?bfmeCtorHelper_00844460@@YGPAVGen_008443A0@@PAX00@Z (identity unknown)
// partial score=0.75 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
//
// Retail (87B) disassembly: SEH prologue (push -1; push handler; save fs:0;
// push ecx [[DEAD reservation, not a live value -- see below]]; xor eax,eax;
// push esi; mov esi,[esp+0x18]) then zeroes esi[0],esi[4],esi[8] (BfmeSehPair
// + BfmeSehSlot state word), calls bfmeStart(edx=[esp+0x1c], ecx=[esp+0x20],
// &[esp+0x18]) with this=esi, then epilogue restores fs:0 and returns
// eax=esi (self).
//
// PROVEN: self is NOT the this-pointer (ecx) of a real member constructor.
// Wrote Gen_00844460 as a genuine 2-arg member ctor (this in ecx, body
// `Gen_00844460 *self=this; bfmeStart(first,second,(void**)&self);`) and
// probed it directly (??0Gen_00844460@@QAE@PAX0@Z): MSVC 7.1 compiles a
// near-identical body (91B, SAME zero/call/epilogue shape, EH frame
// present) EXCEPT it spills 'this' via `sub esp,8` (this lives in ecx, a
// live register) instead of retail's `push ecx`, and loads the object
// pointer from `mov esi,ecx` instead of `mov esi,[esp+0x18]`. If retail's
// "push ecx" were really saving a live this-pointer for later use, the
// compiler would have reloaded it at the SAME small offset (+4) it was
// pushed at, not at +0x18 (which is a genuine incoming STACK argument
// slot four pushes further out) -- so retail's ecx at that point is
// provably a DEAD/garbage register, used only for its cheap 1-byte push
// as frame padding. This means self truly arrives as an explicit STACK
// argument to a non-member (or non-thiscall) function, not as `this`.
//
// Tried and falsified:
//  - manual placement (self->field=0; new(&self->slot) Slot(); self->bfmeStart(...))
//    in one static __stdcall function: compiles with NO EH frame at all
//    (compiler doesn't track unwind for a placement-new'd *pointer* target).
//  - `return new(self) Gen_X(first,second);` via a real out-of-line 2-arg
//    ctor: with <new>'s throw() placement operator new (no null check) the
//    ctor call is NOT inlined into the wrapper (MSVC's inliner refuses to
//    inline any callee that itself installs an SEH frame) -- wrapper shrinks
//    to a bare call, losing the whole shape.
//  - NRVO by-value return (`static Gen_X f(...){ Gen_X result; result.bfmeStart(...);
//    return result; }`): RVO did not elide; produced its own stack-local copy
//    plus a return copy (140B, much bigger, wrong shape).
//  - explicit `__stdcall` keyword on the ctor declaration: MSVC 7.1 silently
//    accepts the syntax but still mangles/compiles it thiscall (QAE, ecx=this)
//    -- calling convention override has no effect on non-static ctors.
//
// OPEN QUESTION for the next attempt: what source construct puts a real,
// non-member, EH-frame-owning function's FIRST parameter as the pointer to
// construct in place, with fields written directly (not via a nested ctor
// call) but still gets SEH? Candidates worth trying: a "vector constructor
// iterator" idiom (array placement new with a count of 1), or check whether
// a __cdecl (not __stdcall) free function changes the inliner's decision
// for the separate-ctor-call variant (the null-checked/no-null-checked
// versions above were only tried __stdcall).
// callee 0x00042BB8 pinned as ?bfmeStart@Gen_008443A0@@QAEXPAX0PAPAX@Z (still a dump).

class BfmeSehPair
{
public:
	BfmeSehPair(void) : m_bfmeA(0), m_bfmeB(0) {}
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class BfmeSehSlot
{
public:
	BfmeSehSlot(void) : m_bfmeC(0) {}
	~BfmeSehSlot(void);
	int m_bfmeC;						// +0x00
};

// Closest empirical candidate (91B vs retail 87B): a genuine thiscall ctor.
// Byte-identical except the this-pointer arrives via ecx (register) instead
// of a stack argument slot -- see notes above for what was ruled out trying
// to fix that without losing the EH frame.
class Gen_00844460 : public BfmeSehPair
{
public:
	Gen_00844460(void *first, void *second);
	void bfmeStart(void *first, void *second, void **slot);	// retail 0x00042BB8
	BfmeSehSlot m_bfmeSlot;					// +0x08
};

Gen_00844460::Gen_00844460(void *first, void *second)
{
	Gen_00844460 *self = this;
	bfmeStart(first, second, (void **)&self);
}

// ?d_00723c50@@YAXXZ
// partial score=0.15 date=2026-09-02
// PARTIAL / UNVERIFIED -- does not compile-match yet. Banked for the next agent.
// ghidra: FUN_00b23c50 retail @ 0x00723C50 size 124
// Sibling of BfmeA1137Cache (see attempt_723b60.cpp). Returns a float (x87
// st0, default 1.0f = 0x3f800000) selected from either the shared global at
// RVA 0x0012F15F8 or `this` depending on whether the global's inner pointer
// (+4) is set, then depending on flag bytes at [+0x40] and this->m_bfme44
// either returns the default float OR tail-jumps into a shared comparator
// helper reached via the 0x00040D7B5 ILT slot, whose real target resolves to
// RVA 0x00096F60 (min/max-shaped: fld [ecx+8]/[ecx+4], fucompp, and a call to
// RVA 0x00096970 on the "not equal" path -- looks like a clamped lerp/min
// helper over two floats stored at [this_or_global + 4] and [+8], i.e. NOT
// literally `this` at those low offsets -- the callee re-derives its own
// object from ecx passed at the tail-jmp, still unidentified).
//
// Blocker: same 0x0012F15F8 global identity gap as the rest of the family,
// plus the exact register/branch shape of the three near-identical
// "jmp 0x40d7b5" tail paths (matching.md warns near-matches on branch layout
// are still failures) and the semantics of RVA 0x00096F60 itself.

extern "C" void *g_bfmeGlobalUnknown1137; // RVA 0x0012F15F8, identity TBD
void __fastcall bfmeWalkLock1137(void *p); // RVA 0x000022BB thunk -> 0x00087A80

class BfmeA1137Cache2
{
public:
	float bfmeQueryCached(); // returns via ecx-tail-jump on 2 of 3 paths
	char m_bfmePad[0x40];
	char m_bfme40;
	char m_bfme44;
};

// Not written: the three tail-jump paths need the RVA 0x00096F60 callee's
// real signature/identity before a byte-matching shape can be attempted.

// cl: /Od
// A stretch of one byte put into the run at a given place, after the place has
// been checked against the length and the new length against the limit. The
// record is handed back. Built without optimisation; all three callees are
// pinned by address.

// retail callee at 0x006434C0, reached through the ILT thunk at 0x000132CD;
// declaration only, the body is game/gen_small/fun_004.cpp
struct Gen_006434c0 { void m(); };

// Retail reaches the length-error helper through the five-byte ILT thunk at
// 0x00042DC0, which the ledger owns as ?j_00042dc0@@YAXXZ
// (game/gen_small/thunks_032.cpp).  Several ?bfmeLenErrVxx pins and the
// invented ?bfmeLengthErrorQX pin name that same folded thunk, so the call has
// to name the definition; ecx still carries the receiver, which the
// fastcall-shaped cast reproduces byte for byte.
extern void j_00042dc0();

struct BfmeThingQX
{
	BfmeThingQX *bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what);

	// 0x0082FBB0, ledger-owned as ?bfmeInsertNChV48@@YGPADPADID@Z in
	// game/GameEngine/Source/Common/BfmeConv1491.cpp.  That body takes its
	// receiver in ecx, so no C++ spelling of the owning name keeps ecx plus
	// three stack arguments; the call is left as the thiscall member until
	// that definition is renamed to a member of this class.
	// Measured: the member-pointer route used by the /O2 files
	// (Rva003855F0Transition.cpp) does not work here, because under /Od MSVC
	// 7.1 stores the pointer-to-member to the frame and emits an indirect
	// `ff 55` call instead of a direct `e8 rel32`.
	void bfmeDoInsertQX(char *at, unsigned int many, unsigned char what);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

BfmeThingQX *BfmeThingQX::bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what)
{
	if (where > (unsigned int)(m_bfmeEnd - m_bfmeAt))
		((Gen_006434c0 *)this)->m();

	if ((unsigned int)(m_bfmeEnd - m_bfmeAt) > 0xfffffffe - many)
		((void (__fastcall *)(BfmeThingQX *))j_00042dc0)(this);

	char *at = m_bfmeAt;

	bfmeDoInsertQX(at + where, many, what);

	return this;
}

// ??0Rva0077CDE0@@QAE@XZ
// partial score=0.93 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /O2 /D_STLP_USE_STATIC_LIB
// stlport
//
// Constructor at retail 0x0077CDE0 (697 B).  21-state EH unwind map
// (FuncInfo 0x0123FE1C).  Own vtable install=0x1124230 (masked DIR32).
// Base is a trivial-inlined polymorphic class whose dtor forwards to the
// already-landed shim at ILT 0x0000951B -- never called on the normal path,
// so it needs no pin.  Nine BFMERetailAsciiString members (dtor already
// pinned at 0x0000D828).  Six small zero-filled opaque sub-objects sized
// from the unwind funclets (their own dtors are only reached on the
// exception path and need no pin either).  The 0x84 member reuses the
// already-modelled 44-byte S4Elem007746E0 record (ctor ILT 0x0000345E).
// The 0xf0 member is a 0x44-byte POD region with mixed scalar/float fields.
// The trailing array[2] at 0x134 is built through the EH vector-constructor
// iterator (??_L, already pinned) over a fresh 0x14-byte element type whose
// ctor/dtor are pinned here.  Late body: two in-place Set() calls on the
// 0x6c/0x78 members, a 188-byte temporary (Rva0077CC10Element, matching the
// element type already modelled for the sibling vector at retail 0x0077CC10
// in RvaVectorPushBack.cpp) constructed, given a literal RetailLayoutString
// label, and always pushed into the 0x24 STL-shaped vector via the overflow
// path (the vector is freshly zeroed, so finish==end_of_storage is always
// true here; the in-place-construct arm is dead code MSVC still emits).
//
// FIXED THIS ROUND (order defect, was: state-0 dword store scheduled before
// [esi+8] instead of between [esi+0xc] and [esi+0x10]): wrap ONLY the LAST
// raw scalar of the +0x8 opaque member (Opaque1) in a trivial one-field
// struct (`struct Wrap { unsigned int m_c; }`), keeping the first two
// fields (a,b) as plain ints.  General rule discovered here: MSVC's lazy
// base-completion state store is emitted immediately before the LAST
// class-typed (declared struct/class, even if trivial) member's
// construction in a flat member-init list, regardless of how many plain
// scalars precede it -- wrapping (a,b) together + c plain left the store at
// the very start (no distinct "last class-typed member" boundary moved);
// wrapping a plain + (b,c) together moved the store to right after a;
// wrapping (a,b) plain + c alone in Wrap moved it to right after both a and
// b, matching retail exactly.  Reusable lever for other "state-0 placement"
// defects: identify retail's real split point among a multi-scalar first
// member and wrap everything AFTER that point into a class type, leaving
// everything up to and including the split point as plain scalars.
//
// REMAINING (unsolved) defect: retail goes straight from state 0xb (before
// the S4Elem ctor call at +0x84) to state 0x11 (before the ??_L array
// call), never emitting anything for the +0xe0..+0xf0 range beyond the
// four string dtors' batched cleanup.  Ours emits ONE spurious extra
// `mov byte ptr [esp+0xe4],0x10` between the m_str9 (+0xec) store and the
// first m_opaque8 (+0xf0) store, 8 bytes MSVC does not put there in
// retail, i.e. 695/697 (matches the 0.91 stash's size, this round only
// fixed ordering, not size).  Ruled out this round (all zero effect on the
// position/presence of the 0x10 store):
//   - `throw()` on Rva0077CDE0Opaque8's ctor AND dtor (both together, and
//     ctor alone) -- the dtor stayed empty inline either way, so this may
//     simply confirm the empty dtor already gets no state, unrelated to
//     the extra store.
//   - Deleting Opaque8's user dtor entirely (implicit trivial dtor).
//   - Pulling Opaque8's first three (zero-valued) dwords OUT of the class
//     entirely into three plain `unsigned int` members directly on the
//     outer Rva0077CDE0 class, declared right after m_str9 and before the
//     (now-smaller) m_opaque8 -- the extra store's position and presence
//     were BYTE-IDENTICAL to the baseline in every one of the above
//     variants, which rules out Opaque8's own shape/type-boundary as the
//     cause (contrast with the +0x8 Opaque1 fix above, which WAS shape-
//     sensitive).  The extra store is an immediate-byte protective state
//     set (`c6 84 24 .. 10`, same instruction family as the real
//     `..,0x11` / `..,0x12` protective sets before real throwing calls
//     elsewhere in this body), NOT the lazy register-fed state-0 store --
//     so it looks like MSVC genuinely believes something between str9 and
//     the ??_L call can throw, but no candidate in the current body
//     (opaque8's ctor, the memset block, any of the three preceding
//     dtors) which is provably-nothrow by hand-inspection reproduces or
//     removes it under any tried restructuring.  Next agent: try declaring
//     BFMERetailAsciiString's dtor throw() (touches all nine string uses,
//     high risk of regressing the already-matching earlier states, not
//     attempted this round given budget) or dump the compiled .obj's own
//     unwind table to see what state 0x10's registered cleanup action
//     actually targets -- that will name the object MSVC thinks needs it.

#include <string>

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class BfmeBase0077CDE0
{
public:
	BfmeBase0077CDE0() {}
	virtual ~BfmeBase0077CDE0() {}
};

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) { }
	~BFMERetailAsciiString();

	void *m_data;
};

class Rva0077CDE0Opaque1
{
public:
	struct Wrap { Wrap() : m_c(0) {} unsigned int m_c; };
	Rva0077CDE0Opaque1() : m_a(0), m_b(0), m_cw() {}
	~Rva0077CDE0Opaque1();                              ///< pinned 0x0002303D (unwind funclet target)
private:
	unsigned int m_a, m_b;
	Wrap m_cw;
};

class Rva0077CDE0Opaque2
{
public:
	Rva0077CDE0Opaque2() : m_a(0), m_b(0), m_c(0) {}
	~Rva0077CDE0Opaque2();                              ///< pinned 0x000395D1 (unwind funclet target)
private:
	unsigned int m_a, m_b, m_c;
};

struct Rva0077CC10Element
{
public:
	Rva0077CC10Element();                              ///< pinned 0x00043905
	Rva0077CC10Element(const Rva0077CC10Element &other); ///< pinned 0x00013FB1
	~Rva0077CC10Element();                              ///< pinned 0x0004A1C4

	unsigned int m_pad0;
	unsigned int m_pad4;
	RetailLayoutString m_layout;
	unsigned char m_tail[188 - 4 - 4 - 1];
};

class Rva0077CDE0Vec3
{
public:
	Rva0077CDE0Vec3() : m_start(0), m_finish(0), m_endOfStorage(0) {}
	~Rva0077CDE0Vec3();                              ///< pinned 0x00003B6B (unwind funclet target)

	void InsertOverflow(Rva0077CC10Element *position,
		const Rva0077CC10Element &value, const void *tag,
		unsigned int fillLength, bool atEnd);           ///< pinned 0x00043270

	Rva0077CC10Element *m_start;
	Rva0077CC10Element *m_finish;
	Rva0077CC10Element *m_endOfStorage;
};

class Rva0077CDE0Opaque4
{
public:
	Rva0077CDE0Opaque4() : m_a(0), m_b(0), m_c(0) {}
	~Rva0077CDE0Opaque4();                              ///< pinned 0x00026AB2 (unwind funclet target)
private:
	unsigned int m_a, m_b, m_c;
};

class Rva0077CDE0Elem5
{
public:
	Rva0077CDE0Elem5() : m_a(0), m_b(0), m_c(0) {}
	~Rva0077CDE0Elem5();                              ///< pinned 0x0002C868 (unwind funclet target)
	void Set(unsigned int a, unsigned int b);            ///< pinned 0x000109F6
	unsigned int m_a, m_b, m_c;
};

class Rva0077CDE0Elem6
{
public:
	Rva0077CDE0Elem6() : m_a(0), m_b(0), m_c(0) {}
	~Rva0077CDE0Elem6();                              ///< pinned 0x00022C2D (unwind funclet target)
	void Set(unsigned int a, unsigned int b);            ///< pinned 0x0001B234
	unsigned int m_a, m_b, m_c;
};

class S4Elem007746E0
{
public:
	S4Elem007746E0();                                    ///< pinned 0x0000345E
	~S4Elem007746E0();                                   ///< pinned 0x0002A8BA

	_STL::string m_first;
	_STL::string m_second;
	_STL::string m_unused;
	int m_unusedValue;
	int m_value;
};

class Rva0077CDE0Opaque8
{
public:
	Rva0077CDE0Opaque8()
		: m_p0(0), m_p4(0), m_p8(0)
		, m_b0c(0), m_b0d(0), m_b0e(0), m_b0f(0)
		, m_d10(0), m_d14(0)
		, m_b18(0), m_b19(0), m_b1a(0), m_b1b(0), m_b1c(0)
		, m_d28(0), m_d2c(0)
		, m_f30(1.0f)
		, m_d34(0)
		, m_b38(0)
		, m_d3c(0xFFFFFFFF)
		, m_b41(0), m_b42(1), m_b43(0)
	{}
	~Rva0077CDE0Opaque8() {}

	unsigned int m_p0, m_p4, m_p8;
	unsigned char m_b0c, m_b0d, m_b0e, m_b0f;
	unsigned int m_d10, m_d14;
	unsigned char m_b18, m_b19, m_b1a, m_b1b, m_b1c;
	unsigned char m_b1d;
	unsigned char m_pad1e, m_pad1f;
	unsigned int m_d20, m_d24;
	unsigned int m_d28, m_d2c;
	float m_f30;
	unsigned int m_d34;
	unsigned char m_b38;
	unsigned char m_pad39, m_pad3a, m_pad3b;
	unsigned int m_d3c;
	unsigned char m_b40;
	unsigned char m_b41, m_b42, m_b43;
};

class Rva0077CDE0ArrElem
{
public:
	Rva0077CDE0ArrElem();                                ///< pinned 0x0002FB80
	~Rva0077CDE0ArrElem();                                ///< pinned 0x0000E746
private:
	unsigned char m_data[0x14];
};

class Rva0077CDE0Block28
{
public:
	Rva0077CDE0Block28() { memset(this, 0, 0x28); }
private:
	unsigned int m_a[10];
};

class Rva0077CDE0 : public BfmeBase0077CDE0
{
public:
	Rva0077CDE0();
	virtual ~Rva0077CDE0() {}

private:
	unsigned int m_pad04;                                 ///< +0x04, never written by retail
	Rva0077CDE0Opaque1 m_opaque1;                        ///< +0x08
	BFMERetailAsciiString m_str1;                        ///< +0x14
	Rva0077CDE0Opaque2 m_opaque2;                        ///< +0x18
	Rva0077CDE0Vec3 m_vec3;                               ///< +0x24
	Rva0077CDE0Opaque4 m_opaque4;                         ///< +0x30
	BFMERetailAsciiString m_str2;                         ///< +0x3c
	BFMERetailAsciiString m_str3;                         ///< +0x40
	BFMERetailAsciiString m_str4;                         ///< +0x44
	BFMERetailAsciiString m_str5;                         ///< +0x48
	int m_neg1;                                           ///< +0x4c
	float m_f50;                                          ///< +0x50
	float m_f54;                                          ///< +0x54
	float m_f58;                                          ///< +0x58
	float m_f5c;                                          ///< +0x5c
	float m_f60;                                          ///< +0x60
	unsigned int m_i64;                                   ///< +0x64
	unsigned char m_b68, m_b69, m_b6a, m_b6b;             ///< +0x68
	Rva0077CDE0Elem5 m_elem5;                             ///< +0x6c
	Rva0077CDE0Elem6 m_elem6;                             ///< +0x78
	S4Elem007746E0 m_s4;                                  ///< +0x84
	unsigned char m_bb0;                                  ///< +0xb0
	unsigned char m_padb1, m_padb2, m_padb3;
	Rva0077CDE0Block28 m_block10;                        ///< +0xb4
	unsigned char m_bdc;                                  ///< +0xdc
	unsigned char m_paddd, m_padde, m_paddf;
	BFMERetailAsciiString m_str6;                         ///< +0xe0
	BFMERetailAsciiString m_str7;                         ///< +0xe4
	BFMERetailAsciiString m_str8;                         ///< +0xe8
	BFMERetailAsciiString m_str9;                         ///< +0xec
	Rva0077CDE0Opaque8 m_opaque8;                         ///< +0xf0
	Rva0077CDE0ArrElem m_arr[2];                          ///< +0x134
};

// ??0Rva0077CDE0@@QAE@XZ
Rva0077CDE0::Rva0077CDE0()
	: m_neg1(-1)
	, m_i64(0)
	, m_b68(0), m_b69(0), m_b6a(1), m_b6b(0)
	, m_bb0(0)
	, m_bdc(0)
{
	m_f50 = 0.0f;
	m_f54 = 2.0f;
	m_f58 = 3.0f;
	m_f5c = 0.4f;
	m_f60 = 0.065f;

	m_elem5.Set(m_elem5.m_a, m_elem5.m_b);
	m_elem6.Set(m_elem6.m_a, m_elem6.m_b);

	Rva0077CC10Element temp;
	temp.m_layout.set("<DefaultEmptyIdleAnimationState>", 0x20);

	Rva0077CC10Element *finish = m_vec3.m_finish;
	Rva0077CC10Element *endOfStorage = m_vec3.m_endOfStorage;
	if (finish != endOfStorage)
	{
		new (finish) Rva0077CC10Element(temp);
		m_vec3.m_finish = finish + 1;
	}
	else
	{
		struct FalseTag { unsigned int m_unused[2]; } tag;
		m_vec3.InsertOverflow(finish, temp,
			reinterpret_cast<const void *>(&tag), 1, true);
	}

	m_opaque8.m_b1d = 0;
	m_opaque8.m_d24 = 0x60;
	m_opaque8.m_d20 = 0x60;
	m_opaque8.m_b40 = 0;
}

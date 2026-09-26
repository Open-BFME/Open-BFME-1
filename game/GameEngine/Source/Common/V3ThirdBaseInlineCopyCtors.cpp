// cl: /EHs-c-
// Two 116-byte __thiscall copy constructors, one level below the nine landed in
// V3HeadNodeCopyCtors.cpp.  Retail (0x005ED590 and 0x005ED6B0 differ only in the
// four vftable dwords marked <...>):
//
//     push esi ; push edi ; mov edi,[esp+0xC] ; push edi ; mov esi,ecx
//     call 0x005ED310                       ; first base's copy ctor, arg at 0
//     test edi,edi
//     mov [esi],     <MID VFTABLE 0>        ; 0x01111994 in BOTH rows
//     mov [esi+0x14],<MID VFTABLE 0x14>     ; 0x01111990 in BOTH rows
//     je L ; lea eax,[edi+0x18] ; jmp M ; L: xor eax,eax ; M:
//     mov [esi+0x18],<THIRD BASE'S OWN VFTABLE>
//     lea ecx,[eax+4]  ; lea edx,[esi+0x1C] ; three dwords copied
//     add eax,0x10     ; lea edx,[esi+0x28] ; three more
//     pop edi
//     mov [esi],     <DERIVED VFTABLE 0>
//     mov [esi+0x14],<DERIVED VFTABLE 0x14>
//     mov [esi+0x18],<DERIVED VFTABLE 0x18>
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  One out-of-line call taking the argument unchanged, then
// THREE rounds of vptr stores at the same three slots {0, 0x14, 0x18}, with a
// null-propagating test/je/lea/jmp/xor pointer conversion to +0x18 and two
// twelve-byte copies wedged between the second and third round.
//
// The callee is 0x005ED310, reached through the incremental-link thunk
// 0x000202F7.  That address is already a ledger row: the copy constructor of
// Rva005ED310, the head-plus-list-node class with one extra polymorphic base at
// 0x14 that V3HeadNodeCopyCtors.cpp landed.  So the first base is 0x18 wide and
// carries the slots at 0 and 0x14 -- which is exactly the pair the SECOND round
// rewrites, and why the third slot only appears from 0x18 on.
//
// THREE ROUNDS MEANS THREE CLASSES ON ONE CHAIN.  A class re-stamps every
// polymorphic base it owns, so the round rewriting {0, 0x14} and nothing else
// belongs to a class deriving from Rva005ED310 alone; the single store at 0x18
// that follows is the third base's OWN constructor, running after it because
// bases are constructed in declaration order; and the final round rewriting all
// three is the most derived class.  Both rows carry the SAME middle pair
// (0x01111994, 0x01111990), so the middle class is one class shared by both --
// that is the fact that forces the extra level rather than a flat two-base
// spelling, which would emit only two rounds.
//
// THE THIRD BASE IS A BASE, NOT A MEMBER: its address is taken through the
// null-check conversion, and a member subobject's address is never null and gets
// a bare displacement (the same argument V3ChainedCopyCtorsWithSecondBase.cpp
// makes at 0xC).  Its copy constructor is implicit and inlined -- vptr first,
// then its two twelve-byte fields at +4 and +0x10 copied into this+0x1C and
// this+0x28 -- so it is 0x1C wide and the derived class is 0x18 + 0x1C = 0x34.
//
// 0x34 IS INDEPENDENTLY CONFIRMED.  Both of these constructors are called by the
// 99-byte `return new T(this)` bodies in Q4NewInlineCtorMembers.cpp, and the
// allocation size those two bodies push is 0x34.  Nothing in this file is padded
// to reach it; the layout the stores dictate lands on it exactly.
//
// IDENTITY IS NOT RECOVERED.  Names come from addresses, and the four vftable
// dwords per body are DIR32 sites the gate takes from the target, leaving 100 of
// the 116 bytes concrete.

typedef int Int;

// ---- the first base, landed in V3HeadNodeCopyCtors.cpp; declared only here ---

class V3Head14
{
public:
	virtual ~V3Head14();
	Int m_unreconstructed_04, m_unreconstructed_08;
	Int m_unreconstructed_0C, m_unreconstructed_10;
};

class V3Vt0110F9CC
{
public:
	virtual void s0();
};

class Rva005ED310 : public V3Head14, public V3Vt0110F9CC
{
public:
	Rva005ED310( const Rva005ED310 & );
};

// ---- the middle class: the round that rewrites {0, 0x14} and nothing else ----

class V3Mid01111994 : public Rva005ED310
{
};

// ---- the third bases, at 0x18, copy constructor implicit and inlined --------

class V3Triple12
{
public:
	Int m_a, m_b, m_c;
};

#define V3_THIRD_BASE( NAME )                                             \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		virtual void t0();                                                \
		V3Triple12 m_first;		/* +0x04 */                               \
		V3Triple12 m_second;	/* +0x10 */                               \
	};

V3_THIRD_BASE( V3Third01110B78 )
V3_THIRD_BASE( V3Third01110BB8 )

// 0x005ED3E0's third base carries only the first of the two fields, so it is
// 0x10 wide and its derived class 0x28 -- again the allocation size its
// Q4NewInlineCtorMembers.cpp caller pushes.
class V3Third01110B0C
{
public:
	virtual void t0();
	V3Triple12 m_first;		/* +0x04 */
};

// 0x005EC640 sits over the THREE-base head instead: Rva005EC730 is 0x1C wide,
// so its middle round covers 0, 0x14 and 0x18 and the third base lands at 0x1C.
// Sixteen bytes at +4 and twelve at +0x14 make it 0x20 wide.  The sixteen are
// FOUR SCALARS and the twelve are ONE CLASS: retail copies the first sixteen
// with bare [eax+disp]/[esi+disp] pairs and the last twelve through a pointer
// held in ecx, which is what an inlined implicit copy constructor looks like.
// Spelling the sixteen as one four-int class puts the pointer form on both.
class V3Third01110BF8
{
public:
	virtual void t0();
	Int m_a, m_b, m_c, m_d;	/* +0x04 .. +0x10 */
	V3Triple12 m_second;	/* +0x14 */
};

class V3Vt0111082C
{
public:
	virtual void s0();
};

class V3Vt0110F9E4
{
public:
	virtual void s0();
};

class Rva005EC730 : public V3Head14, public V3Vt0111082C, public V3Vt0110F9E4
{
public:
	Rva005EC730( const Rva005EC730 & );
};

class V3Mid01113120 : public Rva005EC730
{
};

// -------------------------------------------------------------- the rows ----

#define V3_THIRD_BASE_COPY_CTOR( NAME, THIRD )                            \
	class NAME : public V3Mid01111994, public THIRD                       \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : V3Mid01111994( o ), THIRD( o ) {}

V3_THIRD_BASE_COPY_CTOR( Rva005ED590, V3Third01110B78 )
V3_THIRD_BASE_COPY_CTOR( Rva005ED6B0, V3Third01110BB8 )
V3_THIRD_BASE_COPY_CTOR( Rva005ED3E0, V3Third01110B0C )

class Rva005EC640 : public V3Mid01113120, public V3Third01110BF8
{
public:
	Rva005EC640( const Rva005EC640 & );
};

Rva005EC640::Rva005EC640( const Rva005EC640 &o )
	: V3Mid01113120( o ), V3Third01110BF8( o )
{
}

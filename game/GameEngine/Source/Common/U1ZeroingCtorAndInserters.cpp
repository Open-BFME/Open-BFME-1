// Three unrelated bodies from the 0x005BFEE0 drawer, kept together because
// each is the only one of its shape in the range.
//
// ---- 0x005CEFC0, 77 bytes: A CONSTRUCTOR THAT ZEROES EVERYTHING.
//
//     mov eax,ecx / xor ecx,ecx
//     [eax+4]=[eax+8]=[eax+0xC]=0
//     [eax+0x28]=[eax+0x2C]=[eax+0x30]=0
//     [eax+0x1C]=[eax+0x20]=[eax+0x24]=0
//     [eax+0x10]=[eax+0x14]=[eax+0x18]=0
//     [eax+0x34]=0 / byte [eax+0x38]=0
//     [eax]=<VFTABLE>
//     [eax+0x3C]=[eax+0x40]=[eax+0x44]=[eax+0x48]=0
//     [eax+0x54]=[eax+0x58]=[eax+0x5C]=[eax+0x60]=0
//     ret
//
// The leading `mov eax,ecx` with every store going through eax is a
// constructor returning `this`, and the bare `ret` gives it no parameters.
//
// THE VFTABLE STORE SITS IN THE MIDDLE, and that is what reads out the
// hierarchy.  MSVC 7.1 emits a constructor as base constructors, then its own
// vptr stores, then its body.  Everything BEFORE the vptr store therefore
// belongs to a base whose constructor was inlined, and everything after it is
// this class's own body.  The base's vptr is never written, so the base is not
// polymorphic -- which is also why it sits at offset 4 rather than 0: MSVC
// puts the derived vptr first and a non-polymorphic base after it.
//
// THE STORE ORDER INSIDE THE BASE IS NOT ASCENDING -- 4, 0x28, 0x1C, 0x10 --
// and MSVC 7.1 does not reorder straight-line constant stores, so that IS the
// source order.  Member offsets, on the other hand, are fixed by DECLARATION
// order.  The two orders disagree, which rules out a member-initialiser list
// (those are emitted in declaration order regardless of how they are written)
// and leaves assignments in a constructor BODY, written in whatever order the
// author chose.  The four twelve-byte groups are four three-dword members;
// each group is ascending internally, so each is three separate assignments
// and not one chained one (a chained assignment writes descending).
//
// ---- 0x005C4690, 27 bytes: A CONSTRUCTOR THAT CALLS A PREDICATE.
//
//     mov eax,[esp+4] / push esi / mov esi,ecx / push eax / mov [esi],eax
//     call <REL32> / mov [esi+4],al / add esp,4 / mov eax,esi / pop esi / ret 4
//
// `ret 4`, `this` in ecx, `mov eax,esi` at the end: a one-parameter
// constructor.  The parameter is stored whole at offset 0 and ALSO pushed to a
// callee that the CALLER cleans up after (`add esp,4`), so that callee is
// __cdecl; only its `al` is kept and stored as a byte at offset 4, so it
// returns a one-byte type.  The store at 0 happens before the call and the
// store at 4 after it, in offset order, which is a member-initialiser list in
// declaration order.
//
// ---- 0x005C1BF0, 29 bytes: A RANGE INSERTER.
//
//     mov ecx,[esp+8] / mov eax,[ecx] / mov ecx,[ecx+4] / push esi
//     mov esi,[esp+8] / mov edx,[esi] / sub ecx,eax / push ecx / push eax
//     mov ecx,esi / call dword ptr [edx+0x10] / mov eax,esi / pop esi / ret
//
// __cdecl with two parameters, returning the first -- the same inserter shape
// as U1SinkInserters.cpp.  The second parameter holds TWO pointers, at 0 and
// 4; their DIFFERENCE is computed and passed alongside the first of them, so
// the pair is a begin/end range and the callee takes (begin, count).  `sub`
// with no scaling makes the element one byte wide.  The call is dispatched
// through the first parameter's vftable at displacement 0x10, so the sink is
// polymorphic and the method is SLOT 4.
//
// IDENTITY IS NOT RECOVERED.  The vftable dwords are DIR32 operands copied
// from retail and prove only that these are not each other; every name comes
// from a row or callee address.

// ------------------------------------------------------------ zeroing ctor

class U1Triple
{
public:
	int m_x;
	int m_y;
	int m_z;
};

class U1ZeroBase
{
public:
	U1ZeroBase();

	U1Triple m_a;
	U1Triple m_b;
	U1Triple m_c;
	U1Triple m_d;
	int m_e;
	char m_f;
};

// ??0U1ZeroBase@@QAE@XZ absent-from-retail
U1ZeroBase::U1ZeroBase()
{
	m_a.m_x = 0;
	m_a.m_y = 0;
	m_a.m_z = 0;
	m_d.m_x = 0;
	m_d.m_y = 0;
	m_d.m_z = 0;
	m_c.m_x = 0;
	m_c.m_y = 0;
	m_c.m_z = 0;
	m_b.m_x = 0;
	m_b.m_y = 0;
	m_b.m_z = 0;
	m_e = 0;
	m_f = 0;
}

class U1Zero_005CEFC0 : public U1ZeroBase
{
public:
	U1Zero_005CEFC0();
	virtual void slot0();

	int m_g0;
	int m_g1;
	int m_g2;
	int m_g3;
	char m_gap[ 8 ];
	int m_h0;
	int m_h1;
	int m_h2;
	int m_h3;
};

U1Zero_005CEFC0::U1Zero_005CEFC0()
{
	m_g0 = 0;
	m_g1 = 0;
	m_g2 = 0;
	m_g3 = 0;
	m_h0 = 0;
	m_h1 = 0;
	m_h2 = 0;
	m_h3 = 0;
}

// ----------------------------------------------------------- flagging ctor

bool u1Check_005C2CD0( void *p );

class U1Ctor_005C4690
{
public:
	U1Ctor_005C4690( void *p );

	void *m_pointer;
	bool m_checked;
};

U1Ctor_005C4690::U1Ctor_005C4690( void *p )
	: m_pointer( p ), m_checked( u1Check_005C2CD0( p ) )
{
}

// ----------------------------------------------------------- range inserter

class U1RangeSink
{
public:
	virtual void rangePad0();
	virtual void rangePad1();
	virtual void rangePad2();
	virtual void rangePad3();
	virtual void append( const char *begin, int count );
};

class U1Range
{
public:
	const char *m_begin;
	const char *m_end;
};

U1RangeSink *u1Insert_005C1BF0( U1RangeSink *sink, const U1Range *range )
{
	sink->append( range->m_begin, range->m_end - range->m_begin );
	return sink;
}

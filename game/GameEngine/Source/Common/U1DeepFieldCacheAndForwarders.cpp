// Four bodies from the 0x005BFEE0 drawer that read something out of a
// supplied object and put it somewhere, in two unrelated shapes that share a
// file only because they share a range.
//
// ---- SHAPE A: hand the argument to a member, then cache a field of it.
// 0x005C3590 and 0x005C35E0, 56 bytes each:
//
//     push esi / push edi / mov edi,[esp+0xc] / mov esi,ecx / push edi
//     lea ecx,[esi+<SUB>] / call <REL32>
//     mov eax,[edi] / test eax,eax / je none
//     mov eax,[eax+0xAC]
//     pop edi / mov [esi+<SLOT>],eax / pop esi / ret 4
//     none: xor eax,eax / pop edi / mov [esi+<SLOT>],eax / pop esi / ret 4
//
// __thiscall, one dword parameter, no return value.  The parameter is handed
// unchanged to a member subobject -- `lea ecx,[esi+SUB]` with no null test is
// a member, not a base -- whose method is a `call` and therefore only declared
// here.  Then the SAME parameter is dereferenced at offset 0 for a
// null-checked pointer and, when it survives, a dword at 0xAC of the pointee
// is read.  The value reaches the store in a register on both arms
// (`xor eax,eax`, never an immediate store), so this is one assignment fed by
// a conditional expression; MSVC 7.1 duplicates the store and epilogue into
// each arm rather than merging them.
//
// THE TWO ROWS DIFFER ONLY IN TWO DISPLACEMENTS, 0x170/0x17C and
// 0x160/0x16C, and the gap between them is constant at 0xC.  They call the
// same member method, which makes the member`s type shared; nothing says the
// two enclosing classes are related, so each keeps its own.
//
// ---- SHAPE B: forward every argument to a virtual and return the first.
// 0x005C1340, 42 bytes:
//
//     mov edx,[esp+0x18] / mov eax,[ecx] / push esi / mov esi,[esp+8]
//     push edx / (mov edx,[esp+0x1C] / push edx) x4 / push esi
//     call dword ptr [eax+0x18] / mov eax,esi / pop esi / ret 0x18
//
// `ret 0x18` pops six dwords and ecx is live on entry: __thiscall with six
// parameters.  Every one is re-pushed unchanged, last to first, so the callee
// receives exactly this function`s parameter list; the receiver is `this`
// itself, unmodified in ecx, and the vftable dword loaded at entry makes the
// call SLOT 6.  `mov eax,esi` returns the FIRST parameter -- the value in esi,
// which came from [esp+8] after the one push, i.e. the caller`s [esp+4].
//
// 0x005C0DA0, 47 bytes, is the same shape one slot earlier with a DOUBLE last
// parameter: `fld qword ptr [esp+0x18]` before any push reads eight bytes at
// the sixth and seventh dword slots, and `sub esp,8 / fstp qword ptr [esp]`
// pushes them back as one argument.  `ret 0x1C` pops seven dwords, which is
// five pointers plus that double, and the call goes to SLOT 5.  A float
// parameter would be four bytes on the stack and would not need the
// load-store pair at all.
//
// IDENTITY IS NOT RECOVERED.  No vftable in the ledger reaches these rows and
// no string names any field; every name comes from a row or callee address.

// ------------------------------------------------------------------ shape A

class U1Cached
{
public:
	char m_padAC[ 0xac ];
	void *m_fieldAC;
};

class U1CachedHolder
{
public:
	U1Cached *m_cached;
};

class U1Sub
{
public:
	void apply( U1CachedHolder *holder );
};

#define U1_CACHE_ROW( ROW, SUBOFF )                                           \
	class U1Cache_##ROW                                                       \
	{                                                                         \
	public:                                                                   \
		void update( U1CachedHolder *holder );                                \
                                                                              \
		char m_pad[ SUBOFF ];                                                 \
		U1Sub m_sub;                                                          \
		char m_gap[ 11 ];                                                     \
		void *m_cachedField;                                                  \
	};                                                                        \
	void U1Cache_##ROW::update( U1CachedHolder *holder )                      \
	{                                                                         \
		m_sub.apply( holder );                                                \
		U1Cached *cached = holder->m_cached;                                  \
		m_cachedField = cached ? cached->m_fieldAC : 0;                       \
	}

U1_CACHE_ROW( 005C3590, 0x170 )
U1_CACHE_ROW( 005C35E0, 0x160 )

// ------------------------------------------------------------------ shape B

class U1Fwd_005C1340
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6( void *a, void *b, void *c, void *d, void *e, void *f );

	void *forward( void *a, void *b, void *c, void *d, void *e, void *f );
};

void *U1Fwd_005C1340::forward( void *a, void *b, void *c, void *d, void *e, void *f )
{
	slot6( a, b, c, d, e, f );
	return a;
}

class U1Fwd_005C0DA0
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5( void *a, void *b, void *c, void *d, void *e, double g );

	void *forward( void *a, void *b, void *c, void *d, void *e, double g );
};

void *U1Fwd_005C0DA0::forward( void *a, void *b, void *c, void *d, void *e, double g )
{
	slot5( a, b, c, d, e, g );
	return a;
}

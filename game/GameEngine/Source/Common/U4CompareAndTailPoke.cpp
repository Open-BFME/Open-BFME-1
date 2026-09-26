// cl: /EHs-c-
//
// 0x00605320 (68 bytes) -- a two-key ordering predicate:
//
//     push esi / mov esi,[esp+0xC] / push edi / mov edi,[esp+0xC]
//     push esi / mov ecx,edi / call 0x00090570
//     test eax,eax / jge  / <return true>
//                    jle  / <return false>
//     fld [edi+8] / fcomp [esi+8] / fnstsw ax / test ah,5 / jp FALSE
//     <return true> / FALSE: <return false>
//     ret 8
//
// WHAT THE BYTES SHOW.  Two stack dwords, both used as object addresses, and
// `ret 8`; ecx is written before the call but never read on entry.  The callee
// is already in the ledger: `?compareNoCase@?$StringBase@D@@QBEHABV1@@Z` at
// 0x00090570, __thiscall on a `StringBase<char>` taking another by reference.
// Its receiver is the FIRST argument at offset ZERO and its parameter is the
// second at offset zero, so both objects begin with that string.
//
// THE THREE-WAY RESULT IS SPLIT THE WAY A SOURCE SPLITS IT: `jge` past a
// `return true` and then `jle` past a `return false` is `if (c < 0) return
// true; if (c > 0) return false;`, not a single signed compare -- one
// comparison producing two early returns leaves exactly this pair of tests.
// What remains is the tie-break, a float at +8 of each object: after `fcomp`,
// mask 5 keeps C0 (less) and C2 (unordered), so `jp` -- taken when NEITHER is
// set -- is the not-less branch, and the fallthrough is `a.f8 < b.f8`.
//
// The first two returns are written to `al` and the third to `eax`; both are
// how MSVC 7.1 materialises a `bool`, and the mix is the scheduler's.
//
// 0x006094C0 (25 bytes) -- a virtual call then a guarded tail call:
//
//     mov eax,[ecx] / push 0 / push 0 / call dword ptr [eax+0x30]
//     mov ecx,[<GLOBAL>] / test ecx,ecx / je OUT / jmp <POKE>
//     OUT: ret
//
// The vptr comes off `this`, so slot 0x30 -- vtable index twelve -- is the
// receiver's OWN virtual, called with two literal zeroes.  Then a global dword
// is loaded into ecx and, when non-null, JUMPED to: a __thiscall on the global
// with no arguments and nothing to do afterwards, which is a tail call in the
// source's last statement.  Nothing is popped, so the function itself takes no
// arguments.
//
// IDENTITY IS NOT RECOVERED.  Both hosts, the global and the poked entry are
// named after addresses; `StringBase<char>` is spelled the way the ledger
// already spells it so that the call resolves to the body retail links, and the
// `slotNN` declarations carry vtable positions and nothing else.

template < class T > class StringBase
{
public:
	int compareNoCase( const StringBase< T > &other ) const;
};

struct U4Item00605320
{
	StringBase< char > m_name;
	int m_f04;
	float m_f08;
};

bool __stdcall u4Less00605320( const U4Item00605320 &a, const U4Item00605320 &b )
{
	int order = a.m_name.compareNoCase( b.m_name );
	if ( order < 0 )
		return true;
	if ( order > 0 )
		return false;
	return a.m_f08 < b.m_f08;
}

class U4Global006094C0
{
public:
	void poke( void );
};
extern U4Global006094C0 *g_u4Global006094C0;

class U4Self006094C0
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0C();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1C();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2C();
	virtual void act( int a, int b );
	void run( void );
};

void U4Self006094C0::run( void )
{
	act( 0, 0 );
	if ( g_u4Global006094C0 != 0 )
		g_u4Global006094C0->poke();
}

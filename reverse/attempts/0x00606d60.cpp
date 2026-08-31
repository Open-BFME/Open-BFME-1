// ?firstNamed@U4Scan@@QBE_NPAXPBVU4Filter@@@Z
// partial score=0.96 date=2026-08-30
// Three 25-byte __thiscall forwarders that read TWO DWORDS FROM IN FRONT OF
// their own receiver and hand both on:
//
//     mov eax,[ecx-4] / mov ecx,[ecx-8] / add eax,0x250
//     push eax / mov eax,[esp+8] / push eax
//     call <SCAN> / ret 4
//
// WHAT THE BYTES SHOW.  The receiver is dereferenced at -4 and -8 and never at
// a non-negative offset, so `this` points INTO a larger object: the receiver is
// a member at offset 8 of a host whose first two dwords are what these bodies
// read.  Neither read is null-guarded, which is what `this`-relative arithmetic
// looks like -- the compiler knows `this` is not null.
//
// THE CALLEE FIXES THE REST.  Two of the three call
// Code/GameEngine/Source/Common/U4ElementScanLoops.cpp's scans, whose
// signatures are already read out of their own bytes: `firstFlagged(int *,
// const U4Filter *)` at 0x00606DC0 and `firstMapped(const U4MapKey &, const
// U4Filter *)` at 0x00607000, both __thiscall on a `U4Scan`.  So the dword at
// host+0 is a `U4Scan *` -- it goes into ecx -- and the dword at host+4 is a
// base pointer whose +0x250 is the filter, since that is the argument slot the
// scan reads a filter from.  The third row calls 0x00606D60 with the same two
// arguments in the same two slots and is pinned there.
//
// PUSH ORDER IS ARGUMENT ORDER: the filter is computed and pushed first and the
// forwarded parameter is loaded AFTER that push, from the slot the push moved
// it to, so the parameter is argument one and the filter argument two -- which
// is the order the scans declare.  That late load is also the tell that the
// host pointer is named TWICE in the source rather than held in one local:
// binding it once lets MSVC hoist the parameter load ahead of the pushes and
// costs a register, which is a three-byte-different body.
//
// `ret 4` against a callee that pops eight bytes balances because these
// forwarders pop only their own single argument; the callee's result is passed
// straight back in eax, so each is a plain `return`.
//
// IDENTITY IS NOT RECOVERED.  The three proxies are named after their
// addresses, and nothing here shows what the host is or what 0x250 means.

struct U4MapKey;
struct U4MapVal;

struct U4Elem
{
	char m_pad[0x28];
	void *m_named[0x1C8 / 4];
};

class U4Filter
{
public:
	bool accepts(const U4Elem *element) const;
};

// Defined at 0x00606DC0 and 0x00607000 in
// Code/GameEngine/Source/Common/U4ElementScanLoops.cpp; `firstNamed` is
// 0x00606D60, pinned in reverse/symbols.csv.  Declared and not included so that
// MSVC cannot inline them, which retail's `call` forbids.
class U4Scan
{
public:
	bool firstFlagged( int *out, const U4Filter *filter ) const;
	const U4MapVal *firstMapped( const U4MapKey &key, const U4Filter *filter ) const;
	const char *firstNamed( void *out, const U4Filter *filter ) const;

	int m_f00;
	int m_f04;
	U4Elem *m_begin;
	U4Elem *m_end;
};

const char *U4Scan::firstNamed( void *out, const U4Filter *filter ) const
{
	U4Elem *p = m_begin;
	U4Elem *e = m_end;
	unsigned int index = (unsigned int)out;
	for ( ; p != e; ++p )
	{
		if ( filter->accepts( p ) && p->m_named[index] != 0 )
			return ( (char *)p->m_named[index] ) + 4;
	}
	return 0;
}

struct U4ProxyHost
{
	U4Scan *m_scan;
	char *m_base;
};

#define U4_HOST( self ) ( (const U4ProxyHost *)( (const char *)( self ) - 8 ) )

class U4Proxy00606E20
{
public:
	bool run( void *out ) const;
};

bool U4Proxy00606E20::run( void *out ) const
{
	const U4Filter *filter = (const U4Filter *)( U4_HOST( this )->m_base + 0x250 );
	return U4_HOST( this )->m_scan->firstNamed( out, filter );
}

class U4Proxy00606E40
{
public:
	bool run( int *out ) const;
};

bool U4Proxy00606E40::run( int *out ) const
{
	const U4Filter *filter = (const U4Filter *)( U4_HOST( this )->m_base + 0x250 );
	return U4_HOST( this )->m_scan->firstFlagged( out, filter );
}

class U4Proxy00607070
{
public:
	const U4MapVal *run( const U4MapKey &key ) const;
};

const U4MapVal *U4Proxy00607070::run( const U4MapKey &key ) const
{
	const U4Filter *filter = (const U4Filter *)( U4_HOST( this )->m_base + 0x250 );
	return U4_HOST( this )->m_scan->firstMapped( key, filter );
}

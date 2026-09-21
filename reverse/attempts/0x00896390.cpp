// ?release@Gen00896390Owner@@QAEXPAX@Z
// partial score=0.29 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Address-derived: no owning class or method identity is proven. Structural
// evidence: this+4 is the SAME Gen_00896320 registry (m_count/pad/m_begin,
// retail 0x00896320) already landed as ::append in Gen00896320Append.cpp --
// this body rebases ecx by 4 and calls the same still-dump but pinned
// ::helper (retail 0x008961E0) on it. The array holds 4-byte pointer-sized
// items; the search loop compares each item against the caller's stack
// parameter by identity. On a hit, the parameter itself is decremented as a
// BfmeDropObjectA refcount (retail 0x00895260's own class, BfmeDtorVBW.cpp,
// m_refCount at +0, sizeof 0x18); on a miss, ::helper is asked to look up or
// materialise one via three stack-local out-params, and the result pointer
// is decremented instead. Either way, a refcount that reaches zero is
// destroyed and released through TheBfmeFree (retail global 0x01337830).

extern void ( __cdecl *TheBfmeFree )( void *storage, unsigned int size );

struct Gen00896320Item
{
	void *value;
};

class Gen_00896320
{
public:
	void append( void **source );
	void helper( void *first, void *last, void *result );

	unsigned m_count;
	char m_pad04[ 4 ];
	Gen00896320Item *m_begin;
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

	int m_refCount;
};

struct Gen00896390Owner
{
	void *m_unknown00;
	Gen_00896320 m_registry;			// +4

	void release( void *key );
};

void Gen00896390Owner::release( void *key )
{
	Gen00896320Item *begin = m_registry.m_begin;
	Gen00896320Item *end = &m_registry.m_begin[ m_registry.m_count ];

	Gen00896320Item *it;
	for ( it = begin; it != end; ++it )
	{
		if ( it->value == key )
			break;
	}

	BfmeDropObjectA *target;
	if ( it != end )
	{
		target = ( BfmeDropObjectA * )key;
	}
	else
	{
		BfmeDropObjectA buffer;
		struct { void *position; void *storage; } positionAndStorage = { end, &buffer };
		BfmeDropObjectA *result = 0;
		struct { void *hint; BfmeDropObjectA **resultSlot; } hintAndResult = { 0, &result };
		void *unused;
		m_registry.helper( &unused, &hintAndResult, &positionAndStorage );
		target = result;
	}

	if ( target != 0 )
	{
		if ( --target->m_refCount == 0 )
		{
			target->~BfmeDropObjectA();
			TheBfmeFree( target, 0x18 );
		}
	}
}

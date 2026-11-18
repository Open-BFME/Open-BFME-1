// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x005EE8A0 (285 bytes, ret 8): the module constructor that the
// new-plus-inline-ctor factory V3HostRva005E7420::create (0x005E7420,
// V3NewInlineCtorFactories.cpp) calls after allocating 0x5c bytes.
//
// Layout read off the stores: a primary base holding the owner at +4 (no
// vptr store of its own, hence novtable), BaseY005E7360Secondary at +8 and
// BaseY005E7360Pairs at +0xc with its eight zero-constructed value/frame
// pairs, as in BaseY005E7360Ctor.cpp; their vtables are the recorded
// 0x0110F978 and 0x011128D0. The complete object's three vptrs are the
// pinned bfmeVft0ZL/1ZL/2ZL already stamped by BfmeDerivedZL's copy
// constructor (BfmeConv1879.cpp), stored by hand because the class is
// novtable. The pairs are copied from the template, then the tail is Zero
// Hour's Particle alpha setup: value = key[0].value, target key 1, and
// computeAlphaRate's early-out on a zero frame. Names stay address-derived.

extern "C" void *bfmeVft0ZL[];
extern "C" void *bfmeVft1ZL[];
extern "C" void *bfmeVft2ZL[];

#include "../../../../Include/Common/ScalarTypes.h"


class __declspec(novtable) Rva005EE8A0Owner
{
public:
	Rva005EE8A0Owner( void *owner ) : m_owner( owner ) {}
	virtual void owned() = 0;
	void *m_owner;
};

class BaseY005E7360Secondary
{
public:
	virtual ~BaseY005E7360Secondary() {}
	virtual void secondary() {}
};

struct BaseY005E7360Pair
{
	BaseY005E7360Pair() : value( 0.0f ), pointer( 0 ) {}
	float value;
	void *pointer;
};

class BaseY005E7360Pairs
{
public:
	BaseY005E7360Pairs() {}
	virtual ~BaseY005E7360Pairs() {}
	virtual void pairs() {}
	BaseY005E7360Pair entries[ 8 ];
};

class V3HostRva005E7420
{
public:
	char m_padding[ 0x0c ];
	BaseY005E7360Pair m_entries[ 8 ];
};

class __declspec(novtable) Rva005EE8A0 : public Rva005EE8A0Owner,
	public BaseY005E7360Secondary, public BaseY005E7360Pairs
{
public:
	Rva005EE8A0( void *owner, V3HostRva005E7420 *host );
	virtual void owned() {}

	void computeRate()
	{
		if( (UnsignedInt)entries[ m_alphaTargetKey ].pointer == 0 )
		{
			m_alphaRate = 0.0f;
			return;
		}
		Real delta = entries[ m_alphaTargetKey ].value - m_alpha;
		UnsignedInt time = (UnsignedInt)entries[ m_alphaTargetKey ].pointer - (UnsignedInt)entries[ m_alphaTargetKey - 1 ].pointer;
		m_alphaRate = delta / time;
	}

	Real m_alpha;
	Real m_alphaRate;
	int m_alphaTargetKey;
};

Rva005EE8A0::Rva005EE8A0( void *owner, V3HostRva005E7420 *host )
	: Rva005EE8A0Owner( owner )
{
	((void **)this)[ 0 ] = bfmeVft0ZL;
	((void **)this)[ 2 ] = bfmeVft1ZL;
	((void **)this)[ 3 ] = bfmeVft2ZL;

	for( int index = 0; index < 8; ++index )
		entries[ index ] = host->m_entries[ index ];

	m_alpha = entries[ 0 ].value;
	m_alphaTargetKey = 1;
	computeRate();
}

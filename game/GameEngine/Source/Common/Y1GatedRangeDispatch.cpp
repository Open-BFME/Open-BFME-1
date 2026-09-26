// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Two __thiscall members of one class, 0x003D08F0 (137 bytes) and 0x003D09A0
// (120 bytes).  Both take one pointer, both decide the same way whether to run,
// and both then walk the object's pointer pair at +0x18/+0x1C calling one member
// on every element with that pointer as the argument.
//
//     bool ok = <first range test> && <second range test>;
//     if ( m_gate && <context says stop> )
//         return;
//     if ( !ok )
//         return;
//     for ( it = m_begin; it != m_end; ++it )
//         ( *it )->apply( arg );
//
// WHAT THE BYTES SHOW.  The two tests are member calls whose `this` is inside
// the argument's context object and whose two pushed arguments are the
// addresses of two of THIS object's sub-objects: +0x24 with +0x4C for the first
// and +0x74 with +0x80 for the second.  A pair of addresses handed to a
// predicate that answers AL is a range test; the class layout follows from the
// four `lea` displacements and nothing else.
//
// `mov bl,1` / `xor bl,bl` around the second test is the `&&`: the result is
// materialised into a byte BEFORE the gate is examined, so the source computed
// it into a variable rather than folding it into the following `if`.  Retail
// then reads the gate byte at +0x96, and only THEN looks at the saved result --
// the two conditions are separate statements in that order.
//
// THE ACCESSOR IS LOAD-BEARING (0x003D08F0).  That overload reaches its context
// through the argument's pointer at +8, and retail RE-READS that pointer for the
// second test -- it has to, since the first call could have changed it.  But it
// reads it BEFORE pushing the two addresses, both times.  Spelling the reads as
// `w->m_ctx` puts them after the pushes and turns the `lea` into an `add`;
// spelling them as an inline accessor `w->getCtx()` reproduces retail exactly,
// in both call sites at once.  One site could be luck, two is the source.
//
// THE TWO OVERLOADS SHARE A CLASS.  Same +0x18/+0x1C pair, same +0x24/+0x4C and
// +0x74/+0x80 sub-objects, same +0x96 gate byte.  What differs is the argument:
// one takes the context directly and reads a Bool out of it at +0x64, the other
// takes a wrapper and asks it a question through a call.
//
// THE CALLEES STAY DECLARATIONS.  Every one is a `call` in retail, so none was
// visible to the compiler here; each is named for the incremental-link thunk the
// call site encodes and pinned at that thunk in targets/game/reverse/symbols.csv.
//
// IDENTITY IS NOT RECOVERED.  No caller names either body, neither touches a
// string, and every callee is an unnamed body.  All names are address-derived.

// --- callees, declared only -------------------------------------------------
#include <bitset>

class Y1RangeContext;
class Y1RangeWrapper;

class Gen0003C2E5                       // first range test
{
public:
	bool test( void *low, void *high );
};

class Gen00008E68                       // second range test
{
public:
	bool test( void *low, void *high );
};

class Gen00025C75                       // element callee of 0x003D09A0
{
public:
	void apply( Y1RangeContext *context );
};

class Gen00006D20                       // element callee of 0x003D08F0
{
public:
	void apply( Y1RangeWrapper *wrapper );
};

class Gen00003B1B                       // the wrapper's stop question
{
public:
	bool check( int mode );
};

// --- the two argument shapes ------------------------------------------------
class Y1RangeContext
{
public:
	char m_lead[ 0x30 ];
	Gen0003C2E5 m_first;
	char m_mid[ 0x27 ];
	Gen00008E68 m_second;
	char m_tail[ 0x0B ];
	bool m_stop;
};

class Y1WrappedContext
{
public:
	char m_lead[ 0x90 ];
	Gen00008E68 m_second;
	char m_mid[ 0x7F ];
	Gen0003C2E5 m_first;
};

// The accessor is inlined at all four of its uses, so no body of it survives in
// retail and no row claims the COMDAT the compiler still emits for it.
// ?getContext@Y1RangeWrapper@@QBEPAVY1WrappedContext@@XZ absent-from-retail
class Y1RangeWrapper
{
public:
	char m_lead[ 8 ];
	Y1WrappedContext *m_context;

	Y1WrappedContext *getContext() const { return m_context; }
};

// --- the owner --------------------------------------------------------------
class Rva003D08F0
{
public:
	char m_lead[ 0x18 ];
	Gen00006D20 **m_begin;
	Gen00006D20 **m_end;
	char m_pad20[ 4 ];
	char m_lowA[ 0x28 ];
	char m_highA[ 0x28 ];
	char m_lowB[ 0x0C ];
	char m_highB[ 0x16 ];
	bool m_gate;

	void run( Y1RangeWrapper *wrapper );
	void run( Y1RangeContext *context );
};

bool Gen0003C2E5::test( void *low, void *high )
{
	_STL::bitset<304> tmp = *reinterpret_cast<const _STL::bitset<304> *>(this);
	tmp &= *reinterpret_cast<const _STL::bitset<304> *>(high);
	if (tmp.any())
		return false;

	tmp = *reinterpret_cast<const _STL::bitset<304> *>(this);
	tmp.flip();
	tmp &= *reinterpret_cast<const _STL::bitset<304> *>(low);
	if (tmp.any())
		return false;
	return true;
}

void Rva003D08F0::run( Y1RangeWrapper *wrapper )
{
	bool ok = wrapper->getContext()->m_first.test( m_lowA, m_highA )
			&& wrapper->getContext()->m_second.test( m_lowB, m_highB );

	if ( m_gate && ( (Gen00003B1B *)wrapper->getContext() )->check( 0 ) )
		return;

	if ( !ok )
		return;

	for ( Gen00006D20 **it = m_begin; it != m_end; ++it )
		( *it )->apply( wrapper );
}

void Rva003D08F0::run( Y1RangeContext *context )
{
	bool ok = context->m_first.test( m_lowA, m_highA )
			&& context->m_second.test( m_lowB, m_highB );

	if ( m_gate && context->m_stop )
		return;

	if ( !ok )
		return;

	for ( Gen00025C75 **it = (Gen00025C75 **)m_begin; it != (Gen00025C75 **)m_end; ++it )
		( *it )->apply( context );
}

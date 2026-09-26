// ?drop@Gen003C8A50@@QAEXPAVGen003C8A50Result@@@Z
// partial score=0.955 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// PROGRESS 2026-09-20 (opus): 657B/396-diff -> 673B(size-exact)/30-diff.
// Closed the 16-byte gap and the "second notification EDX/EAX + omitted stack
// store" blocker that stalled seven prior sessions.  Two levers:
//   1) Gen003C8A50Result::m_name lives at +0x28, and the second Flareup payload
//      is spelled (int)&found->m_name (NOT (int)found+0x28).  Retail spills that
//      pointer (mov [esp+0x2c],eax at +009c) because it is a common subexpression
//      with the later found->m_name.compare() receiver; the CSE both forces EAX
//      (materialized before the constant 1) and emits the spill store.  This is
//      the retail stack store the bank omitted.
//   2) The third loop's guard must load holder->m_end into a register the same
//      way the back-edge does.  Caching it in a local (last = holder->m_end;
//      if(it!=last){do..while}) makes the guard `mov eax,[ebp+34]; cmp ebx,eax`
//      which lets MSVC emit a 16-byte-aligned rotated loop pre-header
//      (jmp 0xd0 + npad).  That alignment pre-header IS the bulk of the 16 bytes.
// RESIDUE (30 bytes, not reached): a frame-slot COLORING swap -- the holder
// preserve slot and the inlined invoke `b` temp are transposed (ours _holder$=-56
// / $T1179=-52; retail wants them swapped) -- plus the downstream scratch-register
// naming in the Evenglow notify0C/notify04 calls (payload EAX vs our ECX, key-addr
// ECX vs our EDX) and the 2-instruction compare self-address reg (EDX vs EAX,
// reconverges immediately).  The EDX/EAX scratch choice for the FOUND call was
// reachable (fixed via CSE, lever 1); the Evenglow-cluster scratch naming
// cascades from the coloring swap and did not yield to inline/no-local/frame/
// register/loop shape sweeps.
void * __cdecl operator new( unsigned int size );
void __cdecl f_00881eb0( void *block );
class BfmeReportWeightScaleHolder
{
public:
	static const float value;
};

const float BfmeReportWeightScaleHolder::value = 30.0f;

// Two __thiscall members that look one object up through a stored owner and
// then read a flag out of whatever comes back:
//
//     mov eax,ecx / mov ecx,[eax+0x28] / test ecx,ecx / jz .fail
//     add eax,0x30 / push eax / call <REL32>        ; manager->rva003C8A50(...)
//     test eax,eax / jz .fail
//     <read a field of the result> / ret
//   .fail: xor <ret>,<ret> / ret
//
// WHAT THE BYTES SHOW.  `mov eax,ecx` first and then EVERY later use of `this`
// through eax means the receiver register had to be freed for the call: the
// dword at +0x28 becomes ecx, so it is the __thiscall RECEIVER, and the single
// pushed argument is `this+0x30`, an interior address rather than a value.  The
// callee pops it (no `add esp,4`), so it is __thiscall too.  Both the receiver
// and the result are null-tested before use, so both are pointers.
//
// ONE CALLEE, ONE RESULT TYPE.  Both rows reach 0x003C8A50 through the same
// incremental-link thunk, so the thing it returns is ONE class with two flags
// read here, not two classes: a bool at +0x50 and a bool at +0x84.  A third body
// at 0x003BDF70 makes the same call and reads two pointer pairs at +0x54/+0x58
// and +0x60/+0x64 out of the same result; its guard and call reproduce exactly
// but the scheduler pairs its two pointer differences the other way round in
// every spelling tried, so it is NOT claimed here.
//
// FIELD WIDTH IS READ FROM THE OPCODES.  `mov al,[eax+K]` then a bare `ret`
// returns the byte unchanged -- no `setne`, no `movzx` -- so the field and the
// return type are the same one-byte type.
//
// The lookup identity is now closed by the LivingWorldRegionManager constructor
// and vtable chain and by the LivingWorldRegion allocation/constructor chain.
// The three enclosing row owners remain address-derived where named that way.

#include "ascii_string.h"

class LivingWorldRegion
{
public:
	char   m_pad00[ 0x50 ];
	bool   m_at50;
	char   m_pad51[ 0x2F ];
	int    m_at80;
	bool   m_at84;
};

class LivingWorldRegionManager
{
public:
	LivingWorldRegion *rva003C8A50( const AsciiString &key );
};

class Rva003BAD00Owner
{
public:
	void notify0C( const AsciiString &key, int payload, int b );
	void notify04( const AsciiString &key, int a );
};

// The owner of the separate drop operation is not established by this
// correction; retain its existing address-derived ABI without aliasing lookup.
class Gen003C8A50Result;
class Gen003C8A50Inner;

class Gen003C8A50Holder
{
public:
	char m_pad00[ 0x30 ];
	Gen003C8A50Inner **m_begin;
	Gen003C8A50Inner **m_end;
	char m_pad38[ 0x8 ];
	Rva003BAD00Owner m_owner;
};

class Gen003C8A50
{
public:
	void drop( Gen003C8A50Result *found );

private:
	void *m_vtable;
	Gen003C8A50Holder *m_holder;
};

class Gen003C8A50Inner
{
public:
	char m_pad00[ 0x28 ];
	AsciiString m_name;
	char m_pad2C[ 0x88 ];
	void *m_atB4;
};

class Gen003C8A50Result
{
public:
	char m_pad00[ 0x28 ];
	AsciiString m_name;
};

struct Gen003C8A50HookSlot
{
	int (__cdecl *m_hook)( void *, void *, __int64 );
	int (__cdecl *m_alt)( void *, void *, __int64 );
	char m_pad08[ 0x80 ];
	void *m_a;
	void *m_b;
};

extern Gen003C8A50HookSlot g_Gen003C8A50Hook;

class Obf003C87A0
{
public:
	Obf003C87A0( int *a, int *b );
	unsigned int m_bits[ 8 ];
};

int __cdecl Gen003C78B0( int a, int b );

typedef int (__cdecl *Gen003C8A50Hook)( void *, void *, __int64 );

static __forceinline int invokeGen003C8A50( int a, int b )
{
	Gen003C8A50Hook hook = g_Gen003C8A50Hook.m_hook;
	if( hook )
		goto hot;
	if( g_Gen003C8A50Hook.m_alt )
	{
hot:
		void *pa = g_Gen003C8A50Hook.m_a;
		void *pb = g_Gen003C8A50Hook.m_b;
		Obf003C87A0 state( &a, &b );
		return hook( pa, pb, (__int64)(int)&state );
	}
	return Gen003C78B0( a, b );
}

void Gen003C8A50::drop( Gen003C8A50Result *found )
{
	Gen003C8A50Holder *holder = m_holder;
	Gen003C8A50Inner **it = holder->m_begin;
	Gen003C8A50Inner **last = holder->m_end;
	Rva003BAD00Owner *owner = &holder->m_owner;

	if( it != last )
		{
			do
		{
			owner->notify0C( AsciiString( "ConqueredEffectFlareup" ),
				(int)((char *)*it + 0x28), 0 );
			++it;
		} while( it != holder->m_end );
	}

	owner->notify0C( AsciiString( "ConqueredEffectFlareup" ),
		(int)&found->m_name, 1 );

	it = holder->m_begin;
	last = holder->m_end;
	if( it != last )
	{
		do
		{
			int fn = (int)(*it)->m_atB4;
			int result = invokeGen003C8A50( fn, fn );
			if( result == 1 )
			{
				if( found->m_name.compare( (*it)->m_name ) != 0 )
				{
					owner->notify0C( AsciiString( "ConqueredEffectEvenglow" ),
						(int)((char *)*it + 0x28), 1 );
					continue;
				}
			}
			owner->notify0C( AsciiString( "ConqueredEffectEvenglow" ),
				(int)((char *)*it + 0x28), 0 );
		} while( ++it, it != holder->m_end );
	}

	owner->notify04( AsciiString( "ConqueredEffectFlareup" ), 1 );
	owner->notify04( AsciiString( "ConqueredEffectEvenglow" ), 1 );
}

class Glo012F4B98Type
{
public:
	void report( int count, float weight );

private:
	struct Report
	{
		Report( int count, float weight ) :
			m_weight( static_cast< int >( weight * BfmeReportWeightScaleHolder::value ) ),
			m_count( count )
		{
		}

		int m_weight;
		int m_count;
	};

	char    m_pad00[ 0x4CC ];
	Report *m_report;
};

extern Glo012F4B98Type * Glo012F4B98;

#define BFME_GUARDED_LOOKUP_FLAG( NAME, FIELD )                           \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		bool flag();                                                      \
		char          m_pad00[ 0x28 ];                                    \
		LivingWorldRegionManager * m_at28;                                \
		char          m_pad2C[ 0x4 ];                                     \
		AsciiString   m_at30;                                             \
	};                                                                    \
	bool NAME::flag()                                                     \
	{                                                                     \
		if( m_at28 )                                                      \
		{                                                                 \
			LivingWorldRegion *found = m_at28->rva003C8A50( m_at30 );     \
			if( found )                                                   \
				return found->FIELD;                                      \
		}                                                                 \
		return false;                                                     \
	}

BFME_GUARDED_LOOKUP_FLAG( Rva003BCB00, m_at84 )
BFME_GUARDED_LOOKUP_FLAG( Rva003BCD40, m_at50 )

// ------------------------------------------------- same lookup, no owner guard
// 0x003BCA90 makes the SAME call on the SAME member -- `mov ecx,[edi+0x28]` and
// `lea eax,[edi+0x30]` -- but never null-tests the owner, so the guard above is
// a property of those two rows and not of the lookup.  It reads a THIRD field of
// the result, `mov esi,[esi+0x80]` guarded by `jle`, a SIGNED test, so that one
// is an int.  The constant it then pushes, 0x40E00000, is the bit pattern of
// 7.0f pushed as an immediate, which is how MSVC 7.1 passes a float literal.

class Rva003BCA90
{
public:
	void run();
	char          m_pad00[ 0x28 ];
	LivingWorldRegionManager * m_at28;
	char          m_pad2C[ 0x4 ];
	AsciiString   m_at30;
};
void Rva003BCA90::run()
{
	LivingWorldRegion *found = m_at28->rva003C8A50( m_at30 );
	if( !found )
		return;
	((Gen003C8A50 *)m_at28)->drop( (Gen003C8A50Result *)found );
	int count = found->m_at80;
	if( count <= 0 )
		return;
	Glo012F4B98->report( count, 7.0f );
}

void Glo012F4B98Type::report( int count, float weight )
{
	Report *report = new Report( count, weight );

	if( report != m_report )
	{
		f_00881eb0( m_report );
		m_report = report;
	}
}

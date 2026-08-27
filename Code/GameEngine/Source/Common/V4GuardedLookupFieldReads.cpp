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
//     add eax,0x30 / push eax / call <REL32>        ; owner->find( &this->m_at30 )
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
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pin is address-derived and additive.

class Gen003C8A50Result
{
public:
	char   m_pad00[ 0x50 ];
	bool   m_at50;
	char   m_pad51[ 0x2F ];
	int    m_at80;
	bool   m_at84;
};

class Gen003C8A50
{
public:
	Gen003C8A50Result * find( const char * key );
	void                drop( Gen003C8A50Result * found );
};

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
		Gen003C8A50 * m_at28;                                             \
		char          m_pad2C[ 0x4 ];                                     \
		char          m_at30;                                             \
	};                                                                    \
	bool NAME::flag()                                                     \
	{                                                                     \
		if( m_at28 )                                                      \
		{                                                                 \
			Gen003C8A50Result *found = m_at28->find( &m_at30 );           \
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
	Gen003C8A50 * m_at28;
	char          m_pad2C[ 0x4 ];
	char          m_at30;
};
void Rva003BCA90::run()
{
	Gen003C8A50Result *found = m_at28->find( &m_at30 );
	if( !found )
		return;
	m_at28->drop( found );
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

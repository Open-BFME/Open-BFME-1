// Six more bodies of the shape already landed in Q3SelectorRecordReaders.cpp:
// reserve one dword of stack, store zero into it, immediately overwrite it from
// a register, read it back, mask to two bits, and use that to pick one entry
// out of each of two parallel five-dword arrays inside a static record.
//
//     push ecx / mov dword ptr [esp],0
//     mov  dword ptr [esp],ebp          <-- THE SELECTOR, and it is new
//     mov  eax,[esp] / and eax,3
//     *param0 = record.m_second[eax]
//     *param1 = record.m_first[eax]
//
// WHAT IS NEW HERE.  The existing file records two selectors, `mov [esp],esp`
// (89 24 24) and `rdtsc` + `mov [esp],eax`.  These six are a THIRD: 89 2C 24,
// `mov [esp],ebp`.  The reg field is the only byte that differs from the
// stack-pointer spelling, and ebp is never written anywhere in these functions,
// so whatever ends up in the slot is whatever the caller happened to leave in
// that register.  The dead zero-store survives in all three variants, which is
// what says the source initialises the local, assigns to it, and reads it back
// instead of using the register value directly.
//
// The one-instruction `__asm` is the same concession the sibling file documents
// and for the same reason: there is no C++ spelling of "the current value of
// ebp", and the surrounding body is ordinary C++.
//
// ONE AXIS: the record address.  Six bodies, six DISTINCT records, the two
// loads in each exactly 0x14 apart, so the record layout is the sibling file's
// -- two parallel five-entry dword arrays, the second at +0x14, only the first
// four entries of each reachable through `and eax,3`.  Six distinct addresses
// at one site means six distinct objects; collapsing them would still gate
// green and still be wrong.
//
// Constructor users identify shared records as integer keys and seeds.
// The record and function names retain their address tokens.

struct R3SelectorRecord
{
	int *m_first[ 5 ];
	int *m_second[ 5 ];
};

struct BigObfSelectorRecord
{
	unsigned int m_key[ 5 ];
	unsigned int m_seed[ 5 ];
};

#define BFME_SELECT_BY_FRAME_REGISTER_RECORD( NAME, RECORD, TYPE, FIRST, SECOND )                 \
	extern TYPE RECORD;                                                                              \
	void NAME( int **outSecond, int **outFirst )                              \
	{                                                                         \
		unsigned int selector = 0;                                            \
		__asm { mov selector, ebp }                                           \
		unsigned int index = selector & 3;                                    \
		*outSecond = reinterpret_cast<int *>( RECORD.SECOND[ index ] );                                 \
		*outFirst = reinterpret_cast<int *>( RECORD.FIRST[ index ] );                                   \
	}

#define BFME_SELECT_BY_FRAME_REGISTER( NAME, RECORD ) \
	BFME_SELECT_BY_FRAME_REGISTER_RECORD( NAME, RECORD, R3SelectorRecord, m_first, m_second )
#define BFME_SELECT_BIG_BY_FRAME_REGISTER( NAME, RECORD ) \
	BFME_SELECT_BY_FRAME_REGISTER_RECORD( NAME, RECORD, BigObfSelectorRecord, m_key, m_seed )

BFME_SELECT_BY_FRAME_REGISTER( Rva00072B40, g_r3Record012A72DC )
BFME_SELECT_BY_FRAME_REGISTER( Rva00072BC0, g_r3Record012A732C )
BFME_SELECT_BIG_BY_FRAME_REGISTER( Rva005263F0, g_ObfRecord012B7710 )
BFME_SELECT_BIG_BY_FRAME_REGISTER( Rva00526470, g_ObfRecord012B7760 )
BFME_SELECT_BY_FRAME_REGISTER( Rva0058F570, g_r3Record012B82C4 )
BFME_SELECT_BY_FRAME_REGISTER( Rva0058F5B0, g_r3Record012B82EC )

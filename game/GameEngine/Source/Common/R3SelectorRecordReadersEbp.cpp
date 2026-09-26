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
// IDENTITY IS NOT RECOVERED.  Names are addresses.  The DIR32 operands are
// filled from retail and are not evidence, and nothing here says what the
// entries mean or why a leftover register value is being used as a selector.

struct R3SelectorRecord
{
	int *m_first[ 5 ];
	int *m_second[ 5 ];
};

#define BFME_SELECT_BY_FRAME_REGISTER( NAME, RECORD )                         \
	extern R3SelectorRecord RECORD;                                           \
	void NAME( int **outSecond, int **outFirst )                              \
	{                                                                         \
		unsigned int selector = 0;                                            \
		__asm { mov selector, ebp }                                           \
		unsigned int index = selector & 3;                                    \
		*outSecond = RECORD.m_second[ index ];                                \
		*outFirst = RECORD.m_first[ index ];                                  \
	}

BFME_SELECT_BY_FRAME_REGISTER( Rva00072B40, g_r3Record012A72DC )
BFME_SELECT_BY_FRAME_REGISTER( Rva00072BC0, g_r3Record012A732C )
BFME_SELECT_BY_FRAME_REGISTER( Rva005263F0, g_r3Record012B7710 )
BFME_SELECT_BY_FRAME_REGISTER( Rva00526470, g_r3Record012B7760 )
BFME_SELECT_BY_FRAME_REGISTER( Rva0058F570, g_r3Record012B82C4 )
BFME_SELECT_BY_FRAME_REGISTER( Rva0058F5B0, g_r3Record012B82EC )

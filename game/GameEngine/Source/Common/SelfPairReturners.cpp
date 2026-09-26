// Fifty-nine 28-byte bodies that return a two-field structure by value: the
// result of one call, paired with `this`.
//
//     mov eax,[esp+8] / push esi / push eax / mov esi,ecx / call <REL32>
//     mov ecx,[esp+8] / mov [ecx],eax / mov [ecx+4],esi / mov eax,ecx
//     pop esi / ret 8
//
// WHAT THE BYTES SHOW.  `ret 8` with `this` in ecx is __thiscall with two stack
// dwords, and the second of them is written through as a pair of fields and
// then returned in eax -- the MSVC hidden return pointer.  The arithmetic is
// what proves which is which: after `push esi` and `push eax` the frame is
// eight bytes deeper, yet `mov ecx,[esp+8]` reads the hidden pointer, so the
// intervening call must have popped four bytes of its own.  That makes the
// REL32 callee __thiscall on the same `this` with exactly one stack argument --
// the caller's own second argument, loaded into eax before the frame moves.
//
// An 8-byte plain-old-data pair returns in edx:eax, so a hidden return pointer
// proves the returned type is NOT pod; and the two stores into the return slot
// mean the result is CONSTRUCTED THERE rather than copied from a local (see
// SentinelPairReturners.cpp for the same distinction measured).
//
// THE ONLY AXIS IS THE REL32 TARGET.  Fifty-nine members, twenty-four distinct
// callees, every other byte identical.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

struct SelfPair
{
	SelfPair( void *value, void *owner ) : m_value( value ), m_owner( owner ) {}
	void *m_value;
	void *m_owner;
};

#define BFME_SELF_PAIR_CALLEE( ADDR )                                         \
	class Gen##ADDR                                                           \
	{                                                                         \
	public:                                                                   \
		void *evaluate( void *argument );                                     \
	};

#define BFME_SELF_PAIR_MAKER( NAME, CALLEE )                                  \
	class NAME : public CALLEE                                                \
	{                                                                         \
	public:                                                                   \
		SelfPair make( void *argument );                                      \
	};                                                                        \
	SelfPair NAME::make( void *argument )                                     \
	{                                                                         \
		return SelfPair( evaluate( argument ), this );                        \
	}


BFME_SELF_PAIR_CALLEE( 000D7180 )
BFME_SELF_PAIR_CALLEE( 000D7250 )
BFME_SELF_PAIR_CALLEE( 000F2010 )
BFME_SELF_PAIR_CALLEE( 001366A0 )
BFME_SELF_PAIR_CALLEE( 0038BF10 )
BFME_SELF_PAIR_CALLEE( 004246F0 )
BFME_SELF_PAIR_CALLEE( 00460B30 )
BFME_SELF_PAIR_CALLEE( 00460C00 )
BFME_SELF_PAIR_CALLEE( 00460CD0 )
BFME_SELF_PAIR_CALLEE( 0046A130 )
BFME_SELF_PAIR_CALLEE( 0046A200 )
BFME_SELF_PAIR_CALLEE( 0046A2D0 )
BFME_SELF_PAIR_CALLEE( 0046A3A0 )
BFME_SELF_PAIR_CALLEE( 0046A470 )
BFME_SELF_PAIR_CALLEE( 0046A540 )
BFME_SELF_PAIR_CALLEE( 0046A610 )
BFME_SELF_PAIR_CALLEE( 00583580 )
BFME_SELF_PAIR_CALLEE( 00613AE0 )
BFME_SELF_PAIR_CALLEE( 00613BB0 )
BFME_SELF_PAIR_CALLEE( 006931A0 )
BFME_SELF_PAIR_CALLEE( 0069CBC0 )
BFME_SELF_PAIR_CALLEE( 006A7F80 )
BFME_SELF_PAIR_CALLEE( 006A8050 )
BFME_SELF_PAIR_CALLEE( 009D76F0 )

BFME_SELF_PAIR_MAKER( Rva000D8600Maker, Gen000D7180 )
BFME_SELF_PAIR_MAKER( Rva000D8630Maker, Gen000D7180 )
BFME_SELF_PAIR_MAKER( Rva000D8660Maker, Gen000D7250 )
BFME_SELF_PAIR_MAKER( Rva000D9750Maker, Gen000D7180 )
BFME_SELF_PAIR_MAKER( Rva000D9780Maker, Gen000D7180 )
BFME_SELF_PAIR_MAKER( Rva000F3BA0Maker, Gen000F2010 )
BFME_SELF_PAIR_MAKER( Rva000F3BD0Maker, Gen000F2010 )
BFME_SELF_PAIR_MAKER( Rva000F69B0Maker, Gen000F2010 )
BFME_SELF_PAIR_MAKER( Rva000F69E0Maker, Gen000F2010 )
BFME_SELF_PAIR_MAKER( Rva001372B0Maker, Gen001366A0 )
BFME_SELF_PAIR_MAKER( Rva001372E0Maker, Gen001366A0 )
BFME_SELF_PAIR_MAKER( Rva001376F0Maker, Gen001366A0 )
BFME_SELF_PAIR_MAKER( Rva00137720Maker, Gen001366A0 )
BFME_SELF_PAIR_MAKER( Rva0038EFC0Maker, Gen0038BF10 )
BFME_SELF_PAIR_MAKER( Rva0038EFF0Maker, Gen0038BF10 )
BFME_SELF_PAIR_MAKER( Rva00390720Maker, Gen0038BF10 )
BFME_SELF_PAIR_MAKER( Rva00424EF0Maker, Gen004246F0 )
BFME_SELF_PAIR_MAKER( Rva00424F20Maker, Gen004246F0 )
BFME_SELF_PAIR_MAKER( Rva00425160Maker, Gen004246F0 )
BFME_SELF_PAIR_MAKER( Rva00425190Maker, Gen004246F0 )
BFME_SELF_PAIR_MAKER( Rva004614E0Maker, Gen00460B30 )
BFME_SELF_PAIR_MAKER( Rva00461510Maker, Gen00460C00 )
BFME_SELF_PAIR_MAKER( Rva00461540Maker, Gen00460CD0 )
BFME_SELF_PAIR_MAKER( Rva004619D0Maker, Gen00460B30 )
BFME_SELF_PAIR_MAKER( Rva00461BC0Maker, Gen00460C00 )
BFME_SELF_PAIR_MAKER( Rva00461DD0Maker, Gen00460CD0 )
BFME_SELF_PAIR_MAKER( Rva0046AFB0Maker, Gen0046A130 )
BFME_SELF_PAIR_MAKER( Rva0046AFE0Maker, Gen0046A200 )
BFME_SELF_PAIR_MAKER( Rva0046B010Maker, Gen0046A2D0 )
BFME_SELF_PAIR_MAKER( Rva0046B040Maker, Gen0046A3A0 )
BFME_SELF_PAIR_MAKER( Rva0046B070Maker, Gen0046A470 )
BFME_SELF_PAIR_MAKER( Rva0046B0A0Maker, Gen0046A470 )
BFME_SELF_PAIR_MAKER( Rva0046B0D0Maker, Gen0046A540 )
BFME_SELF_PAIR_MAKER( Rva0046B100Maker, Gen0046A610 )
BFME_SELF_PAIR_MAKER( Rva0046B130Maker, Gen0046A610 )
BFME_SELF_PAIR_MAKER( Rva0046B3D0Maker, Gen0046A130 )
BFME_SELF_PAIR_MAKER( Rva0046B400Maker, Gen0046A200 )
BFME_SELF_PAIR_MAKER( Rva0046B430Maker, Gen0046A2D0 )
BFME_SELF_PAIR_MAKER( Rva0046B460Maker, Gen0046A3A0 )
BFME_SELF_PAIR_MAKER( Rva0046B630Maker, Gen0046A470 )
BFME_SELF_PAIR_MAKER( Rva0046B720Maker, Gen0046A540 )
BFME_SELF_PAIR_MAKER( Rva0046B810Maker, Gen0046A610 )
BFME_SELF_PAIR_MAKER( Rva00583BC0Maker, Gen00583580 )
BFME_SELF_PAIR_MAKER( Rva00583CA0Maker, Gen00583580 )
BFME_SELF_PAIR_MAKER( Rva006144D0Maker, Gen00613AE0 )
BFME_SELF_PAIR_MAKER( Rva00614500Maker, Gen00613BB0 )
BFME_SELF_PAIR_MAKER( Rva006147E0Maker, Gen00613AE0 )
BFME_SELF_PAIR_MAKER( Rva006148C0Maker, Gen00613BB0 )
BFME_SELF_PAIR_MAKER( Rva00693660Maker, Gen006931A0 )
BFME_SELF_PAIR_MAKER( Rva00693850Maker, Gen006931A0 )
BFME_SELF_PAIR_MAKER( Rva0069ED40Maker, Gen0069CBC0 )
BFME_SELF_PAIR_MAKER( Rva006A0F50Maker, Gen0069CBC0 )
BFME_SELF_PAIR_MAKER( Rva006AB600Maker, Gen006A7F80 )
BFME_SELF_PAIR_MAKER( Rva006AB630Maker, Gen006A7F80 )
BFME_SELF_PAIR_MAKER( Rva006AB680Maker, Gen006A8050 )
BFME_SELF_PAIR_MAKER( Rva006AC3E0Maker, Gen006A7F80 )
BFME_SELF_PAIR_MAKER( Rva006AC410Maker, Gen006A7F80 )
BFME_SELF_PAIR_MAKER( Rva006AC5A0Maker, Gen006A8050 )
BFME_SELF_PAIR_MAKER( Rva009D7A40Maker, Gen009D76F0 )

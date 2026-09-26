// Sixteen 16-byte __thiscall members that make two no-argument member calls on
// the same object, the second of them a tail call.
//
//     push esi / mov esi,ecx / call <REL32> / mov ecx,esi / pop esi / jmp <REL32>
//
// WHAT THE BYTES SHOW.  ecx is read once and the body ends in a `jmp`, not a
// `ret`, so nothing is popped: __thiscall with no arguments and a void result.
// `this` is parked in esi across the first call and restored into ecx for the
// second, and neither call adjusts esp, so BOTH callees are no-argument
// __thiscall members entered with the SAME unadjusted `this`.  The tail jump is
// the compiler's own: a void __thiscall call in tail position needs no frame.
//
// TWO EMPTY BASE CLASSES DO NOT WORK.  Spelling the two callees as members of
// two separate empty bases compiles to `lea ecx,[esi+1]` for the second -- MSVC
// 7.1 gives the second empty base offset 1 -- and the bytes reject it.  Both
// callees must be reachable at offset 0, which is exactly what the retail
// `mov ecx,esi` says, so each distinct PAIR of targets is spelled as one class
// declaring both members.  That asserts only what the bytes assert: the two
// callees are members of one class reached through the same `this`.
//
// THE ONLY AXIS IS THE PAIR OF REL32 TARGETS: sixteen members over 16
// distinct pairs.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_TAIL_PAIR_CALLEES( FIRST, SECOND )                              \
	class Gen##FIRST##_##SECOND                                              \
	{                                                                        \
	public:                                                                  \
		void gen##FIRST();                                                   \
		void gen##SECOND();                                                  \
	};

#define BFME_TAIL_PAIR_FORWARDER( NAME, PAIR, FIRST, SECOND )                \
	class NAME : public PAIR                                                 \
	{                                                                        \
	public:                                                                  \
		void invoke();                                                       \
	};                                                                       \
	void NAME::invoke()                                                      \
	{                                                                        \
		gen##FIRST();                                                        \
		gen##SECOND();                                                       \
	}

BFME_TAIL_PAIR_CALLEES( 00087C30, 00088480 )
BFME_TAIL_PAIR_CALLEES( 000889A0, 00089450 )
BFME_TAIL_PAIR_CALLEES( 0013AE00, 0013A820 )
BFME_TAIL_PAIR_CALLEES( 00206CB0, 002B2070 )
BFME_TAIL_PAIR_CALLEES( 002B2070, 00299BB0 )
BFME_TAIL_PAIR_CALLEES( 0045A970, 00723FB0 )
BFME_TAIL_PAIR_CALLEES( 005A3160, 006BB540 )
BFME_TAIL_PAIR_CALLEES( 005A40E0, 005A3FD0 )
BFME_TAIL_PAIR_CALLEES( 0060BC50, 0061D140 )
BFME_TAIL_PAIR_CALLEES( 0060BD30, 0061D150 )
BFME_TAIL_PAIR_CALLEES( 0060BF50, 0061D140 )
BFME_TAIL_PAIR_CALLEES( 0060C030, 0061D150 )
BFME_TAIL_PAIR_CALLEES( 0075C940, 0077FD80 )
BFME_TAIL_PAIR_CALLEES( 00783F60, 00466610 )
BFME_TAIL_PAIR_CALLEES( 00789440, 0046C5F0 )
BFME_TAIL_PAIR_CALLEES( 009A4D60, 0081C330 )

BFME_TAIL_PAIR_FORWARDER( Rva00088980TailPairForwarder, Gen00087C30_00088480, 00087C30, 00088480 )
BFME_TAIL_PAIR_FORWARDER( Rva00089A20TailPairForwarder, Gen000889A0_00089450, 000889A0, 00089450 )
BFME_TAIL_PAIR_FORWARDER( Rva0013B970TailPairForwarder, Gen0013AE00_0013A820, 0013AE00, 0013A820 )
BFME_TAIL_PAIR_FORWARDER( Rva002071E0TailPairForwarder, Gen00206CB0_002B2070, 00206CB0, 002B2070 )
BFME_TAIL_PAIR_FORWARDER( Rva00299D80TailPairForwarder, Gen002B2070_00299BB0, 002B2070, 00299BB0 )
BFME_TAIL_PAIR_FORWARDER( Rva005A4210TailPairForwarder, Gen005A40E0_005A3FD0, 005A40E0, 005A3FD0 )
BFME_TAIL_PAIR_FORWARDER( Rva0060BE70TailPairForwarder, Gen0060BC50_0061D140, 0060BC50, 0061D140 )
BFME_TAIL_PAIR_FORWARDER( Rva0060BE90TailPairForwarder, Gen0060BD30_0061D150, 0060BD30, 0061D150 )
BFME_TAIL_PAIR_FORWARDER( Rva0060C140TailPairForwarder, Gen0060BF50_0061D140, 0060BF50, 0061D140 )
BFME_TAIL_PAIR_FORWARDER( Rva0060C160TailPairForwarder, Gen0060C030_0061D150, 0060C030, 0061D150 )
BFME_TAIL_PAIR_FORWARDER( Rva006BB680TailPairForwarder, Gen005A3160_006BB540, 005A3160, 006BB540 )
BFME_TAIL_PAIR_FORWARDER( Rva00725600TailPairForwarder, Gen0045A970_00723FB0, 0045A970, 00723FB0 )
BFME_TAIL_PAIR_FORWARDER( Rva007814D0TailPairForwarder, Gen0075C940_0077FD80, 0075C940, 0077FD80 )
BFME_TAIL_PAIR_FORWARDER( Rva0078ABE0TailPairForwarder, Gen00783F60_00466610, 00783F60, 00466610 )
BFME_TAIL_PAIR_FORWARDER( Rva0078AC00TailPairForwarder, Gen00789440_0046C5F0, 00789440, 0046C5F0 )
BFME_TAIL_PAIR_FORWARDER( Rva007E3AD0TailPairForwarder, Gen009A4D60_0081C330, 009A4D60, 0081C330 )

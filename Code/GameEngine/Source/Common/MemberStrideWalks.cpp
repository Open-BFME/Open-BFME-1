// Forty-five __cdecl free functions that walk an array between two pointers and
// make one __thiscall member call on each element.
//
//     push esi / mov esi,[esp+8] / push edi / mov edi,[esp+0x10] / cmp esi,edi
//     je end / mov edi,edi / mov ecx,esi / call <REL32> / add esi,<stride>
//     cmp esi,edi / jne loop / end: pop edi / pop esi / ret
//
// WHAT THE BYTES SHOW.  Both arguments are read at [esp+4] upward, ecx is not
// an incoming value, and the plain `ret` pops nothing: __cdecl with two
// pointers, walked as a half-open range.  Inside the loop `mov ecx,esi` loads
// the CURRENT ELEMENT into ecx and the call pops nothing of its own, so the
// callee is a __thiscall member of the element type taking no arguments.  The
// element size is therefore the loop stride, and the ONE call per element with
// no result read is the shape of a per-element member call, not a transform.
// `mov edi,edi` is the compiler's own two-byte loop-alignment pad.
//
// THE ONLY AXES ARE THE STRIDE AND THE REL32 TARGET.  Forty-five members over
// fifteen distinct callees; each callee is reached at exactly one stride, so
// each becomes one element class sized to that stride, carrying that callee as
// its member.
//
// IDENTITY IS NOT RECOVERED.  The element classes are stand-ins sized to the
// stride the bytes prove; names are address-derived and the callee pins are
// additive and address-derived.

#define BFME_WALKED_ELEMENT( ADDR, SIZE )                                    \
	class Gen##ADDR                                                          \
	{                                                                        \
	public:                                                                  \
		void handle();                                                       \
		char m_bytes[ SIZE ];                                                \
	};

#define BFME_MEMBER_WALK( NAME, ELEMENT )                                    \
	void NAME( ELEMENT *first, ELEMENT *last )                               \
	{                                                                        \
		for ( ; first != last; ++first )                                     \
		{                                                                    \
			first->handle();                                                 \
		}                                                                    \
	}

BFME_WALKED_ELEMENT( 000D1690, 96 )
BFME_WALKED_ELEMENT( 000FD010, 36 )
BFME_WALKED_ELEMENT( 0013B8E0, 20 )
BFME_WALKED_ELEMENT( 00252A40, 44 )
BFME_WALKED_ELEMENT( 002E9E10, 20 )
BFME_WALKED_ELEMENT( 00351970, 20 )
BFME_WALKED_ELEMENT( 00351980, 20 )
BFME_WALKED_ELEMENT( 003B9270, 20 )
BFME_WALKED_ELEMENT( 003CDE30, 60 )
BFME_WALKED_ELEMENT( 00425060, 28 )
BFME_WALKED_ELEMENT( 00695630, 120 )
BFME_WALKED_ELEMENT( 006EDEA0, 56 )
BFME_WALKED_ELEMENT( 00753E80, 44 )
BFME_WALKED_ELEMENT( 00762250, 56 )
BFME_WALKED_ELEMENT( 00770F40, 108 )

BFME_MEMBER_WALK( rva000D8690MemberWalk, Gen000D1690 )
BFME_MEMBER_WALK( rva000D9A50MemberWalk, Gen000D1690 )
BFME_MEMBER_WALK( rva000DA560MemberWalk, Gen000D1690 )
BFME_MEMBER_WALK( rva000FE1B0MemberWalk, Gen000FD010 )
BFME_MEMBER_WALK( rva000FEA30MemberWalk, Gen000FD010 )
BFME_MEMBER_WALK( rva000FEA90MemberWalk, Gen000FD010 )
BFME_MEMBER_WALK( rva0013C0B0MemberWalk, Gen0013B8E0 )
BFME_MEMBER_WALK( rva0013C140MemberWalk, Gen0013B8E0 )
BFME_MEMBER_WALK( rva0013C1A0MemberWalk, Gen0013B8E0 )
BFME_MEMBER_WALK( rva00252D10MemberWalk, Gen00252A40 )
BFME_MEMBER_WALK( rva00252D40MemberWalk, Gen00252A40 )
BFME_MEMBER_WALK( rva00252D70MemberWalk, Gen00252A40 )
BFME_MEMBER_WALK( rva002EABC0MemberWalk, Gen002E9E10 )
BFME_MEMBER_WALK( rva002EAE30MemberWalk, Gen002E9E10 )
BFME_MEMBER_WALK( rva002EAEE0MemberWalk, Gen002E9E10 )
BFME_MEMBER_WALK( rva00355500MemberWalk, Gen00351970 )
BFME_MEMBER_WALK( rva00355530MemberWalk, Gen00351980 )
BFME_MEMBER_WALK( rva00357340MemberWalk, Gen00351970 )
BFME_MEMBER_WALK( rva00357370MemberWalk, Gen00351980 )
BFME_MEMBER_WALK( rva00359640MemberWalk, Gen00351970 )
BFME_MEMBER_WALK( rva00359670MemberWalk, Gen00351980 )
BFME_MEMBER_WALK( rva003BA480MemberWalk, Gen003B9270 )
BFME_MEMBER_WALK( rva003BA990MemberWalk, Gen003B9270 )
BFME_MEMBER_WALK( rva003BAFD0MemberWalk, Gen003B9270 )
BFME_MEMBER_WALK( rva003CFA60MemberWalk, Gen003CDE30 )
BFME_MEMBER_WALK( rva003D00B0MemberWalk, Gen003CDE30 )
BFME_MEMBER_WALK( rva003D12F0MemberWalk, Gen003CDE30 )
BFME_MEMBER_WALK( rva004260D0MemberWalk, Gen00425060 )
BFME_MEMBER_WALK( rva004261C0MemberWalk, Gen00425060 )
BFME_MEMBER_WALK( rva004261F0MemberWalk, Gen00425060 )
BFME_MEMBER_WALK( rva0069CC30MemberWalk, Gen00695630 )
BFME_MEMBER_WALK( rva0069EDA0MemberWalk, Gen00695630 )
BFME_MEMBER_WALK( rva006A0F80MemberWalk, Gen00695630 )
BFME_MEMBER_WALK( rva006F02A0MemberWalk, Gen006EDEA0 )
BFME_MEMBER_WALK( rva006F2860MemberWalk, Gen006EDEA0 )
BFME_MEMBER_WALK( rva006F28E0MemberWalk, Gen006EDEA0 )
BFME_MEMBER_WALK( rva0076B490MemberWalk, Gen00762250 )
BFME_MEMBER_WALK( rva0076D780MemberWalk, Gen00762250 )
BFME_MEMBER_WALK( rva0076F8C0MemberWalk, Gen00762250 )
BFME_MEMBER_WALK( rva0076F9B0MemberWalk, Gen00753E80 )
BFME_MEMBER_WALK( rva00770DD0MemberWalk, Gen00753E80 )
BFME_MEMBER_WALK( rva00772130MemberWalk, Gen00753E80 )
BFME_MEMBER_WALK( rva00776300MemberWalk, Gen00770F40 )
BFME_MEMBER_WALK( rva00777FD0MemberWalk, Gen00770F40 )
BFME_MEMBER_WALK( rva00779EE0MemberWalk, Gen00770F40 )

// Recovered Video destructor loops live in GameClient/VideoElementDestruction.cpp.

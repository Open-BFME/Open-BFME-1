// Fifteen 17-byte __stdcall free functions that hand their single argument to
// one __cdecl free function TWICE:
//
//     mov eax,[esp+4] / push eax / push eax / call <REL32> / add esp,8 / ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` with one dword read at [esp+4] and ecx never
// touched is __stdcall with one argument.  Two dwords are pushed and THIS
// function pops them with `add esp,8`, so the callee is __cdecl -- a free
// function, not a member -- with two arguments, and both are the same value:
// the dword is loaded once and pushed from the same register twice.  Nothing
// reads eax afterwards, so the result is unused and the body is spelled void.
//
// THE ONLY AXIS IS THE REL32 TARGET.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

#define BFME_ARGUMENT_TWICE_CALLEE( ADDR )                                \
	void gen##ADDR( void *first, void *second );                          \

#define BFME_ARGUMENT_TWICE_FORWARDER( NAME, CALLEE )                     \
	void __stdcall NAME( void *value )                                    \
	{                                                                     \
		CALLEE( value, value );                                           \
	}

BFME_ARGUMENT_TWICE_CALLEE( 00062EF0 )
BFME_ARGUMENT_TWICE_CALLEE( 000771C0 )
BFME_ARGUMENT_TWICE_CALLEE( 000772C0 )
BFME_ARGUMENT_TWICE_CALLEE( 0009B4B0 )
BFME_ARGUMENT_TWICE_CALLEE( 003897C0 )
BFME_ARGUMENT_TWICE_CALLEE( 00389840 )
BFME_ARGUMENT_TWICE_CALLEE( 003C9220 )
BFME_ARGUMENT_TWICE_CALLEE( 003C92A0 )
BFME_ARGUMENT_TWICE_CALLEE( 005278B0 )
BFME_ARGUMENT_TWICE_CALLEE( 0054E860 )
BFME_ARGUMENT_TWICE_CALLEE( 0054E8E0 )
BFME_ARGUMENT_TWICE_CALLEE( 0054E9E0 )
BFME_ARGUMENT_TWICE_CALLEE( 0056DFC0 )
BFME_ARGUMENT_TWICE_CALLEE( 00593060 )
BFME_ARGUMENT_TWICE_CALLEE( 005930E0 )

BFME_ARGUMENT_TWICE_FORWARDER( rva00063120, gen00062EF0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva00077740, gen000771C0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva00077790, gen000772C0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0009B640, gen0009B4B0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0038BC50, gen003897C0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0038BC70, gen00389840 )
BFME_ARGUMENT_TWICE_FORWARDER( rva003C9630, gen003C9220 )
BFME_ARGUMENT_TWICE_FORWARDER( rva003C9650, gen003C92A0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva00528F40, gen005278B0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0054EDC0, gen0054E860 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0054EDE0, gen0054E8E0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0054EE20, gen0054E9E0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva0056E210, gen0056DFC0 )
BFME_ARGUMENT_TWICE_FORWARDER( rva005941E0, gen00593060 )
BFME_ARGUMENT_TWICE_FORWARDER( rva00594200, gen005930E0 )

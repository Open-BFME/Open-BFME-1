// Twenty-one 27-byte __thiscall members that call one __cdecl free function,
// passing `this` as its FIRST argument ahead of their own three.
//
//     mov eax,[esp+0xC] / mov edx,[esp+8] / push eax / mov eax,[esp+8]
//     push edx / push eax / push ecx / call <REL32> / add esp,0x10 / ret 0xC
//
// WHAT THE BYTES SHOW.  `ret 0xC` with three dwords read at [esp+4] upward and
// ecx never reloaded is __thiscall with three arguments.  Four dwords are
// pushed and the CALLER pops all sixteen, so the callee is __cdecl with four
// arguments -- a free function, not a member -- and the dword it receives first
// is ecx itself, the object pointer.  The three arguments follow in order.  The
// second one is reloaded from [esp+8] after the first push because the pushes
// run right to left across a moving esp, not because the source reorders them.
// Nothing is done with eax afterwards, so the result is unused and the bodies
// are spelled `void`.
//
// THE ONLY AXIS IS THE REL32 TARGET: twenty-one members over twenty callees.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_EXPLICIT_THIS_CALLEE( ADDR )                                    \
	void gen##ADDR( void *self, void *a, void *b, void *c );

#define BFME_EXPLICIT_THIS_FORWARDER( NAME, CALLEE )                         \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		void invoke( void *a, void *b, void *c );                            \
	};                                                                       \
	void NAME::invoke( void *a, void *b, void *c )                           \
	{                                                                        \
		CALLEE( this, a, b, c );                                             \
	}

BFME_EXPLICIT_THIS_CALLEE( 004B2F30 )
BFME_EXPLICIT_THIS_CALLEE( 00032943 )
BFME_EXPLICIT_THIS_CALLEE( 004B3250 )
BFME_EXPLICIT_THIS_CALLEE( 004B4010 )
BFME_EXPLICIT_THIS_CALLEE( 004B42F0 )
BFME_EXPLICIT_THIS_CALLEE( 004B5530 )
BFME_EXPLICIT_THIS_CALLEE( 004B9A50 )
BFME_EXPLICIT_THIS_CALLEE( 004B9F10 )
BFME_EXPLICIT_THIS_CALLEE( 004BBCB0 )
BFME_EXPLICIT_THIS_CALLEE( 004BBFC0 )
BFME_EXPLICIT_THIS_CALLEE( 004BC7E0 )
BFME_EXPLICIT_THIS_CALLEE( 004BCBB0 )
BFME_EXPLICIT_THIS_CALLEE( 004BCFD0 )
BFME_EXPLICIT_THIS_CALLEE( 004BD2A0 )
BFME_EXPLICIT_THIS_CALLEE( 004BD480 )
BFME_EXPLICIT_THIS_CALLEE( 004BD660 )
BFME_EXPLICIT_THIS_CALLEE( 004BDC70 )
BFME_EXPLICIT_THIS_CALLEE( 004BDDA0 )
BFME_EXPLICIT_THIS_CALLEE( 004BE340 )
BFME_EXPLICIT_THIS_CALLEE( 004BF660 )
BFME_EXPLICIT_THIS_CALLEE( 004BFBE0 )

BFME_EXPLICIT_THIS_FORWARDER( Rva0078FCD0ExplicitThisForwarder, gen004B2F30 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00790C70ExplicitThisForwarder, gen00032943 )
BFME_EXPLICIT_THIS_FORWARDER( Rva0078FD00ExplicitThisForwarder, gen004B3250 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00790420ExplicitThisForwarder, gen004B4010 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00790450ExplicitThisForwarder, gen004B42F0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00790CA0ExplicitThisForwarder, gen004B5530 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00791FC0ExplicitThisForwarder, gen004B9F10 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00792010ExplicitThisForwarder, gen004B9A50 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00792090ExplicitThisForwarder, gen004B9A50 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00793180ExplicitThisForwarder, gen004BBCB0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00793D80ExplicitThisForwarder, gen004BBFC0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00793DB0ExplicitThisForwarder, gen004BCBB0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00793E20ExplicitThisForwarder, gen004BC7E0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00796200ExplicitThisForwarder, gen004BCFD0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00796230ExplicitThisForwarder, gen004BD2A0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00796A90ExplicitThisForwarder, gen004BD480 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00796AC0ExplicitThisForwarder, gen004BD660 )
BFME_EXPLICIT_THIS_FORWARDER( Rva007974F0ExplicitThisForwarder, gen004BDDA0 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00797520ExplicitThisForwarder, gen004BDC70 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00798570ExplicitThisForwarder, gen004BE340 )
BFME_EXPLICIT_THIS_FORWARDER( Rva007996D0ExplicitThisForwarder, gen004BF660 )
BFME_EXPLICIT_THIS_FORWARDER( Rva00799700ExplicitThisForwarder, gen004BFBE0 )

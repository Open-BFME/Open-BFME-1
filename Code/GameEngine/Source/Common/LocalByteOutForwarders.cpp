// Sixteen 13-byte __thiscall members that hand one direct call the address of a
// single-byte local and discard it.
//
//     push ecx / lea eax,[esp+3] / push eax / call <REL32> / pop ecx / ret
//
// WHAT THE BYTES SHOW.  The plain `ret` pops nothing and ecx is never reloaded:
// __thiscall with no arguments.  The leading `push ecx` opens a four-byte frame
// slot that the matching `pop ecx` discards -- the classic MSVC allocation of
// one stack dword -- and the address handed to the call is [esp+3], the LAST
// byte of that slot, which is where MSVC 7.1 places a one-byte local.  So the
// argument is the address of a single-byte object, nothing initialises it
// before the call, and nothing reads it after: it is an out-parameter whose
// result these bodies drop.  The call pops its own dword and is entered with
// ecx unchanged, so the callee is a __thiscall member of this class or of a
// base of it, taking that pointer.
//
// THE ONLY AXIS IS THE REL32 TARGET: sixteen members, sixteen distinct callees.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived; callee pins are
// additive and address-derived.

#define BFME_BYTE_OUT_CALLEE( ADDR )                                         \
	class Gen##ADDR                                                          \
	{                                                                        \
	public:                                                                  \
		void handle( char *out );                                            \
	};

#define BFME_BYTE_OUT_FORWARDER( NAME, CALLEE )                              \
	class NAME : public CALLEE                                               \
	{                                                                        \
	public:                                                                  \
		void invoke();                                                       \
	};                                                                       \
	void NAME::invoke()                                                      \
	{                                                                        \
		char result;                                                         \
		handle( &result );                                                   \
	}

BFME_BYTE_OUT_CALLEE( 000657E0 )
BFME_BYTE_OUT_CALLEE( 000BB6A0 )
BFME_BYTE_OUT_CALLEE( 000CFFB0 )
BFME_BYTE_OUT_CALLEE( 000FD720 )
BFME_BYTE_OUT_CALLEE( 00110D40 )
BFME_BYTE_OUT_CALLEE( 00127440 )
BFME_BYTE_OUT_CALLEE( 00201170 )
BFME_BYTE_OUT_CALLEE( 00343C70 )
BFME_BYTE_OUT_CALLEE( 0037E8F0 )
BFME_BYTE_OUT_CALLEE( 00387F90 )
BFME_BYTE_OUT_CALLEE( 004ADA00 )
BFME_BYTE_OUT_CALLEE( 006922A0 )
BFME_BYTE_OUT_CALLEE( 0069FC40 )
BFME_BYTE_OUT_CALLEE( 006FA400 )
BFME_BYTE_OUT_CALLEE( 007683D0 )
BFME_BYTE_OUT_CALLEE( 00768590 )

class Gen_002011d0
{
public:
	void *m( int value );
};

class Rva002085F0ByteOutForwarder : public Gen_002011d0
{
public:
	void invoke();
};

// ?invoke@Rva002085F0ByteOutForwarder@@QAEXXZ
void Rva002085F0ByteOutForwarder::invoke()
{
	char result;
	m( (int)&result );
}

BFME_BYTE_OUT_FORWARDER( Rva00110DE0ByteOutForwarder, Gen00110D40 )
BFME_BYTE_OUT_FORWARDER( Rva00127AB0ByteOutForwarder, Gen00127440 )
BFME_BYTE_OUT_FORWARDER( Rva001964C0ByteOutForwarder, Gen000657E0 )
BFME_BYTE_OUT_FORWARDER( Rva002085E0ByteOutForwarder, Gen00201170 )
BFME_BYTE_OUT_FORWARDER( Rva0033D8A0ByteOutForwarder, Gen000BB6A0 )
BFME_BYTE_OUT_FORWARDER( Rva00344B10ByteOutForwarder, Gen00343C70 )
BFME_BYTE_OUT_FORWARDER( Rva0037EDA0ByteOutForwarder, Gen0037E8F0 )
BFME_BYTE_OUT_FORWARDER( Rva00388960ByteOutForwarder, Gen00387F90 )
BFME_BYTE_OUT_FORWARDER( Rva00430AE0ByteOutForwarder, Gen000FD720 )
BFME_BYTE_OUT_FORWARDER( Rva00442C90ByteOutForwarder, Gen000CFFB0 )
BFME_BYTE_OUT_FORWARDER( Rva004ADC70ByteOutForwarder, Gen004ADA00 )
BFME_BYTE_OUT_FORWARDER( Rva006925C0ByteOutForwarder, Gen006922A0 )
BFME_BYTE_OUT_FORWARDER( Rva006A1760ByteOutForwarder, Gen0069FC40 )
BFME_BYTE_OUT_FORWARDER( Rva006FA490ByteOutForwarder, Gen006FA400 )
BFME_BYTE_OUT_FORWARDER( Rva00769480ByteOutForwarder, Gen007683D0 )
BFME_BYTE_OUT_FORWARDER( Rva00769710ByteOutForwarder, Gen00768590 )

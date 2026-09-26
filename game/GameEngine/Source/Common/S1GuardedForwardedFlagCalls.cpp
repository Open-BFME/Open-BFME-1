// Four eighteen-byte bodies that load a pointer, and only when it is non-null
// forward one constant flag to a __thiscall member of it:
//
//     mov ecx,[<SLOT>] / test ecx,ecx / jz L / push <0|1> /
//     call <REL32> / ret   (L: ret)
//
// WHAT THE BYTES SHOW.  The pointer is loaded straight INTO ecx, which is the
// receiver register -- that is what makes the callee a __thiscall member of the
// pointee rather than a free function taking the pointer as an argument (a free
// function would push it, and the guard would be tested in eax).  Exactly one
// byte-wide constant is pushed and the guard's jz skips both the push and the
// call, so the whole call is the body of the `if`.  Falling to `ret` with eax
// undefined proves void.
//
// TWO SOURCES, NOT ONE.  0048D1B0 and 0048D1D0 read the pointer from a member
// at 0x3050 and call 0x00027F2A; 00539350 and 00539370 read it from a
// module-level slot (a DIR32 site build.py fills from retail -- not evidence)
// and call 0x0000C955.  Each pair differs only in the pushed constant, one
// passing true and the other false, which is the clearest thing in this family:
// the same forwarder written twice with the flag flipped.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  The pushed byte is
// spelled bool because a bool argument compiles to exactly this push, but a
// byte-wide enum would encode the same.

#define BFME_FORWARD_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle( bool flag );                                         \
	};

BFME_FORWARD_CALLEE( 00027F2A )
BFME_FORWARD_CALLEE( 0000C955 )

#define BFME_GUARDED_FORWARD_MEMBER( NAME, CALLEE, OFFSET, VALUE )        \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void forward();                                                   \
		char m_lead[ OFFSET ];                                            \
		CALLEE *m_target;                                                 \
	};                                                                    \
	void NAME::forward()                                                  \
	{                                                                     \
		if ( m_target )                                                   \
		{                                                                 \
			m_target->handle( VALUE );                                    \
		}                                                                 \
	}

BFME_GUARDED_FORWARD_MEMBER( Rva0048D1B0, Gen00027F2A, 0x3050, false )
BFME_GUARDED_FORWARD_MEMBER( Rva0048D1D0, Gen00027F2A, 0x3050, true )

extern Gen0000C955 *Data00EF49FC;

#define BFME_GUARDED_FORWARD_GLOBAL( NAME, VALUE )                        \
	void NAME();                                                          \
	void NAME()                                                           \
	{                                                                     \
		if ( Data00EF49FC )                                               \
		{                                                                 \
			Data00EF49FC->handle( VALUE );                                \
		}                                                                 \
	}

BFME_GUARDED_FORWARD_GLOBAL( Rva00539350, true )
BFME_GUARDED_FORWARD_GLOBAL( Rva00539370, false )

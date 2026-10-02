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
// IDENTITY.  The 0x00027F2A callee is proven GameWindow::winHide; the
// 0x0000C955 callee's name stays address-derived.  The pushed byte is
// spelled bool because a bool argument compiles to exactly this push, but a
// byte-wide enum would encode the same.

#define BFME_FORWARD_CALLEE( ADDR )                                       \
	class Gen##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		void handle( bool flag );                                         \
	};

BFME_FORWARD_CALLEE( 0000C955 )

// The 0x00027F2A callee is the retail thunk of GameWindow::winHide (see
// ?winHide@GameWindow@@QAEH_N@Z in targets/game/reverse/functions.csv), so
// the receiver really is a GameWindow and the flag is its bool parameter.
class GameWindow
{
public:
	int winHide( bool hide );
};

#define BFME_GUARDED_FORWARD_MEMBER( NAME, CALLEE, MEMBER, OFFSET, VALUE ) \
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
			m_target->MEMBER( VALUE );                                    \
		}                                                                 \
	}

BFME_GUARDED_FORWARD_MEMBER( Rva0048D1B0, GameWindow, winHide, 0x3050, false )
BFME_GUARDED_FORWARD_MEMBER( Rva0048D1D0, GameWindow, winHide, 0x3050, true )

// Retail's 0x012F49FC is EA's `BfmeAptScreenOnlineCustomMatch
// *TheBfmeOnlineCustomMatch`: dir32_addresses.csv pins that spelling at that VA
// (from the matched dtor 0x00538CE0, whose body clears it when `this` matches)
// and OnlineCustomMatchDestructor.cpp and NAT_establishConnectionPaths.cpp both
// reference it under that name. The address-derived Data00EF49FC that stood
// here resolved nothing. Only the pointee type may differ per TU, so the class
// is forward declared and this TU's 0x0000C955 callee view is applied at the
// use.
class BfmeAptScreenOnlineCustomMatch;
extern BfmeAptScreenOnlineCustomMatch *TheBfmeOnlineCustomMatch;

#define BFME_GUARDED_FORWARD_GLOBAL( NAME, VALUE )                        \
	void NAME();                                                          \
	void NAME()                                                           \
	{                                                                     \
		Gen0000C955 *target = (Gen0000C955 *)TheBfmeOnlineCustomMatch;      \
		if ( target )                                                     \
		{                                                                 \
			target->handle( VALUE );                                       \
		}                                                                 \
	}

BFME_GUARDED_FORWARD_GLOBAL( Rva00539350, true )
BFME_GUARDED_FORWARD_GLOBAL( Rva00539370, false )

// ?dispatchWhenReady@Rva007E32A0State@@QAE_NHHH@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

// The callee retail entered here (through the incremental-link thunk at
// 0x0003F80F) is the body at 0x007E2F50, owned by the ledger as
// ?d_007e2f50@@YAXXZ (game/gen_asm/d_007df1f0.asm). That symbol's identity is
// not recovered, so the call is spelled with the owning name. It is entered
// with this in ECX and five stack arguments and answers in AL, while the
// owning symbol carries no arguments at all; MSVC 7.1 also rejects __thiscall
// in a free-function-pointer typedef, so the call goes through a
// pointer-to-member view of the owning symbol.
void d_007e2f50();

struct ForwardView
{
	bool forward( int first, int second, int third, int *thirdOut, int enabled );
};
typedef bool (ForwardView::*ForwardCall)( int, int, int, int *, int );

class Rva007E32A0State
{
public:
	bool dispatchWhenReady( int first, int second, int third );

private:
	char m_unknown[ 8 ];
	int m_state;
};

bool Rva007E32A0State::dispatchWhenReady( int first, int second, int third )
{
	if ( m_state == 6 ) {
		union { void (*asFunction)(void); ForwardCall asMember; } forwardCast;
		forwardCast.asFunction = d_007e2f50;
		return (reinterpret_cast<ForwardView *>( this )->*forwardCast.asMember)(
			first, second, third, &third, true );
	}
	return false;
}
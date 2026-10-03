class BfmeSubDPF
{
	unsigned char m_bfmeHead[4];
};

class BfmeFirstDPF
{
public:
	unsigned char m_bfmeHead[0xc];
	BfmeSubDPF m_bfmeSub;
};

// Retail 0x00836580 calls the ILT thunk at 0x0001CB11, defined as
// ?j_0001cb11@@YAXXZ (game/gen_small/thunks_013.cpp) and nothing else. The
// call pushes the sub-object pointer and puts the receiver in ECX, exactly as
// the one-argument thiscall did.
extern void j_0001cb11();

class BfmeOtherDPF
{
};

// VC7 rejects __thiscall on a function pointer (error C4234), so the
// ecx-passed call is expressed through a pointer-to-member-function held in a
// union. For a non-virtual member that representation is the plain code
// address, and the call is still __thiscall.
union ThunkDPF
{
	void (*f_call)();
	void (BfmeOtherDPF::*m_call)(BfmeSubDPF *);
};

class BfmeThingDPF
{
public:
	BfmeOtherDPF *bfmeGoDPF(BfmeOtherDPF *other);
	BfmeFirstDPF *m_bfmeFirst;
};

BfmeOtherDPF *BfmeThingDPF::bfmeGoDPF(BfmeOtherDPF *other)
{
	volatile int tmp = 0;
	ThunkDPF u;
	u.f_call = j_0001cb11;
	(other->*u.m_call)(&m_bfmeFirst->m_bfmeSub);
	return other;
}

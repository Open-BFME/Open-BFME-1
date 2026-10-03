class BfmeArgKD
{
public:
	BfmeArgKD(const BfmeArgKD &other) throw()
	{
		m_bfmeAKD = other.m_bfmeAKD;
		m_bfmeBKD = other.m_bfmeBKD;
		m_bfmeCKD = other.m_bfmeCKD;
	}
	~BfmeArgKD() throw() {}

	int m_bfmeAKD;
	int m_bfmeBKD;
	int m_bfmeCKD;
};

class BfmeTgtKD
{
public:
	// bfmeRunKD() is reached through the ILT thunk below, not declared here.
};

// The forward goes through the five-byte ILT thunk at 0x0003FE77, defined as
// ?j_0003fe77@@YAXXZ in game/gen_small/gthunks_071.cpp (target 0x00733000) and
// pinned for ?bfmeRunKD@BfmeTgtKD@@. The thunk declares no arguments of its own:
// it jumps with the thiscall `this` in ECX and the caller's arguments already in
// place, so the call is spelled through a thiscall member pointer of the same shape.
extern void j_0003fe77();

typedef char (BfmeTgtKD::*bfmeRunKDThunk)(void *first, BfmeArgKD arg, void *last);

union BfmeRunKDThunkCast
{
	char (__cdecl *freeFunction)(void *first, BfmeArgKD arg, void *last);
	bfmeRunKDThunk memberFunction;
};

class BfmeOwnKD
{
public:
	char bfmeFwdKD(void *first, BfmeArgKD arg, void *last);

	unsigned char m_bfmeHeadKD[0x3094];
	BfmeTgtKD *m_bfmeTgtKD;
};

char BfmeOwnKD::bfmeFwdKD(void *first, BfmeArgKD arg, void *last)
{
	if (m_bfmeTgtKD)
	{
		BfmeRunKDThunkCast cast;
		cast.freeFunction = reinterpret_cast<char (__cdecl *)(void *, BfmeArgKD, void *)>(
			&::j_0003fe77);
		return (m_bfmeTgtKD->*cast.memberFunction)(first, arg, last);
	}

	return 0;
}

class BfmeArgKE
{
public:
	BfmeArgKE(const BfmeArgKE &other) throw()
	{
		m_bfmeAKE = other.m_bfmeAKE;
		m_bfmeBKE = other.m_bfmeBKE;
		m_bfmeCKE = other.m_bfmeCKE;
	}
	~BfmeArgKE() throw() {}

	int m_bfmeAKE;
	int m_bfmeBKE;
	int m_bfmeCKE;
};

class BfmeTgtKE
{
public:
	// bfmeRunKE() is reached through the ILT thunk below, not declared here.
};

// The forward goes through the five-byte ILT thunk at 0x0003C795, defined as
// ?j_0003c795@@YAXXZ in game/gen_small/gthunks_067.cpp (target 0x0071C9C0) and
// pinned for ?bfmeRunKE@BfmeTgtKE@@. The thunk declares no arguments of its own:
// it jumps with the thiscall `this` in ECX and the caller's arguments already in
// place, so the call is spelled through a thiscall member pointer of the same shape.
extern void j_0003c795();

typedef char (BfmeTgtKE::*bfmeRunKEThunk)(void *first, BfmeArgKE arg, void *last);

union BfmeRunKEThunkCast
{
	char (__cdecl *freeFunction)(void *first, BfmeArgKE arg, void *last);
	bfmeRunKEThunk memberFunction;
};

class BfmeOwnKE
{
public:
	char bfmeFwdKE(void *first, BfmeArgKE arg, void *last);

	unsigned char m_bfmeHeadKE[0x3098];
	BfmeTgtKE *m_bfmeTgtKE;
};

char BfmeOwnKE::bfmeFwdKE(void *first, BfmeArgKE arg, void *last)
{
	if (m_bfmeTgtKE)
	{
		BfmeRunKEThunkCast cast;
		cast.freeFunction = reinterpret_cast<char (__cdecl *)(void *, BfmeArgKE, void *)>(
			&::j_0003c795);
		return (m_bfmeTgtKE->*cast.memberFunction)(first, arg, last);
	}

	return 0;
}

// cl: /O2 /Ob0

// The base copy goes through the five-byte ILT thunk at 0x0001AB86, defined as
// ?j_0001ab86@@YAXXZ in game/gen_small/thunks_012.cpp (the ILT of the 33B copy
// twins 0x0033A4C0 and 0x0033ACA0).  The thunk declares no arguments of its
// own: it jumps with the thiscall `this` in ECX and the caller's argument
// already in place, so the call is spelled through a thiscall member pointer of
// the same shape.
extern void j_0001ab86();

class Rva0033CopyBase
{
public:
	char m_pad[8];
};

typedef void (Rva0033CopyBase::*baseCopyThunk)(const Rva0033CopyBase &other);

union BaseCopyThunkCast
{
	void (__cdecl *freeFunction)(const Rva0033CopyBase &other);
	baseCopyThunk memberFunction;
};

struct Rva0033A7B0Extra
{
	int a;
	int b;
};

class Rva0033A7B0 : public Rva0033CopyBase
{
	int m_08;
	int m_0C;

public:
	Rva0033A7B0(const Rva0033CopyBase &other, const Rva0033A7B0Extra *extra);
};

Rva0033A7B0::Rva0033A7B0(const Rva0033CopyBase &other, const Rva0033A7B0Extra *extra)
{
	BaseCopyThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(const Rva0033CopyBase &)>(
		&::j_0001ab86);
	(this->*cast.memberFunction)(other);
	m_08 = extra->a;
	m_0C = extra->b;
}
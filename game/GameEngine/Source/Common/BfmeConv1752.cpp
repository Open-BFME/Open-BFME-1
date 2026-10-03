// The forward goes through the five-byte ILT thunk at 0x000157DA, defined as
// ?j_000157da@@YAXXZ in game/gen_small/thunks_009.cpp.  The thunk declares no
// arguments of its own: it jumps with the thiscall `this` in ECX and the
// caller's arguments already in place, so the call is spelled through a
// thiscall member pointer of the same shape.
extern void j_000157da();

class BfmeWakeBJ
{
};

typedef void (BfmeWakeBJ::*bfmeSetWakeBJThunk)(void *object, int sleep);

union BfmeSetWakeBJThunkCast
{
	void (__cdecl *freeFunction)(void *object, int sleep);
	bfmeSetWakeBJThunk memberFunction;
};

class BfmeOwnBJ
{
public:
	void bfmeSleepBJ(int first, int second, int third, int fourth, int fifth);

	unsigned char m_bfmeHeadBJ[0x1c];
	char m_bfmeDoneBJ;
	char m_bfmeArmedBJ;
};

void BfmeOwnBJ::bfmeSleepBJ(int first, int second, int third, int fourth, int fifth)
{
	if (m_bfmeDoneBJ)
		return;

	if (m_bfmeArmedBJ)
		return;

	void *object = *(void **)((char *)this - 0x18);

	m_bfmeArmedBJ = 1;

	BfmeSetWakeBJThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(void *, int)>(
		&::j_000157da);
	(reinterpret_cast<BfmeWakeBJ *>((char *)this - 0x20)->*cast.memberFunction)(
		object, 1);
}
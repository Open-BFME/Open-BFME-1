// Both retail bodies call the five-byte ILT thunk at 0x000013ED, whose
// address-derived identity is ?j_000013ed@@YAXXZ (functions.csv row
// ?j_000013ed@@YAXXZ, defined by game/gen_small/gthunks_000.cpp).  Calling it
// through its own symbol -- the idiom Rva006B9320RequestDispatch.cpp uses --
// is what lets this object link; the call shape stays thiscall so the bytes
// are unchanged.

class BfmeSubDSI
{
};

typedef void (BfmeSubDSI::*BfmeCallDSI_t)(void **);

extern void j_000013ed();

class BfmeThingDSI
{
public:
	void bfmeGoDSI(void *what);
	char m_bfmeHead[0xc];
	BfmeSubDSI m_bfmeSub;
};

void BfmeThingDSI::bfmeGoDSI(void *what)
{
	*(void *volatile *)&what = what;
	union { void (__cdecl *raw)(); BfmeCallDSI_t member; } call;
	call.raw = j_000013ed;
	(m_bfmeSub.*call.member)(&what);
}

class BfmeThingDSJ
{
public:
	void bfmeGoDSJ(void *what);
	char m_bfmeHead[0x10];
	BfmeSubDSI m_bfmeSub;
};

void BfmeThingDSJ::bfmeGoDSJ(void *what)
{
	*(void *volatile *)&what = what;
	union { void (__cdecl *raw)(); BfmeCallDSI_t member; } call;
	call.raw = j_000013ed;
	(m_bfmeSub.*call.member)(&what);
}
class BfmeInnerCAE
{
public:
	virtual void bfmeSpareCAE0();
	virtual void bfmeSpareCAE1();
	virtual void bfmeSpareCAE2();
	virtual void bfmeSpareCAE3();
	virtual void bfmeSpareCAE4();
	virtual void bfmeSpareCAE5();
	virtual void bfmeSpareCAE6();
	virtual void bfmeSpareCAE7();
	virtual int bfmeRunCAE();
};

struct BfmeSubCAE
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerCAE m_bfmeInner;
};

// Retail routes this predicate through the already matched five-byte ILT
// ?j_0004425b@@YAXXZ (0x0004425B -> FUN_00615080), but the call itself still
// sets ECX to (this - 0x10), so use the established pointer-to-member cast
// idiom: the relocation names the verified ILT while the call keeps the
// retail thiscall shape.
void j_0004425b();

struct BfmeAskCAEThunk
{
	bool Call();
};

typedef bool (BfmeAskCAEThunk::*BfmeAskCAE)(void);

union BfmeAskCAECast
{
	void (*asFunction)();
	BfmeAskCAE asMember;
};

class BfmeThingCAE
{
public:
	int bfmeGoCAE();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubCAE *m_bfmeSub;
};

int BfmeThingCAE::bfmeGoCAE()
{
	BfmeAskCAECast fnCast;
	fnCast.asFunction = j_0004425b;

	if ((reinterpret_cast<BfmeAskCAEThunk *>((char *)this - 0x10)->*fnCast.asMember)())
		return m_bfmeSub->m_bfmeInner.bfmeRunCAE();
	return 3;
}

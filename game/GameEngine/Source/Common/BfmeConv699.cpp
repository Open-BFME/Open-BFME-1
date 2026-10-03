class BfmeInnerDHB
{
public:
	virtual void bfmeSpareDHB0();
	virtual void bfmeSpareDHB1();
	virtual void bfmeSpareDHB2();
	virtual void bfmeSpareDHB3();
	virtual void bfmeSpareDHB4();
	virtual void bfmeSpareDHB5();
	virtual void bfmeSpareDHB6();
	virtual void bfmeSpareDHB7();
	virtual void bfmeSpareDHB8();
	virtual void bfmeSpareDHB9();
	virtual void bfmeSpareDHB10();
	virtual void bfmeSpareDHB11();
	virtual void bfmeSpareDHB12();
	virtual void bfmeSpareDHB13();
	virtual void bfmeSpareDHB14();
	virtual int bfmeRunDHB();
};

struct BfmeSubDHB
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerDHB m_bfmeInner;
};

// Retail 0x002151B0 calls the ILT thunk at 0x0004425B, defined as
// ?j_0004425b@@YAXXZ (game/gen_small/thunks_032.cpp). The question is asked
// one-argument fastcall so the receiver lands in ECX, exactly as the
// no-argument thiscall did; the answer comes back in AL.
extern void __cdecl j_0004425b();

typedef bool (__fastcall *BfmeAskDHB)(void *);

class BfmeThingDHB
{
public:
	int bfmeGoDHB();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubDHB *m_bfmeSub;
};

int BfmeThingDHB::bfmeGoDHB()
{
	if (reinterpret_cast<BfmeAskDHB>(&j_0004425b)((char *)this - 0x10))
		return m_bfmeSub->m_bfmeInner.bfmeRunDHB();
	return 0;
}

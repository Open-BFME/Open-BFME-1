class BfmeInnerDHA
{
public:
	virtual void bfmeSpareDHA0();
	virtual void bfmeSpareDHA1();
	virtual void bfmeSpareDHA2();
	virtual void bfmeSpareDHA3();
	virtual void bfmeSpareDHA4();
	virtual void bfmeSpareDHA5();
	virtual void bfmeSpareDHA6();
	virtual void bfmeSpareDHA7();
	virtual void bfmeSpareDHA8();
	virtual void bfmeSpareDHA9();
	virtual void bfmeSpareDHA10();
	virtual void bfmeSpareDHA11();
	virtual void bfmeSpareDHA12();
	virtual void bfmeSpareDHA13();
	virtual void bfmeSpareDHA14();
	virtual void bfmeSpareDHA15();
	virtual void bfmeSpareDHA16();
	virtual void bfmeSpareDHA17();
	virtual void bfmeSpareDHA18();
	virtual void bfmeSpareDHA19();
	virtual void bfmeSpareDHA20();
	virtual void bfmeSpareDHA21();
	virtual void bfmeSpareDHA22();
	virtual void bfmeSpareDHA23();
	virtual void bfmeSpareDHA24();
	virtual void bfmeSpareDHA25();
	virtual void bfmeSpareDHA26();
	virtual void bfmeSpareDHA27();
	virtual void bfmeSpareDHA28();
	virtual int bfmeRunDHA();
};

struct BfmeSubDHA
{
	unsigned char m_bfmeHead[0x10];
	BfmeInnerDHA m_bfmeInner;
};

// Retail 0x00215180 calls the ILT thunk at 0x0004425B, defined as
// ?j_0004425b@@YAXXZ (game/gen_small/thunks_032.cpp). The question is asked
// one-argument fastcall so the receiver lands in ECX, exactly as the
// no-argument thiscall did; the answer comes back in AL.
extern void __cdecl j_0004425b();

typedef bool (__fastcall *BfmeAskDHA)(void *);

class BfmeThingDHA
{
public:
	int bfmeGoDHA();
	unsigned char m_bfmeHead[0xd0];
	BfmeSubDHA *m_bfmeSub;
};

int BfmeThingDHA::bfmeGoDHA()
{
	if (reinterpret_cast<BfmeAskDHA>(&j_0004425b)((char *)this - 0x10))
		return m_bfmeSub->m_bfmeInner.bfmeRunDHA();
	return 0;
}

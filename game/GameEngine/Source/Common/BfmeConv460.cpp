struct BfmePartBGD
{
	unsigned char m_bfmeHead[4];
};

class BfmeSinkBGD
{
};

extern void j_0003c2e5();

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (BfmeSinkBGD::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeSinkBGD *)self)->*u.f)(a, b);
}

class BfmeThingBGD
{
public:
	void bfmeGoBGD(BfmeSinkBGD *sink);
	unsigned char m_bfmeHead[0x24];
	BfmePartBGD m_bfmeA;
	unsigned char m_bfmeGap[0x24];
	BfmePartBGD m_bfmeB;
};

void BfmeThingBGD::bfmeGoBGD(BfmeSinkBGD *sink)
{
	call2<void>(j_0003c2e5, sink, &m_bfmeA, &m_bfmeB);
}

struct BfmeSubBGC
{
	unsigned char m_bfmeHead[4];
};

extern void j_000068b1();

template <class R, class A>
__forceinline R call1(void (*p)(), void *self, A a)
{
	typedef R (BfmeSubBGC::*F)(A);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeSubBGC *)self)->*u.f)(a);
}

class BfmeThingBGC
{
public:
	void *bfmeGoBGC(void *what);
	unsigned char m_bfmeHead[8];
	BfmeSubBGC m_bfmeSub;
};

void *BfmeThingBGC::bfmeGoBGC(void *what)
{
	call1<void>(j_000068b1, &m_bfmeSub, what);
	return what;
}

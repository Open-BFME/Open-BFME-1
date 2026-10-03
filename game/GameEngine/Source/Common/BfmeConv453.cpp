class BfmeSubBFD
{
};

extern void j_00048928();

template <class R>
__forceinline R call0(void (*p)(), void *self)
{
	typedef R (BfmeSubBFD::*F)();
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeSubBFD *)self)->*u.f)();
}

class BfmeThingBFD
{
public:
	int bfmeGoBFD();
	unsigned char m_bfmeHead[0x28];
	BfmeSubBFD *m_bfmeSub;
};

int BfmeThingBFD::bfmeGoBFD()
{
	BfmeSubBFD *sub = m_bfmeSub;
	if (sub != 0)
		return call0<bool>(j_00048928, sub);
	return 0;
}

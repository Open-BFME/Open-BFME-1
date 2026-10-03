class BfmeSubBGB
{
};

extern void j_00014506();

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (BfmeSubBGB::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((BfmeSubBGB *)self)->*u.f)(a, b);
}

int bfmeGoBGB(BfmeSubBGB *sub)
{
	if (sub != 0)
		call2<void>(j_00014506, sub, 8, 0);
	return 0;
}

// Retail 0x0010F100 forwards callback arguments one and three to the
// two-argument receiver at the independently decoded ILT 0x00036917.
class Rva0010F100Receiver
{
};

extern void j_00036917();

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (Rva0010F100Receiver::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva0010F100Receiver *)self)->*u.f)(a, b);
}

void __cdecl rva0010f100Forward(void *first, Rva0010F100Receiver *receiver, void *third)
{
	call2<void>(j_00036917, receiver, first, third);
}

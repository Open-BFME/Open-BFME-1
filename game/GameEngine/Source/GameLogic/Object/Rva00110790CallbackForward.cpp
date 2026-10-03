// Retail 0x00110790 forwards callback arguments one and three to the
// receiver at ILT 0x0001F546, which accepts two stack arguments and ECX.
class Rva00110790Receiver
{
};

extern void j_0001f546();

template <class R, class A, class B>
__forceinline R call2(void (*p)(), void *self, A a, B b)
{
	typedef R (Rva00110790Receiver::*F)(A, B);
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((Rva00110790Receiver *)self)->*u.f)(a, b);
}

void __cdecl rva00110790Forward(void *first, Rva00110790Receiver *receiver, void *third)
{
	call2<void>(j_0001f546, receiver, first, third);
}

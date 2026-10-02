// Retail passes ILT 0001364C, the existing Coord3D destructor, to the CRT's
// eh vector destructor iterator at RVA 009F6D76. VC7.1 cannot spell a free
// __thiscall callback type or take a destructor's address in C++; these
// declarations pass its address unchanged for the CRT to invoke as __thiscall.
extern "C" void __cdecl __identifier("??1Coord3D@@QAE@XZ")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (*dtor)());

class BfmeThingDMA
{
public:
	void *bfmeGoDMA(unsigned char flags);
};

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

void *BfmeThingDMA::bfmeGoDMA(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 0xc, *(int *)base, __identifier("??1Coord3D@@QAE@XZ"));
		if (flags & 1)
			operator delete[](base);
		return base;
	}
	if (flags & 1)
		operator delete(this);
	return this;
}

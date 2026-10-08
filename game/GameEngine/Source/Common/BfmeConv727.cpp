// Retail passes ILT 0001D9EE to the MSVC 7.1 CRT array-destruction helper at
// RVA 009F6D76 and frees through the WWLib operator delete[] (0x00881EF0) and
// operator delete (0x00881EB0) bodies. VC7.1 cannot spell the CRT helper's
// reserved front-end name or a free __thiscall callback type in C++, so both
// addresses are passed unchanged. Convention follows BfmeConv728.cpp.
extern "C" void __cdecl __identifier("bfmeDtorCbDLJ")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (*dtor)());

class BfmeThingDLJ
{
public:
	void *bfmeGoDLJ(unsigned char flags);
};

// Retail calls ILT 0001D9EE with ecx = this. VC7.1 rejects __thiscall on a
// free function pointer (C4234), so the thunk address is laundered through a
// member-function pointer, the idiom MilesAudioManagerRva006A5E60.cpp uses.
union DtorThunkDLJ
{
	void (*raw)();
	void (BfmeThingDLJ::*member)();
};

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

void *BfmeThingDLJ::bfmeGoDLJ(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 0x94, *(int *)base, __identifier("bfmeDtorCbDLJ"));
		if (flags & 1)
			operator delete[](base);
		return base;
	}
	DtorThunkDLJ dtor;
	dtor.raw = __identifier("bfmeDtorCbDLJ");
	(this->*dtor.member)();
	if (flags & 1)
		operator delete(this);
	return this;
}
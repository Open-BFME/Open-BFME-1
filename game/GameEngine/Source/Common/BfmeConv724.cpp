// Retail passes ILT 00039C7A to the MSVC 7.1 CRT array-destruction helper at
// RVA 009F6D76 and frees through the WWLib operator delete[] (0x00881EF0) and
// operator delete (0x00881EB0) bodies. VC7.1 cannot spell the CRT helper's
// reserved front-end name or a free __thiscall callback type in C++, so both
// addresses are passed unchanged; the calling-convention casts keep the
// retail register setup. Convention follows BfmeConv728.cpp.
extern "C" void __cdecl __identifier("bfmeDtorCbDLG")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (*dtor)());

class BfmeThingDLG
{
public:
	void *bfmeGoDLG(unsigned char flags);
};

// Retail calls ILT 00039C7A with ecx = this. VC7.1 rejects __thiscall on a
// free function pointer (C4234), so the thunk address is laundered through a
// member-function pointer, the idiom MilesAudioManagerRva006A5E60.cpp uses.
union DtorThunkDLG
{
	void (*raw)();
	void (BfmeThingDLG::*member)();
};

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

void *BfmeThingDLG::bfmeGoDLG(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 0xa0, *(int *)base, __identifier("bfmeDtorCbDLG"));
		if (flags & 1)
			operator delete[](base);
		return base;
	}
	DtorThunkDLG dtor;
	dtor.raw = __identifier("bfmeDtorCbDLG");
	(this->*dtor.member)();
	if (flags & 1)
		operator delete(this);
	return this;
}
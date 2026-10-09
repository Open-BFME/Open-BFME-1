// Retail passes ILT 00001C80 to the MSVC 7.1 CRT array-destruction helper at
// RVA 009F6D76, frees through the WWLib operator delete[] (0x00881EF0) and
// operator delete (0x00881EB0) bodies, and writes the BfmeBaseVUQ vftable
// (??_7BfmeBaseVUQ@@6B@) into the dying object. VC7.1 cannot spell the CRT
// helper's reserved front-end name or a free __thiscall callback type in C++,
// so both addresses are passed unchanged. Convention follows BfmeConv728.cpp.
extern "C" void __cdecl __identifier("??1Snapshot@@UAE@XZ")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (*dtor)());
extern "C" int __identifier("??_7BfmeBaseVUQ@@6B@")[];

class BfmeThingDMB
{
public:
	void *bfmeGoDMB(unsigned char flags);
	void *m_bfmeVft;
};

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

void *BfmeThingDMB::bfmeGoDMB(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 4, *(int *)base, __identifier("??1Snapshot@@UAE@XZ"));
		if (flags & 1)
			operator delete[](base);
		return base;
	}
	m_bfmeVft = __identifier("??_7BfmeBaseVUQ@@6B@");
	if (flags & 1)
		operator delete(this);
	return this;
}
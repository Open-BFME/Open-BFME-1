// Retail tears this wrapper down through FXParticleSystem's ILT thunk at
// 0x0004791F, the DefaultModuleTemplate<0x0A> virtual destructor: once as the
// whole-object destructor, once as the per-element callback handed to the CRT
// vector destructor iterator ??_M (0x009F6D76). The array memory then goes
// back through the WWLib operator delete[] at 0x00881EF0 and the scalar
// operator delete at 0x00881EB0.
// VC7.1 cannot spell a free __thiscall type and cannot take a virtual
// destructor's address in C++, so both names are declared as extern "C"
// __cdecl identifiers. The iterator is reached through a local __stdcall view
// and the destructor through this repo's pointer-to-member cast, which is what
// keeps retail's `mov ecx, esi` before the destructor call.
extern "C" void __cdecl __identifier("??1?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UAE@XZ")();
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();

typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (*dtor)());

void __cdecl operator delete[](void *what);
void __cdecl operator delete(void *what);

class BfmeThingDLD
{
public:
	void *bfmeGoDLD(unsigned char flags);
};

// The one-word __thiscall entity the destructor name is called through.
struct DtorCallDLD
{
	void dtor();
};
typedef void (DtorCallDLD::*DtorFnDLD)();

void *BfmeThingDLD::bfmeGoDLD(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 0x98, *(int *)base,
			__identifier("??1?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UAE@XZ"));
		if (flags & 1)
			operator delete[](base);
		return base;
	}
	{
		union
		{
			void *asVoid;
			DtorFnDLD asMember;
		} fnCast;
		fnCast.asVoid = reinterpret_cast<void *>(
			__identifier("??1?$DefaultModuleTemplate@$0A@@FXParticleSystem@@UAE@XZ"));
		(reinterpret_cast<DtorCallDLD *>(this)->*fnCast.asMember)();
	}
	if (flags & 1)
		operator delete(this);
	return this;
}
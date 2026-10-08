// Retail 0x007E76E0, ?bfmeGoDME@BfmeThingDME@@QAEPAXE@Z.
//
// Every name below is retail's own, read off the body: the MSVC 7.1 CRT
// array-destruction helper called at +0x1D, the two global operator deletes
// called at +0x28 and +0x44, the ILT thunk pushed as the element destructor at
// +0x11 (it lands on Xfer's destructor at 0x007E7670), and the Xfer vftable
// stored at +0x3B.  They live in
//   game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp   (the deletes)
//   game/gen_small/thunks_027.cpp                      (the thunk)
//   game/GameEngine/Source/Common/System/xfer.cpp      (the vftable)
//   vendored msvc71-crt libc.lib                       (the helper)
// so every reference here resolves to a definition the link already has.

// VA 0x009F6D76: the vendored MSVC 7.1 CRT array-destruction helper.  It is
// __stdcall, so a __stdcall declaration would decorate the symbol with @16 and
// nothing would resolve; VC7.1 cannot spell a free __stdcall callback either.
// BfmeConv728.cpp established the shape used here: declare the helper __cdecl
// with no parameters (so the symbol keeps retail's name and no argument is
// cleaned up here) and call it through a __stdcall pointer type, which MSVC
// folds back into the direct call retail makes.
extern "C" void __cdecl __identifier("??_M@YGXPAXIHP6EX0@Z@Z")();
typedef void (__stdcall *VectorDestructorIterator)(
	void *base, unsigned int size, int count, void (__stdcall *)(void *));

// VA 0x00438D2A: the 5-byte ILT thunk in front of Xfer's destructor, which is
// what retail pushes.
extern "C" void __cdecl __identifier("bfmeDtorCbDME")();

// VA 0x01129258: Xfer's vftable.
extern "C" const unsigned char __identifier("??_7Xfer@@6B@")[];

// VA 0x00881EB0 and VA 0x00881EF0 -- game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp
// defines the global operator delete pair.
void __cdecl operator delete(void *block);
void __cdecl operator delete[](void *block);

class BfmeThingDME
{
public:
	void *bfmeGoDME(unsigned char flags);
	void *m_bfmeVft;
};

void *BfmeThingDME::bfmeGoDME(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		((VectorDestructorIterator)__identifier("??_M@YGXPAXIHP6EX0@Z@Z"))(
			this, 4, *(int *)base,
			(void (__stdcall *)(void *))__identifier("bfmeDtorCbDME"));
		if (flags & 1)
			::operator delete[](base);
		return base;
	}
	m_bfmeVft = (void *)__identifier("??_7Xfer@@6B@");
	if (flags & 1)
		::operator delete(this);
	return this;
}
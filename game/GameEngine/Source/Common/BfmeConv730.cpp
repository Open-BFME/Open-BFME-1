extern "C" void bfmeDtorCbDMC(void *what);

class BfmeThingDMC
{
public:
	void *bfmeGoDMC(unsigned char flags);
};

void __stdcall bfmeVecDtorDMC(void *base, unsigned int size, int count, void (*dtor)(void *));

// 0x00881EF0 and 0x00881EB0 are the game's global operator delete[] and
// operator delete, both owned by game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp
// (??_V@YAXPAX@Z and ??3@YAXPAX@Z). Spell them as the operators so the object
// references the definitions instead of an invented free-function name.
void __cdecl operator delete[](void *block);
void __cdecl operator delete(void *block);

void *BfmeThingDMC::bfmeGoDMC(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMC(this, 0x68, *(int *)base, bfmeDtorCbDMC);
		if (flags & 1)
			::operator delete[](base);
		return base;
	}
	if (flags & 1)
		::operator delete(this);
	return this;
}

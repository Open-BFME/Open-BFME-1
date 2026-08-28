extern "C" void bfmeDtorCbDLF(void *what);

class BfmeThingDLF
{
public:
	void bfmeDtorDLF();
	void *bfmeGoDLF(unsigned char flags);
};

void __stdcall bfmeVecDtorDLF(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLF(void *what);
void bfmeFreeDLF(void *what);

void *BfmeThingDLF::bfmeGoDLF(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLF(this, 0x98, *(int *)base, bfmeDtorCbDLF);
		if (flags & 1)
			bfmeFreeArrDLF(base);
		return base;
	}
	bfmeDtorDLF();
	if (flags & 1)
		bfmeFreeDLF(this);
	return this;
}

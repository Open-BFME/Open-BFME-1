extern "C" void bfmeDtorCbDLI(void *what);

class BfmeThingDLI
{
public:
	void bfmeDtorDLI();
	void *bfmeGoDLI(unsigned char flags);
};

void __stdcall bfmeVecDtorDLI(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLI(void *what);
void bfmeFreeDLI(void *what);

void *BfmeThingDLI::bfmeGoDLI(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLI(this, 0xa0, *(int *)base, bfmeDtorCbDLI);
		if (flags & 1)
			bfmeFreeArrDLI(base);
		return base;
	}
	bfmeDtorDLI();
	if (flags & 1)
		bfmeFreeDLI(this);
	return this;
}

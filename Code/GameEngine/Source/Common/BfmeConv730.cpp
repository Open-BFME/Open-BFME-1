extern "C" void bfmeDtorCbDMC(void *what);

class BfmeThingDMC
{
public:
	void *bfmeGoDMC(unsigned char flags);
};

void __stdcall bfmeVecDtorDMC(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDMC(void *what);
void bfmeFreeDMC(void *what);

void *BfmeThingDMC::bfmeGoDMC(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMC(this, 0x68, *(int *)base, bfmeDtorCbDMC);
		if (flags & 1)
			bfmeFreeArrDMC(base);
		return base;
	}
	if (flags & 1)
		bfmeFreeDMC(this);
	return this;
}

extern "C" void bfmeDtorCbDMA(void *what);

class BfmeThingDMA
{
public:
	void *bfmeGoDMA(unsigned char flags);
};

void __stdcall bfmeVecDtorDMA(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDMA(void *what);
void bfmeFreeDMA(void *what);

void *BfmeThingDMA::bfmeGoDMA(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMA(this, 0xc, *(int *)base, bfmeDtorCbDMA);
		if (flags & 1)
			bfmeFreeArrDMA(base);
		return base;
	}
	if (flags & 1)
		bfmeFreeDMA(this);
	return this;
}

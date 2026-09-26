extern "C" void bfmeDtorCbDLC(void *what);

class BfmeThingDLC
{
public:
	void bfmeDtorDLC();
	void *bfmeGoDLC(unsigned char flags);
};

void __stdcall bfmeVecDtorDLC(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLC(void *what);
void bfmeFreeDLC(void *what);

void *BfmeThingDLC::bfmeGoDLC(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLC(this, 0x8c, *(int *)base, bfmeDtorCbDLC);
		if (flags & 1)
			bfmeFreeArrDLC(base);
		return base;
	}
	bfmeDtorDLC();
	if (flags & 1)
		bfmeFreeDLC(this);
	return this;
}

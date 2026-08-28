extern "C" void bfmeDtorCbDLA(void *what);

class BfmeThingDLA
{
public:
	void bfmeDtorDLA();
	void *bfmeGoDLA(unsigned char flags);
};

void __stdcall bfmeVecDtorDLA(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLA(void *what);
void bfmeFreeDLA(void *what);

void *BfmeThingDLA::bfmeGoDLA(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLA(this, 0x98, *(int *)base, bfmeDtorCbDLA);
		if (flags & 1)
			bfmeFreeArrDLA(base);
		return base;
	}
	bfmeDtorDLA();
	if (flags & 1)
		bfmeFreeDLA(this);
	return this;
}

extern "C" void bfmeDtorCbDLD(void *what);

class BfmeThingDLD
{
public:
	void bfmeDtorDLD();
	void *bfmeGoDLD(unsigned char flags);
};

void __stdcall bfmeVecDtorDLD(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLD(void *what);
void bfmeFreeDLD(void *what);

void *BfmeThingDLD::bfmeGoDLD(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLD(this, 0x98, *(int *)base, bfmeDtorCbDLD);
		if (flags & 1)
			bfmeFreeArrDLD(base);
		return base;
	}
	bfmeDtorDLD();
	if (flags & 1)
		bfmeFreeDLD(this);
	return this;
}

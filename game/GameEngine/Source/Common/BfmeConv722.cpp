extern "C" void bfmeDtorCbDLE(void *what);

class BfmeThingDLE
{
public:
	void bfmeDtorDLE();
	void *bfmeGoDLE(unsigned char flags);
};

void __stdcall bfmeVecDtorDLE(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLE(void *what);
void bfmeFreeDLE(void *what);

void *BfmeThingDLE::bfmeGoDLE(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLE(this, 0x94, *(int *)base, bfmeDtorCbDLE);
		if (flags & 1)
			bfmeFreeArrDLE(base);
		return base;
	}
	bfmeDtorDLE();
	if (flags & 1)
		bfmeFreeDLE(this);
	return this;
}

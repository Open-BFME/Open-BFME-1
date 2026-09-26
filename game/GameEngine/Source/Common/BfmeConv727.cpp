extern "C" void bfmeDtorCbDLJ(void *what);

class BfmeThingDLJ
{
public:
	void bfmeDtorDLJ();
	void *bfmeGoDLJ(unsigned char flags);
};

void __stdcall bfmeVecDtorDLJ(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLJ(void *what);
void bfmeFreeDLJ(void *what);

void *BfmeThingDLJ::bfmeGoDLJ(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLJ(this, 0x94, *(int *)base, bfmeDtorCbDLJ);
		if (flags & 1)
			bfmeFreeArrDLJ(base);
		return base;
	}
	bfmeDtorDLJ();
	if (flags & 1)
		bfmeFreeDLJ(this);
	return this;
}

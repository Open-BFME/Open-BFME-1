extern "C" void bfmeDtorCbDLH(void *what);

class BfmeThingDLH
{
public:
	void bfmeDtorDLH();
	void *bfmeGoDLH(unsigned char flags);
};

void __stdcall bfmeVecDtorDLH(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLH(void *what);
void bfmeFreeDLH(void *what);

void *BfmeThingDLH::bfmeGoDLH(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLH(this, 0x8c, *(int *)base, bfmeDtorCbDLH);
		if (flags & 1)
			bfmeFreeArrDLH(base);
		return base;
	}
	bfmeDtorDLH();
	if (flags & 1)
		bfmeFreeDLH(this);
	return this;
}

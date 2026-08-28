extern "C" void bfmeDtorCbDLB(void *what);

class BfmeThingDLB
{
public:
	void bfmeDtorDLB();
	void *bfmeGoDLB(unsigned char flags);
};

void __stdcall bfmeVecDtorDLB(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLB(void *what);
void bfmeFreeDLB(void *what);

void *BfmeThingDLB::bfmeGoDLB(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLB(this, 0xd0, *(int *)base, bfmeDtorCbDLB);
		if (flags & 1)
			bfmeFreeArrDLB(base);
		return base;
	}
	bfmeDtorDLB();
	if (flags & 1)
		bfmeFreeDLB(this);
	return this;
}

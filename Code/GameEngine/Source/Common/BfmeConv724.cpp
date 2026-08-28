extern "C" void bfmeDtorCbDLG(void *what);

class BfmeThingDLG
{
public:
	void bfmeDtorDLG();
	void *bfmeGoDLG(unsigned char flags);
};

void __stdcall bfmeVecDtorDLG(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDLG(void *what);
void bfmeFreeDLG(void *what);

void *BfmeThingDLG::bfmeGoDLG(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDLG(this, 0xa0, *(int *)base, bfmeDtorCbDLG);
		if (flags & 1)
			bfmeFreeArrDLG(base);
		return base;
	}
	bfmeDtorDLG();
	if (flags & 1)
		bfmeFreeDLG(this);
	return this;
}

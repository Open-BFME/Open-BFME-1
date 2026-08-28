extern "C" void bfmeDtorCbDMD(void *what);
extern "C" unsigned char bfmeVftDMD[];

class BfmeThingDMD
{
public:
	void *bfmeGoDMD(unsigned char flags);
	void *m_bfmeVft;
};

void __stdcall bfmeVecDtorDMD(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDMD(void *what);
void bfmeFreeDMD(void *what);

void *BfmeThingDMD::bfmeGoDMD(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMD(this, 4, *(int *)base, bfmeDtorCbDMD);
		if (flags & 1)
			bfmeFreeArrDMD(base);
		return base;
	}
	m_bfmeVft = bfmeVftDMD;
	if (flags & 1)
		bfmeFreeDMD(this);
	return this;
}

extern "C" void bfmeDtorCbDME(void *what);
extern "C" unsigned char bfmeVftDME[];

class BfmeThingDME
{
public:
	void *bfmeGoDME(unsigned char flags);
	void *m_bfmeVft;
};

void __stdcall bfmeVecDtorDME(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDME(void *what);
void bfmeFreeDME(void *what);

void *BfmeThingDME::bfmeGoDME(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDME(this, 4, *(int *)base, bfmeDtorCbDME);
		if (flags & 1)
			bfmeFreeArrDME(base);
		return base;
	}
	m_bfmeVft = bfmeVftDME;
	if (flags & 1)
		bfmeFreeDME(this);
	return this;
}

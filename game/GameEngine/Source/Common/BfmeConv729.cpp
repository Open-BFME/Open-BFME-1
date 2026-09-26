extern "C" void bfmeDtorCbDMB(void *what);
extern "C" unsigned char bfmeVftDMB[];

class BfmeThingDMB
{
public:
	void *bfmeGoDMB(unsigned char flags);
	void *m_bfmeVft;
};

void __stdcall bfmeVecDtorDMB(void *base, unsigned int size, int count, void (*dtor)(void *));
void bfmeFreeArrDMB(void *what);
void bfmeFreeDMB(void *what);

void *BfmeThingDMB::bfmeGoDMB(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMB(this, 4, *(int *)base, bfmeDtorCbDMB);
		if (flags & 1)
			bfmeFreeArrDMB(base);
		return base;
	}
	m_bfmeVft = bfmeVftDMB;
	if (flags & 1)
		bfmeFreeDMB(this);
	return this;
}

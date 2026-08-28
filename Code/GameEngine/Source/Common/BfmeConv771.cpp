extern "C" void bfmeDtorCbDSE(void *what);
void __stdcall bfmeVecDtorDSE(void *base, unsigned int size, int count, void (*dtor)(void *));

class BfmeThingDSE
{
public:
	void bfmeGoDSE();
	char m_bfmeHead[8];
};

void BfmeThingDSE::bfmeGoDSE()
{
	bfmeVecDtorDSE((char *)this + 8, 0xc, 4, bfmeDtorCbDSE);
}

class BfmeThingDSF
{
public:
	void bfmeGoDSF();
	char m_bfmeHead[0x60];
};

void BfmeThingDSF::bfmeGoDSF()
{
	bfmeVecDtorDSE((char *)this + 0x60, 0xc, 4, bfmeDtorCbDSE);
}

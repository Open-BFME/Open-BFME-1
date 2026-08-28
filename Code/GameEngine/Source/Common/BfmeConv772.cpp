class BfmeSubDSI
{
public:
	void bfmeCallDSI(void **what);
};

class BfmeThingDSI
{
public:
	void bfmeGoDSI(void *what);
	char m_bfmeHead[0xc];
	BfmeSubDSI m_bfmeSub;
};

void BfmeThingDSI::bfmeGoDSI(void *what)
{
	*(void *volatile *)&what = what;
	m_bfmeSub.bfmeCallDSI(&what);
}

class BfmeThingDSJ
{
public:
	void bfmeGoDSJ(void *what);
	char m_bfmeHead[0x10];
	BfmeSubDSI m_bfmeSub;
};

void BfmeThingDSJ::bfmeGoDSJ(void *what)
{
	*(void *volatile *)&what = what;
	m_bfmeSub.bfmeCallDSI(&what);
}

class BfmeGlobDSV
{
public:
	virtual void bfmeV0();
	virtual void bfmeV1();
	virtual void bfmeV2();
	virtual void bfmeV3();
	virtual void bfmeV4();
	virtual void bfmeRunDSV();
};

extern BfmeGlobDSV *g_bfmeDSV;

class BfmeSubDSV
{
public:
	void bfmeOneDSV();
};

struct BfmeThingDSV
{
	void bfmeGoDSV();
	unsigned char m_bfmeHead[0xc];
	BfmeSubDSV *m_bfmeSub;
};

void BfmeThingDSV::bfmeGoDSV()
{
	m_bfmeSub->bfmeOneDSV();
	g_bfmeDSV->bfmeRunDSV();
}

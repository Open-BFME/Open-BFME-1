struct BfmeSrcBPD
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmePad[3];
	unsigned char m_bfmeRest[4];
};

struct BfmeSubBPD
{
	void bfmeSetBPD(void *what);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBPD
{
public:
	BfmeThingBPD *bfmeGoBPD(BfmeSrcBPD *src);
	unsigned char m_bfmeKind;
	unsigned char m_bfmePad[3];
	BfmeSubBPD m_bfmeSub;
};

BfmeThingBPD *BfmeThingBPD::bfmeGoBPD(BfmeSrcBPD *src)
{
	m_bfmeKind = src->m_bfmeKind;
	m_bfmeSub.bfmeSetBPD(src->m_bfmeRest);
	return this;
}

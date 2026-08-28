extern "C" unsigned char bfmeVftTD[];

struct BfmeSubTD
{
	void bfmeStartTD(void *what);
};

class BfmeThingTD
{
public:
	BfmeThingTD *bfmeInitTD(void *what);
	void *m_bfmeVft;
	BfmeSubTD m_bfmeSub;
};

BfmeThingTD *BfmeThingTD::bfmeInitTD(void *what)
{
	m_bfmeVft = bfmeVftTD;
	m_bfmeSub.bfmeStartTD(what);
	return this;
}

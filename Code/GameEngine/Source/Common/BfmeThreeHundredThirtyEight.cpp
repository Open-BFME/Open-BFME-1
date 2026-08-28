extern "C" unsigned char bfmeVftSJ[];

class BfmeThingSJ
{
public:
	void bfmeBaseSJ(int what);
	BfmeThingSJ *bfmeDropSJ(int what);
	void *m_bfmeVft;
};

BfmeThingSJ *BfmeThingSJ::bfmeDropSJ(int what)
{
	bfmeBaseSJ(0);
	m_bfmeVft = bfmeVftSJ;
	return this;
}

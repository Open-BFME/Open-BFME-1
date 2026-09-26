extern "C" unsigned char bfmeVftSK[];

class BfmeThingSK
{
public:
	void bfmeBaseSK(int what);
	BfmeThingSK *bfmeDropSK();
	void *m_bfmeVft;
};

BfmeThingSK *BfmeThingSK::bfmeDropSK()
{
	bfmeBaseSK(0);
	m_bfmeVft = bfmeVftSK;
	return this;
}

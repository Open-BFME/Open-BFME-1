extern "C" unsigned char bfmeVftSI[];

extern int g_bfmeCountSI;

class BfmeThingSI
{
public:
	void bfmeTailSI();
	void bfmeResetSI();
	void *m_bfmeVft;
};

void BfmeThingSI::bfmeResetSI()
{
	m_bfmeVft = bfmeVftSI;
	g_bfmeCountSI = 0;
	bfmeTailSI();
}

// Open-BFME5 conversions.

extern void *g_bfmeVftSE[];

class BfmeThingSE
{
public:
	BfmeThingSE();
	void bfmeBaseSE();
	void bfmeStartSE();
	void *m_bfme00;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
};

BfmeThingSE::BfmeThingSE()
{
	bfmeBaseSE();
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme60 = 20.0f;
	m_bfme64 = 0;
	m_bfme00 = g_bfmeVftSE;
	bfmeStartSE();
}

// Open-BFME5 conversions.

class BfmeSubSKA
{
public:
	char bfmeTestSKA(int a);
};

class BfmeSinkSKA
{
public:
	void bfmeSendSKA(int tag, int a, int v);
};

class BfmeThingSKA
{
public:
	void bfmeGoSKA(int a, int b);
	char m_bfmePad[4];
	BfmeSinkSKA *m_bfmeSink;
	char m_bfmePad2[0x50];
	BfmeSubSKA *m_bfmeSub;
};

void BfmeThingSKA::bfmeGoSKA(int a, int b)
{
	m_bfmeSink->bfmeSendSKA(0x504c5654, a,
		m_bfmeSub->bfmeTestSKA(b) == 0 ? 0x6e74666e : 0);
}

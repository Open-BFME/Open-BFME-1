// Open-BFME5 conversions.

class BfmeItem964
{
public:
	void bfmeRelease964();				// ILT 0x000024A5
};

class BfmeClear964
{
public:
	void bfmeClear964();

	char m_bfmePad[0x20];
	BfmeItem964 *m_bfmeA;
	BfmeItem964 *m_bfmeB;
	BfmeItem964 *m_bfmeD;
	BfmeItem964 *m_bfmeC;
	char m_bfmePad2[0x25];
	char m_bfmeDone;
};

void BfmeClear964::bfmeClear964()
{
	if (m_bfmeA) {
		m_bfmeA->bfmeRelease964();
		m_bfmeA = 0;
	}
	if (m_bfmeB) {
		m_bfmeB->bfmeRelease964();
		m_bfmeB = 0;
	}
	if (m_bfmeC) {
		m_bfmeC->bfmeRelease964();
		m_bfmeC = 0;
	}
	if (m_bfmeD) {
		m_bfmeD->bfmeRelease964();
		m_bfmeD = 0;
	}
	m_bfmeDone = 0;
}

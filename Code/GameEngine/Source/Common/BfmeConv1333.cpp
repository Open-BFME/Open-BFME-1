// Open-BFME5 conversions.

class BfmeElemUHA
{
public:
	~BfmeElemUHA();
	char m_bfmePad[4];
};

class BfmeThingUHA
{
public:
	void bfmeClearUHA();
	void *m_bfmeVft;
	BfmeElemUHA *m_bfmeArray;
	int m_bfmeCount;
	char m_bfmePad;
	char m_bfmeOwned;
};

void BfmeThingUHA::bfmeClearUHA()
{
	if (m_bfmeArray && m_bfmeOwned) {
		delete [] m_bfmeArray;
		m_bfmeArray = 0;
	}
	m_bfmeOwned = 0;
	m_bfmeCount = 0;
}

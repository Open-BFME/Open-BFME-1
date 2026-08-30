// Open-BFME5 conversions.

struct BfmeV1246
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

class BfmeA1246
{
public:
	void bfmeSet1246(BfmeV1246 v, int a4, int a5, int a6, int a7, int a8);
	char m_bfmePad00[0x6c];
	BfmeV1246 m_bfme6c;
	int m_bfme78;
	int m_bfme7c;
	int m_bfme80;
	int m_bfme84;
	int m_bfme88;
};

void BfmeA1246::bfmeSet1246(BfmeV1246 v, int a4, int a5, int a6, int a7, int a8)
{
	m_bfme6c = v;
	m_bfme78 = a4;
	m_bfme7c = a5;
	m_bfme80 = a6;
	m_bfme88 = a7;
	m_bfme84 = a8;
}

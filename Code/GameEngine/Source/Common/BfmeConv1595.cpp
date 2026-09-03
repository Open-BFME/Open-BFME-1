// Open-BFME5 conversions.

class BfmeStrVSV
{
public:
	BfmeStrVSV() { m_bfme00 = 0; }
	~BfmeStrVSV() { bfmeClearVSV(); }
	void bfmeClearVSV();
	char *m_bfme00;
};

class BfmeOwnVSV
{
public:
	BfmeOwnVSV();
	virtual void bfmeSlot0VSV() = 0;
	BfmeStrVSV m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfme10;
	BfmeStrVSV m_bfme14;
	BfmeStrVSV m_bfme18;
	int m_bfme1c;
};

BfmeOwnVSV::BfmeOwnVSV()
	: m_bfme08(0), m_bfme0c(0), m_bfme10(0), m_bfme1c(0)
{
	m_bfme04.bfmeClearVSV();
}

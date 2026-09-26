// Open-BFME5 conversions.

class BfmeStrVUP
{
public:
	BfmeStrVUP() { m_bfme00 = 0; }
	~BfmeStrVUP() { bfmeClearVUP(); }
	void bfmeClearVUP();
	char *m_bfme00;
};

class BfmeOwnVUP
{
public:
	BfmeOwnVUP();
	virtual void bfmeSlot0VUP();
	BfmeStrVUP m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	char m_bfmePad18[0x50];
	int m_bfme68;
	char m_bfmePad6c[0x50];
	int m_bfmebc;
	char m_bfmePadc0[0x50];
	int m_bfme110;
	char m_bfmePad114[0x50];
	int m_bfme164;
	char m_bfmePad168[0x50];
	BfmeStrVUP m_bfme1b8;
	int m_bfme1bc;
};

BfmeOwnVUP::BfmeOwnVUP()
	: m_bfme08(0), m_bfme0c(1), m_bfme10(2), m_bfme1bc(0)
{
	m_bfme04.bfmeClearVUP();
	m_bfme1b8.bfmeClearVUP();
	m_bfme14 = 0;
	m_bfme68 = 0;
	m_bfmebc = 0;
	m_bfme110 = 0;
	m_bfme164 = 0;
}

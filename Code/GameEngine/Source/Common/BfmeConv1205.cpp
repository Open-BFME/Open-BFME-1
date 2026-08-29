// Open-BFME5 conversions.

class BfmeA1205
{
public:
	void bfmeSet1205(int a1, int a2);
	char m_bfmePad0[0xd8];
	volatile int m_bfmed8;
	volatile int m_bfmedc;
	volatile int m_bfmee0;
	volatile int m_bfmee4;
	volatile int m_bfmee8;
	volatile int m_bfmeec;
	char m_bfmePad1[0x18];
	volatile int m_bfme108;
	char m_bfmePad2[0x40];
	volatile int m_bfme14c;
	volatile int m_bfme150;
	volatile int m_bfme154;
	volatile int m_bfme158;
	volatile int m_bfme15c;
	volatile int m_bfme160;
	volatile int m_bfme164;
	volatile int m_bfme168;
	volatile int m_bfme16c;
	volatile int m_bfme170;
	volatile int m_bfme174;
};

void BfmeA1205::bfmeSet1205(int a1, int a2)
{
	m_bfme154 = a2;
	m_bfme14c = a2;
	m_bfme150 = a1;
	m_bfme158 = a1;
	m_bfme160 = m_bfmed8;
	m_bfme164 = m_bfmedc;
	m_bfme168 = m_bfmee0;
	m_bfme16c = m_bfmee4;
	m_bfme170 = m_bfmee8;
	m_bfme174 = m_bfmeec;
	m_bfme15c = m_bfme108;
}

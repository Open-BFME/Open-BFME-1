class BfmeSubAJK
{
public:
	void bfmeInitJK(int a);

	unsigned char m_bfmeGapJK[12];
};

struct BfmePod16WR
{
	char m_b[16];
};

struct BfmeTagWR
{
};

BfmePod16WR *bfmeCopyWR(BfmePod16WR *first, BfmePod16WR *last,
	BfmePod16WR *result, const BfmeTagWR &, int *);

class BfmeVecWR
{
public:
	BfmePod16WR *begin() { return m_start; }
	BfmePod16WR *end() { return m_finish; }
	unsigned size() const { return (unsigned)(m_finish - m_start); }

	void resize(unsigned n, BfmePod16WR value);
	void resize(unsigned n);
	void fillInsert(BfmePod16WR *pos, unsigned n, const BfmePod16WR &value);

	BfmePod16WR *m_start;
	BfmePod16WR *m_finish;
	BfmePod16WR *m_end;
};

class BfmeBigJK
{
public:
	void bfmeClearJK();

	unsigned char m_bfmeHeadJK[8];
	int m_bfme08JK;
	int m_bfme0cJK;
	unsigned char m_bfmeGap0JK[0x10];
	int m_bfme20JK;
	int m_bfme24JK;
	unsigned char m_bfmeGap1JK[0x64];
	int m_bfme8cJK;
	int m_bfme90JK;
	int m_bfme94JK;
	int m_bfme98JK;
	int m_bfme9cJK;
	unsigned char m_bfmeGap2JK[4];
	int m_bfmeAJK[0x1000];
	int m_bfmeBJK[0x1000];
	BfmeVecWR m_bfmeSubBJK;
	BfmeSubAJK m_bfmeSubAJK;
	int m_bfme80bcJK;
	unsigned char m_bfmeGap3JK[0xa008];
	int m_bfme120c8JK;
	unsigned char m_bfmeGap4JK[4];
	int m_bfme120d0JK;
	unsigned char m_bfmeGap5JK[0xc];
	int m_bfme120e0JK;
	int m_bfme120e4JK;
	int m_bfme120e8JK;
	int m_bfme120ecJK;
};

void BfmeBigJK::bfmeClearJK()
{
	m_bfme08JK = 0;
	m_bfme0cJK = 0;
	m_bfme20JK = 0;
	m_bfme24JK = 0;
	m_bfme120e0JK = 0;
	m_bfme120e4JK = 0;
	m_bfme80bcJK = 0;
	m_bfme120e8JK = 0x81;
	m_bfme120ecJK = 0x81;
	m_bfme8cJK = 0;
	m_bfme90JK = 0;
	m_bfme98JK = 0;
	m_bfme94JK = 0;
	m_bfme120c8JK = 1;
	m_bfme120d0JK = 1;

	m_bfmeSubAJK.bfmeInitJK(1);

	m_bfme9cJK = 0;

	m_bfmeSubBJK.resize(1);

	for (int i = 0; i < 0x1000; i++)
	{
		m_bfmeAJK[i] = 0;
		m_bfmeBJK[i] = 0;
	}
}

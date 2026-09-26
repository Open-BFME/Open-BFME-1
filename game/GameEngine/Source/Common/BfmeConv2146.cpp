class BfmeRefYB
{
public:
	virtual void bfmeDropYB();

	int m_bfmeRefsYB;
};

struct BfmeElemYB
{
	BfmeRefYB *m_bfme00YB;
	int m_bfme04YB;
	int m_bfme08YB;
	int m_bfme0CYB;
	int m_bfme10YB;
	int m_bfme14YB;
	unsigned char m_bfme18YB;
	unsigned char m_bfme19YB;
};

class BfmeHostYB
{
public:
	void bfmeResetYB(int i);

	unsigned char m_bfmeHeadYB[0xdc];
	BfmeElemYB m_bfmeArrYB[16];
};

void BfmeHostYB::bfmeResetYB(int i)
{
	BfmeRefYB *r = m_bfmeArrYB[i].m_bfme00YB;

	if (r != 0)
	{
		if (--r->m_bfmeRefsYB == 0)
			r->bfmeDropYB();

		m_bfmeArrYB[i].m_bfme00YB = 0;
	}

	m_bfmeArrYB[i].m_bfme04YB = 0;
	m_bfmeArrYB[i].m_bfme19YB = 0;
	m_bfmeArrYB[i].m_bfme10YB = 0;
	m_bfmeArrYB[i].m_bfme0CYB = 0;
	m_bfmeArrYB[i].m_bfme08YB = 0;
	m_bfmeArrYB[i].m_bfme18YB = 0;
	m_bfmeArrYB[i].m_bfme14YB = 1;
}

// Open-BFME5 conversions.

class BfmePoolVMP
{
public:
	virtual void bfmeSlot0VMP();
	virtual void bfmeSlot1VMP();
	virtual void bfmeSlot2VMP();
	virtual void bfmeFreeVMP(void *p, int f);
};

BfmePoolVMP *bfmeGetPoolVMP();
void bfmeDeleteVMP(void *p, unsigned n);

struct BfmeBufVMP
{
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
};

class BfmeCtxVMP
{
public:
	void bfmeResetVMP();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBufVMP *m_bfme18;
};

void BfmeCtxVMP::bfmeResetVMP()
{
	BfmeBufVMP *b = m_bfme18;

	if (b != 0)
	{
		bfmeGetPoolVMP()->bfmeFreeVMP(b->m_bfme08, 1);
		b->m_bfme04 = 0;
		b->m_bfme00 = 0;
		b->m_bfme08 = 0;
		bfmeDeleteVMP(b, 0xc);
	}
	m_bfme04 = 0;
	m_bfme00 = 0;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
}

// Open-BFME5 conversions.

extern void *g_bfmeVtaVNF;
extern void *g_bfmeVtcVNF;

struct BfmeVecVNF
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

class BfmeBoxVNF
{
public:
	BfmeBoxVNF *bfmeInitVNF(unsigned w, const BfmeVecVNF *v, int n, unsigned h, char f);
	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
	char m_bfmePad09[3];
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	unsigned m_bfme1c;
};

BfmeBoxVNF *BfmeBoxVNF::bfmeInitVNF(unsigned w, const BfmeVecVNF *v, int n, unsigned h, char f)
{
	m_bfme00 = &g_bfmeVtaVNF;
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
	m_bfme00 = &g_bfmeVtcVNF;
	m_bfme0c = v->m_bfme00;
	m_bfme10 = v->m_bfme04;
	m_bfme14 = v->m_bfme08;
	m_bfme18 = n;
	m_bfme1c = (int)((float)h * 0.03f);
	return this;
}

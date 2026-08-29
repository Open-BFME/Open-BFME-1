// Open-BFME5 conversions.

struct BfmeNode1110
{
	char m_bfmePad[8];
	BfmeNode1110 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
	int m_bfme14;
};

struct BfmeW1110
{
	char m_bfmePad[0x4c];
	BfmeNode1110 *m_bfme4c;
	char m_bfmePad1[0x108];
	int m_bfme158;
};

BfmeNode1110 *__cdecl bfmeNext1110(BfmeNode1110 *p);

int __cdecl bfmeGo1110A(BfmeW1110 *w)
{
	BfmeNode1110 *h = w->m_bfme4c;
	BfmeNode1110 *p = h->m_bfme08;
	int best = 0;
	int val = 0;

	while (p != h) {
		int v = p->m_bfme14;

		if ((unsigned int)v >= (unsigned int)best) {
			val = p->m_bfme10;
			best = v;
		}
		p = bfmeNext1110(p);
		h = w->m_bfme4c;
	}
	if (!best)
		return -1;
	return w->m_bfme158 >= best ? 0 : val;
}

class BfmeR1110
{
public:
	BfmeR1110 *bfmeNextR1110(void);
	char m_bfmePad[8];
	unsigned int m_bfme08;
};

struct BfmeQ1110
{
	char m_bfmePad[0xc];
	unsigned int m_bfme0c;
	char m_bfmePad1[0x264];
	BfmeR1110 *m_bfme274;
};

struct BfmeM1110
{
	char m_bfmePad[8];
	BfmeM1110 *m_bfme08;
	char m_bfmePad1[0xc];
	BfmeQ1110 *m_bfme18;
};

BfmeM1110 *__cdecl bfmeNextM1110(BfmeM1110 *p);

class BfmeV1110
{
public:
	void bfmeGo1110B(void);
	char m_bfmePad[4];
	BfmeM1110 *m_bfme04;
	char m_bfmePad1[8];
	unsigned int m_bfme10;
	unsigned int m_bfme14;
};

void BfmeV1110::bfmeGo1110B(void)
{
	BfmeM1110 *h = m_bfme04;
	BfmeM1110 *p;

	m_bfme14 = 0;
	m_bfme10 = 0;
	p = h->m_bfme08;
	while (p != h) {
		BfmeQ1110 *q = p->m_bfme18;
		unsigned int a = q->m_bfme0c;
		BfmeR1110 *r;

		if (a >= m_bfme10)
			m_bfme10 = a + 1;
		r = q->m_bfme274;
		while (r) {
			unsigned int b = r->m_bfme08;

			if (b >= m_bfme14)
				m_bfme14 = b + 1;
			r = r->bfmeNextR1110();
		}
		p = bfmeNextM1110(p);
		h = m_bfme04;
	}
}

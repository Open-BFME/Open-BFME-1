// Open-BFME5 conversions.

struct BfmeA1112
{
	char m_bfmePad[0x18];
};

struct BfmeB1112
{
	char m_bfmePad[0x18];
};

class BfmeSub1112
{
public:
	char bfmeChk1112(BfmeA1112 *a, BfmeB1112 *b);
};

struct BfmeQ1112
{
	char m_bfmePad[0xc8];
	BfmeSub1112 m_bfmec8;
};

struct BfmeNode1112
{
	char m_bfmePad[8];
	BfmeNode1112 *m_bfme08;
	char m_bfmePad1[4];
	BfmeQ1112 *m_bfme10;
	int m_bfme14;
};

struct BfmeSlot1112
{
	BfmeNode1112 *m_bfmeHead;
	char m_bfmePad[8];
};

BfmeNode1112 *__cdecl bfmeNext1112(BfmeNode1112 *p);

class BfmeV1112
{
public:
	int bfmeGo1112A(BfmeA1112 a, BfmeB1112 b);
	int bfmeGo1112B(BfmeA1112 a, BfmeB1112 b);
	char m_bfmePad[0x144];
	BfmeNode1112 *m_bfme144;
	char m_bfmePad1[8];
	BfmeSlot1112 m_bfme150[0x20];
};

int BfmeV1112::bfmeGo1112A(BfmeA1112 a, BfmeB1112 b)
{
	BfmeNode1112 *h = m_bfme144;
	BfmeNode1112 *p = h->m_bfme08;
	int n = 0;

	while (p != h) {
		BfmeQ1112 *q = p->m_bfme10;
		int w = p->m_bfme14;

		if (q && q->m_bfmec8.bfmeChk1112(&a, &b))
			n += w;
		p = bfmeNext1112(p);
		h = m_bfme144;
	}
	return n;
}

int BfmeV1112::bfmeGo1112B(BfmeA1112 a, BfmeB1112 b)
{
	int n = 0;
	BfmeSlot1112 *s = m_bfme150;
	int i = 0x20;

	do {
		BfmeNode1112 *h = s->m_bfmeHead;
		BfmeNode1112 *p = h->m_bfme08;

		while (p != h) {
			BfmeQ1112 *q = p->m_bfme10;
			int w = p->m_bfme14;

			if (q && q->m_bfmec8.bfmeChk1112(&a, &b))
				n += w;
			p = bfmeNext1112(p);
			h = s->m_bfmeHead;
		}
		s++;
		i--;
	} while (i);
	return n;
}

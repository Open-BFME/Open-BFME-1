// Open-BFME5 conversions.

class BfmeK1113
{
public:
	char bfmeChk1113(int a);
};

struct BfmeL1113
{
	BfmeL1113 *m_bfme00;
	char m_bfmePad[4];
	BfmeK1113 *m_bfme08;
};

struct BfmeNode1113
{
	char m_bfmePad[8];
	BfmeNode1113 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
};

class BfmeB1113
{
public:
	BfmeK1113 *bfmeFind1113(int a);
};

extern BfmeB1113 *g_bfmeB1113;

BfmeNode1113 *__cdecl bfmeNext1113(BfmeNode1113 *p);

class BfmeW1113
{
public:
	char bfmeGo1113A(int a);
	char m_bfmePad[0x30];
	BfmeNode1113 *m_bfme30;
};

char BfmeW1113::bfmeGo1113A(int a)
{
	BfmeL1113 *h1 = *(BfmeL1113 **)((char *)this - 0xac);
	BfmeL1113 *q = h1->m_bfme00;
	BfmeNode1113 *h;
	BfmeNode1113 *p;

	while (q != h1) {
		if (q->m_bfme08->bfmeChk1113(a))
			return 1;
		q = q->m_bfme00;
		h1 = *(BfmeL1113 **)((char *)this - 0xac);
	}
	h = m_bfme30;
	p = h->m_bfme08;
	while (p != h) {
		BfmeK1113 *k = g_bfmeB1113->bfmeFind1113(p->m_bfme10);

		if (k->bfmeChk1113(a))
			return 1;
		p = bfmeNext1113(p);
		h = m_bfme30;
	}
	return 0;
}

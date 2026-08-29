// Open-BFME5 conversions.

class BfmeK1114
{
public:
	char bfmeChk1114(int a);
};

struct BfmeL1114
{
	BfmeL1114 *m_bfme00;
	char m_bfmePad[4];
	BfmeK1114 *m_bfme08;
};

struct BfmeNode1114
{
	char m_bfmePad[8];
	BfmeNode1114 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
};

class BfmeB1114
{
public:
	BfmeK1114 *bfmeFind1114(int a);
};

extern BfmeB1114 *g_bfmeB1114;

BfmeNode1114 *__cdecl bfmeNext1114(BfmeNode1114 *p);

class BfmeW1114
{
public:
	char bfmeGo1114A(int a);
	char m_bfmePad[0x30];
	BfmeNode1114 *m_bfme30;
};

char BfmeW1114::bfmeGo1114A(int a)
{
	BfmeL1114 *h1 = *(BfmeL1114 **)((char *)this - 0xac);
	BfmeL1114 *q = h1->m_bfme00;
	BfmeNode1114 *h;
	BfmeNode1114 *p;

	while (q != h1) {
		if (q->m_bfme08->bfmeChk1114(a))
			return 1;
		q = q->m_bfme00;
		h1 = *(BfmeL1114 **)((char *)this - 0xac);
	}
	h = m_bfme30;
	p = h->m_bfme08;
	while (p != h) {
		BfmeK1114 *k = g_bfmeB1114->bfmeFind1114(p->m_bfme10);

		if (k && k->bfmeChk1114(a))
			return 1;
		p = bfmeNext1114(p);
		h = m_bfme30;
	}
	return 0;
}

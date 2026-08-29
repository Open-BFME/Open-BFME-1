// Open-BFME5 conversions.

struct BfmeE1115
{
	char m_bfmePad[0x18];
	int m_bfme18;
	char m_bfmePad1[4];
	char m_bfme20;
};

struct BfmeL1115
{
	BfmeL1115 *m_bfme00;
	char m_bfmePad[4];
	BfmeE1115 *m_bfme08;
};

struct BfmeNode1115
{
	char m_bfmePad[8];
	BfmeNode1115 *m_bfme08;
	char m_bfmePad1[8];
	BfmeL1115 *m_bfme14;
};

struct BfmeSlot1115
{
	BfmeNode1115 *m_bfmeHead;
	char m_bfmePad[8];
};

struct BfmeArg1115
{
	char m_bfmePad[0x74];
	int m_bfme74;
};

BfmeNode1115 *__cdecl bfmeNext1115(BfmeNode1115 *p);

class BfmeW1115
{
public:
	void bfmeGo1115A(BfmeArg1115 *g);
	void bfmeGo1115B(BfmeArg1115 *g);
	char m_bfmePad[0x5cc];
	BfmeSlot1115 m_bfme5cc[0x20];
};

void BfmeW1115::bfmeGo1115A(BfmeArg1115 *g)
{
	int key = g->m_bfme74;
	BfmeSlot1115 *s = m_bfme5cc;
	int i = 0x20;

	do {
		BfmeNode1115 *h = s->m_bfmeHead;
		BfmeNode1115 *p = h->m_bfme08;

		while (p != h) {
			BfmeL1115 *lh = p->m_bfme14;
			BfmeL1115 *r = lh->m_bfme00;

			while (r != lh) {
				BfmeE1115 *e = r->m_bfme08;

				if (e->m_bfme18 == key)
					e->m_bfme20 = 1;
				r = r->m_bfme00;
				lh = p->m_bfme14;
			}
			p = bfmeNext1115(p);
			h = s->m_bfmeHead;
		}
		s++;
		i--;
	} while (i);
}

void BfmeW1115::bfmeGo1115B(BfmeArg1115 *g)
{
	int key = g->m_bfme74;
	BfmeSlot1115 *s = m_bfme5cc;
	int i = 0x20;

	do {
		BfmeNode1115 *h = s->m_bfmeHead;
		BfmeNode1115 *p = h->m_bfme08;

		while (p != h) {
			BfmeL1115 *lh = p->m_bfme14;
			BfmeL1115 *r = lh->m_bfme00;

			while (r != lh) {
				BfmeE1115 *e = r->m_bfme08;

				if (e->m_bfme18 == key)
					e->m_bfme20 = 0;
				r = r->m_bfme00;
				lh = p->m_bfme14;
			}
			p = bfmeNext1115(p);
			h = s->m_bfmeHead;
		}
		s++;
		i--;
	} while (i);
}


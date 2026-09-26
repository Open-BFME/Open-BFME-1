// Open-BFME5 conversions.

class BfmeK1105
{
public:
	void bfmeDrop1105(void);
};

struct BfmeNode1105
{
	char m_bfmePad[8];
	BfmeNode1105 *m_bfme08;
	char m_bfmePad1[4];
	int m_bfme10;
	BfmeK1105 *m_bfme14;
};

BfmeNode1105 *__cdecl bfmeNext1105(BfmeNode1105 *p);

class BfmeW1105
{
public:
	void bfmeGo1105A(void);
	int *bfmeGo1105C(int n);
	BfmeNode1105 *m_bfme00;
};

void BfmeW1105::bfmeGo1105A(void)
{
	BfmeNode1105 *h = m_bfme00;
	BfmeNode1105 *p = h->m_bfme08;

	while (p != h) {
		if (p->m_bfme14)
			p->m_bfme14->bfmeDrop1105();
		p = bfmeNext1105(p);
		h = m_bfme00;
	}
}

int *BfmeW1105::bfmeGo1105C(int n)
{
	BfmeNode1105 *h = m_bfme00;
	BfmeNode1105 *p = h->m_bfme08;

	while (p != h) {
		if (!n)
			return &p->m_bfme10;
		p = bfmeNext1105(p);
		h = m_bfme00;
		n--;
	}
	return 0;
}

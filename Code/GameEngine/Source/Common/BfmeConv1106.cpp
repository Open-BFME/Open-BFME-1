// Open-BFME5 conversions.

class BfmeK1106
{
public:
	void bfmeDrop1106(void);
};

struct BfmeNode1106
{
	char m_bfmePad[8];
	BfmeNode1106 *m_bfme08;
	char m_bfmePad1[8];
	BfmeK1106 *m_bfme14;
	char m_bfmePad2[0x18];
	int m_bfme30;
	int m_bfme34;
};

BfmeNode1106 *__cdecl bfmeNext1106(BfmeNode1106 *p);

class BfmeW1106
{
public:
	void bfmeGo1106A(void);
	int bfmeGo1106B(void);
	BfmeNode1106 *m_bfme00;
	char m_bfmePad[0x20];
	BfmeNode1106 *m_bfme24;
};

void BfmeW1106::bfmeGo1106A(void)
{
	BfmeNode1106 *h = m_bfme00;
	BfmeNode1106 *p = h->m_bfme08;

	while (p != h) {
		if (p->m_bfme14)
			p->m_bfme14->bfmeDrop1106();
		p = bfmeNext1106(p);
		h = m_bfme00;
	}
}

int BfmeW1106::bfmeGo1106B(void)
{
	BfmeNode1106 *h = m_bfme24;
	BfmeNode1106 *p = h->m_bfme08;
	int n = 0xf;

	while (p != h) {
		if (!p->m_bfme30) {
			int v = p->m_bfme34 + 0xf;

			if (n < v)
				n = v;
		}
		p = bfmeNext1106(p);
	}
	return n;
}

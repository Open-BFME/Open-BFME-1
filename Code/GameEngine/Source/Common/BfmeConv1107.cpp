// Open-BFME5 conversions.

struct BfmeQ1107
{
	char m_bfmePad[0xc];
	int m_bfme0c;
};

struct BfmeNode1107
{
	char m_bfmePad[8];
	BfmeNode1107 *m_bfme08;
	char m_bfmePad1[0xc];
	BfmeQ1107 *m_bfme18;
};

BfmeNode1107 *__cdecl bfmeNext1107(BfmeNode1107 *p);

class BfmeW1107
{
public:
	BfmeQ1107 *bfmeGo1107A(int k);
	char m_bfmePad[0xc];
	BfmeNode1107 *m_bfme0c;
};

BfmeQ1107 *BfmeW1107::bfmeGo1107A(int k)
{
	BfmeNode1107 *h = m_bfme0c;
	BfmeNode1107 *p = h->m_bfme08;

	while (p != h) {
		BfmeQ1107 *q = p->m_bfme18;

		if (q->m_bfme0c == k)
			return q;
		p = bfmeNext1107(p);
		h = m_bfme0c;
	}
	return 0;
}

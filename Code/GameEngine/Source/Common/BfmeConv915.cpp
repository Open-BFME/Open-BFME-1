// Open-BFME5 conversions.

struct BfmeNode915A
{
	BfmeNode915A *m_bfmeNext;
	BfmeNode915A *m_bfmePrev;
	void *m_bfmeKey;
};

void bfmeFree915A(void *p, unsigned int n);

class BfmeThing915A
{
public:
	void bfmeGo915A(void *k);
	char m_bfmePad[0x288];
	BfmeNode915A *m_bfmeList;
};

void BfmeThing915A::bfmeGo915A(void *k)
{
	BfmeNode915A *l = m_bfmeList;
	for (BfmeNode915A *n = l->m_bfmeNext; n != l; n = n->m_bfmeNext) {
		if (k == n->m_bfmeKey) {
			BfmeNode915A *nx = n->m_bfmeNext;
			BfmeNode915A *pv = n->m_bfmePrev;
			pv->m_bfmeNext = nx;
			nx->m_bfmePrev = pv;
			bfmeFree915A(n, 0xc);
			return;
		}
	}
}

class BfmeElem915C
{
public:
	int bfmeTail915C(void *a);
	char m_bfmePad[0x24];
};

class BfmeThing915C
{
public:
	int bfmeGo915C(void *a);
	char m_bfmePad[0x2c4];
	BfmeElem915C *volatile m_bfmeBeg;
	BfmeElem915C *m_bfmeEnd;
};

int BfmeThing915C::bfmeGo915C(void *a)
{
	if (m_bfmeEnd - m_bfmeBeg > 0)
		return m_bfmeBeg->bfmeTail915C(a);
	return 0;
}


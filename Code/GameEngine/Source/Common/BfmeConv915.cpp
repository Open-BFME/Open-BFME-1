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


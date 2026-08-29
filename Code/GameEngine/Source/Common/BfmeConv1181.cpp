// Open-BFME5 conversions.

struct BfmePair1181
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeP1181
{
public:
	bool bfmeGroundOk1181(void *a1, void *a2, void *a3, int a4);
	void bfmeConv1181(void *p, BfmePair1181 *out);
	int bfmeCheck1181(BfmePair1181 *a, BfmePair1181 *b, void *c, BfmePair1181 *d);
};

bool BfmeP1181::bfmeGroundOk1181(void *a1, void *a2, void *a3, int a4)
{
	BfmePair1181 s;
	BfmePair1181 r1;
	BfmePair1181 r2;

	s.m_bfme00 = (int)this;
	s.m_bfme04 = a4;
	bfmeConv1181(a1, &r2);
	bfmeConv1181(a3, &r1);

	return bfmeCheck1181(&r2, &r1, a2, &s) == 0;
}

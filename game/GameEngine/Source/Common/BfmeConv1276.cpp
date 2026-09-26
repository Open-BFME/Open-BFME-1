// Open-BFME5 conversions.

class BfmeQ1276
{
public:
	BfmeQ1276(int a);
	char m_bfmePad00[0x14];
	int m_bfme14;
	int m_bfme18;
};

class BfmeA1276
{
public:
	int bfmeGo1276(int a1, int a2, int a3);
	void bfmeDo1276(int a1, int a2, BfmeQ1276 *q, int a3, int a4);
};

int BfmeA1276::bfmeGo1276(int a1, int a2, int a3)
{
	BfmeQ1276 q(a1);

	bfmeDo1276(a2, a3, &q, 0, 2);
	return q.m_bfme14;
}

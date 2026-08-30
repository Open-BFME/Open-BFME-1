// Open-BFME5 conversions.

class BfmeQ1275
{
public:
	BfmeQ1275();
	char m_bfmePad00[0x14];
	int m_bfme14;
};

class BfmeA1275
{
public:
	int bfmeGo1275(int a1, int a2, int a3, int a4);
	void bfmeDo1275(int a1, int a2, BfmeQ1275 *q, int a3, int a4);
};

int BfmeA1275::bfmeGo1275(int a1, int a2, int a3, int a4)
{
	BfmeQ1275 q;

	bfmeDo1275(a1, a2, &q, a3, a4);
	return q.m_bfme14;
}

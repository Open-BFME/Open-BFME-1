// Open-BFME5 conversions.

extern char g_bfmeStr1279A[];
extern char g_bfmeStr1279B[];

class BfmeQ1279
{
public:
	void bfmeCopy1279(char *s, char *dst, int n);
};

class BfmeA1279
{
public:
	BfmeA1279(BfmeQ1279 *a);
	BfmeQ1279 *m_bfme00;
	char m_bfme04[0x100];
	char m_bfme104[0x100];
};

BfmeA1279::BfmeA1279(BfmeQ1279 *a)
{
	m_bfme00 = a;
	a->bfmeCopy1279(g_bfmeStr1279A, m_bfme04, 0x100);
	m_bfme00->bfmeCopy1279(g_bfmeStr1279B, m_bfme104, 0x100);
}

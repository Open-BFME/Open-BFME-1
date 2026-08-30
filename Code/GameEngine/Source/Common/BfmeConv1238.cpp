// Open-BFME5 conversions.

class BfmeS1238
{
public:
	int bfmeLen1238();
	BfmeS1238 *bfmeAt1238B(int i);
};

class BfmeU1238
{
public:
	BfmeS1238 *bfmeAt1238C(int i);
};

class BfmeT1238
{
public:
	BfmeU1238 *bfmeGet1238();
	int m_bfme00;
};

class BfmeQ1238
{
public:
	char m_bfmePad00[0x10];
	BfmeS1238 *m_bfme10;
	char m_bfmePad14[0x24 - 0x14];
	BfmeT1238 m_bfme24;
};

class BfmeN1238
{
public:
	BfmeS1238 *bfmeAt1238(int i);
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x4c - 0x08];
	BfmeS1238 *m_bfme4c;
	BfmeQ1238 *m_bfme50;
};

BfmeS1238 *BfmeN1238::bfmeAt1238(int i)
{
	unsigned f;
	BfmeS1238 *s;
	BfmeQ1238 *q;
	int n;

	if (i == 0)
		return m_bfme4c;

	f = m_bfme04;
	if ((f & 0x3f) == 0x13 && !((unsigned char)(~(f >> 15)) & 1)) {
		s = 0;
	} else {
		q = m_bfme50;
		if (q == 0 || q == (BfmeQ1238 *)0xbaadf00d)
			s = 0;
		else
			s = q->m_bfme10;
	}

	n = 1;
	if (s)
		n = s->bfmeLen1238() + 1;

	if (i > 0 && i < n)
		return s->bfmeAt1238B(i - 1);

	return m_bfme50->m_bfme24.bfmeGet1238()->bfmeAt1238C(i - n);
}

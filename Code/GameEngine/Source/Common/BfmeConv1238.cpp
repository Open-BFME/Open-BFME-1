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

class Rva008BD1B0Node
{
public:
	int count() const;
};

class BfmeN1238
{
public:
	BfmeS1238 *bfmeAt1238(int i);
	int bfmeSize1237() const;
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x4c - 0x08];
	BfmeS1238 *m_bfme4c;
	BfmeQ1238 *m_bfme50;
};

// ?bfmeSize1237@BfmeN1238@@QBEHXZ
int BfmeN1238::bfmeSize1237() const
{
	BfmeN1238 *that = (BfmeN1238 *)this;
	unsigned flags = that->m_bfme04;
	BfmeS1238 *s;
	BfmeQ1238 *q;
	int n;

	if ((flags & 0x3f) == 0x13 && !((unsigned char)(~(flags >> 15)) & 1))
	{
		s = 0;
	}
	else
	{
		q = that->m_bfme50;
		if (q == 0 || q == (BfmeQ1238 *)0xbaadf00d)
			s = 0;
		else
			s = q->m_bfme10;
	}

	n = 1;
	if (s)
		n = s->bfmeLen1238() + 1;

	flags = that->m_bfme04;
	if ((flags & 0x3f) == 0x0d)
	{
		if (!((unsigned char)(~(flags >> 15)) & 1))
			goto add_count;
	}
	if ((flags & 0x3f) != 0x12)
		return n;
	if (((unsigned char)(~(flags >> 15)) & 1))
		return n;

add_count:
	q = that->m_bfme50;
	if (q != 0)
		n += ((Rva008BD1B0Node *)q->m_bfme24.bfmeGet1238())->count();
	return n;
}

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

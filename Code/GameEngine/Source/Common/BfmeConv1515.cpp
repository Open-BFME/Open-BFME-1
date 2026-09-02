// Open-BFME5 conversions.

class BfmeValVNJ
{
public:
	BfmeValVNJ(const BfmeValVNJ &o);
	int m_bfme00;
};

extern char g_bfmeDefVNJ;

class BfmeThingVNJ
{
public:
	BfmeValVNJ bfmeGetVNJ(int idx);
	char *m_bfme00;
};

BfmeValVNJ BfmeThingVNJ::bfmeGetVNJ(int idx)
{
	volatile int n1 = 0;
	char *t = m_bfme00;

	if (t != 0)
	{
		char *p = t + idx * 8 + 6;

		if (p != 0 && *p == 3)
			return *(const BfmeValVNJ *)(p + 4);
	}
	return *(const BfmeValVNJ *)&g_bfmeDefVNJ;
}

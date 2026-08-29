// Open-BFME5 conversions.

class BfmeD1032;

class BfmeSink1032
{
public:
	void bfmeSend1032(int a, BfmeD1032 *o);
};

class BfmeD1032
{
public:
	void bfmeGo1032D(int a);

	char m_bfmePad[0x120e0];
	BfmeSink1032 *m_bfmeSink;
};

void BfmeD1032::bfmeGo1032D(int a)
{
	if (m_bfmeSink != 0)
		m_bfmeSink->bfmeSend1032(a, this);
}

extern char g_bfmeDefault1032[];
char * __stdcall bfmeFind1032(int a);

char * __stdcall bfmeGo1032E(int a)
{
	char *y = bfmeFind1032(a);

	if (y == 0)
		return g_bfmeDefault1032;

	return y + 0x48;
}


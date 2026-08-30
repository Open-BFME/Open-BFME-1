// Open-BFME5 conversions.

class BfmeE1226
{
public:
	int m_bfme00;
	void *m_bfme04;
};

struct BfmeP1226
{
	int m_bfme00;
	BfmeE1226 **m_bfme04;
};

class BfmeR1226
{
public:
	void bfmeAdd1226(void *a, void *b, int c);
	void bfmeLine1226(char *a);
};

extern BfmeR1226 g_bfmeR1226;
extern char g_bfmeStr1226[];

class BfmeA1226
{
public:
	void bfmeDump1226(void *a, int k);
	int m_bfme00;
	BfmeP1226 *m_bfme04;
};

void BfmeA1226::bfmeDump1226(void *a, int k)
{
	int i;
	BfmeE1226 *e;

	for (i = 0; i < m_bfme04[k].m_bfme00; ++i) {
		e = m_bfme04[k].m_bfme04[i];
		if (e->m_bfme00 == 1) {
			g_bfmeR1226.bfmeAdd1226(e->m_bfme04, a, -1);
			g_bfmeR1226.bfmeLine1226(g_bfmeStr1226);
		}
	}
}

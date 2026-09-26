// Open-BFME5 conversions.

class BfmeE1227
{
public:
	int m_bfme00;
	void *m_bfme04;
};

struct BfmeP1227
{
	int m_bfme00;
	BfmeE1227 **m_bfme04;
};

class BfmeR1227
{
public:
	void bfmeAdd1227(void *a, void *b, void *c);
};

extern BfmeR1227 *g_bfmeR1227;
extern void *g_bfmeTag1227;

class BfmeA1227
{
public:
	void bfmeDump1227(void *a, int k);
	int m_bfme00;
	BfmeP1227 *m_bfme04;
};

void BfmeA1227::bfmeDump1227(void *a, int k)
{
	int i;
	BfmeE1227 *e;

	for (i = 0; i < m_bfme04[k].m_bfme00; ++i) {
		e = m_bfme04[k].m_bfme04[i];
		if (e->m_bfme00 == 1)
			g_bfmeR1227->bfmeAdd1227(&e->m_bfme04, a, g_bfmeTag1227);
	}
}

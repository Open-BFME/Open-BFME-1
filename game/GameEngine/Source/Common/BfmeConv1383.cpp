// Open-BFME5 conversions.

class BfmeMsgVJC
{
public:
	void bfmeSetVJC(const char *k, void *v);
	void bfmeSet3VJC(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

// retail 0x007E8AC0
class Rva007E8AC0 { public: void run(); };

extern void *g_bfmeVJE;

// retail 0x007F1800: FESL search serializer shared by the VJC/VJD/VJE wrappers.
class Rva007E8810Message
{
public:
	void addInt64(const char *key, __int64 value);
};

class Rva007F1800Search
{
public:
	void serialize(Rva007E8810Message *message, int maxRecords, void *queryArg);
};

class BfmeThingVJE
{
public:
	void bfmeGoVJE(BfmeMsgVJC *m, int downloadMin, int downloadMax, int topN, int periodType, int periodsPast, void *b);
};

void BfmeThingVJE::bfmeGoVJE(BfmeMsgVJC *m, int downloadMin, int downloadMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_bfmeVJE;
	((Rva007E8AC0*)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, topN, b);
	if (downloadMin > -1)
		m->bfmeSet3VJC("downloadMin", downloadMin);
	if (downloadMax > -1)
		m->bfmeSet3VJC("downloadMax", downloadMax);
	if (topN > -1)
		m->bfmeSet3VJC("topN", topN);
	if (periodType > -1)
		m->bfmeSet3VJC("periodType", periodType);
	if (periodsPast > -1)
		m->bfmeSet3VJC("periodsPast", periodsPast);
}

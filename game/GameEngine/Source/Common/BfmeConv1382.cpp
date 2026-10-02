// Open-BFME5 conversions.

// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run();
};

class BfmeMsgVJC
{
public:
	void bfmeSetVJC(const char *k, void *v);
	void bfmeSet3VJC(const char *k, int v);
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

extern void *g_bfmeVJC;

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

class BfmeThingVJC
{
public:
	void bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b);
};

void BfmeThingVJC::bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b)
{
	void *g = g_bfmeVJC;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, (int)a, b);
	if (ratingMin > -1)
		m->bfmeSet3VJC("ratingMin", ratingMin);
	if (ratingMax > -1)
		m->bfmeSet3VJC("ratingMax", ratingMax);
	if (downloadMin > -1)
		m->bfmeSet3VJC("downloadMin", downloadMin);
	if (downloadMax > -1)
		m->bfmeSet3VJC("downloadMax", downloadMax);
}

extern void *g_bfmeVJD;

class BfmeThingVJD
{
public:
	void bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b);
};

void BfmeThingVJD::bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_bfmeVJD;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	m->bfmeSetVJC("TXN", g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, topN, b);
	if (ratingMin > -1)
		m->bfmeSet3VJC("ratingMin", ratingMin);
	if (ratingMax > -1)
		m->bfmeSet3VJC("ratingMax", ratingMax);
	if (topN > 0)
		m->bfmeSet3VJC("topN", topN);
	if (periodType > -1)
		m->bfmeSet3VJC("periodType", periodType);
	if (periodsPast > -1)
		m->bfmeSet3VJC("periodsPast", periodsPast);
}

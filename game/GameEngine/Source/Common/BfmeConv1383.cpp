// Open-BFME5 conversions.

class BfmeMsgVJC
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

// retail 0x007E8AC0
class Rva007E8AC0 { public: void run(); };

// Canonical serializer names from the matched 0x007E8A10 and 0x007E88D0
// bodies. The integer writer forwards its second word to Rva007EC5C0's int.
class BfmeC994
{
public:
	void addString(const char *key, const char *value);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *key, void *value);
};

// Retail's transaction-string pointer is zero in the shipped virtual image.
void *g_Va0130A5B8 = 0;

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
	void *g = g_Va0130A5B8;
	((Rva007E8AC0*)m)->run();
	m->m_bfme1c = 0x626c6f62;
	((BfmeC994 *)m)->addString("TXN", (const char *)g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, topN, b);
	if (downloadMin > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("downloadMin", (void *)downloadMin);
	if (downloadMax > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("downloadMax", (void *)downloadMax);
	if (topN > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("topN", (void *)topN);
	if (periodType > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("periodType", (void *)periodType);
	if (periodsPast > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("periodsPast", (void *)periodsPast);
}

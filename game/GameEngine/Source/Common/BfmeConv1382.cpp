// Open-BFME5 conversions.

// retail 0x007E8AC0: ?run@Rva007E8AC0@@QAEXXZ
class Rva007E8AC0
{
public:
	void run();
};

// Matched serializers at 0x007E8A10 and 0x007E88D0; both are
// thiscall RET 8. The integer writer forwards its second word as an int.
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

class BfmeMsgVJC
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

// Shipped zero transaction-string pointer, VA 0x0130A5DC.
void *g_Va0130A5DC = 0;

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
	void *g = g_Va0130A5DC;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	((BfmeC994 *)m)->addString("TXN", (const char *)g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, (int)a, b);
	if (ratingMin > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("ratingMin", (void *)ratingMin);
	if (ratingMax > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("ratingMax", (void *)ratingMax);
	if (downloadMin > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("downloadMin", (void *)downloadMin);
	if (downloadMax > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("downloadMax", (void *)downloadMax);
}

// Shipped zero transaction-string pointer, VA 0x0130A618.
void *g_Va0130A618 = 0;

class BfmeThingVJD
{
public:
	void bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b);
};

void BfmeThingVJD::bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_Va0130A618;
	((Rva007E8AC0 *)m)->run();
	m->m_bfme1c = 0x626c6f62;
	((BfmeC994 *)m)->addString("TXN", (const char *)g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m, topN, b);
	if (ratingMin > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("ratingMin", (void *)ratingMin);
	if (ratingMax > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("ratingMax", (void *)ratingMax);
	if (topN > 0)
		((BfmeThingCIB *)m)->bfmeGoCIB("topN", (void *)topN);
	if (periodType > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("periodType", (void *)periodType);
	if (periodsPast > -1)
		((BfmeThingCIB *)m)->bfmeGoCIB("periodsPast", (void *)periodsPast);
}

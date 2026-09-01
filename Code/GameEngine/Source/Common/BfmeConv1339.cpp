// Open-BFME5 conversions.

extern char g_bfmeEmptyUPA[];

class BfmeStrUPA
{
public:
	void bfmeSetUPA(const char *s);
};

class BfmeThingUPA
{
public:
	BfmeStrUPA *bfmeGoUPA(BfmeStrUPA *out);
	char m_bfmePad[0x18];
	int m_bfmeMode;
	char m_bfmeText[4];
};

BfmeStrUPA *BfmeThingUPA::bfmeGoUPA(BfmeStrUPA *out)
{
	volatile int m_bfmeUnused = 0;
	if (m_bfmeMode == 1)
		out->bfmeSetUPA(m_bfmeText);
	else
		out->bfmeSetUPA(g_bfmeEmptyUPA);
	return out;
}

extern char g_bfmeFmtUPB[];

void *bfmeFindUPB(void *table, void *a);
void bfmeFormatUPB(void *r, char *out, void *c, const char *fmt);

class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *a, char *out, void *c);
	char m_bfmePad[0x10];
	void *m_bfmeTable;
};

char BfmeThingUPB::bfmeGoUPB(void *a, char *out, void *c)
{
	void *r = bfmeFindUPB(m_bfmeTable, a);
	if (!r) {
		*out = 0;
		return 0;
	}
	bfmeFormatUPB(r, out, c, g_bfmeFmtUPB);
	return 1;
}

struct BfmeValueUPC
{
	int m_bfmeType;
	char m_bfmePad[4];
	void *m_bfmeValue;
};

struct BfmeStateUPC
{
	BfmeValueUPC *m_bfmeTop;
	char m_bfmePad[4];
	BfmeValueUPC *m_bfmeLimit;
};

void *bfmeNewTableUPC(BfmeStateUPC *L, int a, int b);
void bfmeGrowUPC(BfmeStateUPC *L, int n);

void bfmeGoUPC(BfmeStateUPC *L, int n)
{
	L->m_bfmeTop->m_bfmeValue = bfmeNewTableUPC(L, 0, n);
	L->m_bfmeTop->m_bfmeType = 4;
	if (L->m_bfmeTop == L->m_bfmeLimit)
		bfmeGrowUPC(L, 1);
	L->m_bfmeTop = (BfmeValueUPC *)((char *)L->m_bfmeTop + 0x10);
}

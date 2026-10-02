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

// The pinned empty-string literal (symbols.csv ?g_Rva0107301CEmptyString@@3QBDB,
// RVA 0x00C7301C); the census alias ?g_bfmeFmtUPB@@3PADA was a placeholder for
// it.  g_bfmeEmptyUPA is a different datum and keeps its own name.
extern const char g_Rva0107301CEmptyString[];

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
	bfmeFormatUPB(r, out, c, g_Rva0107301CEmptyString);
	return 1;
}

// bfmeGoUPC (0x00990780) is Lua's sized lua_newtable: game/Libraries/Source/Lua/lapi.c.

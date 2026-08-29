// Open-BFME5 conversions.

struct BfmeSubFHH;

class BfmeResFHH
{
public:
	void bfmeUseFHH(void *a, void *b);
};

class BfmeGlobFHH
{
public:
	BfmeResFHH *bfmeLookFHH(BfmeSubFHH *s);
};

extern BfmeGlobFHH *g_bfmeObjFHH;

struct BfmeStr917F
{
	char m_bfmePad[4];
	unsigned short m_bfmeLen;
};

struct BfmeSubFHH
{
	BfmeStr917F *m_bfmeStr;
};

struct BfmeArg917F
{
	char m_bfmePad[0x14];
	BfmeSubFHH m_bfmeSub;
};

void bfmeGo917F(BfmeArg917F *a, void *b, void *c)
{
	BfmeStr917F *s = a->m_bfmeSub.m_bfmeStr;
	BfmeSubFHH *k = &a->m_bfmeSub;
	if (!s)
		return;
	if (s->m_bfmeLen == 0)
		return;
	BfmeResFHH *r = g_bfmeObjFHH->bfmeLookFHH(k);
	if (!r)
		return;
	r->bfmeUseFHH(b, c);
}

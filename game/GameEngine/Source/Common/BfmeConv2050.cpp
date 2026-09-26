class BfmeVecFN
{
public:
	unsigned char m_bfmeHeadFN[4];
};

class BfmeBufFN
{
public:
	void bfmeAppendFN(const char *s);

	unsigned char m_bfmeHeadFN[8];
};

class BfmeOwnerFN
{
public:
	int bfmeFindFN(BfmeVecFN *v, const char *name);

	unsigned char m_bfmeHeadFN[0x2b8];
	BfmeVecFN m_bfmeVecFN;
};

class BfmeHostFP
{
public:
	int bfmeAddFP(const char *name, const char *text);

	void *m_bfmeVfFN;
	BfmeOwnerFN *m_bfmeOwnerFN;
	unsigned char m_bfmeGapFN[0x18];
	BfmeBufFN *m_bfmeBufsFN;
	int m_bfmeCountFN;
};

int BfmeHostFP::bfmeAddFP(const char *name, const char *text)
{
	int idx = m_bfmeOwnerFN->bfmeFindFN(&m_bfmeOwnerFN->m_bfmeVecFN, name);

	if (idx == -1)
		return -106;

	BfmeBufFN *b = idx >= m_bfmeCountFN ? 0 : &m_bfmeBufsFN[idx];

	b->bfmeAppendFN(text);

	return 0;
}

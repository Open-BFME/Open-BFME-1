class BfmeVecFN
{
public:
	unsigned char m_bfmeHeadFN[4];
};

// jabba util.cpp container, defined out of line at 0x008002C0
// (game/GameEngine/Source/GameNetwork/Y2FeslBufferAndChain.cpp).
class Rva00800290Buffer
{
public:
	void append(const char *s);

	unsigned char m_bfmeHeadFN[8];
};

class BfmeOwnerFN
{
public:
	int bfmeFindFN(BfmeVecFN *v, const char *name);

	unsigned char m_bfmeHeadFN[0x2b0];
	BfmeVecFN m_bfmeVecFN;
};

class BfmeHostFO
{
public:
	int bfmeAddFO(const char *name, const char *text);

	void *m_bfmeVfFN;
	BfmeOwnerFN *m_bfmeOwnerFN;
	unsigned char m_bfmeGapFN[0x10];
	Rva00800290Buffer *m_bfmeBufsFN;
	int m_bfmeCountFN;
};

int BfmeHostFO::bfmeAddFO(const char *name, const char *text)
{
	int idx = m_bfmeOwnerFN->bfmeFindFN(&m_bfmeOwnerFN->m_bfmeVecFN, name);

	if (idx == -1)
		return -106;

	Rva00800290Buffer *b = idx >= m_bfmeCountFN ? 0 : &m_bfmeBufsFN[idx];

	b->append(text);

	return 0;
}

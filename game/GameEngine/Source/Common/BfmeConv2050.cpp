// The host key vector retail passes by pointer to
// ?rva007F76F0@Rva00802240Host@@QAEHPAURva007F76F0Vector@@PBD@Z (defined in
// game/GameEngine/Source/GameNetwork/Rva007F76F0FeslKeyIndex.cpp). Only the
// address is used here, so the local payload width is irrelevant to the call.
struct Rva007F76F0Vector
{
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

// The host half is Rva00802240Host: the retail body at 0x007F76F0 is its
// member lookup, and this file's host prefix reaches the key vector at the
// same offset the matched host layout uses.
class Rva00802240Host
{
public:
	int rva007F76F0(Rva007F76F0Vector *v, const char *name);

	unsigned char m_bfmeHeadFN[0x2b8];
	Rva007F76F0Vector m_bfmeVecFN;
};

class BfmeHostFP
{
public:
	int bfmeAddFP(const char *name, const char *text);

	void *m_bfmeVfFN;
	Rva00802240Host *m_bfmeOwnerFN;
	unsigned char m_bfmeGapFN[0x18];
	Rva00800290Buffer *m_bfmeBufsFN;
	int m_bfmeCountFN;
};

int BfmeHostFP::bfmeAddFP(const char *name, const char *text)
{
	int idx = m_bfmeOwnerFN->rva007F76F0(&m_bfmeOwnerFN->m_bfmeVecFN, name);

	if (idx == -1)
		return -106;

	Rva00800290Buffer *b = idx >= m_bfmeCountFN ? 0 : &m_bfmeBufsFN[idx];

	b->append(text);

	return 0;
}

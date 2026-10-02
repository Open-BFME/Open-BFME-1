// Open-BFME5 conversions: push onto a global list, then drop a shared string.

class Rva0089E1E0
{
public:
	unsigned char cmp(int n);

	unsigned short *m_bfmeData;
};

struct Bfme5FreeTable
{
	void (__cdecl *m_bfmeF0)(void *);
	void (__cdecl *m_bfmeF1)(void *);
};

// The allocator-pair pointer and intrusive-list head have one definition each.
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU only bumps its leading unsigned short, so it views the block through
// that member and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
static inline unsigned short *bfme5SharedEmptyRef()
{
	return (unsigned short *)&g_rva012D5298Empty;
}

class Bfme5AttachNodeA
{
public:
	void bfmeAttach(void);

	int m_bfme00;
	int m_bfme04;
	Rva0089E1E0 m_bfmeStr;
	Bfme5AttachNodeA *m_bfmeNext;
};

void Bfme5AttachNodeA::bfmeAttach(void)
{
	m_bfmeNext = (Bfme5AttachNodeA *)g_rva01338478NodeHead;
	g_rva01338478NodeHead = (Rva008C3B60Node *)this;

	if (m_bfmeStr.cmp(0x21)) {
		unsigned short *h = m_bfmeStr.m_bfmeData;

		if (--*h == 0)
			((Bfme5FreeTable *)g_rva01337A30AllocPair)->m_bfmeF1(h);

		m_bfmeStr.m_bfmeData = bfme5SharedEmptyRef();
		++*bfme5SharedEmptyRef();
	}
}

class Bfme5AttachNodeB
{
public:
	void bfmeAttach(void);

	int m_bfme00;
	int m_bfme04;
	Rva0089E1E0 m_bfmeStr;
	Bfme5AttachNodeB *m_bfmeNext;
};

void Bfme5AttachNodeB::bfmeAttach(void)
{
	m_bfmeNext = (Bfme5AttachNodeB *)g_rva01338478NodeHead;
	g_rva01338478NodeHead = (Rva008C3B60Node *)this;

	if (m_bfmeStr.cmp(0x21)) {
		unsigned short *h = m_bfmeStr.m_bfmeData;

		if (--*h == 0)
			((Bfme5FreeTable *)g_rva01337A30AllocPair)->m_bfmeF1(h);

		m_bfmeStr.m_bfmeData = bfme5SharedEmptyRef();
		++*bfme5SharedEmptyRef();
	}
}

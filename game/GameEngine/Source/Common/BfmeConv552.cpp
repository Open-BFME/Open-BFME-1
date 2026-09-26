struct BfmePayloadBXE
{
	void bfmeDtorBXE();
};

struct BfmeNodeBXE
{
	BfmeNodeBXE *m_bfmeNext;
	BfmeNodeBXE *m_bfmePrev;
	BfmePayloadBXE m_bfmePayload;
};

struct BfmeListBXE
{
	BfmeNodeBXE *m_bfmeFirst;
};

class BfmeThingBXE
{
public:
	void bfmeGoBXE();
	BfmeListBXE *m_bfmeList;
};

void bfmeFreeBXE(void *what, unsigned int size);

void BfmeThingBXE::bfmeGoBXE()
{
	BfmeNodeBXE *node = m_bfmeList->m_bfmeFirst;
	BfmeNodeBXE *next = node->m_bfmeNext;
	BfmeNodeBXE *prev = node->m_bfmePrev;
	prev->m_bfmeNext = next;
	next->m_bfmePrev = prev;
	node->m_bfmePayload.bfmeDtorBXE();
	bfmeFreeBXE(node, 0x24);
}

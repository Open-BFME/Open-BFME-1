struct BfmePayloadBXD
{
	void bfmeDtorBXD();
};

struct BfmeNodeBXD
{
	BfmeNodeBXD *m_bfmeNext;
	BfmeNodeBXD *m_bfmePrev;
	BfmePayloadBXD m_bfmePayload;
};

struct BfmeListBXD
{
	BfmeNodeBXD *m_bfmeFirst;
};

class BfmeThingBXD
{
public:
	void bfmeGoBXD();
	BfmeListBXD *m_bfmeList;
};

void bfmeFreeBXD(void *what, unsigned int size);

void BfmeThingBXD::bfmeGoBXD()
{
	BfmeNodeBXD *node = m_bfmeList->m_bfmeFirst;
	BfmeNodeBXD *next = node->m_bfmeNext;
	BfmeNodeBXD *prev = node->m_bfmePrev;
	prev->m_bfmeNext = next;
	next->m_bfmePrev = prev;
	node->m_bfmePayload.bfmeDtorBXD();
	bfmeFreeBXD(node, 0x20);
}

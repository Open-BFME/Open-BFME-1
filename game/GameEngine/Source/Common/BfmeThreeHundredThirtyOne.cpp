struct BfmeNodeSC
{
	unsigned char m_bfmeHead[4];
	unsigned short m_bfmeTag;
};

struct BfmeKeySC
{
	BfmeNodeSC *m_bfmeNode;
};

struct BfmeSlotSC
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

class BfmeMapSC
{
public:
	BfmeSlotSC *bfmeFindSC(BfmeKeySC *key);
	BfmeSlotSC *m_bfmeFirst;
};

class BfmeThingSC
{
public:
	void * bfmeLookSC(BfmeKeySC *key);
	unsigned char m_bfmeHead[0x334];
	BfmeMapSC m_bfmeMap;
};

void * BfmeThingSC::bfmeLookSC(BfmeKeySC *key)
{
	BfmeNodeSC *node = key->m_bfmeNode;
	if (node == 0)
		return 0;
	if (node->m_bfmeTag == 0)
		return 0;
	BfmeSlotSC *at = m_bfmeMap.bfmeFindSC(key);
	if (at == m_bfmeMap.m_bfmeFirst)
		return 0;
	return at->m_bfmeWhat;
}

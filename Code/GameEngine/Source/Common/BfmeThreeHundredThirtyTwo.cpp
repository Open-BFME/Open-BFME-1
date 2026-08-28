struct BfmeNodeSD
{
	unsigned char m_bfmeHead[4];
	unsigned short m_bfmeTag;
};

struct BfmeKeySD
{
	BfmeNodeSD *m_bfmeNode;
};

struct BfmeSlotSD
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

class BfmeMapSD
{
public:
	BfmeSlotSD *bfmeFindSD(BfmeKeySD *key);
	BfmeSlotSD *m_bfmeFirst;
};

class BfmeThingSD
{
public:
	void ** bfmeLookSD(BfmeKeySD *key);
	unsigned char m_bfmeHead[0x328];
	BfmeMapSD m_bfmeMap;
};

void ** BfmeThingSD::bfmeLookSD(BfmeKeySD *key)
{
	BfmeNodeSD *node = key->m_bfmeNode;
	if (node == 0)
		return 0;
	if (node->m_bfmeTag == 0)
		return 0;
	BfmeSlotSD *at = m_bfmeMap.bfmeFindSD(key);
	if (at == m_bfmeMap.m_bfmeFirst)
		return 0;
	return &at->m_bfmeWhat;
}

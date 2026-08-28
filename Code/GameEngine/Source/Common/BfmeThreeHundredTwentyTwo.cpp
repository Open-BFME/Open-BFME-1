class BfmeSlotRT
{
public:
	void bfmeUseRT();
};

class BfmeMapRT
{
public:
	void *bfmeFindRT(void *key);
	BfmeSlotRT *bfmeAtRT(void *key, void *what);
	void *m_bfmeEnd;
};

class BfmeThingRT
{
public:
	void bfmeSetRT(void *key, void *what);
	unsigned char m_bfmeHead[0x20];
	BfmeMapRT m_bfmeMap;
};

void BfmeThingRT::bfmeSetRT(void *key, void *what)
{
	if (m_bfmeMap.bfmeFindRT(key) != m_bfmeMap.m_bfmeEnd)
		m_bfmeMap.bfmeAtRT(key, what)->bfmeUseRT();
}

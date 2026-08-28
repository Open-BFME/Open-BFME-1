void __cdecl bfmeFreeEXB(void *p, unsigned int n);

struct BfmeNodeEXB
{
	BfmeNodeEXB *m_bfmeNext;
	BfmeNodeEXB *m_bfmePrev;
};

struct BfmeThingEXBa
{
	void bfmeGoEXBa();
	unsigned char m_bfmeHead[0xc];
	BfmeNodeEXB *m_bfmeHead2;
};

void BfmeThingEXBa::bfmeGoEXBa()
{
	BfmeNodeEXB *head = m_bfmeHead2;
	BfmeNodeEXB *n = head->m_bfmeNext;
	while (n != head)
	{
		BfmeNodeEXB *p = n;
		n = n->m_bfmeNext;
		bfmeFreeEXB(p, 0x10);
		head = m_bfmeHead2;
	}
	m_bfmeHead2->m_bfmeNext = m_bfmeHead2;
	m_bfmeHead2->m_bfmePrev = m_bfmeHead2;
}

struct BfmeThingEXBb
{
	void bfmeGoEXBb();
	unsigned char m_bfmeHead[0x2c];
	BfmeNodeEXB *m_bfmeHead2;
};

void BfmeThingEXBb::bfmeGoEXBb()
{
	BfmeNodeEXB *head = m_bfmeHead2;
	BfmeNodeEXB *n = head->m_bfmeNext;
	while (n != head)
	{
		BfmeNodeEXB *p = n;
		n = n->m_bfmeNext;
		bfmeFreeEXB(p, 0xc);
		head = m_bfmeHead2;
	}
	m_bfmeHead2->m_bfmeNext = m_bfmeHead2;
	m_bfmeHead2->m_bfmePrev = m_bfmeHead2;
}

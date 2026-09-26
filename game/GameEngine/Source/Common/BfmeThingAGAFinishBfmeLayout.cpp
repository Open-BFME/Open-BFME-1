// BFME layout reconstruction of BfmeThingAGA::bfmeFinishAGA.  This method
// drains the auxiliary list at +0x18 through the owning subobject at -0x20.

class BfmeFinishNodeAGA
{
public:
	BfmeFinishNodeAGA *m_bfmeNext;
	unsigned char m_bfmeGap[4];
	void *m_bfmeItem;
};

class BfmeFinishDispatcherAGA
{
public:
	void step(void *item, void *what);
};

class BfmeThingAGA
{
public:
	unsigned char m_bfmeHead[0x18];
	BfmeFinishNodeAGA *m_bfmeList;

	void bfmeFinishAGA(void *what);
};

void BfmeThingAGA::bfmeFinishAGA(void *what)
{
	BfmeFinishNodeAGA *node = m_bfmeList->m_bfmeNext;
	while (node != m_bfmeList)
	{
		BfmeFinishDispatcherAGA *dispatcher =
			reinterpret_cast<BfmeFinishDispatcherAGA *>(
				reinterpret_cast<unsigned char *>(this) - 0x20);
		dispatcher->step(node->m_bfmeItem, what);
		node = m_bfmeList->m_bfmeNext;
	}
}

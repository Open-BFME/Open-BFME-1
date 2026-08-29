// Open-BFME5 conversions.

class BfmeItem1008
{
public:
	virtual void bfmeVI01008();
	virtual void bfmeVI11008();
	virtual void bfmeVI21008();
	virtual void bfmeVI31008();
	virtual void bfmeVI41008();
	virtual void bfmeVI51008();
	virtual void bfmeVI61008();
	virtual void bfmeVI71008();
	virtual void bfmeVI81008();
	virtual void bfmeVI91008();
	virtual void bfmeVI101008();
	virtual void bfmeVI111008();
	virtual void bfmeVI121008();
	virtual void bfmeVI131008();
	virtual void bfmeVI141008();
	virtual void bfmeVI151008();
	virtual void bfmeVI161008();
	virtual void bfmeVI171008();
	virtual void bfmeDoA1008();
	virtual void bfmeVI191008();
	virtual void bfmeVI201008();
	virtual void bfmeVI211008();
	virtual void bfmeVI221008();
	virtual void bfmeDoB1008(void *a);
};

struct BfmeNode1008
{
	BfmeNode1008 *m_bfmeNext;
	BfmeNode1008 *m_bfmePrev;
	BfmeItem1008 *m_bfmeItem;
};

class BfmeP1008
{
public:
	void bfmeGoAP1008();
	void bfmeGoBP1008(void *a);

	void bfmeFinishAP1008();
	void bfmeFinishBP1008(void *a);

	char m_bfmePad[0xc4];
	BfmeNode1008 *m_bfmeList;
};

void BfmeP1008::bfmeGoAP1008()
{
	for (BfmeNode1008 *n = m_bfmeList; n != m_bfmeList->m_bfmeNext; n = n->m_bfmePrev)
		n->m_bfmePrev->m_bfmeItem->bfmeDoA1008();

	bfmeFinishAP1008();
}

void BfmeP1008::bfmeGoBP1008(void *a)
{
	for (BfmeNode1008 *n = m_bfmeList; n != m_bfmeList->m_bfmeNext; n = n->m_bfmePrev)
		n->m_bfmePrev->m_bfmeItem->bfmeDoB1008(a);

	bfmeFinishBP1008(a);
}

class BfmeQ1008
{
public:
	void bfmeGoAQ1008();
	void bfmeGoBQ1008(void *a);

	void bfmeFinishAQ1008();
	void bfmeFinishBQ1008(void *a);

	char m_bfmePad[0xcc];
	BfmeNode1008 *m_bfmeList;
};

void BfmeQ1008::bfmeGoAQ1008()
{
	for (BfmeNode1008 *n = m_bfmeList; n != m_bfmeList->m_bfmeNext; n = n->m_bfmePrev)
		n->m_bfmePrev->m_bfmeItem->bfmeDoA1008();

	bfmeFinishAQ1008();
}

void BfmeQ1008::bfmeGoBQ1008(void *a)
{
	for (BfmeNode1008 *n = m_bfmeList; n != m_bfmeList->m_bfmeNext; n = n->m_bfmePrev)
		n->m_bfmePrev->m_bfmeItem->bfmeDoB1008(a);

	bfmeFinishBQ1008(a);
}

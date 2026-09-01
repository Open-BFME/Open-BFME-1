// Open-BFME5 conversions.

class BfmeBlockVKO
{
public:
	bool bfmeCmpVKO(const BfmeBlockVKO &o);
	int m_bfmeArr[10];
};

class BfmeXVKO
{
public:
	char m_bfmePad[0x250];
	BfmeBlockVKO m_bfme250;
};

class BfmeAVKO
{
public:
	virtual void bfmeA00VKO();
	virtual void bfmeA04VKO();
	virtual void bfmeA08VKO();
	virtual void bfmeA0CVKO();
	virtual void bfmeA10VKO();
	virtual void bfmeA14VKO();
	virtual void bfmeA18VKO();
	virtual void bfmeA1CVKO();
	virtual void bfmeA20VKO();
	virtual void bfmeA24VKO();
	virtual class BfmeXVKO *bfmeA28VKO();
};

class BfmeThingVKO
{
public:
	virtual void bfmeV00VKO();
	virtual void bfmeV04VKO();
	virtual void bfmeV08VKO();
	virtual void bfmeV0CVKO();
	virtual void bfmeV10VKO();
	virtual void bfmeV14VKO();
	virtual void bfmeV18VKO();
	virtual void bfmeV1CVKO();
	virtual void bfmeV20VKO();
	virtual void bfmeV24VKO();
	virtual void bfmeV28VKO();
	virtual void bfmeV2CVKO();
	virtual void bfmeV30VKO();
	virtual void bfmeV34VKO();
	virtual void bfmeV38VKO();
	virtual void bfmeV3CVKO();
	virtual void bfmeV40VKO();
	virtual void bfmeV44VKO();
	void bfmeGoVKO();
	char m_bfmePad04[4];
	BfmeAVKO *m_bfme08;
	char m_bfmePad0c[0x74];
	BfmeBlockVKO m_bfme80;
};

void BfmeThingVKO::bfmeGoVKO()
{
	BfmeXVKO *p = m_bfme08->bfmeA28VKO();
	if (p)
	{
		BfmeBlockVKO tmp = p->m_bfme250;
		if (tmp.bfmeCmpVKO(m_bfme80))
		{
			bfmeV44VKO();
			m_bfme80 = tmp;
		}
	}
}

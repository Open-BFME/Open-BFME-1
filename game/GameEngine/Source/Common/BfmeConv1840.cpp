struct BfmeMarkXD
{
	unsigned char m_bfmeOneXD;
	unsigned char m_bfmeTwoXD;
};

struct BfmeTailXD
{
	unsigned char m_bfmeBytesXD[4];
};

class BfmeItemXD
{
public:
	virtual void bfmeV0XD();
	virtual void bfmeV1XD();
	virtual void bfmeV2XD();
	virtual bool bfmeReadyXD();
	virtual void bfmeV4XD();
	virtual void bfmeV5XD();
	virtual void bfmeV6XD();
	virtual void bfmeV7XD();
	virtual void bfmeV8XD();
	virtual void bfmeV9XD();
	virtual void bfmeMarkedXD(BfmeMarkXD *mark);
	virtual void bfmeV11XD();
	virtual void bfmeUseXD(void *thing);
	virtual void bfmeV13XD();
	virtual void bfmeV14XD();
	virtual void bfmeV15XD();
	virtual void bfmeV16XD();
	virtual void bfmeV17XD();
	virtual void bfmeV18XD();
	virtual void bfmeV19XD();
	virtual void bfmeV20XD();
	virtual void bfmeV21XD();
	virtual void bfmeV22XD();
	virtual void bfmeV23XD();
	virtual void bfmeV24XD();
	virtual void bfmeV25XD();
	virtual void bfmeV26XD();
	virtual void bfmeV27XD();
	virtual void bfmeV28XD();
	virtual void bfmeFinishXD(BfmeTailXD *tail);
};

class BfmeHolderXD
{
public:
	void bfmeQueryXD(BfmeItemXD *item);

	unsigned char m_bfmeHeadXD[0x40];
	void *m_bfmeThingXD;
	void *m_bfmeSpareXD;
	BfmeTailXD m_bfmeTailXD;
};

void BfmeHolderXD::bfmeQueryXD(BfmeItemXD *item)
{
	BfmeMarkXD mark;

	mark.m_bfmeOneXD = 1;
	mark.m_bfmeTwoXD = 2;
	item->bfmeMarkedXD(&mark);

	if (item->bfmeReadyXD() && m_bfmeThingXD)
		item->bfmeUseXD(m_bfmeThingXD);

	if (mark.m_bfmeTwoXD >= 2)
		item->bfmeFinishXD(&m_bfmeTailXD);
}

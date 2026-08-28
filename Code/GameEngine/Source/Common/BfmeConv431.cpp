struct BfmeFlagsAXB
{
	unsigned char m_bfmeOne;
	unsigned char m_bfmeTwo;
};

class BfmeSrcAXB
{
public:
	virtual void bfmeSpareAXBa0();
	virtual void bfmeSpareAXBa1();
	virtual void bfmeSpareAXBa2();
	virtual bool bfmeAskAXB();
	virtual void bfmeSpareAXBb0();
	virtual void bfmeSpareAXBb1();
	virtual void bfmeSpareAXBb2();
	virtual void bfmeSpareAXBb3();
	virtual void bfmeSpareAXBb4();
	virtual void bfmeSpareAXBb5();
	virtual void bfmeFillAXB(BfmeFlagsAXB *out);
};

class BfmeThingAXB
{
public:
	void bfmeSendAXB(BfmeSrcAXB *src, BfmeFlagsAXB *flags);
	void bfmeGoAXB(BfmeSrcAXB *src);
};

void BfmeThingAXB::bfmeGoAXB(BfmeSrcAXB *src)
{
	if (src->bfmeAskAXB())
		return;
	BfmeFlagsAXB flags;
	flags.m_bfmeOne = 1;
	flags.m_bfmeTwo = 2;
	src->bfmeFillAXB(&flags);
	bfmeSendAXB(src, &flags);
}

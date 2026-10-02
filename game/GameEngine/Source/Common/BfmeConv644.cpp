class BfmeOutCTA
{
public:
	virtual void bfmeSpareCTA_0();
	virtual void bfmeSpareCTA_1();
	virtual void bfmeSpareCTA_2();
	virtual void bfmeSpareCTA_3();
	virtual void bfmeSpareCTA_4();
	virtual void bfmeBeginCTA();
	virtual void bfmeSpareCTA_6();
	virtual void bfmeSpareCTA_7();
	virtual void bfmeSendCTA(int code);
	virtual void bfmeSpareCTA_9();
	virtual void bfmeSpareCTA_10();
	virtual void bfmeSpareCTA_11();
	virtual void bfmeSpareCTA_12();
	virtual void bfmeSpareCTA_13();
	virtual void bfmeWriteVCTA(void *what);
	void bfmeWriteNCTA(void *what);
};

class ObjectIsMobileBody;

class BfmeThingCTA
{
public:
	unsigned char m_bfmeHead[8];
	ObjectIsMobileBody *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCTA *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCTA(void *one, void *two);
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

void BfmeThingCTA::bfmeGoCTA(void *one, void *two)
{
	if (m_bfmeSub->isMobile())
	{
		m_bfmeOut->bfmeBeginCTA();
		m_bfmeOut->bfmeWriteNCTA(one);
		m_bfmeVal = two;
		m_bfmeOut->bfmeSendCTA(0x2f);
	}
}

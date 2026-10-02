class BfmeOutCSF
{
public:
	virtual void bfmeSpareCSF_0();
	virtual void bfmeSpareCSF_1();
	virtual void bfmeSpareCSF_2();
	virtual void bfmeSpareCSF_3();
	virtual void bfmeSpareCSF_4();
	virtual void bfmeBeginCSF();
	virtual void bfmeSpareCSF_6();
	virtual void bfmeSpareCSF_7();
	virtual void bfmeSendCSF(int code);
	virtual void bfmeSpareCSF_9();
	virtual void bfmeSpareCSF_10();
	virtual void bfmeSpareCSF_11();
	virtual void bfmeSpareCSF_12();
	virtual void bfmeSpareCSF_13();
	virtual void bfmeWriteVCSF(void *what);
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;
};

class BfmeThingCSF
{
public:
	unsigned char m_bfmeHead[8];
	ObjectIsMobileBody *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	BfmeOutCSF *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
	void bfmeGoCSF(void *one, void *two);
};

void BfmeThingCSF::bfmeGoCSF(void *one, void *two)
{
	if (m_bfmeSub->isMobile())
	{
		m_bfmeOut->bfmeBeginCSF();
		m_bfmeOut->bfmeWriteVCSF(one);
		m_bfmeVal = two;
		m_bfmeOut->bfmeSendCSF(0x39);
	}
}

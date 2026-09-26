class BfmeSinkAEB
{
public:
	virtual void bfmeSpareAEB0();
	virtual void bfmeAttachAEB(void *link);
};

class BfmeInnerAEB
{
public:
	virtual void bfmeFireAEB();
};

class BfmeThingAEB;

class BfmeOwnerAEB
{
public:
	void bfmeAddAEB(BfmeThingAEB *who);
	unsigned char m_bfmeHead[4];
	BfmeInnerAEB m_bfmeInner;
	unsigned char m_bfmeGap[0x14];
	BfmeSinkAEB *m_bfmeSink;
};

class BfmeThingAEB
{
public:
	void bfmeStartAEB(BfmeOwnerAEB *owner);
	unsigned char m_bfmeHead[4];
	unsigned char m_bfmeLink[4];
	bool m_bfmeDone;
	bool m_bfmeOn;
	unsigned char m_bfmePad[6];
	BfmeOwnerAEB *m_bfmeOwner;
	BfmeSinkAEB *m_bfmeSink;
};

void BfmeThingAEB::bfmeStartAEB(BfmeOwnerAEB *owner)
{
	m_bfmeOn = true;
	m_bfmeOwner = owner;
	m_bfmeSink = owner->m_bfmeSink;
	owner->bfmeAddAEB(this);
	m_bfmeSink->bfmeAttachAEB(m_bfmeLink);
	if (!m_bfmeDone)
		m_bfmeOwner->m_bfmeInner.bfmeFireAEB();
}

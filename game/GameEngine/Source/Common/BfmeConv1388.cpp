// Open-BFME5 conversions.

class BfmeMsgVJK
{
public:
	void bfmeInitVJK(char *buf, int n);
	void bfmeDoneVJK();
	char m_bfmePad[0x34];
};

class BfmeAVJK
{
public:
	virtual void bfmeA00VJK() throw();
	virtual void bfmeA04VJK() throw();
	virtual void bfmeA08VJK() throw();
	virtual void bfmeA0CVJK() throw();
	virtual void bfmeA10VJK() throw();
	virtual void bfmeA14VJK() throw();
	virtual void bfmeA18VJK() throw();
	virtual void bfmeA1CVJK() throw();
	virtual void bfmeA20VJK() throw();
	virtual void bfmeA24VJK() throw();
	virtual void bfmeA28VJK() throw();
	virtual void bfmeA2CVJK() throw();
	virtual void bfmeA30VJK() throw();
	virtual void bfmeA34VJK() throw();
	virtual void bfmeA38VJK() throw();
	virtual void bfmeA3CVJK() throw();
	virtual void bfmeA40VJK() throw();
	virtual void bfmeA44VJK() throw();
	virtual void bfmeA48VJK() throw();
	virtual void bfmeA4CVJK() throw();
	virtual void bfmeA50VJK(class BfmeMsgVJK *m) throw();
};

class BfmeBVJK
{
public:
	virtual void bfmeB00VJK() throw();
	virtual void bfmeB04VJK() throw();
	virtual void bfmeB08VJK(class BfmeMsgVJK *m, int x, int y, int z) throw();
};

class BfmeThingVJK
{
public:
	void bfmeGoVJK(int unused);
	char m_bfmePad00[0x10];
	BfmeAVJK *m_bfme10;
	BfmeBVJK *m_bfme14;
	char m_bfmePad18[0x2c4];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJK::bfmeGoVJK(int unused)
{
	BfmeMsgVJK msg;
	msg.bfmeInitVJK(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA50VJK(&msg);
	m_bfme14->bfmeB08VJK(&msg, 0, 0, m_bfme6dc);
	msg.bfmeDoneVJK();
}

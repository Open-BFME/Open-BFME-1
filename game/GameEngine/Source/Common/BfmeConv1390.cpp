// Open-BFME5 conversions.

class BfmeMsgVJM
{
public:
	void bfmeInitVJM(char *buf, int n);
	void bfmeDoneVJM();
	char m_bfmePad[0x34];
};

class BfmeAVJM
{
public:
	virtual void bfmeA00VJM();
	virtual void bfmeA04VJM();
	virtual void bfmeA08VJM();
	virtual void bfmeA0CVJM();
	virtual void bfmeA10VJM();
	virtual void bfmeA14VJM();
	virtual void bfmeA18VJM();
	virtual void bfmeA1CVJM();
	virtual void bfmeA20VJM(class BfmeMsgVJM *m, int a, int b);
};

class BfmeBVJM
{
public:
	virtual void bfmeB00VJM();
	virtual void bfmeB04VJM();
	virtual void bfmeB08VJM(class BfmeMsgVJM *m, void (__stdcall *cb)(), void *o, int n);
};

void __stdcall bfmeCbVJM();

class BfmeThingVJM
{
public:
	void bfmeGoVJM(int a, int b);
	char m_bfmePad00[0x10];
	BfmeAVJM *m_bfme10;
	BfmeBVJM *m_bfme14;
	char m_bfmePad18[0x2c4];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJM::bfmeGoVJM(int a, int b)
{
	BfmeMsgVJM msg;
	msg.bfmeInitVJM(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA20VJM(&msg, a, b);
	m_bfme14->bfmeB08VJM(&msg, bfmeCbVJM, this, m_bfme6dc);
	msg.bfmeDoneVJM();
}

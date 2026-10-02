// Open-BFME5 conversions.

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is this body's "done the message" step.
class Gen_007e86c0
{
public:
	void m();
};

// The "message" is built by the buffer constructor retail calls at 0x007E8850
// (ledger: ??0BfmeC994@@QAE@PADH@Z), so this is that class, not a local type
// with an extra init member.
class BfmeC994
{
public:
	BfmeC994(char *buf, int n);
	char m_bfmePad[0x34];
};

class BfmeAVJN
{
public:
	virtual void bfmeA00VJN();
	virtual void bfmeA04VJN();
	virtual void bfmeA08VJN();
	virtual void bfmeA0CVJN();
	virtual void bfmeA10VJN();
	virtual void bfmeA14VJN();
	virtual void bfmeA18VJN();
	virtual void bfmeA1CVJN();
	virtual void bfmeA20VJN();
	virtual void bfmeA24VJN();
	virtual void bfmeA28VJN();
	virtual void bfmeA2CVJN();
	virtual void bfmeA30VJN();
	virtual void bfmeA34VJN();
	virtual void bfmeA38VJN();
	virtual void bfmeA3CVJN();
	virtual void bfmeA40VJN();
	virtual void bfmeA44VJN();
	virtual void bfmeA48VJN();
	virtual void bfmeA4CVJN();
	virtual void bfmeA50VJN();
	virtual void bfmeA54VJN(class BfmeC994 *m, int a, int b, int c, int d, int e);
};

class BfmeBVJN
{
public:
	virtual void bfmeB00VJN();
	virtual void bfmeB04VJN();
	virtual void bfmeB08VJN(class BfmeC994 *m, int z, void *o, int n);
};

class BfmeThingVJN
{
public:
	void bfmeGoVJN(int a, int b, int c, int d, int e);
	char m_bfmePad00[0x10];
	BfmeAVJN *m_bfme10;
	BfmeBVJN *m_bfme14;
	char m_bfmePad18[0x2c4];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJN::bfmeGoVJN(int a, int b, int c, int d, int e)
{
	BfmeC994 msg(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA54VJN(&msg, a, b, c, d, e);
	m_bfme14->bfmeB08VJN(&msg, 0, this, m_bfme6dc);
	((Gen_007e86c0 *)&msg)->m();
}

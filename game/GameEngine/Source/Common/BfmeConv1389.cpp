// cl: /GS
// Open-BFME5 conversions.

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is this body's "done the message" step.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeMsgVJL
{
public:
	void bfmeInitVJL(char *buf, int n);
	char m_bfmePad[0x34];
};

class BfmeXVJL
{
public:
	virtual void bfmeB00VJL();
	virtual void bfmeB04VJL();
	virtual void bfmeB08VJL();
	virtual void bfmeB0CVJL(class BfmeMsgVJL *m);
};

class BfmeThingVJL
{
public:
	virtual void bfmeA00VJL();
	virtual class BfmeXVJL *bfmeA04VJL();
	virtual void bfmeA08VJL();
	virtual void bfmeA0CVJL();
	virtual void bfmeA10VJL();
	virtual void bfmeA14VJL();
	virtual void bfmeA18VJL(class BfmeMsgVJL *m);
	void bfmeGoVJL(int unused);
};

void BfmeThingVJL::bfmeGoVJL(int unused)
{
	char buf[0x20];
	BfmeMsgVJL msg;
	msg.bfmeInitVJL(buf, 0x20);
	bfmeA18VJL(&msg);
	bfmeA04VJL()->bfmeB0CVJL(&msg);
	((Gen_007e86c0 *)&msg)->m();
}

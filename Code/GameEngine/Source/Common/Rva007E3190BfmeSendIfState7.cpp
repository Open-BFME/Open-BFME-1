// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// BfmeB996 state-7 packet send recovered at retail 0x007E3190.

class BfmePkt996
{
public:
	char m_pad[4];
	int m_size;
};

class BfmeDev996S7
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual int send(BfmePkt996 *pkt, int size);
};

class BfmeB996
{
public:
	bool sendIfState7(BfmePkt996 *pkt);

private:
	char m_bfmePad[4];
	BfmeDev996S7 *m_bfmeDev;
	int m_bfmeKind;
};

bool BfmeB996::sendIfState7(BfmePkt996 *pkt)
{
	if (m_bfmeKind == 7)
	{
		BfmeDev996S7 *dev = m_bfmeDev;
		BfmePkt996 *p = pkt;
		int want = p->m_size;
		int got = dev->send(p, want);
		return got == p->m_size;
	}
	return false;
}

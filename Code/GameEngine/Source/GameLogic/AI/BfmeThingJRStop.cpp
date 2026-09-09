class BfmeXJR
{
public:
	virtual void bfmeVt0JR();
	virtual void bfmeVt1JR();
	virtual void bfmeVt2JR();
	virtual void bfmeVt3JR();
	virtual void bfmeVt4JR();
	virtual void bfmeStopXJR(int a);
};

class BfmeThingJR
{
public:
	int bfmeStopJR();
	int bfmeFinishJR(int a);

	unsigned char m_bfmeHeadJR[0x18];
	int m_bfme18JR;
	BfmeXJR *m_bfme1cJR;
	int m_bfme20JR;
	int m_bfme24JR;
	int m_bfme28JR;
	int m_bfme2cJR;
	int m_bfme30JR;
	int m_bfme34JR;
	int m_bfme38JR;
	int m_bfme3cJR;
	char m_bfme40JR;
	char m_bfme41JR;
	unsigned char m_bfmePadJR[2];
};

int BfmeThingJR::bfmeStopJR()
{
	if (m_bfme40JR != 0)
		return -2;

	if (m_bfme41JR == 0)
		return -2;

	BfmeXJR *x = m_bfme1cJR;

	if (x != 0)
		x->bfmeStopXJR(1);

	m_bfme1cJR = 0;
	m_bfme20JR = 0;
	m_bfme24JR = 0;
	m_bfme28JR = 0;
	m_bfme2cJR = 0;
	m_bfme30JR = 0;
	m_bfme34JR = 0;
	m_bfme38JR = 0;
	m_bfme3cJR = 0;

	return bfmeFinishJR(m_bfme18JR);
}

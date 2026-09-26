class BfmeAESR;

class BfmeSubESR
{
public:
	char bfmeReadyESR();
};

class BfmeOwnerESR
{
public:
	void bfmeDetachESR(BfmeSubESR *sub);
};

class BfmeTargetESR
{
public:
	virtual void bfmeSlot00ESR();
	virtual void bfmeSlot01ESR();
	virtual void bfmeSlot02ESR();
	virtual void bfmeSlot03ESR();
	virtual void bfmeSlot04ESR();
	virtual void bfmeSlot05ESR();
	virtual void bfmeSlot06ESR();
	virtual void bfmeSlot07ESR();
	virtual void bfmeSlot08ESR(int mode);
	virtual void bfmeSlot09ESR();
	virtual void bfmeSlot10ESR();
	virtual void bfmeSlot11ESR();
	virtual void bfmeSlot12ESR();
	virtual void bfmeSlot13ESR();
	virtual void bfmeSlot14ESR(BfmeAESR *a);
};

class BfmeHostESR
{
public:
	void bfmeStartESR(BfmeAESR *a, int value);

	unsigned char m_bfmeHeadESR[8];
	BfmeSubESR *m_bfme08ESR;
	unsigned char m_bfmeMid1ESR[0x24];
	BfmeTargetESR *m_bfme30ESR;
	unsigned char m_bfmeMid2ESR[0x14];
	int m_bfme48ESR;
	unsigned char m_bfmeMid3ESR[0x120];
	int m_bfme16cESR;
	unsigned char m_bfmeMid4ESR[0x5c];
	BfmeOwnerESR *m_bfme1ccESR;
	unsigned char m_bfmeMid5ESR[0x155];
	char m_bfme325ESR;
	char m_bfme326ESR;
	unsigned char m_bfmeMid6ESR[4];
	char m_bfme32bESR;
};

void BfmeHostESR::bfmeStartESR(BfmeAESR *a, int value)
{
	if (m_bfme32bESR != 0)
		return;

	if (!m_bfme08ESR->bfmeReadyESR())
		return;

	if (m_bfme1ccESR != 0)
		m_bfme1ccESR->bfmeDetachESR(m_bfme08ESR);

	m_bfme30ESR->bfmeSlot05ESR();
	m_bfme30ESR->bfmeSlot14ESR(a);

	m_bfme16cESR = 0;
	m_bfme325ESR = 0;
	m_bfme326ESR = 0;
	m_bfme48ESR = value;

	m_bfme30ESR->bfmeSlot08ESR(0x3f);
}

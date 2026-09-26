class BfmeResBT;

class BfmeResBT
{
public:
	int m_bfmeValBT;
};

class BfmeOwnerBT
{
public:
	virtual ~BfmeOwnerBT();
	virtual void bfmeSlot01BT();
	virtual void bfmeSlot02BT();
	virtual void bfmeSlot03BT();
	virtual void bfmeSlot04BT();
	virtual void bfmeSlot05BT();
	virtual void bfmeSlot06BT();
	virtual void bfmeSlot07BT();
	virtual void bfmeSlot08BT();
	virtual BfmeResBT *bfmeSecondBT(int *out);
	virtual BfmeResBT *bfmeFirstBT(int *out);
};

class BfmeSinkBT
{
public:
	virtual void bfmeSlot00SK();
	virtual void bfmeSlot01SK();
	virtual void bfmeSlot02SK();
	virtual void bfmeSlot03SK();
	virtual void bfmeSlot04SK();
	virtual void bfmeSlot05SK();
	virtual void bfmeSlot06SK();
	virtual void bfmeSlot07SK();
	virtual void bfmeSlot08SK();
	virtual void bfmeSlot09SK();
	virtual void bfmeSlot10SK();
	virtual void bfmeSlot11SK();
	virtual void bfmeSlot12SK();
	virtual void bfmeSlot13SK();
	virtual void bfmeDoneBT(int mode);
};

class BfmeHostBT
{
public:
	void bfmeCloseBT(void *unused);
	void bfmeReportBT(int first, int second);

	unsigned char m_bfmeHeadBT[0x1c];
	BfmeSinkBT *m_bfmeSinkBT;
	unsigned char m_bfmePadBT[0x2b8];
	BfmeOwnerBT *m_bfmeOwnerBT;
};

void BfmeHostBT::bfmeCloseBT(void *unused)
{
	int second;
	int first;

	BfmeResBT *r1 = m_bfmeOwnerBT->bfmeFirstBT(&first);
	BfmeResBT *r2 = m_bfmeOwnerBT->bfmeSecondBT(&second);

	bfmeReportBT(r2->m_bfmeValBT, r1->m_bfmeValBT);

	delete m_bfmeOwnerBT;
	m_bfmeOwnerBT = 0;

	m_bfmeSinkBT->bfmeDoneBT(0);
}

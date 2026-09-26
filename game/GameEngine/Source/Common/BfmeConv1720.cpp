class BfmeFirstGM
{
public:
	unsigned char m_bfmeFirstDataGM[4];
};

class BfmeBaseGM
{
public:
	unsigned char m_bfmeBaseDataGM[4];
};

class BfmeDerivedGM : public BfmeFirstGM, public BfmeBaseGM
{
public:
	void bfmeSetGM(void *value);
};

class BfmeSinkGM
{
public:
	virtual void bfmeSlot0GM(void);
	virtual void bfmeTakeGM(BfmeBaseGM *base);
};

class BfmeOwnerGM
{
public:
	void bfmeFlushGM(void);

	unsigned char m_bfmeHeadGM[9];
	char m_bfmeDirtyGM;
	unsigned char m_bfmeMidGM[6];
	BfmeDerivedGM *m_bfmeDerivedGM;
	BfmeSinkGM *m_bfmeSinkGM;
};

void BfmeOwnerGM::bfmeFlushGM(void)
{
	if (m_bfmeDirtyGM == 0)
		return;

	m_bfmeDerivedGM->bfmeSetGM(m_bfmeSinkGM);
	m_bfmeSinkGM->bfmeTakeGM(m_bfmeDerivedGM);

	m_bfmeDirtyGM = 0;
}
